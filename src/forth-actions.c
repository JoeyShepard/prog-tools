#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "forth.h"
#include "forth-engine.h"
#include "forth-process.h"
#include "forth-primitives.h"
#include "mem.h"

int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,struct CompileInfo *compile)
{
    uint32_t prior_start=*start;
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len=next_word_source(source,start);
    if (word_len>FORTH_WORD_MAX)
    {
        //Error - word of source is longer than allowed
        //Point to word for error message in caller
        *compile->error_word=source+*start;
        return FORTH_ERROR_TOO_LONG;
    }
    else if (word_len==0)
    {
        //Error - no word name after :
        *compile->error_word=source+prior_start-compile->word_len;
        *start=prior_start;
        return FORTH_ERROR_NO_WORD;
    }

    //Make sure name of new word is not primitive or number
    strncpy(word_buffer,source+*start,word_len);
    word_buffer[word_len]=0;
    int word_type=classify_word(word_buffer);
    if (word_type==FORTH_TYPE_OTHER)
        word_type=classify_other(word_buffer,compile);

    //Advance past name of new word
    *start+=word_len;

    //Save address of word header created by colon since other headers may be added before definition is closed
    compile->colon_word=(struct ForthWordHeader *)((*compile->word_IDs)->data+(*compile->word_IDs)->index);

    if (word_type==FORTH_TYPE_SECONDARY)
    {
        //Word already exists - delete existing word and update pointers to code
        //TODO
    }
    else if (word_type==FORTH_TYPE_NOT_FOUND)
    {
        //Word not found - create new header

        printf("Colon:\n");
        printf("- address: %p\n",(*compile->word_IDs)->data+(*compile->word_IDs)->index);
        printf("- index: %d\n",(*compile->word_IDs)->index);
        printf("- bytes_left: %d\n",(*compile->word_IDs)->bytes_left);
        printf("\n");

        //Create word header for new word
        int result=new_secondary(word_buffer,FORTH_SECONDARY_WORD,compile);
        if (result!=FORTH_ERROR_NONE) return result;

        printf("Created new definition: %s\n",word_buffer);
        printf("- test value: 0x%X\n",**(uint32_t **)compile->control_stack);
        printf("- bytes left: %d\n",(*compile->word_IDs)->bytes_left);
        printf("\n");
    }
    else
    {
        //Error - name of defined word can't be number or primitive
        *compile->error_word=source+*start;
        return FORTH_ERROR_INVALID_NAME;
    }

    //Set compile state to compiling
    engine->state=FORTH_STATE_COMPILE;

    return FORTH_ERROR_NONE;
}

int action_semicolon(struct ForthEngine *engine,struct CompileInfo *compile)
{
    //Add primitive to word to stop exectuing
    int result=write_definition_primitive(&prim_hidden_done,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Start at word defined by colon and mark all words as done
    struct ForthWordHeader *secondary=compile->colon_word;

    //Mark header for word and any other headers created in word as done
    while(secondary->last==false)
    {

        printf("Marking %s as done\n",secondary->name);

        secondary->done=true;
        secondary=(struct ForthWordHeader *)((uint8_t *)secondary+secondary->header_size);
    }

    //Set compile state back to interpret
    engine->state=FORTH_STATE_INTERPRET;

    return FORTH_ERROR_NONE;
}

int action_char_common(const char *source,uint32_t *start,int32_t *index,struct CompileInfo *compile)
{
    //Save index in case needed for error message
    uint32_t prior_start=*start;

    //Find next word in source
    uint32_t word_len=next_word_source(source,start);
    if (word_len==0)
    {
        //No word after CHAR
        *compile->error_word=source+prior_start-compile->word_len;
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

void action_words(struct ForthEngine *engine,struct ForthWordIDsInfo *word_IDs)
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
    struct ForthWordHeader *secondary=(struct ForthWordHeader *)(word_IDs->data);
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
                    secondary=(struct ForthWordHeader *)((uint8_t *)secondary+secondary->header_size);
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

int action_tick_common(const char *source,uint32_t *start,uint32_t *index,struct CompileInfo *compile)
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
        *compile->error_word=source+*start;
        return FORTH_ERROR_TOO_LONG;
    }
    else if (word_len==0)
    {
        //Error - no word name after '
        *compile->error_word=source+prior_start-compile->word_len;
        *start=prior_start;
        return FORTH_ERROR_NO_WORD;
    }
    //Make sure name of new word is not primitive or number
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
        *compile->error_word=source+*start;
        return FORTH_ERROR_INVALID_NAME;
    }
}

