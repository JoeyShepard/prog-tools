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

uint32_t align4(uint32_t value)
{
    return value+((4-value%4)%4);
}

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
        if (secondary->last==true)
        {
            //Found empty header indicating end of list - done searching
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

int classify_other(const char *word,struct CompileInfo *compile)
{
    //Default return value in case word is primitive
    compile->secondary=NULL;

    //Word is primitive?
    compile->primitive_ID=find_primitive(word);
    if (compile->primitive_ID!=FORTH_PRIM_NOT_FOUND) return FORTH_TYPE_PRIMITIVE;

    //Word is secondary?
    compile->secondary=find_secondary(word,*compile->word_IDs);
    if (compile->secondary!=NULL) return FORTH_TYPE_SECONDARY;
    
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

int expand_definitions(uint32_t size,struct CompileInfo *compile)
{
    if (compile->definitions->bytes_left<size)
    {
        //Not enough memory left in dictionary - expand memory
        int result=expand_object(FORTH_MEM_DEFINITIONS,FORTH_ID_DEFINITIONS,compile->heap_ptr);
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
        compile->definitions->bytes_left+=FORTH_MEM_DEFINITIONS;

        //Update pointers since shifted by expand_object above
        *compile->control_stack=(struct ForthControlElement *)object_address(FORTH_ID_CONTROL_STACK,compile->heap_ptr);
        *compile->word_IDs=(struct ForthWordIDsInfo *)object_address(FORTH_ID_WORD_IDS,compile->heap_ptr);
    }
    return FORTH_ERROR_NONE;
}

//Function pointer here should be 32 bit on calculator so write_dict_u32 would work but adding this for testing on x86.
int write_definition_primitive(void (*word)(struct ForthEngine *engine),struct CompileInfo *compile)
{
    //Expand definitions memory if necessary
    int result=expand_definitions(sizeof(word),compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Write value to definitions - memcpy to avoid casting object pointer to function pointer
    memcpy(compile->definitions->data+compile->definitions->index,&word,sizeof(word));

    //Update counts in definitions memory
    compile->definitions->index+=sizeof(word);
    compile->definitions->bytes_left-=sizeof(word);

    //Update size of definition in word header
    compile->colon_word->definition_size+=sizeof(word);
    
    return FORTH_ERROR_NONE;
}

int write_definition_i32(int32_t value,struct CompileInfo *compile)
{
    //Expand definitions memory if necessary
    int result=expand_definitions(sizeof(value),compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Write value to definitions - memcpy to avoid casting object pointer to function pointer
    memcpy(compile->definitions->data+compile->definitions->index,&value,sizeof(value));

    //Update counts in definitions memory
    compile->definitions->index+=sizeof(value);
    compile->definitions->bytes_left-=sizeof(value);

    //Update size of definition in word header
    compile->colon_word->definition_size+=sizeof(value);

    return FORTH_ERROR_NONE;
}

int write_definition_u32(uint32_t value,struct CompileInfo *compile)
{
    //Expand definitions memory if necessary
    int result=expand_definitions(sizeof(value),compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Write value to definitions - memcpy to avoid casting object pointer to function pointer
    memcpy(compile->definitions->data+compile->definitions->index,&value,sizeof(value));

    //Update counts in definitions memory
    compile->definitions->index+=sizeof(value);
    compile->definitions->bytes_left-=sizeof(value);

    //Update size of definition in word header
    compile->colon_word->definition_size+=sizeof(value);

    return FORTH_ERROR_NONE;
}

int execute_secondary(struct ForthEngine *engine,struct CompileInfo *compile)
{
    //Error if secondary has header but hasn't been defined
    if (compile->secondary->type==FORTH_SECONDARY_WORD)
    {
        //Prepare engine to run secondary
        forth_engine_pre_exec(engine);
        engine->executing=true;
        engine->address=compile->secondary->address;
        engine->word_headers=(*compile->word_IDs)->data;
        engine->word_bodies=compile->definitions->data;
        engine->error=FORTH_ENGINE_ERROR_NONE;

        //Mark end of R-stack so interpreter can stop executing when it returns from top-level word
        forth_rstack_push(0,FORTH_RSTACK_DONE,engine->word_index,engine);
        
        //Execute primitives
        while(engine->executing)
        {
            (*engine->address)(engine);
            engine->address++;
        }
    }
    else if (compile->secondary->type==FORTH_SECONDARY_UNDEFINED)
    {
        engine->error=FORTH_ENGINE_ERROR_UNDEFINED;
        engine->error_word=compile->secondary->name;
    }

    
    //Flag error if any
    if (engine->error!=FORTH_ENGINE_ERROR_NONE) return FORTH_ERROR_ENGINE;
    else return FORTH_ERROR_NONE;
}

int new_secondary(const char *word_buffer,uint8_t word_type,struct CompileInfo *compile)
{
    //Pointer to new secondary
    struct ForthWordHeader *secondary=(struct ForthWordHeader *)((*compile->word_IDs)->data+(*compile->word_IDs)->index);
    
    uint32_t word_len=strlen(word_buffer);

    //Need enough space for current header and empty header following which marks end of list
    if ((*compile->word_IDs)->bytes_left<sizeof(struct ForthWordHeader)*2+word_len+1)
    {
        //Not enough memory to add new word ID - expand memory
        int result=expand_object(FORTH_MEM_WORD_IDS,FORTH_ID_WORD_IDS,compile->heap_ptr);
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
        (*compile->word_IDs)->bytes_left+=FORTH_MEM_WORD_IDS;

        //Update control stack address since shifted by expand_object above
        *compile->control_stack=(struct ForthControlElement *)object_address(FORTH_ID_CONTROL_STACK,compile->heap_ptr);
    }

    //Write new word info to header
    secondary->address=(void(**)(struct ForthEngine *engine))(compile->definitions->data+compile->definitions->index);
    secondary->offset=compile->definitions->index;
    secondary->definition_size=0;
    secondary->header_size=align4(sizeof(struct ForthWordHeader)+word_len+1);
    secondary->ID=compile->definitions->ID;
    secondary->type=word_type;
    secondary->name_len=word_len;
    secondary->last=false;
    secondary->done=false;
    strcpy(secondary->name,word_buffer);

    //Advance to next ID in definitions since current one was used above
    compile->definitions->ID++;

    //Advance index in preparation of next header
    (*compile->word_IDs)->index+=secondary->header_size;
    (*compile->word_IDs)->bytes_left-=secondary->header_size;

    //Write next header and set last to true to indicate end of list
    secondary=(struct ForthWordHeader *)((uint8_t *)secondary+secondary->header_size);
    secondary->last=true;

    return FORTH_ERROR_NONE;
}

int process_source(struct ForthEngine *engine,const char *source,const char **error_word,
                            struct ForthDefinitionsInfo *definitions,struct ForthWordIDsInfo *word_IDs,
                            struct ForthControlElement *control_stack,uint8_t *heap_ptr)
{
    //Store informaton for compiling in struct so easier to pass to functions
    struct CompileInfo compile;
    compile.error_word=error_word;
    compile.definitions=definitions;
    compile.word_IDs=&word_IDs;
    compile.control_stack=&control_stack;
    compile.heap_ptr=heap_ptr;

    //Primitive like BYE may set flag to request that caller close program
    engine->exit_program=false;

    //Loop through words in source
    compile.word_len=0;
    uint32_t start=0;
    uint32_t control_stack_index=0;
    do
    {
        //Get next word of source
        compile.word_len=next_word_source(source,&start);

        if (compile.word_len>FORTH_WORD_MAX)
        {
            //Error - word of source is longer than allowed
            //Point to word for error message in caller
            *error_word=source+start;
            return FORTH_ERROR_TOO_LONG;
        }
        else if (compile.word_len>0)
        {
            //Word found
            char word_buffer[FORTH_WORD_MAX+1];
            strncpy(word_buffer,source+start,compile.word_len);
            word_buffer[compile.word_len]=0;

            //Classify word
            int32_t num=0;
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
                word_type=classify_other(word_buffer,&compile);
            }
            else
            {
                //Other value including FORTH_TYPE_NONE which should not be possible
                //TODO: error!
            }

            //Advance past word in source
            start+=compile.word_len;

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
                    int (*immediate_func)(struct ForthEngine *engine)=forth_primitives[compile.primitive_ID].immediate;
                    if (immediate_func!=NULL)
                    {
                        //Primitive has special immediate behavior
                        forth_engine_pre_exec(engine);
                        int result=immediate_func(engine);
                        if (result!=FORTH_ENGINE_ERROR_NONE)
                        {
                            //Error in word
                            engine->error=result;
                            //Set pointer to word in case used in error message
                            *compile.error_word=source+start-compile.word_len;
                            return FORTH_ERROR_ENGINE;
                        }

                        //Process outer interpreter action requested by word if present
                        //This keeps platform specific code out of primitives for portability
                        switch (engine->word_action)
                        {
                            case FORTH_ACTION_COLON:
                                {
                                    int result=action_colon(engine,source,&start,&compile);
                                    if (result!=FORTH_ERROR_NONE) return result;
                                    break;
                                }
                            case FORTH_ACTION_CHAR:
                                int32_t index;
                                int result=action_char_common(source,&start,&index,&compile);
                                if (result!=FORTH_ERROR_NONE) return result;
                                forth_push(engine,index);
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
                                    int result=action_tick_common(source,&start,&index,&compile);
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
                        void (*body_func)(struct ForthEngine *engine)=forth_primitives[compile.primitive_ID].body;
                        if (body_func!=NULL)
                        {
                            forth_engine_pre_exec(engine);
                            body_func(engine);
                        }
                    }
                }
                else if (word_type==FORTH_TYPE_SECONDARY)
                {
                    //Secondary
                    int result=execute_secondary(engine,&compile);

                    //Abort if error occured while running secondary
                    if (result!=FORTH_ERROR_NONE) return result;
                }
                else if (word_type==FORTH_TYPE_NOT_FOUND)
                {
                    //Error - word not found
                    //Point to unknown word for error message in caller
                    *compile.error_word=source+start-compile.word_len;
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
                    int result=write_definition_primitive(&prim_hidden_push,&compile);
                    if (result!=FORTH_ERROR_NONE) return result;
                    result=write_definition_i32(num,&compile);
                    if (result!=FORTH_ERROR_NONE) return result;
                }
                else if (word_type==FORTH_TYPE_PRIMITIVE)
                {
                    //Primitive
                    int (*compile_func)(struct ForthEngine *engine)=forth_primitives[compile.primitive_ID].compile;
                    if (compile_func!=NULL)
                    {
                        //Primitive has special compile behavior
                        //TODO: do any compile functions return error? moved compiling functions here
                        forth_engine_pre_exec(engine);
                        int result=compile_func(engine);
                        if (result!=FORTH_ENGINE_ERROR_NONE)
                        {
                            //Error in word
                            engine->error=result;
                            //Set pointer to word in case used in error message
                            *error_word=source+start-compile.word_len;
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
                                int result=action_semicolon(engine,&compile);
                                if (result!=FORTH_ERROR_NONE) return result;
                                break;
                        }
                    }
                    else
                    {
                        //No special compile behavior - compile address
                        int result=write_definition_primitive(forth_primitives[compile.primitive_ID].body,&compile);
                        if (result!=FORTH_ERROR_NONE) return result;
                    }
                }
                else if (word_type==FORTH_TYPE_SECONDARY)
                {
                    //Compile pointer to pointer to secondary
                    int result=write_definition_primitive(&prim_hidden_secondary,&compile);
                    if (result!=FORTH_ERROR_NONE) return result;
                    result=write_definition_u32((uintptr_t)compile.secondary-(uintptr_t)(*compile.word_IDs)->data,&compile);
                    if (result!=FORTH_ERROR_NONE) return result;
                }
                else if (word_type==FORTH_TYPE_NOT_FOUND)
                {
                    //Save copy of address of header where new word will be
                    struct ForthWordHeader *secondary=(struct ForthWordHeader *)((*compile.word_IDs)->data+(*compile.word_IDs)->index);

                    //Unknown symbol - add word header but don't error
                    int result=new_secondary(word_buffer,FORTH_SECONDARY_UNDEFINED,&compile);
                    if (result!=FORTH_ERROR_NONE) return result;

                    //Compile pointer to pointer to secondary
                    result=write_definition_primitive(&prim_hidden_secondary,&compile);
                    if (result!=FORTH_ERROR_NONE) return result;
                    result=write_definition_u32((uintptr_t)secondary-(uintptr_t)(*compile.word_IDs)->data,&compile);
                    if (result!=FORTH_ERROR_NONE) return result;
                }
            }
        }
    }while(compile.word_len>0);

    return FORTH_ERROR_NONE;
}

