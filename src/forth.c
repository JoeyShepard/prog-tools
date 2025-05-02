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
    return -1;
}

static uint8_t *find_secondary(const char *word)
{
    if (!strcmp(word,"foo")) return (uint8_t *)1;
    else return NULL;
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
                for (int32_t j=start;j<start+word_len;j++)
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

static int process_source(struct ForthEngine *engine,const char *source)
{
    uint32_t word_len;
    uint32_t start=0;
    do
    {
        //Get next word of source
        word_len=next_word_source(source,&start);

        if (word_len>FORTH_WORD_MAX)
        {
            //Error - word of source is longer than allowed
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
                bool negative=false;
                char *num_ptr=word_buffer;
                if (*num_ptr=='-')
                {
                    negative=true;
                    num_ptr++;
                }
                while (*num_ptr)
                {
                    num*=10;
                    num+=*num_ptr-'0';
                    num_ptr++;
                }
                if (negative) num*=-1;
            }
            else if (word_type==FORTH_TYPE_HEX)
            {
                //Hex
                bool negative=false;
                char *num_ptr=word_buffer;
                if (*num_ptr=='-')
                {
                    negative=true;
                    num_ptr++;
                }
                while (*num_ptr)
                {
                    num*=0x10;
                    if ((*num_ptr>='0')&&(*num_ptr<='9'))
                        num+=*num_ptr-'0';
                    else if ((*num_ptr>='a')&&(*num_ptr<='f'))
                        num+=*num_ptr-'a'+10;
                    else if ((*num_ptr>='A')&&(*num_ptr<='F'))
                        num+=*num_ptr-'A'+10;
                    num_ptr++;
                }
                if (negative) num*=-1;
            } 
            else if (word_type==FORTH_TYPE_OTHER)
            {
                primitive_ID=find_primitive(word_buffer);
                if (primitive_ID!=-1)
                {
                    //Word is primitive
                    word_type=FORTH_TYPE_PRIMATIVE;
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
            if (engine->state==0)
            {
                //Interpret mode
                if ((word_type==FORTH_TYPE_NUMBER)||(word_type==FORTH_TYPE_HEX))
                {
                    //Number or hex - push to stack
                    forth_push(engine,num);
                }
                else if (word_type==FORTH_TYPE_PRIMATIVE)
                {
                    //Primitive
                    int (*immediate)(struct ForthEngine *engine)=forth_primitives[primitive_ID].immediate;
                    if (immediate!=NULL)
                    {
                        //Primitive has special immediate behavior
                        engine->source=source;
                        engine->source_index=&start;
                        int result=immediate(engine);
                        if (result!=FORTH_ENGINE_ERROR_NONE)
                        {
                            //Error in word - return to caller
                            engine->error=result;
                            return FORTH_ERROR_ENGINE;
                        }
                    }
                    else
                    {
                        //No special immediate behavior - execute body
                        forth_primitives[primitive_ID].body(engine);
                    }
                }
            }
            else
            {
                //Compile mode
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
        int32_t color;
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
            forth_accept,
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

        //Restore pointer to Forth definitions
        forth_definitions=object_address(FORTH_ID_DEFINITIONS,heap_ptr);

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

        //Remap keys for Forth
        key=forth_key_remap(key);
        
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
                    add_input_text(cancel_text,FORTH_COL_FG,FORTH_COL_BG,false,console);

                    //Copy input text to console
                    for (int i=0;i<console->input.len;i++)
                    {
                        console_char(console->input.text[i].character,console->input.text[i].fg,console->input.text[i].bg,console);
                    }
                    console->reset_input=true;
                    break;
                case VKEY_EXE:
                    //Only process if text exists
                    if (console->input.len==console->input.start) break;

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
                    
                    START HERE
                    - cant just hide input line like this
                    - problem seems to be no \n before input line
                    - problem still exists when not even calling draw_input_line
                    
                    //Hide input line since program may output to console
                    console_text_default("-",console);
                    console->input.visible=false;
                    draw_console(console);
                    dupdate();
                    //Process input
                    char input_buffer[FORTH_INPUT_MAX];
                    copy_console_text(&console->input,input_buffer,FORTH_INPUT_MAX,console->input.start);
                    process_source(&forth->engine,input_buffer);
                    console->input.visible=true;

                    //Check engine state and error if in compile state or word not complete like [

                    /*
                    int return_code=
                    if (return_code!=COMMAND_NONE)
                    {
                        //Return to window manager to process any return code such as closing console
                        return return_code;
                    }
                    */
                    console_char('\n',0,0,console);
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

