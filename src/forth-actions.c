#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "forth.h"
#include "forth-engine.h"
#include "forth-process.h"
#include "forth-primitives.h"
#include "mem.h"

static uint32_t align4(uint32_t value)
{
    return value+((4-value%4)%4);
}

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
    int primitive_ID;
    struct ForthWordHeader *secondary_ptr;
    if (word_type==FORTH_TYPE_OTHER)
        word_type=classify_other(word_buffer,compile);
    if ((word_type!=FORTH_TYPE_SECONDARY)&&(word_type!=FORTH_TYPE_NOT_FOUND))
    {
        //Error - name of new word can't be number or primitive
        *compile->error_word=source+*start;
        return FORTH_ERROR_INVALID_NAME;
    }

    //Advance past name of new word
    *start+=word_len;

    if (word_type==FORTH_TYPE_SECONDARY)
    {
        //TODO
        //Word already exists - delete existing word and update pointers
    }

    printf("Colon:\n");
    printf("- definitions.data: %p (%ld)\n",compile->definitions->data,(uintptr_t)(*compile->word_IDs)-(uintptr_t)compile->definitions->data);
    printf("  - bytes_left: %d\n",compile->definitions->bytes_left);
    printf("- word_IDs.data:    %p (%ld)\n",(*compile->word_IDs)->data,(uintptr_t)(*compile->control_stack)-(uintptr_t)(*compile->word_IDs)->data);
    printf("  - bytes_left: %d\n",(*compile->word_IDs)->bytes_left);
    printf("- control_stack:    %p\n",*compile->control_stack);

    //Expand word ID memory for new word if necessary
    struct ForthWordHeader *new_secondary=(struct ForthWordHeader *)((*compile->word_IDs)->data+(*compile->word_IDs)->index);
    //Need enough space for current header and empty header following
    if ((*compile->word_IDs)->bytes_left<sizeof(struct ForthWordHeader)*2+word_len+1)
    {
        
        printf("Allocating more word_IDs memory!\n");

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
    new_secondary->address=(void(**)())(compile->definitions->data+compile->definitions->index);
    new_secondary->offset=compile->definitions->index;
    new_secondary->definition_size=0;
    new_secondary->header_size=align4(sizeof(struct ForthWordHeader)+word_len+1);
    new_secondary->ID=compile->definitions->ID;
    new_secondary->type=FORTH_SECONDARY_WORD;
    new_secondary->name_len=word_len;
    strcpy(new_secondary->name,word_buffer);

    //Write next header with length 0 to indicate end of header list
    new_secondary=(struct ForthWordHeader *)((uint8_t *)new_secondary+new_secondary->header_size);
    new_secondary->header_size=0;

    printf("New definition: %s\n",word_buffer);
    printf("- test value: 0x%X\n",**(uint32_t **)compile->control_stack);
    printf("- bytes left: %d\n",(*compile->word_IDs)->bytes_left);
    printf("\n");

    //Set compile state to compiling
    engine->state=FORTH_STATE_COMPILE;

    return FORTH_ERROR_NONE;
}

int action_semicolon(struct ForthEngine *engine,struct CompileInfo *compile)
{

    printf("Semicolon\n");

    //Add primitive to word to stop exectuing
    int result=write_definition_primitive(&prim_hidden_done,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Point to next header which has 0 length header size to indicate end of header list
    struct ForthWordHeader *secondary=(struct ForthWordHeader *)((*compile->word_IDs)->data+(*compile->word_IDs)->index);
    (*compile->word_IDs)->index+=secondary->header_size;
    (*compile->word_IDs)->bytes_left-=secondary->header_size;

    //Advance to next ID in definitions
    compile->definitions->ID++;

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
                if (secondary->header_size==0)
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
    int primitive_ID;
    struct ForthWordHeader *secondary_ptr;
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
        *index=forth_primitives_len+compile->secondary_ptr->ID;
        return FORTH_ERROR_NONE;
    }
    else
    {
        //Error - can only get ID of primitive or secondary not number or anything else
        *compile->error_word=source+*start;
        return FORTH_ERROR_INVALID_NAME;
    }
}

