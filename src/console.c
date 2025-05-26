#include <string.h>

#include "compatibility.h"
#include "console.h"
#include "getkey.h"
#include "manager.h"
#include "text.h"
#include "structs.h"

//Functions
//=========
void init_console(
    //Console
    struct ConsoleInfo *console,
    color_t text_col_fg,
    color_t text_col_bg,
    //Input
    struct ConsoleChar *input_text,
    struct ConsoleChar *input_copy_text,
    int input_text_max,
    color_t input_col_fg,
    color_t input_col_bg,
    //History
    struct ConsoleInput *history,
    struct ConsoleChar *history_texts,
    int history_array_size)
{
    //Console colors
    console->text_col_fg=text_col_fg;
    console->text_col_bg=text_col_bg;

    //Input
    console->input.text=input_text;
    console->input.visible=true;
    console->input_copy.text=input_copy_text;
    console->input_text_max=input_text_max;
    console->input_col_fg=input_col_fg;
    console->input_col_bg=input_col_bg;

    //History
    console->history=history;
    console->history_texts=history_texts;
    console->history_array_size=history_array_size;

    //Calcuate offsets for reseting pointers when struct address changes
    console->offset_input_text=(void*)input_text-(void*)console;
    console->offset_input_copy_text=(void*)input_copy_text-(void*)console;
    console->offset_history=(void*)history-(void*)console;
    console->offset_history_texts=(void*)history_texts-(void*)console;
}

//Reset pointers that changed after struct moved 
void reset_console_pointers(struct ConsoleInfo *console)
{
    console->input.text=(struct ConsoleChar*)(((void*)console)+console->offset_input_text);
    console->input_copy.text=(struct ConsoleChar*)(((void*)console)+console->offset_input_copy_text);
    console->history=(struct ConsoleInput*)(((void*)console)+console->offset_history);
    console->history_texts=(struct ConsoleChar*)(((void*)console)+console->offset_history_texts);
    for (int i=0;i<console->history_array_size;i++)
    {
        console->history[i].text=console->history_texts+i*console->input_text_max;
    }
}

void init_history(struct ConsoleInfo *console)
{
    for (int i=0;i<console->history_array_size;i++)
    {
        console->history[i].text[0].character=0;
        console->history[i].len=0;
    }
    console->history_index=0;
    console->history_count=0;
}

//Set size and location to match split. Not called from init_console since may ignore and use
//only part of allocated space for console window.
void init_position(struct ConsoleInfo *console,struct Point pos,int split_state)
{
    //Set coordinates, width, and height based on window state
    if (split_state==WINDOW_HSPLIT)
    {
        //Split horizontally - half width
        console->x=pos.x+CONS_HALF_X;
        console->width=CONS_HALF_WIDTH;
    }
    else
    {
        //Whole screen or split vertically - full width
        console->x=pos.x+CONS_WHOLE_X;
        console->width=CONS_WHOLE_WIDTH;
    }
    
    if (split_state==WINDOW_VSPLIT)
    {
        //Split vertically - half height
        console->y=pos.y+CONS_HALF_Y;
        console->height=CONS_HALF_HEIGHT;
    }
    else
    {
        //Whole screen or split horizontally - full height
        console->y=pos.y+CONS_WHOLE_Y;
        console->height=CONS_WHOLE_HEIGHT;
    }
}

void console_char(char character, color_t fg, color_t bg, struct ConsoleInfo *console)
{
    if (console->text_len<CONS_BUFFER_SIZE)
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
    if (console->buffer_index==CONS_BUFFER_SIZE) console->buffer_index=0;
}

void console_char_default(char character, struct ConsoleInfo *console)
{
    console_char(character,console->text_col_fg,console->text_col_bg,console);
}

void console_text(const char *text, color_t fg, color_t bg, struct ConsoleInfo *console)
{
    while (*text)
    {
        console_char(*text,fg,bg,console);
        text++;
    }
}

void console_text_default(const char *text, struct ConsoleInfo *console)
{
    console_text(text,console->text_col_fg,console->text_col_bg,console);
}

void add_input_text(const char *text,color_t fg,color_t bg,struct ConsoleInfo *console)
{
    int text_len=strlen(text);
    if (console->input.len+text_len>=console->input_text_max-1)
    {
        //Shorten text to be added if longer than space available
        text_len=console->input_text_max-1-console->input.len;
    }

    //Add text to input
    int text_index;
    text_index=console->input.cursor;

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

    console->input.cursor+=text_len;
    console->input.len+=text_len;
}

void add_input_char(char character,color_t fg,color_t bg,struct ConsoleInfo *console)
{
    char buffer[2];
    buffer[0]=character;
    buffer[1]=0;
    add_input_text(buffer,fg,bg,console);
}

struct Point draw_input_line(struct ConsoleInfo *console,struct Point pos,int *col,int *row)
{
    bool invert;
    char character;
    int color_fg, color_bg;

    if (console->input.visible==true)
    {
        for (uint32_t char_index=0;char_index<console->input.len+1;char_index++)
        {
            if (char_index==console->input.len)
            {
                //Space character after all input. Needed when cursor is at end of input.
                character=' ';
                color_fg=console->input_col_fg;
                color_bg=console->input_col_bg;
            }
            else
            {
                //Draw character of input
                character=console->input.text[char_index].character;
                color_fg=console->input.text[char_index].fg;
                color_bg=console->input.text[char_index].bg;
            }

            if (char_index==console->input.cursor)
            {
                //Cursor character - invert
                invert=true;
            }
            else invert=false;

            //Print character
            pos=draw_char(character,pos,color_fg,color_bg,invert,FONT_5x8);

            //Advance to next column and wrap text if necessary
            *col=*col+1;
            if (*col==console->width)
            {
                *col=0;
                *row=*row+1;
                pos.x=console->x;
                pos.y+=CONS_ROW_HEIGHT;
            }
        }
    }
    return pos;
}

void draw_console(struct ConsoleInfo *console)
{
    //If input line visible, loop backwards through screen buffer to find length of last line 
    //printed since needed to calculate how many lines input line needs
    int input_height;
    int last_line_length;
    if (console->input.visible==true)
    {
        //Loop backwards through screen buffer
        int line_length=0;
        int buffer_counter=console->buffer_index;
        bool newline_found=false;
        for (uint32_t i=0;i<console->text_len;i++)
        {
            buffer_counter--;
            if (buffer_counter<0)
            {
                //Wrap index - buffer is circular
                buffer_counter+=CONS_BUFFER_SIZE;
            }

            if (console->text[buffer_counter].character=='\n')
            {
                //Newline character - done searching
                last_line_length=line_length%console->width;
                newline_found=true;
                break;
            }
            else line_length++;
        }

        if (newline_found==false)
        {
            //No newline in console output - calculate last line length from count of overflow characters
            last_line_length=(console->overflow_count+line_length)%console->width;
        }
        
        //Calculate extra lines for input
        input_height=((last_line_length+console->input.len)/console->width);
    }
    else input_height=0;

    //Adjust console_height to make room for input line based on calculation above
    int new_height=console->height-input_height;

    //Find starting point in circular screen buffer for printing characters
    int line_length=0;
    int line_count=0;
    int buffer_counter=console->buffer_index;
    int buffer_start=buffer_counter;
    for (uint32_t i=0;i<console->text_len;i++)
    {
        //Loop backwards through screen buffer until enough lines are generated to fill screen
        buffer_counter--;
        if (buffer_counter<0)
        {
            //Wrap index - buffer is circular
            buffer_counter+=CONS_BUFFER_SIZE;
        }

        if (console->text[buffer_counter].character=='\n')
        {
            //Newline character - calculate number of lines generated by text on this line
            line_count++;
            buffer_start-=line_length%console->width;
            int line_length_copy=line_length;
            line_length=0;
            if (line_count==new_height)
            {
                //Found enough lines of text to fill the screen - stop looping
                break;
            }
            int new_lines=line_length_copy/console->width;
            if (line_count+new_lines<new_height)
            {
                //Add remaining lines to output
                buffer_start-=new_lines*console->width;
                buffer_start--;
                line_count+=new_lines;
            }
            else
            {
                //More than enough lines found so only add enough to fill the screen
                new_lines=new_height-line_count;
                buffer_start-=new_lines*console->width;
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
        if (line_count<new_height)
        {
            //Still room left on screen for more lines
            if ((console->overflow_count+line_length)%console->width!=0)
            {
                //Align text accounting for characters that have scrolled out of the buffer
                buffer_start-=(console->overflow_count+line_length)%console->width;
                line_count++;
            }
        }
        int new_lines=line_length/console->width;
        if (line_count+new_lines<new_height)
        {
            //Add more lines if room left
            buffer_start-=new_lines*console->width;
        }
        else
        {
            //More than enough lines left. Add enough to fill screen.
            new_lines=new_height-line_count;
            buffer_start-=new_lines*console->width;
        }
    }

    bool draw_once=false;
    while (buffer_start<0)
    {
        //Code above starts at end of output and moves buffer_start back until it finds where to start
        //to output the correct number of characters. Screen buffer is circular so buffer_start may
        //become negative. It seems that adding CMD_BUFFER_SIZE once would account for all cases of
        //wrapping but looping here in case once isn't enough.
        buffer_start+=CONS_BUFFER_SIZE;
        //Make sure loop below draws a character at least once since buffer_start may be equal to
        //-CMD_BUFFER_SIZE then becomes 0 with line above which signals no more characters whereas
        //exactly CMD_BUFFER_SIZE characters should be drawn.
        draw_once=true;
    }

    //Draw screen output
    struct Point text_pos={console->x,console->y};
    int blank_count=0;
    int row=0,col=0;
    bool input_drawn=false;

    //TODO: remove
    static int flip=0;
    flip^=2;

    while(row<console->height)
    {
        bool console_done=((buffer_start==(int)console->buffer_index)&&(draw_once==false));
        if ((console_done)&&(input_drawn==false))
        {
            //Draw input line
            text_pos=draw_input_line(console,text_pos,&col,&row);
            input_drawn=true;
        }
        else
        {
            if ((console_done)||(blank_count>0))
            {
                //Draw blanks if no more text
                text_pos=draw_char(' ',text_pos,console->input_col_fg,console->input_col_bg,false,FONT_5x8);
                if (blank_count>0) blank_count--;
            }
            else
            {
                char character=console->text[buffer_start].character;
                if (character=='\n')
                {
                    //Newline character - fill rest of line with blanks
                    blank_count=console->width-col;
                    //Draw one character less so no blank character for newline
                    col--;
                }
                else
                {
                    //Draw character of input
                    color_t fg=console->text[buffer_start].fg;
                    color_t bg=console->text[buffer_start].bg;
                    text_pos=draw_char(character,text_pos,fg,bg,false,FONT_5x8);
                }

                //Advance to next character in buffer
                buffer_start++;
                if (buffer_start==CONS_BUFFER_SIZE) buffer_start=0;
                draw_once=false;
            }

            //Advance to next character on screen
            col++;
            if (col==console->width)
            {
                //Reached end of line on screen - go to next line
                col=0;
                row++;
                text_pos.x=console->x;
                text_pos.y+=CONS_ROW_HEIGHT;
            }
        }
    }
}

void reset_console(struct ConsoleInfo *console)
{
    console->overflow_count=0;
    console->buffer_index=0;
    console->text_len=0;
    console->input.text[0].character=0;
    console->input.cursor=0;
    console->input.len=0;
}

void add_history(struct ConsoleInfo *console)
{
    input_deep_copy(console->history+console->history_index,&console->input,console->input_text_max);
    console->history_index++;
    if (console->history_index==console->history_array_size)
        console->history_index=0;
    if (console->history_count<console->history_array_size)
        console->history_count++;
}

void console_key(struct ConsoleInfo *console,int key)
{
    switch(key)
    {
        case VKEY_UP:
            if (console->history_count>0)
            {
                //Scroll up in history if there are history lines
                if (console->input_copied==false)
                {
                    //First time up pressed - save current input
                    input_deep_copy(&console->input_copy,&console->input,console->input_text_max);
                    console->input_copied=true;
                    console->history_read_count=console->history_count;
                }

                if (console->history_read_count>0)
                {
                    //Items left to scroll back to
                    if (console->history_count==console->history_read_count)
                    {
                        //Current line edited is copy of input when up was pressed meaning input
                        //scrolled up then back to original input. Save that input including changes
                        //in case scroll back to that.
                        input_deep_copy(&console->input_copy,&console->input,console->input_text_max);
                    }

                    //Scroll up one line and copy line from history to input
                    console->history_read_count--;
                    int read_index=console->history_index;
                    read_index-=console->history_count;
                    read_index+=console->history_read_count;
                    if (read_index<0) read_index+=console->history_array_size;
                    input_deep_copy(&console->input,console->history+read_index,console->input_text_max);
                }
            }
            break;
        case VKEY_DOWN:
            if (console->input_copied)
            {
                //Only scroll down in history if previously scrolled up
                if (console->history_read_count==console->history_count)
                {
                    //Already scrolled all the way down - nothing to do
                    break;
                }
                
                //Advance to next history line
                console->history_read_count++;
                if (console->history_read_count==console->history_count)
                {
                    //Advanced past last line so use copy of original input from before
                    //scrolling up. This way, scrolling up, scrolling down, modifying 
                    //original input then scrolling up then back down to original input
                    //doesn't lose changes.
                    input_deep_copy(&console->input,&console->input_copy,console->input_text_max);
                }
                else
                {
                    //Copy line from history to input
                    int read_index=console->history_index;
                    read_index-=console->history_count;
                    read_index+=console->history_read_count;
                    if (read_index<0) read_index+=console->history_array_size;
                    input_deep_copy(&console->input,console->history+read_index,console->input_text_max);
                }
            }
            break;
        case VKEY_LEFT:
            //Move cursor left
            if (console->input.cursor>0)
                console->input.cursor--; 
            break;
        case VKEY_RIGHT:
            //Move cursor right
            if (console->input.cursor<console->input.len)
                console->input.cursor++;
            break;
        case VKEY_SHIFT_LEFT:
            //Move cursor to beginning of input
            console->input.cursor=0;
            break;
        case VKEY_SHIFT_RIGHT:
            //Move cursor to end of input
            console->input.cursor=console_strlen(console->input.text);
            break;
        case VKEY_UNDO:
            //DEL with alpha active - treat as DEL so don't need to remove alpha to delete
            //Fallthrough!
        case VKEY_DEL:
            if (console->input.cursor>0)
            {
                console->input.cursor--;
                for (uint32_t i=console->input.cursor;i<console->input.len;i++)
                {
                    console->input.text[i]=console->input.text[i+1];
                }
                console->input.len--;
            }
            break;
    }
}

void copy_console_text(struct ConsoleInput *input,char *input_buffer,int input_size,int offset)
{
    //Copy all characters excluding color data
    for (int i=offset;i<input_size;i++)
        input_buffer[i-offset]=input->text[i].character;

    //Loop above copies 0 terminator but add here just in case
    if (input_size>0)
        input_buffer[input_size-1]=0;
}

int console_strlen(struct ConsoleChar *text)
{
    int size=0;
    while(text->character)
    {
        text++;
        size++;
    }
    return size;
}


void input_deep_copy(struct ConsoleInput *dest,struct ConsoleInput *source,int elements)
{
    //Save pointer to text before overwriting
    struct ConsoleChar *text_ptr=dest->text;

    *dest=*source;
    dest->text=text_ptr;
    memcpy(dest->text,source->text,elements*sizeof(struct ConsoleChar));
}
