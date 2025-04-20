#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compatibility.h"
#include "error.h"
#include "forth.h"
#include "getkey.h"
#include "graphics.h"
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
    return -1;
}

static uint8_t *find_secondary(const char *word)
{
    if (!strcmp(word,"foo")) return (uint8_t *)1;
    else return NULL;
}

static int32_t next_word(struct ConsoleInfo *console,int32_t *start)
{
    int parse_state=FORTH_PARSE_NONE;
    int len=0;
    for (int32_t i=*start;i<console->input.len;i++)
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

static void color_input(struct ConsoleInfo *console,bool color_highlighted)
{
    int32_t start=console->input.start;
    int32_t word_len=0;
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

        //Copy word to buffer for classification
        char word_buffer[FORTH_WORD_MAX+1];
        for (int32_t j=start;j<start+word_len;j++)
        {
            word_buffer[j-start]=console->input.text[j].character;
            word_buffer[j-start+1]=0;
        }

        //Figure out what color to use for word
        color_t word_color;
        if (in_quote)
        {
            //In quote like s" or ."
            word_color=FORTH_COL_STRING;
            if (word_buffer[word_len-1]=='"') in_quote=false;
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
                    else if (find_primitive(word_buffer)!=-1)
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
    uint8_t *forth_definitions;
    uint8_t *forth_code;

    if (command_ID==COMMAND_START) 
    {
        //Allocate memory for console and Forth systems
        forth=(struct ForthInfo *)add_object(sizeof(struct ForthInfo),heap_ptr);

        //Make sure allocation succeeded
        if (forth==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Allocate space for Forth words
        forth_definitions=add_object(sizeof(struct ForthWordHeader),heap_ptr);

        //Make sure allocation succeeded
        if (forth==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //First definition is empty marking end of definitions
        ((struct ForthWordHeader *)forth_definitions)->size=0;
        //TODO: remove
        ((struct ForthWordHeader *)forth_definitions)->name_len=42;

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

        //Init Forth Engine (these values don't change when program is reloaded)
        forth->engine.stack_upper=(int32_t *)FORTH_STACK_ADDRESS;
        forth->engine.stack=(int32_t *)(FORTH_STACK_ADDRESS+FORTH_STACK_SIZE-FORTH_CELL_SIZE);
        forth->engine.rstack_upper=(int32_t *)FORTH_RSTACK_ADDRESS;
        forth->engine.rstack=(int32_t *)(FORTH_RSTACK_ADDRESS+FORTH_RSTACK_SIZE-FORTH_CELL_SIZE);
    }
    else
    {
        //Resume or Redraw - reuse existing memory for console
        forth=(struct ForthInfo *)object_address(FORTH_ID_CONSOLE,heap_ptr);
        console=&forth->console;
        reset_console_pointers(console);

        //Restore pointer to Forth definitions
        forth_definitions=object_address(FORTH_ID_DEFINITIONS,heap_ptr);

        //Restore stack memory
        memcpy(FORTH_STACK_ADDRESS,forth->stack_copy,FORTH_STACK_SIZE);
        memcpy(FORTH_RSTACK_ADDRESS,forth->rstack_copy,FORTH_RSTACK_SIZE);
    }

    //Reset pointers in Forth object
    forth->engine.data=forth->data;

    //Redraw screen but only spare pixels on edges. Letters redrawn below.
    draw_rect(pos.x,pos.y,width,height,FORTH_COL_BG,FORTH_COL_BG);

    //Set position based on split location
    init_position(console,pos,window.split_state);

    //Main loop
    bool redraw_screen=true;
    bool redraw_modifier=true;
    while (1)
    {
        //Set text for input line
        if (console->reset_input)
        {
            console->input.text[0].character=0;
            console->input.start=0;
            console->input.cursor=0;
            console->input.len=0;
            add_input_text(FORTH_PROMPT,FORTH_COL_FG,FORTH_COL_BG,true,console);
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
                
            //Return if Redraw only
            if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;
        }

        //Copy updates to screen if modifier keys or text have changed
        if ((redraw_screen)||(redraw_modifier)) dupdate();
        redraw_screen=true;
        
        //Get key
        int old_modifier=console->modifier;
        int key=getkey_text(true,&console->modifier);

        //Remap keys for characters not on keypad
        if (key==VKEY_COS) key=VKEY_COLON;
        else if (key==VKEY_TAN) key=VKEY_SEMICOLON;

        //Redraw modifiers (shift, alpha) next time through if they have changed
        if (old_modifier!=console->modifier) redraw_modifier=true;
        else redraw_modifier=false;

        //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
        char character=vkey_printable[key];
        if (character!=0)
        {
            //Printable character - add to input line
            add_input_char(character,FORTH_COL_FG,FORTH_COL_BG,false,console);
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
                    if (console->input.len==console->input.start)
                    {
                        //No input on line - don't cancel
                        break;
                    }
                    
                    //Append ^C to show input cancelled
                    const char *cancel_text="^C";
                    if (console->input.len>=FORTH_INPUT_MAX-(int)strlen(cancel_text))
                    {
                        //Not enough room to append ^C so drop characters from end of input to make room
                        console->input.len=FORTH_INPUT_MAX-strlen(cancel_text)-1;
                        console->input.cursor=FORTH_INPUT_MAX-strlen(cancel_text)-1;
                    }
                    add_input_text(cancel_text,FORTH_COL_FG,FORTH_COL_BG,false,console);

                    //Fallthrough
                case VKEY_EXE:
                    //Color input before copying to console since secondaries previously not colored if cursor is on them
                    color_input(console,true);

                    //Copy input text to console
                    for (int i=0;i<console->input.len;i++)
                    {
                        console_char(console->input.text[i].character,console->input.text[i].fg,console->input.text[i].bg,console);
                    }
                    console_char('\n',0,0,console);
                    console->reset_input=true;

                    //Process input if EXE pressed (just copy input if ESC)
                    if (key==VKEY_EXE)
                    {
                        //Add input to history
                        add_history(console);
                        
                        //Process input
                        char input_buffer[FORTH_INPUT_MAX];
                        copy_console_text(&console->input,input_buffer,FORTH_INPUT_MAX,console->input.start);

                        /*
                        int return_code=
                        if (return_code!=COMMAND_NONE)
                        {
                            //Return to window manager to process any return code such as closing console
                            return return_code;
                        }
                        */
                    }
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
                    history_key(console,key);
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

