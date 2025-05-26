#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: remove
#include "debug.h"

#include "error.h"
#include "forth.h"
#include "forth-engine.h"
#include "forth-process.h"
#include "forth-primitives.h"
#include "mem.h"

//Helper function to compact definition memory and reassign pointers
static void action_compact(uint32_t delete_offset,uint32_t delete_size,struct ForthCompileInfo *compile)
{
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
        if (update_secondary->address>(void(**)(struct ForthEngine *))dest)
        {
            //Code address is part of memory shifted by memmove. Adjust pointer.
            update_secondary->address=(void(**)(struct ForthEngine *))((uint8_t *)update_secondary->address-delete_size);
            update_secondary->offset-=delete_size;
        }
        update_secondary++;
    }
}

//Helper function for functions expecting name after primitive like constant, var, colon, etc
static int action_source_pre(const char *source,uint32_t *start,char *word_buffer,uint32_t *word_len,int *word_type,
                                struct ForthCompileInfo *compile)
{
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

    return FORTH_ERROR_NONE;
}

//TODO: rearrange functions here to match alphabetical order in header
int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile)
{
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len;
    int word_type;
    int result=action_source_pre(source,start,word_buffer,&word_len,&word_type,compile);
    if (result!=FORTH_ERROR_NONE) return result;
    
    if (word_type==FORTH_TYPE_SECONDARY)
    {
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
        //Save address of word header created by colon since other headers may be added before definition is closed
        compile->colon_word=compile->words->header+compile->words->index;
        compile->colon_word_index=compile->words->index;

        //Word not found - create header for new word
        int result=new_secondary(word_buffer,FORTH_SECONDARY_WORD,compile);
        if (result!=FORTH_ERROR_NONE) return result;

        //No definition deleted to make room for new word - let semicolon know nothing to delete
        compile->colon_word_exists=false;
    }

    //Set compile state to compiling
    engine->state=FORTH_STATE_COMPILE;

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
    
    //Handle constant depending on whether word already exists
    if (word_type==FORTH_TYPE_SECONDARY)
    {
        //Word already exists - mark existing code for this word for deletion
        uint32_t delete_offset=compile->secondary->offset;
        uint32_t delete_size=compile->secondary->definition_size;

        //Update existing word header with new details
        compile->secondary->address=(void(**)(struct ForthEngine *))(compile->definitions->data+compile->definitions->index);
        compile->secondary->offset=compile->definitions->index;
        compile->secondary->definition_size=0;
        compile->secondary->type=FORTH_SECONDARY_WORD;

        //Compact memory of old definition
        action_compact(delete_offset,delete_size,compile);

    }
    else if (word_type==FORTH_TYPE_NOT_FOUND)
    {
        //Save address of new constant
        compile->colon_word=compile->words->header+compile->words->index;
        compile->colon_word_index=compile->words->index;

        //Word not found - create header for new word
        int result=new_secondary(word_buffer,FORTH_SECONDARY_WORD,compile);
        if (result!=FORTH_ERROR_NONE) return result;
    }

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

int action_semicolon(struct ForthEngine *engine,struct ForthCompileInfo *compile)
{
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

//Helper function - use print_color if it exists and print otherwise
static void action_words_print(struct ForthEngine *engine,const char *text, color_t color)
{
    if (engine->print_color!=NULL) engine->print_color(text,color);
    else if (engine->print!=NULL) engine->print(text);
}

void action_words(struct ForthEngine *engine,struct ForthWordHeaderInfo *words)
{
    enum SearchModes
    {
        SEARCH_PRIMITIVES,
        SEARCH_SECONDARIES
    };
    if ((engine->print_color==NULL)&&(engine->print==NULL))
    {
        //No way to print words
        return;
    }

    action_words_print(engine,"\n",0);
    bool first_word=true;
    int line_characters=0;
    int search_mode=SEARCH_PRIMITIVES;
    int primitive_index=0;
    int word_len;
    const char *word_name;
    color_t word_color;
    bool looping=true;
    struct ForthWordHeader *secondary=words->header;
    while (looping)
    {
        switch (search_mode)
        {
            //Output primitives first
            case SEARCH_PRIMITIVES:
                word_len=forth_primitives[primitive_index].len;
                word_name=forth_primitives[primitive_index].name;
                word_color=FORTH_COL_PRIMITIVE;
                primitive_index++;
                if (primitive_index==forth_primitives_len)
                {
                    //Done outputting primitives - switch to secondaries
                    search_mode=SEARCH_SECONDARIES;
                }
                break;
            case SEARCH_SECONDARIES:
                //Next, output secondaries
                if (secondary->last==true)
                {
                    //Empty header reached - done looping
                    looping=false;
                }
                else
                {
                    //Output secondaries
                    word_len=secondary->name_len;
                    word_name=secondary->name;
                    word_color=FORTH_COL_SECONDARY;
                    secondary++;
                }
                break;
        }
        
        //Search for secondaries above may have reached end so only print if still searching
        if (looping)
        {
            if ((engine->screen_width>0)&&(line_characters+word_len+1>=engine->screen_width))
            {
                //Move to new line to prevent word wrapping at edge of screen
                action_words_print(engine,"\n",0);
                line_characters=0;
            }
            else
            {
                if (first_word==false)
                {
                    //Space between printed words but not before very first word
                    action_words_print(engine," ",0);
                    line_characters++;
                }
            }
            first_word=false;

            //Print out word
            action_words_print(engine,word_name,word_color);
            line_characters+=word_len;
        }
    }

    //Update screen
    if (engine->update_screen!=NULL) engine->update_screen();
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

