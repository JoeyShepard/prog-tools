//placeholder functions for menu
#include <string.h>

#include "command.h"
#include "compatibility.h"
#include "debug.h"
#include "getkey.h"
#include "graphics.h"
#include "text.h"
#include "dummy.h"
#include "manager.h"
#include "mem.h"
#include "structs.h"


//Functions
static void console_char(const char character, color_t fg, color_t bg, struct ConsoleInfo *console)
{
    if (console->text_len<CMD_BUFFER_SIZE)
    {
        //Text buffer not full yet
        console->text_len++;
    }
    else
    {
        //Buffer full - keep track of number of characters overwritten
        if (console->text[console->buffer_index].character=='\n')
        {
            //New line overwritten - reset count
            console->overflow_count=0;
        }
        else
        {
            //Add character overwritten to count for alignment when printing
            console->overflow_count++;
        }
    }
    console->text[console->buffer_index].character=character;
    console->text[console->buffer_index].fg=fg;
    console->text[console->buffer_index].bg=bg;
    console->buffer_index++;
    if (console->buffer_index==CMD_BUFFER_SIZE) console->buffer_index=0;
}

static void console_text(const char *text, color_t fg, color_t bg, struct ConsoleInfo *console)
{
    while (*text)
    {
        console_char(*text,fg,bg,console);
        text++;
    }
}

static void add_input_text(const char *text,color_t fg,color_t bg,bool add_to_start,struct ConsoleInfo *console)
{
    int text_len=strlen(text);
    if (console->input.len+text_len>=CMD_INPUT_MAX-1)
    {
        //Shorten text to be added if longer than space available
        text_len=CMD_INPUT_MAX-1-console->input.len;
    }

    int text_index;
    if (add_to_start)
    {
        //Add text to display text at the beginning
        text_index=console->input.len;
    }
    else
    {
        //Add text to input
        text_index=console->input.cursor;
    }

    //Move existing text right if inserting text in middle of string
    for (int i=console->input.len;i>=text_index;i--)
    {
        console->input.text[i+text_len]=console->input.text[i];
    }

    //Copy in new text
    for (int i=0;i<text_len;i++)
    {
        console->input.text[text_index+i].character=text[i];
        console->input.text[text_index+i].fg=fg;
        console->input.text[text_index+i].bg=bg;
    }

    if (add_to_start)
    {
        //Text added to display text at beginning
        console->input.start+=text_len;
    }
    console->input.cursor+=text_len;
    console->input.len+=text_len;
}

static void add_input_char(char character,color_t fg,color_t bg,bool add_to_start,struct ConsoleInfo *console)
{
    char buffer[2];
    buffer[0]=character;
    buffer[1]=0;
    add_input_text(buffer,fg,bg,add_to_start,console);
}

static void draw_input_line(struct ConsoleInfo *console,struct point pos,int console_width,int input_height)
{
    int starting_x=pos.x;
    int char_index=0;
    bool cursor_drawn=false;
    bool invert;
    for (int row=0;row<input_height;row++)
    {
        for (int col=0;col<console_width;col++)
        {
            char character;
            int color_fg, color_bg;
            if (console->input.text[char_index].character!=0)
            {
                //Draw character of input
                character=console->input.text[char_index].character;
                color_fg=console->input.text[char_index].fg;
                color_bg=console->input.text[char_index].bg;
                if (char_index==console->input.cursor)
                {
                    //Cursor character - invert
                    invert=true;
                    cursor_drawn=true;
                }
                else invert=false;
                char_index++;
            }
            else
            {
                character=' ';
                color_fg=CMD_COL_FG;
                color_bg=CMD_COL_BG;
                if (cursor_drawn==false)
                {
                    //Cursor not drawn yet - draw cursor
                    invert=true;
                    cursor_drawn=true;
                }
                else
                {
                    //Draw spaces for rest of line
                    invert=false;
                }
            }
            pos=draw_char(character,pos,color_fg,color_bg,invert,FONT_5x8);
        }
        pos.x=starting_x;
        pos.y+=CMD_ROW_HEIGHT;
    }
}

static void draw_console(struct ConsoleInfo *console,int console_x,int console_y,int console_width,int console_height)
{
    //Adjust console_height to make room for input line
    int input_height=((console->input.len)/console_width)+1;
    console_height-=(input_height-1);

    //Find starting point in circular screen buffer for printing characters
    int line_length=0;
    int line_count=0;
    int buffer_counter=console->buffer_index;
    int buffer_start=buffer_counter;
    for (int i=0;i<console->text_len;i++)
    {
        //Loop backwords through screen buffer until enough lines are generated to fill screen
        buffer_counter--;
        if (buffer_counter<0)
        {
            //Wrap index - buffer is circular
            buffer_counter=CMD_BUFFER_SIZE-1;
        }

        if (console->text[buffer_counter].character=='\n')
        {
            //Newline character - calculate number of lines generated by text on this line
            line_count++;
            buffer_start-=line_length%console_width;
            int line_length_copy=line_length;
            line_length=0;
            if (line_count==console_height)
            {
                //Found enough lines of text to fill the screen - stop looping
                break;
            }
            int new_lines=line_length_copy/console_width;
            if (line_count+new_lines<console_height)
            {
                //Add remaining lines to output
                buffer_start-=new_lines*console_width;
                buffer_start--;
                line_count+=new_lines;
            }
            else
            {
                //More than enough lines found so only add enough to fill the screen
                new_lines=console_height-line_count;
                buffer_start-=new_lines*console_width;
                line_count+=new_lines;
                break;
            }
        }
        else
        {
            //Character other than newline in buffer. Just count then make adjustment later.
            line_length++;
        }
    }
    
    if (line_length>0)
    {
        //Process characters left over from searching output buffer
        if (line_count<console_height)
        {
            //Still room left on screen for more lines
            if ((console->overflow_count+line_length)%console_width!=0)
            {
                //Align text accounting for characters that has scrolled out of the buffer
                buffer_start-=(console->overflow_count+line_length)%console_width;
                line_count++;
            }
        }
        int new_lines=line_length/console_width;
        if (line_count+new_lines<console_height)
        {
            //Add more lines if room left
            buffer_start-=new_lines*console_width;
        }
        else
        {
            //More than enough lines left. Add enough to fill screen.
            new_lines=console_height-line_count;
            buffer_start-=new_lines*console_width;
        }
    }

    bool draw_once=false;
    while (buffer_start<0)
    {
        //Code above starts at end of output and moves buffer_start back until it finds where to start
        //to output the correct number of characters. Screen buffer is circular so buffer_start may
        //become negative. It seems that adding CMD_BUFFER_SIZE once would account for all cases of
        //wrapping but looping here in case once isn't enough.
        buffer_start+=CMD_BUFFER_SIZE;
        //Make sure loop below draws a character at least once since buffer_start may be equal to
        //-CMD_BUFFER_SIZE then becomes 0 with line above which signals no more characters whereas
        //exactly CMD_BUFFER_SIZE characters should be drawn.
        draw_once=true;
    }

    //Draw screen output
    struct point text_pos={console_x,console_y};
    int blank_count=0;
    int row=0,col=0;
    bool input_drawn=false;
    while(row<console_height-1)
    {
        if ((blank_count>0)||((buffer_start==console->buffer_index)&&(draw_once==false)))
        {
            //Draw blanks if no more text
            text_pos=draw_char(' ',text_pos,CMD_COL_FG,CMD_COL_BG,false,FONT_5x8);
            if (blank_count>0) blank_count--;
        }
        else
        {
            char character=console->text[buffer_start].character;
            if (character=='\n')
            {
                //Newline character - fill rest of line with blanks
                blank_count=console_width-col;
                //Draw one character less so no blank character for newline
                col--;
            }
            else
            {
                //Draw character
                color_t fg=console->text[buffer_start].fg;
                color_t bg=console->text[buffer_start].bg;
                text_pos=draw_char(character,text_pos,fg,bg,false,FONT_5x8);
            }

            //Advance to next character in buffer
            buffer_start++;
            if (buffer_start==CMD_BUFFER_SIZE) buffer_start=0;
            draw_once=false;
        }

        //Advance to next character on screen
        col++;
        if (col==console_width)
        {
            //Reached end of line on screen - go to next line
            col=0;
            row++;
            text_pos.x=console_x;
            text_pos.y+=CMD_ROW_HEIGHT;
            if ((buffer_start==console->buffer_index)&&(input_drawn==false))
            {
                //Draw input line
                draw_input_line(console,text_pos,console_width,input_height);
                text_pos.y+=CMD_ROW_HEIGHT*input_height;
                input_drawn=true;
            }
        }
    }
}
static void reset_console(struct ConsoleInfo *console)
{
    console->overflow_count=0;
    console->buffer_index=0;
    console->text_len=0;
    console->input.text[0].character=0;
    console->input.start=0;
    console->input.cursor=0;
    console->input.len=0;
}

static void add_history(struct ConsoleInfo *console)
{
    console->history[console->history_index]=console->input;
    console->history_index++;
    if (console->history_index==CMD_HIST_COUNT)
        console->history_index=0;
    if (console->history_count<CMD_HIST_COUNT)
        console->history_count++;
}

int command_line(int command_ID, struct WindowInfo *windows, int selected_window)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct point pos;
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
    struct ConsoleInfo *console;

    if (command_ID==COMMAND_START) 
    {
        //Start - allocate memory for and initialize console
        console=(struct ConsoleInfo *)add_object(sizeof(struct ConsoleInfo),heap_ptr);

        //TODO: check if allocation succeeded

        //Init console
        reset_console(console);

        //Init input
        console_text("Calculator shell for fx-CG50\nType 'help' for more info.\n",CMD_COL_FG,CMD_COL_BG,console);
        console->reset_input=true;
        console->modifier=MODIFIER_NONE;
        console->input_copied=false;

        //Init history
        for (int i=0;i<CMD_HIST_COUNT;i++)
        {
            console->history[i].text[0].character=0;
            console->history[i].len=0;
        }
        console->history_index=0;
        console->history_count=0;
    }
    else
    {
        //Resume or Redraw - reuse existing memory for console
        console=(struct ConsoleInfo *)object_address(CMD_ID_CONSOLE,heap_ptr);
    }

    //Redraw screen but only spare pixels on edges. Letters redrawn below.
    draw_rect(pos.x,pos.y,width,height,CMD_COL_BG,CMD_COL_BG);

    //Set coordinates, width, and height based on window state
    int console_width,console_x;
    if (window.split_state==WINDOW_HSPLIT)
    {
        //Split horizontally - half width
        console_x=pos.x+CMD_HALF_X;
        console_width=CMD_HALF_WIDTH;
    }
    else
    {
        //Whole screen or split vertically - full width
        console_x=pos.x+CMD_WHOLE_X;
        console_width=CMD_WHOLE_WIDTH;
    }
    
    int console_height,console_y;
    if (window.split_state==WINDOW_VSPLIT)
    {
        //Split vertically - half height
        console_y=pos.y+CMD_HALF_Y;
        console_height=CMD_HALF_HEIGHT;
    }
    else
    {
        //Whole screen or split horizontally - full height
        console_y=pos.y+CMD_WHOLE_Y;
        console_height=CMD_WHOLE_HEIGHT;
    }

    //Main loop
    bool redraw_screen=true;
    bool redraw_modifier=true;
    bool redraw_input=true;
    while (1)
    {
        //Set text for input line
        if (console->reset_input)
        {
            console->input.text[0].character=0;
            console->input.start=0;
            console->input.cursor=0;
            console->input.len=0;
            add_input_text("CG50",COL_GREEN,COL_BLACK,true,console);
            add_input_char(':',COL_WHITE,COL_BLACK,true,console);
            add_input_text("/ram/",COL_BLUE,COL_BLACK,true,console);
            console->input_copied=false;
        }
        console->reset_input=false;

        //Redraw modifiers (shift, alpha) as necessary even if rest of screen not redrawn
        if (redraw_modifier) draw_modifier(console->modifier);

        if (redraw_screen)
        {
            //Always redraw screen whether START, RESUME, or REDRAW
            draw_console(console,console_x,console_y,console_width,console_height);
                
            //Return if Redraw only
            if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;
        }

        //TODO
        //if (redraw_input)

        //Copy updates to screen if modifier keys or text have changed
        if ((redraw_screen)||(redraw_modifier)||(redraw_input)) dupdate();
        redraw_screen=true;
        
        //Get key
        int old_modifier=console->modifier;
        int key=getkey_text(true,&console->modifier);

        //Redraw modifiers (shift, alpha) next time through if they have changed
        if (old_modifier!=console->modifier) redraw_modifier=true;
        else redraw_modifier=false;

        //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
        char character=vkey_printable[key];
        if (character!=0)
        {
            if (character=='1') add_input_text("Test text!",COL_RED,COL_BLUE,false,console);
            else if (character=='2') add_input_text("Test text!",COL_BLUE,COL_RED,false,console);
            else

            //Printable character - add to input line
            add_input_char(character,CMD_COL_FG,CMD_COL_BG,false,console);
        }
        else
        {
            switch (key)
            {
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
                    if (console->input.len>=CMD_INPUT_MAX-strlen(cancel_text))
                    {
                        //Not enough room to append ^C so drop characters from end of input to make room
                        console->input.len=CMD_INPUT_MAX-strlen(cancel_text)-1;
                        console->input.cursor=CMD_INPUT_MAX-strlen(cancel_text)-1;
                    }
                    add_input_text(cancel_text,CMD_COL_FG,CMD_COL_BG,false,console);

                    //Fallthrough
                case VKEY_EXE:
                    //Copy input text to console
                    for (unsigned int i=0;i<console->input.len;i++)
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
                    }
                    break;
                case VKEY_UP:
                    if (console->history_count>0)
                    {
                        if (console->input_copied==false)
                        {
                            //First time up pressed - save current input
                            console->input_copy=console->input;
                            console->input_copied=true;
                            console->history_read_count=console->history_count;
                        }

                        if (console->history_read_count>0)
                        {
                            if (console->history_count==console->history_read_count)
                            {
                                console->input_copy=console->input;
                            }
                            console->history_read_count--;
                            int read_index=console->history_index;
                            read_index-=console->history_count;
                            read_index+=console->history_read_count;
                            if (read_index<0) read_index+=CMD_HIST_COUNT;
                            console->input=console->history[read_index];
                        }
                    }
                    break;
                case VKEY_DOWN:
                    if (console->input_copied)
                    {
                        if (console->history_read_count==console->history_count)
                        {
                            break;
                        }

                        console->history_read_count++;
                        if (console->history_read_count==console->history_count)
                        {
                            console->input=console->input_copy;    
                        }
                        else
                        {
                            int read_index=console->history_index;
                            read_index-=console->history_count;
                            read_index+=console->history_read_count;
                            if (read_index<0) read_index+=CMD_HIST_COUNT;
                            console->input=console->history[read_index];
                        }
                    }
                    break;
                case VKEY_LEFT:
                    if (console->input.cursor>console->input.start)
                        console->input.cursor--; 
                    break;
                case VKEY_RIGHT:
                    if (console->input.cursor<console->input.len)
                        console->input.cursor++;
                    break;
                case VKEY_UNDO:
                    //DEL with alpha active - treat as DEL so don't need to remove alpha to delete
                    //Fallthrough!
                case VKEY_DEL:
                    if (console->input.cursor>console->input.start)
                    {
                        console->input.cursor--;
                        for (int i=console->input.cursor;i<console->input.len;i++)
                        {
                            console->input.text[i]=console->input.text[i+1];
                        }
                        console->input.len--;
                    }
                    break;
                default:
                    //Check for sys_keys like MENU, OFF, etc
                    int return_command=sys_key_handler(key);
                    if (return_command!=COMMAND_NONE)
                    {
                        //System key - return to window manager to handle key
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

