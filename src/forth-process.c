#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "forth.h"
#include "forth-actions.h"
#include "forth-primitives.h"
#include "forth-process.h"
#include "mem.h"


//TODO: table look up if this is too slow
int classify_char(char c)
{
    if (c=='-') return FORTH_CHAR_MINUS; 
    else if (c=='0') return FORTH_CHAR_0; 
    else if (strchr("123456789",c)) return FORTH_CHAR_1_9;
    else if (strchr("abcdef",c)) return FORTH_CHAR_A_F;
    else if (strchr("ABCDEF",c)) return FORTH_CHAR_A_F;
    else if (c=='x') return FORTH_CHAR_x;
    else if (strchr("ghijklmnopqrstuvwyz",c)) return FORTH_CHAR_G_Z;
    else if (strchr("GHIJKLMNOPQRSTUVWYZ",c)) return FORTH_CHAR_G_Z;
    return FORTH_CHAR_OTHER;
}

int classify_word(const char *word)
{
    int text_type=FORTH_PARSE_NONE;
    while(*word)
    {
        int char_class=classify_char(*word);
        switch(text_type)
        {
            case FORTH_PARSE_NONE:
                if (char_class==FORTH_CHAR_MINUS) text_type=FORTH_PARSE_MINUS;
                else if (char_class==FORTH_CHAR_0) text_type=FORTH_PARSE_0;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_PARSE_NUMBER;
                else if (char_class==FORTH_CHAR_A_F) text_type=FORTH_PARSE_OTHER;
                else if (char_class==FORTH_CHAR_G_Z) text_type=FORTH_PARSE_OTHER;
                else if (char_class==FORTH_CHAR_x) text_type=FORTH_PARSE_OTHER;
                else if (char_class==FORTH_CHAR_OTHER) text_type=FORTH_PARSE_OTHER;
                break;
            case FORTH_PARSE_NUMBER:
                if (char_class==FORTH_CHAR_0) text_type=FORTH_PARSE_NUMBER;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_PARSE_NUMBER;
                else text_type=FORTH_PARSE_OTHER;
                break;
            case FORTH_PARSE_HEX: 
                if (char_class==FORTH_CHAR_0) text_type=FORTH_PARSE_HEX;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_PARSE_HEX;
                else if (char_class==FORTH_CHAR_A_F) text_type=FORTH_PARSE_HEX;
                else text_type=FORTH_PARSE_OTHER;
                break;
            case FORTH_PARSE_MINUS:
                if (char_class==FORTH_CHAR_0) text_type=FORTH_PARSE_0;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_PARSE_NUMBER;
                else text_type=FORTH_PARSE_OTHER;
                break;
            case FORTH_PARSE_0:        
                if (char_class==FORTH_CHAR_x) text_type=FORTH_PARSE_0x;
                else text_type=FORTH_PARSE_OTHER;
                break;
            case FORTH_PARSE_0x:
                if (char_class==FORTH_CHAR_0) text_type=FORTH_PARSE_HEX;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_PARSE_HEX;
                else if (char_class==FORTH_CHAR_A_F) text_type=FORTH_PARSE_HEX;
                else text_type=FORTH_PARSE_OTHER;
                break;
            case FORTH_PARSE_OTHER:       
                //No changes - always stays same type
                break;
        }
        word++;
    }

    switch (text_type)
    {
        case FORTH_PARSE_NUMBER:
        case FORTH_PARSE_0:
            return FORTH_TYPE_NUMBER;
        case FORTH_PARSE_HEX:
            return FORTH_TYPE_HEX;
        case FORTH_PARSE_NONE:
            return FORTH_TYPE_NONE;
        case FORTH_PARSE_OTHER:
        case FORTH_PARSE_MINUS:
        case FORTH_PARSE_0x:
            return FORTH_TYPE_OTHER;
        default:
            //Should not be possible but just in case
            return FORTH_TYPE_NONE;
    }
}

int find_primitive(const char *word)
{
    int word_len=strlen(word);
    for (int i=0;i<forth_primitives_len;i++)
    {
        if (forth_primitives[i].len==word_len)
        {
            if (!strcasecmp(forth_primitives[i].name,word)) return i;
        }
    }
    return FORTH_PRIM_NOT_FOUND;
}

struct ForthWordHeader *find_secondary(const char *word,struct ForthWordIDsInfo *word_IDs)
{
    struct ForthWordHeader *secondary=(struct ForthWordHeader *)word_IDs->data;
    while(1)
    {
        if (secondary->header_size==0)
        {
            //Zero-length header indicates end of list - done searching
            return NULL;
        }
        else if (!strcasecmp(word,secondary->name))
        {
            //Word found - return pointer to header
            return secondary;
        }
        else
        {
            //No match - advance to next header and keep searching
            secondary=(struct ForthWordHeader *)((uint8_t *)secondary+secondary->header_size);
        }
    }
}

int classify_other(const char *word,int *primitive_ID,struct ForthWordHeader **secondary_ptr,
                            struct ForthWordIDsInfo *word_IDs)
{
    //Default return value in case word is primitive
    *secondary_ptr=NULL;

    //Word is primitive?
    *primitive_ID=find_primitive(word);
    if (*primitive_ID!=FORTH_PRIM_NOT_FOUND) return FORTH_TYPE_PRIMITIVE;

    //Word is secondary?
    *secondary_ptr=find_secondary(word,word_IDs);
    if (*secondary_ptr!=NULL) return FORTH_TYPE_SECONDARY;
    
    //Word not primitve or secondary - not found
    return FORTH_TYPE_NOT_FOUND;
}

uint32_t next_word(struct ConsoleInfo *console,uint32_t *start)
{
    enum ForthParse
    {
        FORTH_PARSE_NONE,
        FORTH_PARSE_WORD
    };

    int parse_state=FORTH_PARSE_NONE;
    uint32_t len=0;
    for (uint32_t i=*start;i<console->input.len;i++)
    {
        char new_char=console->input.text[i].character;
        if (parse_state==FORTH_PARSE_NONE)
        {
            if (new_char!=' ')
            {
                *start=i;
                len=1;
                parse_state=FORTH_PARSE_WORD;
            }
        }
        else if (parse_state==FORTH_PARSE_WORD)
        {
            if (new_char!=' ') len++;
            else return len;
        }

        if (i==console->input.len-1) return len;
    }

    //No more words to process
    return 0;
}

uint32_t next_word_source(const char *source,uint32_t *start)
{
    enum ForthParse
    {
        FORTH_PARSE_NONE,
        FORTH_PARSE_WORD
    };

    int parse_state=FORTH_PARSE_NONE;
    uint32_t len=0;
    uint32_t index=*start;
    while (source[index])
    {
        char new_char=source[index];
        if (parse_state==FORTH_PARSE_NONE)
        {
            if (new_char!=' ')
            {
                *start=index;
                len=1;
                parse_state=FORTH_PARSE_WORD;
            }
        }
        else if (parse_state==FORTH_PARSE_WORD)
        {
            if (new_char!=' ') len++;
            else return len;
        }
        index++;
    }
    return len;
}

int32_t int32_text(const char *word_buffer)
{
    int32_t num=0;
    bool negative=false;
    if (*word_buffer=='-')
    {
        negative=true;
        word_buffer++;
    }
    while (*word_buffer)
    {
        num*=10;
        num+=*word_buffer-'0';
        word_buffer++;
    }
    if (negative) num*=-1;

    return num;
}

int32_t hex32_text(const char *word_buffer)
{
    int32_t num=0;
    bool negative=false;
    if (*word_buffer=='-')
    {
        negative=true;
        word_buffer++;
    }
    
    //Skip over 0x prefix
    word_buffer+=2;

    while (*word_buffer)
    {
        num*=0x10;
        if ((*word_buffer>='0')&&(*word_buffer<='9'))
            num+=*word_buffer-'0';
        else if ((*word_buffer>='a')&&(*word_buffer<='f'))
            num+=*word_buffer-'a'+10;
        else if ((*word_buffer>='A')&&(*word_buffer<='F'))
            num+=*word_buffer-'A'+10;
        word_buffer++;
    }
    if (negative) num*=-1;

    return num;
}

int expand_definitions(uint32_t size,struct ForthDefinitionsInfo *definitions,struct ForthWordIDsInfo **word_IDs,
                                struct ForthControlElement **control_stack,uint8_t *heap_ptr)
{
    if (definitions->bytes_left<size)
    {
        //Not enough memory left in dictionary - expand memory
        int result=expand_object(FORTH_MEM_DEFINITIONS,FORTH_ID_DEFINITIONS,heap_ptr);
        if (result!=ERROR_NONE)
        {
            //Error while allocating memory
            if (result==ERROR_OUT_OF_MEMORY)
                return FORTH_ERROR_OUT_OF_MEMORY;
            else
            {
                //Some other type of allocation error like alignment
                return FORTH_ERROR_MEMORY_OTHER;
            }
        }

        //Update count of bytes left
        definitions->bytes_left+=FORTH_MEM_DEFINITIONS;

        //Update pointers since shifted by expand_object above
        *control_stack=(struct ForthControlElement *)object_address(FORTH_ID_CONTROL_STACK,heap_ptr);
        *word_IDs=(struct ForthWordIDsInfo*)object_address(FORTH_ID_WORD_IDS,heap_ptr);
    }
    return FORTH_ERROR_NONE;
}

//Function pointer here should be 32 bit on calculator so write_dict_u32 would work but adding this for testing on x86.
int write_definition_primitive(void (*word)(struct ForthEngine *engine),struct ForthDefinitionsInfo *definitions,
                                        struct ForthWordIDsInfo **word_IDs,struct ForthControlElement **control_stack,
                                        uint8_t *heap_ptr)
{
    //Expand definitions memory if necessary
    int result=expand_definitions(sizeof(word),definitions,word_IDs,control_stack,heap_ptr);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Write value to definitions - memcpy to avoid casting object pointer to function pointer
    memcpy(definitions->data+definitions->index,&word,sizeof(word));

    //Update counts in definitions memory
    definitions->index+=sizeof(word);
    definitions->bytes_left-=sizeof(word);

    return FORTH_ERROR_NONE;
}

int write_definition_i32(int32_t value,struct ForthDefinitionsInfo *definitions,struct ForthWordIDsInfo **word_IDs,
                                struct ForthControlElement **control_stack,uint8_t *heap_ptr)
{

    //Expand definitions memory if necessary
    int result=expand_definitions(sizeof(value),definitions,word_IDs,control_stack,heap_ptr);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Write value to definitions - memcpy to avoid casting object pointer to function pointer
    memcpy(definitions->data+definitions->index,&value,sizeof(value));

    //Update counts in definitions memory
    definitions->index+=sizeof(value);
    definitions->bytes_left-=sizeof(value);

    return FORTH_ERROR_NONE;
}

int write_definition_u32(uint32_t value,struct ForthDefinitionsInfo *definitions,struct ForthWordIDsInfo **word_IDs,
                                struct ForthControlElement **control_stack,uint8_t *heap_ptr)
{
    //Expand definitions memory if necessary
    int result=expand_definitions(sizeof(value),definitions,word_IDs,control_stack,heap_ptr);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Write value to definitions - memcpy to avoid casting object pointer to function pointer
    memcpy(definitions->data+definitions->index,&value,sizeof(value));

    //Update counts in definitions memory
    definitions->index+=sizeof(value);
    definitions->bytes_left-=sizeof(value);

    return FORTH_ERROR_NONE;
}

int execute_secondary(struct ForthEngine *engine,struct ForthWordHeader *word,struct ForthWordIDsInfo *word_IDs,
                                struct ForthDefinitionsInfo *definitions)
{
    //Prepare engine to run secondary
    forth_engine_pre_exec(engine);
    engine->executing=true;
    engine->address=word->address;
    engine->word_headers=word_IDs->data;
    engine->word_bodies=definitions->data;

    //Mark end of R-stack so interpreter can stop executing when it returns from top-level word
    forth_rstack_push(0,FORTH_RSTACK_DONE,engine->word_index,engine);
    
    //Execute primitives
    while(engine->executing)
    {
        (*engine->address)(engine);
        engine->address++;
    }
    
    //Flag error if any
    if (engine->error!=FORTH_ENGINE_ERROR_NONE) return FORTH_ERROR_ENGINE;
    else return FORTH_ERROR_NONE;
    
}

int process_source(struct ForthEngine *engine,const char *source,const char **error_word,
                            struct ForthDefinitionsInfo *definitions,struct ForthWordIDsInfo *word_IDs,
                            struct ForthControlElement *control_stack,uint8_t *heap_ptr)
{
    //Primitive like BYE may set flag to request that caller close program
    engine->exit_program=false;

    //Loop through words in source
    uint32_t word_len=0;
    uint32_t start=0;
    uint32_t control_stack_index=0;
    do
    {
        //Get next word of source
        word_len=next_word_source(source,&start);

        if (word_len>FORTH_WORD_MAX)
        {
            //Error - word of source is longer than allowed
            //Point to word for error message in caller
            *error_word=source+start;
            return FORTH_ERROR_TOO_LONG;
        }
        else if (word_len>0)
        {
            //Word found
            char word_buffer[FORTH_WORD_MAX+1];
            strncpy(word_buffer,source+start,word_len);
            word_buffer[word_len]=0;

            //Classify word
            int32_t num=0;
            int primitive_ID;
            struct ForthWordHeader *secondary_ptr;
            int word_type=classify_word(word_buffer);
            if (word_type==FORTH_TYPE_NUMBER)
            {
                //Number
                num=int32_text(word_buffer);
            }
            else if (word_type==FORTH_TYPE_HEX)
            {
                //Hex
                num=hex32_text(word_buffer);
            } 
            else if (word_type==FORTH_TYPE_OTHER)
            {
                //Determine whether primitive, secondary, or unknown
                word_type=classify_other(word_buffer,&primitive_ID,&secondary_ptr,word_IDs);
            }
            else
            {
                //Other value including FORTH_TYPE_NONE which should not be possible
                //TODO: error!
            }

            //Advance past word in source
            start+=word_len;

            //Handle word depending on state
            if (engine->state==FORTH_STATE_INTERPRET)
            {
                //Interpret mode
                if ((word_type==FORTH_TYPE_NUMBER)||(word_type==FORTH_TYPE_HEX))
                {
                    //Number or hex - push to stack
                    forth_push(engine,num);
                }
                else if (word_type==FORTH_TYPE_PRIMITIVE)
                {
                    //Primitive
                    int (*immediate)(struct ForthEngine *engine)=forth_primitives[primitive_ID].immediate;
                    if (immediate!=NULL)
                    {
                        //Primitive has special immediate behavior
                        forth_engine_pre_exec(engine);
                        int result=immediate(engine);
                        if (result!=FORTH_ENGINE_ERROR_NONE)
                        {
                            //Error in word
                            engine->error=result;
                            //Set pointer to word in case used in error message
                            *error_word=source+start-word_len;
                            return FORTH_ERROR_ENGINE;
                        }

                        //Process outer interpreter action requested by word if present
                        //This keeps platform specific code out of primitives for portability
                        switch (engine->word_action)
                        {
                            case FORTH_ACTION_COLON:
                                {
                                    int result=action_colon(engine,source,&start,error_word,word_len,definitions,
                                                            &word_IDs,&control_stack,heap_ptr);
                                    if (result!=FORTH_ERROR_NONE) return result;
                                    break;
                                }
                            case FORTH_ACTION_CHAR:
                                forth_push(engine,action_char_common(source,&start));
                                break;
                            case FORTH_ACTION_PAREN:
                                action_paren(source,&start);
                                break;
                            case FORTH_ACTION_WORDS:
                                action_words(engine,word_IDs);
                                break;
                            case FORTH_ACTION_TICK:
                                {
                                    //Find ID or primitive and secondary if it exists
                                    uint32_t index;
                                    int result=action_tick_common(source,&start,error_word,word_len,
                                                                    word_IDs,&index);
                                    if (result!=FORTH_ERROR_NONE) return result;

                                    //Push tick ID of word to stack
                                    forth_push(engine,index);
                                    break;
                                }
                        }
                    }
                    else
                    {
                        //No special immediate behavior - execute body
                        void (*body)(struct ForthEngine *engine)=forth_primitives[primitive_ID].body;
                        if (body!=NULL)
                        {
                            forth_engine_pre_exec(engine);
                            body(engine);
                        }
                    }
                }
                else if (word_type==FORTH_TYPE_SECONDARY)
                {
                    //Secondary
                    int result=execute_secondary(engine,secondary_ptr,word_IDs,definitions);

                    //Abort if error occured while running secondary
                    if (result!=FORTH_ERROR_NONE) return result;
                }
                else if (word_type==FORTH_TYPE_NOT_FOUND)
                {
                    //Error - word not found
                    //Point to unknown word for error message in caller
                    *error_word=source+start-word_len;
                    return FORTH_ERROR_NOT_FOUND;
                }

                //Return if word like BYE requested program exit
                if (engine->exit_program) return FORTH_ERROR_NONE;
            }
            else if (engine->state==FORTH_STATE_COMPILE)
            {
                //Compile mode
                if ((word_type==FORTH_TYPE_NUMBER)||(word_type==FORTH_TYPE_HEX))
                {
                    //Number or hex - compile to dictionary
                    int result=write_definition_primitive(&prim_hidden_push,definitions,&word_IDs,&control_stack,heap_ptr);
                    if (result!=FORTH_ERROR_NONE) return result;
                    result=write_definition_i32(num,definitions,&word_IDs,&control_stack,heap_ptr);
                    if (result!=FORTH_ERROR_NONE) return result;
                }
                else if (word_type==FORTH_TYPE_PRIMITIVE)
                {
                    //Primitive
                    int (*compile)(struct ForthEngine *engine)=forth_primitives[primitive_ID].compile;
                    if (compile!=NULL)
                    {
                        //Primitive has special compile behavior
                        //TODO: do any compile functions return error? moved compiling functions here
                        forth_engine_pre_exec(engine);
                        int result=compile(engine);
                        if (result!=FORTH_ENGINE_ERROR_NONE)
                        {
                            //Error in word
                            engine->error=result;
                            //Set pointer to word in case used in error message
                            *error_word=source+start-word_len;
                            return FORTH_ERROR_ENGINE;
                        }

                        //Process outer interreter action requested by word if present
                        //This keeps platform specific code out of the primitives for portability
                        switch (engine->word_action)
                        {
                            case FORTH_ACTION_PAREN:
                                action_paren(source,&start);
                                break;
                            case FORTH_ACTION_SEMICOLON:
                                int result=action_semicolon(engine,definitions,&word_IDs,&control_stack,heap_ptr);
                                if (result!=FORTH_ERROR_NONE) return result;
                                break;
                        }
                    }
                    else
                    {
                        //No special compile behavior - compile address
                        int result=write_definition_primitive(forth_primitives[primitive_ID].body,
                            definitions,&word_IDs,&control_stack,heap_ptr);
                        if (result!=FORTH_ERROR_NONE) return result;
                    }
                }
                else if (word_type==FORTH_TYPE_SECONDARY)
                {
                    //Compile pointer to pointer to secondary
                    int result=write_definition_primitive(&prim_hidden_secondary,definitions,&word_IDs,&control_stack,heap_ptr);
                    if (result!=FORTH_ERROR_NONE) return result;
                    result=write_definition_u32((uintptr_t)&secondary_ptr->address-(uintptr_t)word_IDs->data,
                                                definitions,&word_IDs,&control_stack,heap_ptr);
                    if (result!=FORTH_ERROR_NONE) return result;
                }
                else if (word_type==FORTH_TYPE_NOT_FOUND)
                {
                    printf("Compile empty word for %s\n",word_buffer);
                }
            }
        }
    }while(word_len>0);

    return FORTH_ERROR_NONE;
}

