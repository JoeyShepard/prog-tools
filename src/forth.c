#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compatibility.h"
#include "error.h"
#include "forth.h"
#include "forth-compatibility.h"
#include "forth-engine.h"
#include "getkey.h"
#include "graphics.h"
#include "key-remap.h"
#include "text.h"
#include "manager.h"
#include "mem.h"
#include "structs.h"

//Tables
static const char *quote_words[]=
{
    ".\"",
    "S\"",
    "S\\\""
};


//Functions

//TODO: table look up if this is too slow
static int classify_char(char c)
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

static int classify_word(const char *word)
{
    int text_type=FORTH_TYPE_NONE;
    while(*word)
    {
        int char_class=classify_char(*word);
        switch(text_type)
        {
            case FORTH_TYPE_NONE:
                if (char_class==FORTH_CHAR_MINUS) text_type=FORTH_TYPE_MINUS;
                else if (char_class==FORTH_CHAR_0) text_type=FORTH_TYPE_0;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_TYPE_NUMBER;
                else if (char_class==FORTH_CHAR_A_F) text_type=FORTH_TYPE_OTHER;
                else if (char_class==FORTH_CHAR_G_Z) text_type=FORTH_TYPE_OTHER;
                else if (char_class==FORTH_CHAR_x) text_type=FORTH_TYPE_OTHER;
                else if (char_class==FORTH_CHAR_OTHER) text_type=FORTH_TYPE_OTHER;
                break;
            case FORTH_TYPE_NUMBER:
                if (char_class==FORTH_CHAR_0) text_type=FORTH_TYPE_NUMBER;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_TYPE_NUMBER;
                else text_type=FORTH_TYPE_OTHER;
                break;
            case FORTH_TYPE_HEX: 
                if (char_class==FORTH_CHAR_0) text_type=FORTH_TYPE_HEX;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_TYPE_HEX;
                else if (char_class==FORTH_CHAR_A_F) text_type=FORTH_TYPE_HEX;
                else text_type=FORTH_TYPE_OTHER;
                break;
            case FORTH_TYPE_MINUS:
                if (char_class==FORTH_CHAR_0) text_type=FORTH_TYPE_0;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_TYPE_NUMBER;
                else text_type=FORTH_TYPE_OTHER;
                break;
            case FORTH_TYPE_0:        
                if (char_class==FORTH_CHAR_x) text_type=FORTH_TYPE_0x;
                else text_type=FORTH_TYPE_OTHER;
                break;
            case FORTH_TYPE_0x:       
                if (char_class==FORTH_CHAR_0) text_type=FORTH_TYPE_HEX;
                else if (char_class==FORTH_CHAR_1_9) text_type=FORTH_TYPE_HEX;
                else if (char_class==FORTH_CHAR_A_F) text_type=FORTH_TYPE_HEX;
                else text_type=FORTH_TYPE_OTHER;
                break;
            case FORTH_TYPE_OTHER:       
                //No changes - always stays same type
                break;
        }
        word++;
    }

    switch (text_type)
    {
        case FORTH_TYPE_NUMBER:
        case FORTH_TYPE_HEX:
        case FORTH_TYPE_NONE:
        case FORTH_TYPE_OTHER:
            return text_type;
        case FORTH_TYPE_MINUS:
        case FORTH_TYPE_0x:
            return FORTH_TYPE_OTHER;
        case FORTH_TYPE_0:
            return FORTH_TYPE_NUMBER;
        default:
            //Should not be possible but just in case
            return FORTH_TYPE_NONE;
    }
}

static int find_primitive(const char *word)
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

static uint8_t *find_secondary(const char *word)
{
    if (!strcmp(word,"foo")) return (uint8_t *)1;
    else return NULL;
}

//Don't combine with classify_word! Need result of find_primitive or find_secondary in some cases
static int classify_other(const char *word)
{
    if (find_primitive(word)!=FORTH_PRIM_NOT_FOUND) return FORTH_TYPE_PRIMITIVE;
    else if (find_secondary(word)!=NULL) return FORTH_TYPE_SECONDARY;
    else return FORTH_TYPE_NOT_FOUND;
}

static uint32_t next_word(struct ConsoleInfo *console,uint32_t *start)
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

static uint32_t next_word_source(const char *source,uint32_t *start)
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

static void color_input(struct ConsoleInfo *console,bool color_highlighted)
{
    uint32_t start=0;
    uint32_t word_len=0;
    bool in_quote=false;
    bool in_word=false;
    bool colon_last=false;
    bool colon_current=false;
    while(1)
    {
        //Get next word in input
        start+=word_len;
        word_len=next_word(console,&start);

        //Stop looping if no words left
        if (word_len==0) break;

        //Figure out what color to use for word
        color_t word_color;
        if (in_quote)
        {
            //In quote like s" or ."
            word_color=FORTH_COL_STRING;
            if (console->input.text[start+word_len-1].character=='"') in_quote=false;
        }
        else
        {
            if (word_len>FORTH_WORD_MAX)
            {
                //Word too long - color but do not check if primitive or secondary
                word_color=FORTH_COL_ERROR;   
            }
            else
            {
                //Copy word to buffer for classification
                char word_buffer[FORTH_WORD_MAX+1];
                for (uint32_t j=start;j<start+word_len;j++)
                {
                    word_buffer[j-start]=console->input.text[j].character;
                    word_buffer[j-start+1]=0;
                }

                //Classify word
                int word_type=classify_word(word_buffer);
                if ((word_type!=FORTH_TYPE_OTHER)&&(colon_last==true))
                {
                    //Name in colon definition can't be number 
                    word_color=FORTH_COL_ERROR;
                }
                else if (word_type==FORTH_TYPE_NUMBER) word_color=FORTH_COL_NUMBER;
                else if (word_type==FORTH_TYPE_HEX) word_color=FORTH_COL_HEX;
                else if (word_type==FORTH_TYPE_OTHER)
                {
                    if (!strcmp(word_buffer,":"))
                    {
                        //Handle : different from other primitives
                        if (in_word)
                        {
                            //Not allowed in definition
                            word_color=FORTH_COL_ERROR;
                        }
                        else
                        {
                            in_word=true;
                            word_color=FORTH_COL_DEF;
                            colon_current=true;
                        }
                    }
                    else if (!strcmp(word_buffer,";"))
                    {
                        //Handle ; different from other primitives
                        if (in_word)
                        {
                            in_word=false;
                            word_color=FORTH_COL_DEF;
                        }
                        else
                        {
                            //Not allowed outside of definition
                            word_color=FORTH_COL_ERROR;
                        }
                    }
                    else if (find_primitive(word_buffer)!=FORTH_PRIM_NOT_FOUND)
                    {
                        //Always color primitives
                        if (colon_last)
                        {
                            //Primitive can't be word name after colon
                            word_color=FORTH_COL_ERROR;
                        }
                        else
                        {
                            //Default color for primitives
                            word_color=FORTH_COL_PRIMITIVE;

                            //Start quoted string if word found
                            for (int i=0;i<ARRAY_SIZE(quote_words);i++)
                            {
                                if (!strcasecmp(word_buffer,quote_words[i]))
                                {
                                    in_quote=true;
                                    word_color=FORTH_COL_STRING;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        //Word is not primitive
                        bool cursor_on_word=(console->input.cursor>=start)&&(console->input.cursor<=start+word_len);
                        if ((cursor_on_word)&&(color_highlighted==false))
                        {
                            //Cursor is on secondary word - don't color as unknown since still typing
                            word_color=FORTH_COL_TYPING;
                        }
                        else 
                        {
                            if (find_secondary(word_buffer)!=NULL)
                            {
                                //Secondary found
                                word_color=FORTH_COL_SECONDARY;
                            }
                            else
                            {
                                if (colon_last)
                                {
                                    //Name of word definition;
                                    word_color=FORTH_COL_NEW_WORD;
                                }
                                else
                                {
                                    //Unknown word
                                    word_color=FORTH_COL_NOT_FOUND;
                                }
                            }
                        }
                    }
                }
                else if (word_type==FORTH_TYPE_NONE)
                {
                    //Should never happen but just in case
                    word_color=FORTH_COL_NONE;
                }
            }
        }

        //Logic to color definition name after colon
        colon_last=colon_current;
        colon_current=false;
    
        //Apply color to word
        for (int j=start;j<start+word_len;j++)
        {
            console->input.text[j].fg=word_color;
        }
    }
}

static int32_t int32_text(const char *word_buffer)
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

static int32_t hex32_text(const char *word_buffer)
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

static int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,const char **error_word)
{
    char word_buffer[FORTH_WORD_MAX+1];
    uint32_t word_len=next_word_source(source,start);
    if (word_len>FORTH_WORD_MAX)
    {
        //Error - word of source is longer than allowed
        //Point to word for error message in caller
        *error_word=source+*start;
        return FORTH_ERROR_TOO_LONG;
    }
    else if (word_len==0)
    {
        //Error - no word name after :
        return FORTH_ERROR_COLON_NO_WORD;
    }
    //Make sure name of new word is not primitive or number
    strncpy(word_buffer,source+*start,word_len);
    word_buffer[word_len]=0;
    int word_type=classify_word(word_buffer);
    if (word_type==FORTH_TYPE_OTHER)
        word_type=classify_other(word_buffer);

    
    //TODO: switch from classify_other to find_secondary

    if ((word_type!=FORTH_TYPE_SECONDARY)&&(word_type!=FORTH_TYPE_NOT_FOUND))
    {
        //Error - name of new word can't be number or primitive
        *error_word=source+*start;
        return FORTH_ERROR_COLON_NAME;
    }
    //Advance past name of new word
    *start+=word_len;

    printf("New definition: %s\n",word_buffer);

    engine->state=FORTH_STATE_COMPILE;

    return FORTH_ERROR_NONE;
}


static int32_t action_char_common(const char *source,uint32_t *start)
{
    //Find next word in source
    uint32_t word_len=next_word_source(source,start);
    if (word_len==0)
    {
        //Word not found
        return 0;
    }
    else
    {
        //Return first character of word
        uint8_t ret_val=*(uint8_t*)(source+*start);
        //Advance to next word
        *start+=word_len;
        return ret_val;
    }
}


static void action_paren(const char *source,uint32_t *start)
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

static int process_source(struct ForthEngine *engine,const char *source,const char **error_word,
                            struct DefinitionsInfo *definitions,uint8_t *word_IDs,uint8_t *control_stack)
{
    uint32_t word_len;
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
            uint8_t *secondary_ptr;
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
                //Can't replace with class_other since primitive_ID and secondary_ptr used below
                primitive_ID=find_primitive(word_buffer);
                if (primitive_ID!=-1)
                {
                    //Word is primitive
                    word_type=FORTH_TYPE_PRIMITIVE;
                }
                else
                {
                    secondary_ptr=find_secondary(word_buffer);
                    if (secondary_ptr!=NULL)
                    {
                        //Word is secondary
                        word_type=FORTH_TYPE_SECONDARY;
                    }
                    else
                    {
                        //Word not primitve or secondary - not found
                        word_type=FORTH_TYPE_NOT_FOUND;
                    }
                }
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
                        engine->word_action=FORTH_ACTION_NONE;
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
                                int result=action_colon(engine,source,&start,error_word);
                                if (result!=FORTH_ERROR_NONE) return result;
                                break;
                            case FORTH_ACTION_CHAR:
                                forth_push(engine,action_char_common(source,&start));
                                break;
                            case FORTH_ACTION_PAREN:
                                action_paren(source,&start);
                                break;
                        }
                    }
                    else
                    {
                        //No special immediate behavior - execute body
                        void (*body)(struct ForthEngine *engine)=forth_primitives[primitive_ID].body;
                        if (body!=NULL) body(engine);
                    }
                }
                else if (word_type==FORTH_TYPE_NOT_FOUND)
                {
                    //Error - word not found
                    //Point to unknown word for error message in caller
                    *error_word=source+start-word_len;
                    return FORTH_ERROR_NOT_FOUND;
                }
            }
            else if (engine->state==FORTH_STATE_COMPILE)
            {
                //Compile mode
                if ((word_type==FORTH_TYPE_NUMBER)||(word_type==FORTH_TYPE_HEX))
                {
                    //Number or hex - compile to dictionary
                    printf("Compile number: %d\n",num);
                }
                else if (word_type==FORTH_TYPE_PRIMITIVE)
                {
                    //Primitive
                    int (*compile)(struct ForthEngine *engine)=forth_primitives[primitive_ID].compile;
                    if (compile!=NULL)
                    {
                        //Primitive has special compile behavior
                        //TODO: do any compile functions return error? moved compiling functions here
                        engine->word_action=FORTH_ACTION_NONE;
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
                                engine->state=FORTH_STATE_INTERPRET;
                                break;
                        }
                    }
                    else
                    {
                        //No special compile behavior - compile address
                        //forth_primitives[primitive_ID].body;
                        printf("Compile primitive: %s\n",word_buffer);
                    }
                }
                else if (word_type==FORTH_TYPE_SECONDARY)
                {
                    //Compile pointer to pointer to secondary
                    printf("Compile secondary\n");
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

static void draw_forth_stack(struct ForthEngine *engine,int x,int y,int text_x,int text_y,int height,int window_state)
{
    //Text buffer to output stack count and stack values (ie "0:12345678")
    char text_buffer[sizeof("x:xxxxxxxx")];

    //Gray background to left of console window
    draw_rect(x,y,FORTH_STACK_WIDTH,height,FORTH_STACK_BORDER,FORTH_STACK_BG);

    //Print out Stack title and stack count
    struct Point pos={text_x,text_y};
    pos=draw_text("Stack[",pos,FORTH_STACK_FG,COL_TRANS,false,FONT_5x8);

    //Stack count should always be less than 256 but limit anyway since only space for three characters on screen
    uint8_t stack_count=forth_stack_count(engine);
    text_int32(stack_count,text_buffer);
    pos=draw_text(text_buffer,pos,FORTH_STACK_FG,COL_TRANS,false,FONT_5x8);
    pos=draw_text("]",pos,FORTH_STACK_FG,COL_TRANS,false,FONT_5x8);

    //Print stack values
    pos.x=text_x;
    pos.y+=CONS_ROW_HEIGHT;
    text_buffer[1]=':';
    for (int i=0;i<FORTH_STACK_SHOW_COUNT;i++)
    {
        int index=FORTH_STACK_SHOW_COUNT-i-1;
        text_buffer[0]=index+'0';
        if (index<stack_count)
        {
            //Stack value to print
            text_hex32(*(engine->stack+index+1),text_buffer+2,8);
        }
        else
        {
            //Out of stack values - print placeholder instead
            strcpy(text_buffer+2," --     ");
        }

        //Color every other row of stack values slightly darker
        color_t color;
        if ((i&1)==0) color=FORTH_STACK_BG;
        else color=FORTH_STACK_BG2;
        pos=draw_text(text_buffer,pos,FORTH_STACK_FG,color,false,FONT_5x8);

        //Advance to next stack value
        pos.y+=CONS_ROW_HEIGHT;
        pos.x=text_x;
    }

    //Bottom line of last stack value is one pixel too tall so overwrite to match the others.
    draw_line_horz(x,x+FORTH_STACK_WIDTH-1,pos.y,FORTH_STACK_BG);

    //If full screen, fill remaining space with key legend and typing suggestion
    if (window_state==WINDOW_WHOLE)
    {
        //Small gap after stack display so easier to see
        pos.y+=FORTH_LEGEND_OFFSET1;
        
        //Key legend
        const struct KeyText
        {
            const char *key;
            const char *remapped_key;
            const color_t color;
        }key_texts[]={
        {"radian  ","!",COL_ALPHA},
        {"theta   ","@",COL_ALPHA},
        {"ln      ","'",FORTH_COL_FG},
        {"sin     ","?",FORTH_COL_FG},
        {"cos     ",":",FORTH_COL_FG},
        {"tan     ",";",FORTH_COL_FG},
        {"i       ","<",COL_SHIFT},
        {"pi      ",">",COL_SHIFT}};

        for (int i=0;i<ARRAY_SIZE(key_texts);i++)
        {
            pos=draw_text(key_texts[i].key,pos,key_texts[i].color,-1,false,FONT_5x8);
            draw_text(key_texts[i].remapped_key,pos,FORTH_STACK_FG,-1,false,FONT_5x8);
            pos.y+=CONS_ROW_HEIGHT;
            pos.x=text_x;
        }

        //Typing suggestion
        pos.y+=FORTH_LEGEND_OFFSET2;
        pos=draw_char(CHAR_RIGHT_ARROW,pos,FORTH_COL_FG,-1,false,FONT_5x8);
        draw_text(" for word",pos,FORTH_COL_FG,-1,false,FONT_5x8);
        pos.y+=FORTH_SUGGESTION_ROW_HEIGHT;
        pos.x=text_x;
        draw_text("ACCEPT",pos,FORTH_COL_PRIMITIVE,FORTH_STACK_BG,true,FONT_5x8);
        pos.y+=FORTH_SUGGESTION_ROW_HEIGHT;
        pos.x=text_x;
        draw_text("ALIGN",pos,FORTH_COL_PRIMITIVE,-1,false,FONT_5x8);
        pos.y+=FORTH_SUGGESTION_ROW_HEIGHT;
        pos.x=text_x;
        draw_text("ALIGNED",pos,FORTH_COL_PRIMITIVE,FORTH_STACK_BG,true,FONT_5x8);
    }
}

int forth(int command_ID, struct WindowInfo *windows, int selected_window)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct Point pos;
    int drawn_split;
    if (command_ID==COMMAND_REDRAW)
    {
        //Split being drawn for REDRAW is the split that isn't selected so invert split number
        drawn_split=window.selected_split^1;
        pos=window_pos(window,false);
    }
    else
    {
        drawn_split=window.selected_split;
        pos=window_pos(window,true);
    }

    //Heap memory
    select_heap(window.tab_index,drawn_split);
    uint8_t *heap_ptr=get_split_heap();

    //Pointers to data on heap
    struct ForthInfo *forth;
    struct ConsoleInfo *console;
    struct DefinitionsInfo *forth_definitions;
    uint8_t *forth_word_IDs;
    uint8_t *forth_control_stack;

    if (command_ID==COMMAND_START) 
    {
        //Allocate memory for console and Forth system
        forth=(struct ForthInfo *)add_object(sizeof(struct ForthInfo),heap_ptr);

        //Make sure allocation succeeded
        if (forth==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Allocate space for Forth word definitions
        forth_definitions=(struct DefinitionsInfo *)add_object(FORTH_MEM_DEFINITIONS,heap_ptr);

        //Make sure allocation succeeded
        if (forth_definitions==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Initialize empty definition list
        forth_definitions->index=0;
        forth_definitions->bytes_left=FORTH_MEM_DEFINITIONS-sizeof(struct DefinitionsInfo);

        //Allocate space for list of word IDs
        forth_word_IDs=add_object(FORTH_MEM_WORD_IDS,heap_ptr);

        //Make sure allocation succeeded
        if (forth_word_IDs==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //First definition is empty marking end of definitions
        ((struct ForthWordHeader *)forth_word_IDs)->size=0;

        //Allocate space for control stack
        forth_control_stack=add_object(FORTH_MEM_CONTROL_STACK,heap_ptr);

        //Make sure allocation succeeded
        if (forth_control_stack==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Init console
        console=&forth->console;
        init_console(
            //Console
            console,
            FORTH_COL_FG,
            FORTH_COL_BG,
            //Input
            forth->input_text,
            forth->input_copy_text,
            FORTH_INPUT_MAX,
            FORTH_COL_FG,
            FORTH_COL_BG,
            //History
            forth->history,
            forth->history_texts,
            FORTH_HIST_COUNT);
        reset_console_pointers(console);
        reset_console(console);

        //Init input
        console_text_default(FORTH_CONSOLE_STRING,console);
        console->reset_input=true;
        console->modifier=MODIFIER_ALPHA_LOWER_LOCK;
        console->input_copied=false;

        //Init history
        init_history(console);

        //Init Forth window
        forth->draw_stack=true;

        //Init Forth engine 
        forth_init_engine(&forth->engine,
            (uintptr_t)FORTH_STACK_ADDRESS,
            (uintptr_t)FORTH_RSTACK_ADDRESS,
            FORTH_STACK_ELEMENTS,
            FORTH_RSTACK_ELEMENTS,
            FORTH_DATA_SIZE,
            forth_print,
            forth_print_color,
            forth_input,
            forth_getkey,
            forth_printable,
            forth_update_screen,
            forth_update_modifiers,
            forth_clear_console,
            FORTH_MAX_SPACES,
            CONS_WHOLE_WIDTH-FORTH_STACK_CHAR_WIDTH,
            CONS_WHOLE_HEIGHT,
            FORTH_COL_PRIMITIVE);
    }
    else
    {
        //Resume or Redraw - reuse existing memory for console
        forth=(struct ForthInfo *)object_address(FORTH_ID_CONSOLE,heap_ptr);
        console=&forth->console;
        reset_console_pointers(console);

        //Restore pointers to word definitions and ID list
        forth_definitions=(struct DefinitionsInfo *)object_address(FORTH_ID_DEFINITIONS,heap_ptr);
        forth_word_IDs=object_address(FORTH_ID_WORD_IDS,heap_ptr);

        //Restore stack memory
        memcpy(FORTH_STACK_ADDRESS,forth->stack_copy,FORTH_STACK_SIZE);
        memcpy(FORTH_RSTACK_ADDRESS,forth->rstack_copy,FORTH_RSTACK_SIZE);
    }

    //Compatibility layer settings
    forth_console=console;

    //Reset pointers in Forth engine
    forth_reload_engine(&forth->engine,forth->data);

    //Redraw screen but only spare pixels on edges. Letters redrawn below.
    draw_rect(pos.x,pos.y,width,height,FORTH_COL_BG,FORTH_COL_BG);

    //Set position based on split location
    init_position(console,pos,window.split_state);

    //Display stack if split vertically or no split but not if split horizontally
    bool draw_stack;
    int stack_x,stack_y;
    int stack_text_x;
    int stack_text_y;
    if (((window.split_state==WINDOW_VSPLIT)||(window.split_state==WINDOW_WHOLE))&&(forth->draw_stack))
    {
        stack_x=pos.x;
        stack_y=pos.y;
        stack_text_x=pos.x;
        stack_text_y=console->y;
        console->x+=FORTH_STACK_WIDTH+FORTH_STACK_CONSOLE_X_OFFSET;
        console->width-=FORTH_STACK_CHAR_WIDTH;
        draw_stack=true;
    }
    else draw_stack=false;

    //Main loop
    bool redraw_screen=true;
    bool redraw_modifier=true;
    while (1)
    {
        //Set text for input line
        if (console->reset_input)
        {
            console->input.text[0].character=0;
            console->input.cursor=0;
            console->input.len=0;
            
            //add_input_text(FORTH_PROMPT,FORTH_COL_FG,FORTH_COL_BG,true,console);
            console_text(FORTH_PROMPT,FORTH_COL_FG,FORTH_COL_BG,console);

            console->input_copied=false;
        }
        console->reset_input=false;

        //Redraw modifiers (shift, alpha) as necessary even if rest of screen not redrawn
        if (redraw_modifier) draw_modifier(console->modifier);

        if (redraw_screen)
        {
            //Color code input
            color_input(console,false);

            //Always redraw screen whether START, RESUME, or REDRAW
            draw_console(console);

            //Redraw stack if visible
            if (draw_stack)
            {
                draw_forth_stack(&forth->engine,stack_x,stack_y,stack_text_x,stack_text_y,height,window.split_state);
            }
                
            //Return if Redraw only
            if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;
        }

        //Copy updates to screen if modifier keys or text have changed
        if ((redraw_screen)||(redraw_modifier)) dupdate();
        redraw_screen=true;
        
        //Get key
        int old_modifier=console->modifier;
        int key=getkey_text(true,&console->modifier,forth_keys);

        //Remap keys on keypad for Forth. Also, recognize PC keyboard keys for testing.
        key=forth_key_remap(key);
        
        //Redraw modifiers (shift, alpha) next time through if they have changed
        if (old_modifier!=console->modifier) redraw_modifier=true;
        else redraw_modifier=false;

        //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
        char character=vkey_printable[key];
        if (character!=0)
        {
            //Printable character - add to input line
            add_input_char(character,FORTH_COL_FG,FORTH_COL_BG,console);
        }
        else
        {
            switch (key)
            {
                case VKEY_QUIT: //Shift+EXIT
                    //Exit and return to window manager
                    return COMMAND_EXIT;
                    break;
                case VKEY_EXIT:
                    //Clear line but do not exit program
                    //Handle here so not picked up by sys_key_handler below which would exit program
                    if (console->input.len==0)
                    {
                        //No input on line - don't cancel
                        break;
                    }
                    
                    //Color line before ^C added
                    color_input(console,true);

                    //Append ^C to show input cancelled
                    const char *cancel_text="^C";
                    if (console->input.len>=FORTH_INPUT_MAX-(int)strlen(cancel_text))
                    {
                        //Not enough room to append ^C so drop characters from end of input to make room
                        console->input.len=FORTH_INPUT_MAX-strlen(cancel_text)-1;
                        console->input.cursor=FORTH_INPUT_MAX-strlen(cancel_text)-1;
                    }
                    add_input_text(cancel_text,FORTH_COL_FG,FORTH_COL_BG,console);

                    //Copy input text to console
                    for (int i=0;i<console->input.len;i++)
                    {
                        console_char(console->input.text[i].character,console->input.text[i].fg,console->input.text[i].bg,console);
                    }
                    console->reset_input=true;
                    
                    //Newline after cancelled input
                    console_text_default(" \n",console);
                    break;
                case VKEY_EXE:
                    //Only process if text exists
                    if (console->input.len==0) break;

                    //Color input before copying to console since secondaries previously not colored if cursor is on them
                    color_input(console,true);

                    //Copy input text to console
                    for (int i=0;i<console->input.len;i++)
                    {
                        console_char(console->input.text[i].character,console->input.text[i].fg,console->input.text[i].bg,console);
                    }
                    console->reset_input=true;

                    //Add input to history
                    add_history(console);
                    
                    //Hide input line since program may output to console
                    console_text_default(" ",console);
                    console->input.visible=false;
                    draw_console(console);
                    dupdate();

                    //Process input
                    char input_buffer[FORTH_INPUT_MAX];
                    copy_console_text(&console->input,input_buffer,FORTH_INPUT_MAX,0);
                    const char *error_word;
                    int process_result=process_source(&forth->engine,input_buffer,&error_word,
                        forth_definitions,forth_word_IDs,forth_control_stack);
                    console->input.visible=true;
                    console_text_default("\n",console);

                    //Process errors from processing source
                    switch (process_result)
                    {
                        case FORTH_ERROR_NONE:
                            //No error - nothing to do
                            break;
                        case FORTH_ERROR_TOO_LONG:
                        case FORTH_ERROR_NOT_FOUND:
                        case FORTH_ERROR_COLON_NAME:
                            //All of these errors share code for printing out word that caused error
                            if (process_result==FORTH_ERROR_TOO_LONG)
                                console_text_default("Word too long: ",console);
                            else if (process_result==FORTH_ERROR_NOT_FOUND)
                                console_text_default("Undefined word: ",console);
                            else if (process_result==FORTH_ERROR_COLON_NAME)
                                console_text_default("Invalid name for word definition: ",console);
                            uint32_t start=0;
                            uint32_t word_len=next_word_source(error_word,&start);
                            for (uint32_t i=0;i<word_len;i++)
                                console_char_default(error_word[i],console);
                            console_text_default("\n",console);
                            break;
                        case FORTH_ERROR_ENGINE:
                            //Error set in Forth engine - ie inside of primitive
                            switch (forth->engine.error)
                            {
                                case FORTH_ENGINE_ERROR_NONE:
                                    //Should never happen but just in case
                                    console_text_default("Engine error but code not set\n",console);
                                    break;
                                case FORTH_ENGINE_ERROR_INTERPRET_ONLY:
                                case FORTH_ENGINE_ERROR_COMPILE_ONLY:
                                    if (forth->engine.error==FORTH_ENGINE_ERROR_INTERPRET_ONLY)
                                        console_text_default("Word is interpret only: ",console);
                                    else if (forth->engine.error==FORTH_ENGINE_ERROR_COMPILE_ONLY)
                                        console_text_default("Word is compile only: ",console);
                                    //All of these errors share code for printing out word that caused error
                                    uint32_t start=0;
                                    uint32_t word_len=next_word_source(error_word,&start);
                                    for (uint32_t i=0;i<word_len;i++)
                                        console_char_default(error_word[i],console);
                                    console_text_default("\n",console);
                                    break;
                                default:
                                    //No error message for error - should never reach here unless forgot to add error message
                                    console_text_default("Unhandled engine error: ",console);
                                    char num_buffer[TEXT_INT32_SIZE];
                                    text_int32(forth->engine.error,num_buffer);
                                    console_text_default(num_buffer,console);
                                    console_text_default("\n",console);
                                    break;
                            }
                            break;
                        case FORTH_ERROR_COLON_NO_WORD:
                            console_text_default("No name for word definition\n",console);
                            break;
                        default:
                            //No error message for error - should never reach here unless forgot to add error message
                            console_text_default("Unhandled error: ",console);
                            char num_buffer[TEXT_INT32_SIZE];
                            text_int32(process_result,num_buffer);
                            console_text_default(num_buffer,console);
                            console_text_default("\n",console);
                            break;
                    }

                    //TODO
                    //Error if still in compile state or after [
                    
                    break;
                case VKEY_UP:
                case VKEY_DOWN:
                case VKEY_LEFT:
                case VKEY_RIGHT:
                case VKEY_SHIFT_LEFT:
                case VKEY_SHIFT_RIGHT:
                case VKEY_UNDO:
                    //DEL with alpha active - treat as DEL so don't need to remove alpha to delete
                    //Fallthrough!
                case VKEY_DEL:
                    console_key(console,key);
                    break;
                default:
                    //Check for system keys like MENU, OFF, etc
                    int return_command=sys_key_handler(key);
                    if (return_command!=COMMAND_NONE)
                    {
                        //System key - save Forth stack memory before returning
                        memcpy(forth->stack_copy,FORTH_STACK_ADDRESS,FORTH_STACK_SIZE);
                        memcpy(forth->rstack_copy,FORTH_RSTACK_ADDRESS,FORTH_RSTACK_SIZE);

                        //Return to window manager to handle system key
                        return return_command;
                    }
                    else
                    {
                        //No key found - don't redraw screen
                        redraw_screen=false;
                    }
            }
        }
    }

    //Shouldn't reach here - added to silence warning
    return COMMAND_DONE;
}

