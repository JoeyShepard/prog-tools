#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "forth.h"
#include "forth-engine.h"
#include "forth-process.h"
#include "forth-primitives.h"
#include "logging.h"
#include "mem.h"

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
        //Error - no word name after :
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

//Helper function - use print_color if it exists and print otherwise
static void action_words_print(struct ForthEngine *engine,const char *text, color_t color)
{
    if (engine->print_color!=NULL) engine->print_color(text,color);
    else if (engine->print!=NULL) engine->print(text);
}


//TODO: rearrange functions here to match alphabetical order in header

//Actions - triggered in primitive and handled here to avoid platform specific code in primitives
//===============================================================================================
int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_COLON,"action_colon");

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

int action_constant(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
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
    //Extract word name, len, and type. Also, catch errors - no name, name too long, name not primary or secondary.
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len;
    int word_type;
    int result=action_source_pre(source,start,word_buffer,&word_len,&word_type,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    //Reuse or create word for CREATE
    result=action_prepare_word(word_buffer,word_type,FORTH_SECONDARY_CREATE,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Add code to push create address
    result=write_definition_primitive(&prim_hidden_push,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    result=write_definition_i32(engine->data_index,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Add primitive to word to stop exectuing
    result=write_definition_primitive(&prim_hidden_done,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    return FORTH_ERROR_NONE;
}

int action_semicolon(struct ForthEngine *engine,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_SEMICOLON,"action_semicolon");
    log_text("name: %s\n",compile->colon_word->name);
    log_text("size: %d\n",compile->colon_word->definition_size);

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

    //Logging
    log_pop();

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
            //since using ( here like \ since no \ on calculator keypad
            return;
        }
    }
}

int action_variable(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_ACTION_VARIABLE,"action_variable");

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
    uint32_t variable_address=engine->data_index;
    engine->data_index=(engine->data_index+sizeof(int32_t))&engine->data_mask_32; 

    //Add code to push variable address
    result=write_definition_primitive(&prim_hidden_push,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    result=write_definition_i32(variable_address,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Add primitive to word to stop exectuing
    result=write_definition_primitive(&prim_hidden_done,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Logging
    log_pop();

    return FORTH_ERROR_NONE;
}

void action_primitives(struct ForthEngine *engine,bool *first_word,int *line_characters,bool redraw,struct ForthCompileInfo *compile)
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

