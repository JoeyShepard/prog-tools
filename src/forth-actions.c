#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: remove
#include "macros.h"
#include "text.h"



#include "error.h"
#include "forth.h"
#include "forth-engine.h"
#include "forth-process.h"
#include "forth-primitives.h"
#include "logging.h"
#include "mem.h"
#include "util.h"

//Helper functions
//================
//Compact definition memory and reassign pointers
static void action_compact(uint32_t delete_offset,uint32_t delete_size,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_COMPACT,"action_compact");

    //Nothing to compact if delete size is 0
    if (delete_size>0)
    {
        //Logging
        log_text("delete size: %d\n",delete_size);
    
        //Copy code for definitions later in memory to overwrite old definition
        void *dest=compile->definitions->data+delete_offset;
        void *src=dest+delete_size;
        uint32_t move_size=(uintptr_t)(compile->definitions->data+compile->definitions->index)-(uintptr_t)src;
        compile->definitions->index-=delete_size;
        compile->definitions->bytes_left+=delete_size;
        //memmove since memory ranges overlap
        memmove(dest,src,move_size);

        //Adjust pointers to definition memory in all word headers to account for code shifted above
        struct ForthWordHeader *update_secondary=compile->words->header;
        while (update_secondary->last==false)
        {
            //Logging
            log_text("adjusting secondary\n");
            log_text("  name: %s\n",update_secondary->name);
            log_text("  address: %p\n",update_secondary->address);
            log_text("  dest: %p\n",dest);
            log_text("  offset: %p\n",update_secondary->offset);
            if (update_secondary->address>(void(**)(struct ForthEngine *))dest)
            {
                //Logging
                log_text("  updating address\n");

                //Code address is part of memory shifted by memmove. Adjust pointer.
                update_secondary->address=(void(**)(struct ForthEngine *))((uint8_t *)update_secondary->address-delete_size);
                update_secondary->offset-=delete_size;

                //Logging
                log_text("  new address: %p\n",update_secondary->address);
                log_text("  new offset: %p\n",update_secondary->offset);
            }
            else
            {
                //Logging
                log_text("  not updating address\n");
            }
            update_secondary++;
        }
    }
    else
    {
        //Delete size is 0 - nothing to do
        
        //Logging
        log_text("nothing to compact\n");
    }

    //Logging
    log_pop();
}

//Helper function to reuse or create word for constant, variable, create, etc
static int action_prepare_word(const char *word_buffer,int word_type,uint8_t secondary_type,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_PREPARE_WORD,"action_prepare_word");
    log_text("name: %s\n",word_buffer);

    //Handle constant depending on whether word already exists
    if (word_type==FORTH_TYPE_SECONDARY)
    {
        //Word already exists - mark existing code for this word for deletion
        uint32_t delete_offset=compile->secondary->offset;
        uint32_t delete_size=compile->secondary->definition_size;

        //Save address of re-used word header for processing later
        compile->colon_word=compile->secondary;
        compile->colon_word_index=compile->secondary->ID;

        //Update existing word header with new details
        compile->secondary->address=(void(**)(struct ForthEngine *))(compile->definitions->data+compile->definitions->index);
        compile->secondary->offset=compile->definitions->index;
        compile->secondary->definition_size=0;
        compile->secondary->type=secondary_type;

        //Compact memory of old definition
        action_compact(delete_offset,delete_size,compile);
    }
    else if (word_type==FORTH_TYPE_NOT_FOUND)
    {
        //Save address of new constant
        compile->colon_word=compile->words->header+compile->words->index;
        compile->colon_word_index=compile->words->index;

        //Word not found - create header for new word
        int result=new_secondary(word_buffer,secondary_type,compile);
        if (result!=FORTH_ERROR_NONE) return result;
    }

    //Logging
    log_pop();

    return FORTH_ERROR_NONE;
}

//Helper function for functions expecting name after primitive like constant, var, colon, etc
static int action_source_pre(const char *source,uint32_t *start,char *word_buffer,uint32_t *word_len,int *word_type,
                                struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_SOURCE_PRE,"action_source_pre");

    uint32_t prior_start=*start;
    *word_len=next_word_source(source,start);
    uint32_t arg_start=*start;
    if (*word_len>FORTH_WORD_MAX)
    {
        //Error - word of source is longer than allowed
        //Point to word for error message in caller
        compile->error_word=source+*start;
        return FORTH_ERROR_TOO_LONG;
    }
    else if (*word_len==0)
    {
        //Error - no word name after primitive
        compile->error_word=source+prior_start-compile->word_len;
        *start=prior_start;
        return FORTH_ERROR_NO_WORD;
    }

    //Make sure name of new word is not primitive or number
    strncpy(word_buffer,source+*start,*word_len);
    word_buffer[*word_len]=0;
    *word_type=classify_word(word_buffer);
    if (*word_type==FORTH_TYPE_OTHER)
        *word_type=classify_other(word_buffer,compile);

    //Advance past name of new word
    *start+=*word_len;

    //Make sure word is the right type
    if ((*word_type!=FORTH_TYPE_SECONDARY)&&(*word_type!=FORTH_TYPE_NOT_FOUND))
    {
        compile->error_word=source+arg_start;
        return FORTH_ERROR_INVALID_NAME;
    }

    //Logging
    log_pop();

    return FORTH_ERROR_NONE;
}

//Helper function - use print_color if it exists and print otherwise
static void action_words_print(struct ForthEngine *engine,const char *text, color_t color)
{
    if (engine->print_color!=NULL) engine->print_color(text,color);
    else if (engine->print!=NULL) engine->print(text);
}


//Actions - triggered in primitive and handled here to avoid platform specific code in primitives
//===============================================================================================
int action_again(struct ForthCompileInfo *compile)
{
    //Pop element from control stack which should be BEGIN to match AGAIN
    struct ForthControlElement popped_element;
    int result=pop_control_element(&popped_element,compile);
    if (result!=FORTH_ERROR_NONE)
    {
        if (result==FORTH_ERROR_CONTROL_UNDERFLOW)
        {
            //Only error here should be FORTH_ERROR_CONTROL_UNDERFLOW meaning stack is empty so no BEGIN to match AGAIN
            return FORTH_ERROR_AGAIN_WITHOUT_BEGIN;
        }
        else return result;
    }

    if (popped_element.type!=FORTH_CONTROL_BEGIN)
    {
        //Element on control stack is something else like DO or CASE that doesn't match AGAIN
        return FORTH_ERROR_AGAIN_WITHOUT_BEGIN;
    }

    //Write primitive that jumps to BEGIN
    result=write_definition_primitive(&prim_hidden_jump,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write jump offset at address after primitive so primitive will jump here
    int32_t offset=-(compile->definitions->index-popped_element.index);
    result=write_definition_i32(offset,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_begin(struct ForthCompileInfo *compile)
{
    //Save offset into definitions where matching AGAIN or REPEAT will jump to
    uint32_t index=compile->definitions->index;

    //Write offset and type (BEGIN) to control stack
    int result=push_control_element(index,FORTH_CONTROL_BEGIN,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_char_common(const char *source,uint32_t *start,int32_t *index,struct ForthCompileInfo *compile)
{
    //Save index in case needed for error message
    uint32_t prior_start=*start;

    //Find next word in source
    uint32_t word_len=next_word_source(source,start);
    if (word_len==0)
    {
        //No word after CHAR
        compile->error_word=source+prior_start-compile->word_len;
        *start=prior_start;
        return FORTH_ERROR_NO_WORD;
    }
    else
    {
        //Return first character of word
        *index=*(uint8_t *)(source+*start);

        //Advance to next word
        *start+=word_len;

        return FORTH_ERROR_NONE;
    }
}

int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_COLON,"action_colon");

    if (engine->in_bracket==true)
    {
        //Logging
        log_pop();

        //Error - not allowed after [ while defining word
        compile->error_word=source+*start-compile->word_len;
        return FORTH_ERROR_NOT_BETWEEN_BRACKETS;
    }

    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len;
    int word_type;
    int result=action_source_pre(source,start,word_buffer,&word_len,&word_type,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Logging
    log_text("name: %s\n",word_buffer);

    if (word_type==FORTH_TYPE_SECONDARY)
    {
        //Logging
        log_text("word exists\n");
        log_text("  offset: %d\n",compile->secondary->offset);
        log_text("  definition_size: %d\n",compile->secondary->definition_size);

        //Word already exists - mark existing code for this word for deletion in semicolon 
        //(don't delete code here in case missing semicolon)
        compile->delete_offset=compile->secondary->offset;
        compile->delete_size=compile->secondary->definition_size;

        //Save address of re-used word header for processing later
        compile->colon_word=compile->secondary;
        compile->colon_word_index=compile->secondary->ID;
        compile->colon_word_exists=true;

        //Save header info in case error and info needs to be restored
        compile->save_offset=compile->secondary->offset;
        compile->save_definition_size=compile->secondary->definition_size;
        compile->save_type=compile->secondary->type;

        //Update existing word header with new details
        compile->secondary->address=(void(**)(struct ForthEngine *))(compile->definitions->data+compile->definitions->index);
        compile->secondary->offset=compile->definitions->index;
        compile->secondary->definition_size=0;
        compile->secondary->type=FORTH_SECONDARY_WORD;
    }
    else if (word_type==FORTH_TYPE_NOT_FOUND)
    {
        //Logging
        log_text("new word\n");

        //Save address of word header created by colon since other headers may be added before definition is closed
        compile->colon_word=compile->words->header+compile->words->index;
        compile->colon_word_index=compile->words->index;

        //No definition deleted to make room for new word - let semicolon know nothing to delete
        compile->colon_word_exists=false;

        //Word not found - create header for new word
        int result=new_secondary(word_buffer,FORTH_SECONDARY_WORD,compile);
        if (result!=FORTH_ERROR_NONE) return result;
    }

    //Set compile state to compiling
    engine->state=FORTH_STATE_COMPILE;

    //Logging
    log_pop();

    return FORTH_ERROR_NONE;
}

void action_comment(const char *source,uint32_t *start)
{
    while(1)
    {
        char character=source[*start];
        if ((character==10)||(character==0))
        {
            //Reached end of line or of string - comment ended
            return;
        }
        *start=*start+1;
    }
}

int action_constant(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_CONSTANT,"action_constant");

    if (engine->in_bracket==true)
    {
        //Logging
        log_pop();

        //Error - not allowed after [ while defining word
        compile->error_word=source+*start-compile->word_len;
        return FORTH_ERROR_NOT_BETWEEN_BRACKETS;
    }

    //Extract word name, len, and type. Also, catch errors - no name, name too long, name not primary or secondary.
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len;
    int word_type;
    int result=action_source_pre(source,start,word_buffer,&word_len,&word_type,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Reuse or create word for CONSTANT
    result=action_prepare_word(word_buffer,word_type,FORTH_SECONDARY_CONSTANT,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Add code to push constant value
    result=write_definition_primitive(&prim_hidden_push,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    result=write_definition_i32(forth_pop(engine),compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Add primitive to word to stop exectuing
    result=write_definition_primitive(&prim_hidden_done,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_create(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_CREATE,"action_create");

    if (engine->in_bracket==true)
    {
        //Logging
        log_pop();

        //Error - not allowed after [ while defining word
        compile->error_word=source+*start-compile->word_len;
        return FORTH_ERROR_NOT_BETWEEN_BRACKETS;
    }

    //Extract word name, len, and type. Also, catch errors - no name, name too long, name not primary or secondary.
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len;
    int word_type;
    int result=action_source_pre(source,start,word_buffer,&word_len,&word_type,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Reuse or create word for CREATE
    result=action_prepare_word(word_buffer,word_type,FORTH_SECONDARY_CREATE,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Allocate address in data section for create
    uint32_t variable_address=align4(engine->data_index)&engine->data_mask_32;
    engine->data_index=(variable_address+sizeof(int32_t))&engine->data_mask_32; 

    //Add code to push create address
    result=write_definition_primitive(&prim_hidden_push,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    result=write_definition_u32(variable_address,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Add primitive to word to stop exectuing
    result=write_definition_primitive(&prim_hidden_done,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_do(struct ForthCompileInfo *compile)
{
    //Write primitive to set up loop counter
    int result=write_definition_primitive(&prim_hidden_do,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Save offset into definitions where matching LOOP or +LOOP will jump to
    uint32_t index=compile->definitions->index;

    //Write offset and type (DO) to control stack
    result=push_control_element(index,FORTH_CONTROL_DO,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_dot_quote_interpret(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    //Save index in case needed for error message
    uint32_t prior_start=*start;

    //Skip first character which should be space but could be 0
    bool skip_first=true;

    //Print out characters
    char buffer[2];
    buffer[1]=0;
    bool characters_printed=false;
    while(1)
    {
        buffer[0]=source[*start];
        *start=*start+1;
        if (buffer[0]=='"')
        {
            //Matching " found - done printing
            return FORTH_ERROR_NONE;
        }
        else if (buffer[0]==0)
        {
            //Error - reached end of string with no terminating "
            compile->error_word=source+prior_start-compile->word_len;
            *start=prior_start;
            return FORTH_ERROR_MISSING_QUOTE;
        }
        else
        {
            if (skip_first==true)
            {
                //Skip first character which should be space but could be 0
                skip_first=false;
            }
            else
            {
                //Print out character if print function is defined
                if (engine->print!=NULL)
                {
                    engine->print(buffer);
                    characters_printed=true;
                }
            }
        }
    }

    //Update screen if anything printed
    if ((engine->update_screen!=NULL)&&(characters_printed)) engine->update_screen();
}

int action_else(struct ForthCompileInfo *compile)
{
    //Pop element from control stack which should be IF to match ELSE
    struct ForthControlElement popped_element;
    int result=pop_control_element(&popped_element,compile);
    if (result!=FORTH_ERROR_NONE)
    {
        if (result==FORTH_ERROR_CONTROL_UNDERFLOW)
        {
            //Only error here should be FORTH_ERROR_CONTROL_UNDERFLOW meaning stack is empty so no IF to match THEN
            return FORTH_ERROR_ELSE_WITHOUT_IF;
        }
        else return result;
    }

    if (popped_element.type!=FORTH_CONTROL_IF)
    {
        //Element on control stack is something else like DO or CASE that doesn't match ELSE 
        return FORTH_ERROR_ELSE_WITHOUT_IF;
    }

    //Write primitive at end of IF block to jump over ELSE block
    result=write_definition_primitive(&prim_hidden_jump,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Save offset into definitions where matching THEN will write jump address
    uint32_t index=compile->definitions->index;

    //Write offset and type (ELSE) to control stack
    result=push_control_element(index,FORTH_CONTROL_ELSE,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Reserve room in dictionary for offset which matching THEN will write
    result=write_definition_u32(0,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write jump offset at address after primitive so primitive will jump here
    uint32_t offset=compile->definitions->index-popped_element.index;
    *(uint32_t *)(compile->definitions->data+popped_element.index)=offset;

    return FORTH_ERROR_NONE;
}

int action_execute(struct ForthEngine *engine,int *word_type,struct ForthCompileInfo *compile)
{
    //EXECUTE while interpreting
    uintptr_t lower;
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    uint32_t word_ID=*engine->stack;

    if (word_ID<(uint32_t)forth_primitives_len)
    {
        //ID on stack is primitive
        *word_type=FORTH_TYPE_PRIMITIVE;
        compile->primitive_ID=word_ID;
    }
    else if (word_ID<forth_primitives_len+compile->words->index)
    {
        //ID is a secondary
        *word_type=FORTH_TYPE_SECONDARY;
        uint32_t secondary_id=word_ID-forth_primitives_len;
        compile->secondary=&compile->words->header[secondary_id];
    }
    else return FORTH_ERROR_EXECUTE;

    return FORTH_ERROR_NONE;
}

int action_i(struct ForthCompileInfo *compile)
{
    //Write primitive to push I counter
    int result=write_definition_primitive(&prim_hidden_i,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_if(struct ForthCompileInfo *compile)
{
    //Write primitive that performs IF function
    int result=write_definition_primitive(&prim_hidden_if,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Save offset into definitions where matching ELSE or THEN will write jump address
    uint32_t index=compile->definitions->index;

    //Reserve room in dictionary for offset which matching ELSE or THEN will write
    result=write_definition_u32(0,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write offset and type (IF) to control stack
    result=push_control_element(index,FORTH_CONTROL_IF,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    return FORTH_ERROR_NONE;
}

int action_j(struct ForthCompileInfo *compile)
{
    //Write primitive to push J counter
    int result=write_definition_primitive(&prim_hidden_j,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_loop(struct ForthCompileInfo *compile)
{
    //Pop element from control stack which should be DO to match LOOP
    struct ForthControlElement popped_element;
    int result=pop_control_element(&popped_element,compile);
    if (result!=FORTH_ERROR_NONE)
    {
        if (result==FORTH_ERROR_CONTROL_UNDERFLOW)
        {
            //Only error here should be FORTH_ERROR_CONTROL_UNDERFLOW meaning stack is empty so no DO to match LOOP
            return FORTH_ERROR_LOOP_WITHOUT_DO;
        }
        else return result;
    }

    if (popped_element.type!=FORTH_CONTROL_DO)
    {
        //Element on control stack is something else like BEGIN or CASE that doesn't match DO
        return FORTH_ERROR_LOOP_WITHOUT_DO;
    }

    //Write primitive for LOOP
    result=write_definition_primitive(&prim_hidden_loop,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write jump offset at address after primitive so primitive will jump here
    int32_t offset=-(compile->definitions->index-popped_element.index);
    result=write_definition_i32(offset,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

void action_paren(const char *source,uint32_t *start)
{
    while(1)
    {
        char character=source[*start];
        *start=*start+1;
        if (character==')')
        {
            //Matching ) found - comment ended
            return;
        }
        else if (character==0)
        {
            //Reached end of zero terminated string with no matching ) but no error
            return;
        }
    }
}

int action_plus_loop(struct ForthCompileInfo *compile)
{
    //Pop element from control stack which should be DO to match +LOOP
    struct ForthControlElement popped_element;
    int result=pop_control_element(&popped_element,compile);
    if (result!=FORTH_ERROR_NONE)
    {
        if (result==FORTH_ERROR_CONTROL_UNDERFLOW)
        {
            //Only error here should be FORTH_ERROR_CONTROL_UNDERFLOW meaning stack is empty so no DO to match +LOOP
            return FORTH_ERROR_PLUS_LOOP_WITHOUT_DO;
        }
        else return result;
    }

    if (popped_element.type!=FORTH_CONTROL_DO)
    {
        //Element on control stack is something else like BEGIN or CASE that doesn't match DO
        return FORTH_ERROR_PLUS_LOOP_WITHOUT_DO;
    }

    //Write primitive for +LOOP
    result=write_definition_primitive(&prim_hidden_plus_loop,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write jump offset at address after primitive so primitive will jump here
    int32_t offset=-(compile->definitions->index-popped_element.index);
    result=write_definition_i32(offset,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

void action_primitives(struct ForthEngine *engine,bool *first_word,int *line_characters,bool redraw)
{
    enum SearchModes
    {
        SEARCH_PRIMITIVES_BEGIN,
        SEARCH_PRIMITIVES
    };

    if ((engine->print_color==NULL)&&(engine->print==NULL))
    {
        //No way to print words
        return;
    }

    if (*first_word==true)
    {
        //First word printed here is first word of output so start with newline
        action_words_print(engine,"\n",0);
    }

    int search_mode=SEARCH_PRIMITIVES_BEGIN;
    int word_len;
    const char *word_name;
    bool looping=true;
    while (looping)
    {
        switch (search_mode)
        {
            case SEARCH_PRIMITIVES_BEGIN:
                //Find first primitive alphabetically and print it out
                word_name=forth_primitives[0].name;
                word_len=forth_primitives[0].len;
                for (int i=0;i<forth_primitives_len;i++)
                {
                    if (strcasecmp(word_name,forth_primitives[i].name)>0)
                    {
                        word_name=forth_primitives[i].name;
                        word_len=forth_primitives[i].len;
                    }
                }
                search_mode=SEARCH_PRIMITIVES;
                break;
            case SEARCH_PRIMITIVES:
            {
                //Next, print out rest of primitives alphabetically 
                char const *test_name=NULL;
                for (int i=0;i<forth_primitives_len;i++)
                {
                    if (strcasecmp(word_name,forth_primitives[i].name)<0)
                    {   
                        if (test_name==NULL)
                        {
                            test_name=forth_primitives[i].name;
                            word_len=forth_primitives[i].len;
                        }
                        else if (strcasecmp(test_name,forth_primitives[i].name)>0)
                        {
                            test_name=forth_primitives[i].name;
                            word_len=forth_primitives[i].len;
                        }
                    }
                }
                word_name=test_name;

                if (word_name==NULL)
                {
                    //Done outputting primitives
                    looping=false;
                }
                break;
            }
        }
        
        //Search above may have reached end so only print if still searching
        if ((looping)&&(word_name!=NULL))
        {
            if ((engine->screen_width>0)&&(*line_characters+word_len+1>=engine->screen_width))
            {
                //Move to new line to prevent word wrapping at edge of screen
                action_words_print(engine,"\n",0);
                *line_characters=0;
            }
            else
            {
                if (*first_word==false)
                {
                    //Space between printed words but not before very first word
                    action_words_print(engine," ",0);
                    *line_characters=*line_characters+1;
                }
            }
            *first_word=false;

            //Print out word
            action_words_print(engine,word_name,FORTH_COL_PRIMITIVE);
            *line_characters+=word_len;
        }
    }

    //Update screen
    if ((engine->update_screen!=NULL)&&(redraw==true)) engine->update_screen();
}

int action_quote_common(struct ForthEngine *engine,const char *source,uint32_t *start,bool escape,bool definition,
                    struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_QUOTE_COMMON,"action_quote_common");
    log_text("escape: %d\n",escape);
    log_text("definition: %d\n",definition);

    //Save index in case needed for error message
    uint32_t prior_start=*start;

    //Track count of bytes written for padding at end
    uint32_t bytes_written=0;

    //Return on stack at end
    uint32_t address=engine->data_index;
   
    //Hex value for \x escape code
    uint8_t hex_value;

    //Skip first character which should be space but could be 0
    bool skip_first=true;

    //If defining word, reserve space for length and write at end
    uint32_t length_index=compile->definitions->index;
    if (definition)
    {
        int result=write_definition_u32(0,compile);
        if (result!=FORTH_ERROR_NONE) return result;
    }

    //Escape sequence handling
    enum EscapeStates
    {
        ESCAPE_NONE,
        ESCAPE_FOUND,
        ESCAPE_HEX1,
        ESCAPE_HEX2,
    } escape_state=ESCAPE_NONE;

    //Loop through characters and write to thread
    while(1)
    {
        //Get next character
        char character=source[*start];
        *start=*start+1;

        //Logging
        log_text("character: %c (%d)\n",character,character);

        //Flag whether to write character at end of loop
        bool write_character=false;

        //Escape \m writes two characters
        char character2;
        bool write_character2=false;

        if (character==0)
        {
            //Error - reached end of string with no terminating "
            compile->error_word=source+prior_start-compile->word_len;
            *start=prior_start;
            return FORTH_ERROR_MISSING_QUOTE;
        }
        else if ((escape==false)||((escape==true)&&(escape_state==ESCAPE_NONE)))
        {
            //Process character normally
            if (skip_first==true)
            {
                //Skip first character which should be space but could be 0
                skip_first=false;
            }
            else if (character=='"')
            {
                //Logging
                log_text("done processing\n");
                log_text("bytes_written: %d\n",bytes_written);

                //Matching " found - done looping
                if (definition)
                {
                    //Writing to word definition

                    //Logging
                    log_text("definition\n");
                    log_text("address: %p\n",compile->definitions->data+compile->definitions->index);

                    //Write string length to beginning of word at saved address
                    *(uint32_t *)(compile->definitions->data+length_index)=bytes_written;

                    //Calculate padding bytes
                    int ptr_size=sizeof(void(*)(struct ForthEngine *));
                    int padding_count=(ptr_size-(bytes_written+sizeof(uint32_t))%ptr_size)%ptr_size;

                    //Logging
                    log_text("ptr_size: %u\n",ptr_size);
                    log_text("padding_count: %d\n",padding_count);

                    //Write padding bytes
                    for (int i=0;i<padding_count;i++)
                    {
                        int result=write_definition_u8(0,compile);
                        if (result!=FORTH_ERROR_NONE) return result;
                    }

                    //Logging
                    log_text("address: %p\n",compile->definitions->data+compile->definitions->index);
                }
                else
                {
                    //Writing to data memory - write return values
                    *engine->stack=address;
                    uintptr_t lower;
                    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
                    engine->stack=(int32_t*)((engine->stack_base)|lower);
                    *engine->stack=bytes_written;
                    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
                    engine->stack=(int32_t*)((engine->stack_base)|lower);
                }

                //Logging
                log_pop();

                return FORTH_ERROR_NONE;
            }
            else
            {
                if ((escape==true)&&(character=='\\'))
                {
                    //Switch to escape mode
                    escape_state=ESCAPE_FOUND;
                }
                else
                {
                    //Character to print - set flag and write below
                    write_character=true;
                }
            }
        }
        else if ((escape==true)&&(escape_state!=ESCAPE_NONE))
        {
            if (escape_state==ESCAPE_FOUND)
            {
                if (character=='x')
                {
                    //Following two characters are hex digits
                    escape_state=ESCAPE_HEX1;
                }
                else
                {
                    //Escape codes from Forth standard - including all even if not used
                    write_character=true;
                    switch (character)
                    {
                        case 'a':
                            //alert
                            character=7;
                            break;
                        case 'b':
                            //backspace
                            character=8;
                            break;
                        case 'e':
                            //escape
                            character=27;
                            break;
                        case 'f':
                            //form feed
                            character=12;
                            break;
                        case 'l':
                            //line feed
                            character=10;
                            break;
                        case 'm':
                            //CR/LF
                            character=13;
                            character2=10;
                            write_character2=true;
                            break;
                        case 'n':
                            //newline
                            character=10;
                            break;
                        case 'q':
                            //double-quote
                            character='"';
                            break;
                        case 'r':
                            //carriage return
                            character=13;
                            break;
                        case 't':
                            //horizontal tab
                            character=9;
                            break;
                        case 'v':
                            //vertical tab
                            character=11;
                            break;
                        case 'z':
                            //no character
                            character=0;
                            break;
                        case '"':
                            //double-quote
                            character='"';
                            break;
                        case '\\':
                            //backslash
                            character='\\';
                            break;
                        default:
                            write_character=false;
                    }
                    escape_state=ESCAPE_NONE;
                }
            }
            else
            {
                //Processing hex value
                uint8_t new_value;
                if ((character>='0')&&(character<='9')) new_value=character-'0';
                else if ((character>='A')&&(character<='F')) new_value=character-'A'+10;
                else if ((character>='a')&&(character<='f')) new_value=character-'a'+10;

                if (escape_state==ESCAPE_HEX1)
                {
                    //First of two hex characters
                    hex_value=new_value;
                    escape_state=ESCAPE_HEX2;
                }
                else
                {
                    //Second hex character
                    hex_value=(hex_value<<4)|new_value;
                    escape_state=ESCAPE_NONE;
                    character=hex_value;
                    write_character=true;
                }
            }
        }

        if (definition)
        {
            //Write character to definition
            if (write_character==true)
            {
                //First character
                int result=write_definition_u8(character,compile);
                if (result!=FORTH_ERROR_NONE) return result;
                bytes_written++;
            }
            if (write_character2==true)
            {
                //Second character
                int result=write_definition_u8(character2,compile);
                if (result!=FORTH_ERROR_NONE) return result;
                bytes_written++;
            }
        }
        else
        {
            //Write character to data memory
            if (write_character==true)
            {
                //First character
                *(engine->data+engine->data_index)=character;
                bytes_written++;

                //Advance data pointer
                engine->data_index=(engine->data_index+sizeof(character))&engine->data_mask;
            }
            if (write_character2==true)
            {
                //Second character
                *(engine->data+engine->data_index)=character2;
                bytes_written++;

                //Advance data pointer
                engine->data_index=(engine->data_index+sizeof(character))&engine->data_mask;
            }
        }
    }
}

int action_repeat(struct ForthCompileInfo *compile)
{
    //Pop element from control stack which should be WHILE to match REPEAT
    struct ForthControlElement while_element;
    int result=pop_control_element(&while_element,compile);
    if (result!=FORTH_ERROR_NONE)
    {
        if (result==FORTH_ERROR_CONTROL_UNDERFLOW)
        {
            //Only error here should be FORTH_ERROR_CONTROL_UNDERFLOW meaning stack is empty so no WHILE to match REPEAT
            return FORTH_ERROR_REPEAT_WITHOUT_WHILE;
        }
        else return result;
    }

    if (while_element.type!=FORTH_CONTROL_WHILE)
    {
        //Element on control stack is something else like DO or CASE that doesn't match REPEAT
        return FORTH_ERROR_REPEAT_WITHOUT_WHILE;
    }

    //Pop element from control stack which is definitely BEGIN since WHILE already made sure it is
    struct ForthControlElement begin_element;
    pop_control_element(&begin_element,compile);

    //Write primitive that jumps to BEGIN
    result=write_definition_primitive(&prim_hidden_jump,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write jump offset at address after primitive so primitive will jump here
    int32_t offset=-(compile->definitions->index-begin_element.index);
    result=write_definition_i32(offset,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write jump offset at address after WHILE so primitive will jump here
    offset=compile->definitions->index-while_element.index;
    *(int32_t *)(compile->definitions->data+while_element.index)=offset;

    return FORTH_ERROR_NONE;
}

void action_secondaries(struct ForthEngine *engine,bool *first_word,int *line_characters,bool defined,bool redraw,
                        struct ForthCompileInfo *compile)
{
    enum SearchModes
    {
        SEARCH_SECONDARIES_BEGIN,
        SEARCH_SECONDARIES
    };

    if ((engine->print_color==NULL)&&(engine->print==NULL))
    {
        //No way to print words
        return;
    }

    if (*first_word==true)
    {
        //First word printed here is first word of output so start with newlin
        action_words_print(engine,"\n",0);
    }

    int search_mode=SEARCH_SECONDARIES_BEGIN;
    int word_len;
    const char *word_name;
    bool looping=true;
    while (looping)
    {
        switch (search_mode)
        {
            case SEARCH_SECONDARIES_BEGIN:
            {
                //Find first secondary alphabetically and print it out
                struct ForthWordHeader *secondary=compile->words->header;
                word_name=NULL;
                while(secondary->last==false)
                {
                    if ((secondary->type!=FORTH_SECONDARY_UNDEFINED)==defined)
                    {
                        //Word matches type of word searching for - defined or undefined
                        if (word_name==NULL)
                        {
                            //First matching word found
                            word_name=secondary->name;
                            word_len=secondary->name_len;
                        }
                        else
                        {
                            //Compare word to alphabetically lowest word found so far
                            if (strcasecmp(word_name,secondary->name)>0)
                            {
                                word_name=secondary->name;
                                word_len=secondary->name_len;
                            }
                        }
                    }
                    secondary++;
                }

                if (word_name==NULL)
                {
                    //No match words found - done searching
                    looping=false;
                }
                else
                {
                    //Search through rest of secondaries
                    search_mode=SEARCH_SECONDARIES;
                }
                break;
            }
            case SEARCH_SECONDARIES:
            {
                //Next, print out rest of secondaries alphabetically
                struct ForthWordHeader *secondary=compile->words->header;
                char const *test_name=NULL;
                while(secondary->last==false)
                {
                    if ((secondary->type!=FORTH_SECONDARY_UNDEFINED)==defined)
                    {
                        //Word matches type of word searching for - defined or undefined
                        if (strcasecmp(word_name,secondary->name)<0)
                        {   
                            if (test_name==NULL)
                            {
                                test_name=secondary->name;
                                word_len=secondary->name_len;
                            }
                            else if (strcasecmp(test_name,secondary->name)>0)
                            {
                                test_name=secondary->name;
                                word_len=secondary->name_len;
                            }
                        }
                    }
                    secondary++;
                }
                word_name=test_name;

                if (word_name==NULL)
                {
                    //Done outputting secondaries - stop looping
                    looping=false;
                }
                break;
            }
        }
        
        //Search for secondaries above may have reached end so only print if still searching
        if ((looping)&&(word_name!=NULL))
        {
            if ((engine->screen_width>0)&&(*line_characters+word_len+1>=engine->screen_width))
            {
                //Move to new line to prevent word wrapping at edge of screen
                action_words_print(engine,"\n",0);
                *line_characters=0;
            }
            else
            {
                if (*first_word==false)
                {
                    //Space between printed words but not before very first word
                    action_words_print(engine," ",0);
                    *line_characters=*line_characters+1;
                }
            }
            *first_word=false;

            //Print out word
            color_t word_color;
            if (defined==true) word_color=FORTH_COL_SECONDARY;
            else word_color=FORTH_COL_NOT_FOUND;
            action_words_print(engine,word_name,word_color);
            *line_characters+=word_len;
        }
    }

    //Update screen
    if ((engine->update_screen!=NULL)&&(redraw==true)) engine->update_screen();
}

int action_semicolon(struct ForthEngine *engine,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_SEMICOLON,"action_semicolon");
    log_text("name: %s\n",compile->colon_word->name);
    log_text("size: %d\n",compile->colon_word->definition_size);

    //Error if control structure like IF or BEGIN left unterminated
    if (compile->control_stack->index!=0)
    {
        struct ForthControlElement element;
        pop_control_element(&element,compile);
        //TODO: accounted for all control types? double check forth-process.h
        switch (element.type)
        {
            case FORTH_CONTROL_BEGIN:
                return FORTH_ERROR_UNTERMINATED_BEGIN;
            case FORTH_CONTROL_CASE:
                return FORTH_ERROR_UNTERMINATED_CASE;
            case FORTH_CONTROL_OF:
                return FORTH_ERROR_UNTERMINATED_OF;
            case FORTH_CONTROL_DO:
                return FORTH_ERROR_UNTERMINATED_DO;
            case FORTH_CONTROL_IF:
                return FORTH_ERROR_UNTERMINATED_IF;
            case FORTH_CONTROL_ELSE:
                return FORTH_ERROR_UNTERMINATED_ELSE;
            case FORTH_CONTROL_WHILE:
                return FORTH_ERROR_UNTERMINATED_WHILE;
        }
    }
    
    //Add primitive to word to stop executing
    int result=write_definition_primitive(&prim_hidden_done,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Start at word defined by colon and mark all words as done
    //(New word is either newly created in which case it and all headers after should be marked done OR the new word
    //reuses an existing header since the word is being redefined in which case there may not be any new word headers and
    //the search here may needlessly re-mark a lot of headers done. Redefining a word is relatively rare so leave as is.) 
    struct ForthWordHeader *secondary=compile->colon_word;

    //Mark header for word and any other headers created in word as done
    while(secondary->last==false)
    {
        secondary->done=true;
        secondary++;
    }

    //Recover definition memory if word was redfined
    if ((compile->colon_word_exists==true)&&(compile->delete_size!=0))
    {
        //Compact memory of old definition
        action_compact(compile->delete_offset,compile->delete_size,compile);
    }

    //Set compile state back to interpret
    engine->state=FORTH_STATE_INTERPRET;
    engine->in_bracket=false;

    //Logging
    log_pop();

    return FORTH_ERROR_NONE;
}

int action_then(struct ForthCompileInfo *compile)
{
    //Pop element from control stack which should be IF to match THEN
    struct ForthControlElement popped_element;
    int result=pop_control_element(&popped_element,compile);
    if (result!=FORTH_ERROR_NONE)
    {
        if (result==FORTH_ERROR_CONTROL_UNDERFLOW)
        {
            //Only error here should be FORTH_ERROR_CONTROL_UNDERFLOW meaning stack is empty so no IF to match THEN
            return FORTH_ERROR_THEN_WITHOUT_IF;
        }
        else return result;
    }

    if ((popped_element.type!=FORTH_CONTROL_IF)&&(popped_element.type!=FORTH_CONTROL_ELSE))
    {
        //Element on control stack is something else like DO or CASE that doesn't match THEN 
        return FORTH_ERROR_THEN_WITHOUT_IF;
    }

    //Write jump offset at address after primitive so primitive will jump here
    int32_t offset=compile->definitions->index-popped_element.index;
    *(int32_t *)(compile->definitions->data+popped_element.index)=offset;

    return FORTH_ERROR_NONE;
}

int action_tick_common(const char *source,uint32_t *start,uint32_t *index,struct ForthCompileInfo *compile)
{
    //Save index in case needed for error message
    uint32_t prior_start=*start;

    //Fetch next word in source
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len=next_word_source(source,start);
    if (word_len>FORTH_WORD_MAX)
    {
        //Error - word of source is longer than allowed
        //Point to word for error message in caller
        compile->error_word=source+*start;
        return FORTH_ERROR_TOO_LONG;
    }
    else if (word_len==0)
    {
        //Error - no word name after '
        compile->error_word=source+prior_start-compile->word_len;
        *start=prior_start;
        return FORTH_ERROR_NO_WORD;
    }

    //Make sure word name is primitive or secondary
    strncpy(word_buffer,source+*start,word_len);
    word_buffer[word_len]=0;
    int word_type=classify_word(word_buffer);
    if (word_type==FORTH_TYPE_OTHER)
        word_type=classify_other(word_buffer,compile);

    if (word_type==FORTH_TYPE_PRIMITIVE)
    {
        //Advance past name of argument word
        *start+=word_len;

        //Return index of primitive
        *index=compile->primitive_ID;
        return FORTH_ERROR_NONE;
    }
    else if (word_type==FORTH_TYPE_SECONDARY)
    {
        //Advance past name of argument word
        *start+=word_len;

        //Return index of secondary
        *index=forth_primitives_len+compile->secondary->ID;
        return FORTH_ERROR_NONE;
    }
    else
    {
        //Error - can only get ID of primitive or secondary not number or anything else
        compile->error_word=source+*start;
        return FORTH_ERROR_INVALID_NAME;
    }
}

int action_until(struct ForthCompileInfo *compile)
{
    //Pop element from control stack which should be BEGIN to match UNTIL
    struct ForthControlElement popped_element;
    int result=pop_control_element(&popped_element,compile);
    if (result!=FORTH_ERROR_NONE)
    {
        if (result==FORTH_ERROR_CONTROL_UNDERFLOW)
        {
            //Only error here should be FORTH_ERROR_CONTROL_UNDERFLOW meaning stack is empty so no BEGIN to match UNTIL
            return FORTH_ERROR_UNTIL_WITHOUT_BEGIN;
        }
        else return result;
    }

    if (popped_element.type!=FORTH_CONTROL_BEGIN)
    {
        //Element on control stack is something else like DO or CASE that doesn't match UNTIL
        return FORTH_ERROR_UNTIL_WITHOUT_BEGIN;
    }

    //Write primitive that jumps to BEGIN if not true - same behavior as IF
    result=write_definition_primitive(&prim_hidden_if,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write jump offset at address after primitive so primitive will jump here
    int32_t offset=-(compile->definitions->index-popped_element.index);
    result=write_definition_i32(offset,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_variable(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_VARIABLE,"action_variable");

    if (engine->in_bracket==true)
    {
        //Logging
        log_pop();

        //Error - not allowed after [ while defining word
        compile->error_word=source+*start-compile->word_len;
        return FORTH_ERROR_NOT_BETWEEN_BRACKETS;
    }

    //Extract word name, len, and type. Also, catch errors - no name, name too long, name not primary or secondary.
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len;
    int word_type;
    int result=action_source_pre(source,start,word_buffer,&word_len,&word_type,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Reuse or create word for VARIABLE
    result=action_prepare_word(word_buffer,word_type,FORTH_SECONDARY_VARIABLE,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Allocate address in data section for variable
    uint32_t variable_address=align4(engine->data_index)&engine->data_mask_32;
    engine->data_index=(variable_address+sizeof(int32_t))&engine->data_mask_32; 

    //Add code to push variable address
    result=write_definition_primitive(&prim_hidden_push,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    result=write_definition_u32(variable_address,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Add primitive to word to stop exectuing
    result=write_definition_primitive(&prim_hidden_done,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Logging
    log_pop();

    return FORTH_ERROR_NONE;
}

int action_while(struct ForthCompileInfo *compile)
{
    //Peek element from control stack which should be BEGIN to match WHILE
    struct ForthControlElement begin_element;
    int result=peek_control_element(&begin_element,compile);
    if (result!=FORTH_ERROR_NONE)
    {
        if (result==FORTH_ERROR_CONTROL_UNDERFLOW)
        {
            //Only error here should be FORTH_ERROR_CONTROL_UNDERFLOW meaning stack is empty so no BEGIN to match WHILE
            return FORTH_ERROR_WHILE_WITHOUT_BEGIN;
        }
        else return result;
    }

    if (begin_element.type!=FORTH_CONTROL_BEGIN)
    {
        //Element on control stack is something else like DO or CASE that doesn't match WHILE
        return FORTH_ERROR_WHILE_WITHOUT_BEGIN;
    }

    //Write primitive that performs WHILE function - same behavior as IF
    result=write_definition_primitive(&prim_hidden_if,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Save offset into definitions where matching ELSE or THEN will write jump address
    uint32_t index=compile->definitions->index;

    //Reserve room in dictionary for offset which matching REPEAT will write
    result=write_definition_u32(0,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Write offset and type (WHILE) to control stack
    result=push_control_element(index,FORTH_CONTROL_WHILE,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_wordsize(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len;
    int word_type;
    int result=action_source_pre(source,start,word_buffer,&word_len,&word_type,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    if (word_type==FORTH_TYPE_SECONDARY)
    {
        //Write word size to stack
        *engine->stack=compile->secondary->definition_size;
        uintptr_t lower;
        lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
        engine->stack=(int32_t*)((engine->stack_base)|lower);
        return FORTH_ERROR_NONE;
    }
    else
    {
        //Error - type is FORTH_TYPE_NOT_FOUND. All other errors caught above by action_source_pre.
        compile->error_word=source+*start-word_len;
        return FORTH_ERROR_INVALID_NAME;
    }
}

