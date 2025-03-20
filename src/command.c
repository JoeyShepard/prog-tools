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

static void console_print(const char *text, uint16_t fg, uint16_t bg, struct ConsoleInfo *console)
{
    while (*text)
    {
        if (console->text_len<CMD_BUFFER_SIZE)
        {
            //Text buffer not full yet
            console->text_len++;
        }
        else
        {
            //Buffer full - keep track of number of characters overwritten
            if (console->text[console->buffer_index]=='\n')
            {
                //New line overwritten - reset count
                console->overflow_count=0;

                printf("console_print: new line\n");

            }
            else
            {
                //Add character overwritten to count for alignment when printing
                console->overflow_count++;
            }
        }
        console->text[console->buffer_index]=*text;
        console->color_fg[console->buffer_index]=fg;
        console->color_bg[console->buffer_index]=bg;
        console->buffer_index++;
        if (console->buffer_index==CMD_BUFFER_SIZE) console->buffer_index=0;
        text++;
    }
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
        //Start - allocate memory for console
        console=(struct ConsoleInfo *)add_object(sizeof(struct ConsoleInfo),heap_ptr);

        //Set default values for console
        for (int index=0;index<CMD_WHOLE_HEIGHT*CMD_WHOLE_WIDTH;index++)
        {
            //console->text[index]=(index)%26+'A';
            console->text[index]='-';
            console->color_fg[index]=C_RGB(COL_MAX,0,index%COL_MAX);
            int gray=index%COL_1_4;
            console->color_bg[index]=C_RGB(gray,gray,gray);
        }
        //console->text[0]='0'+window.tab_index;
        //console->text[1]='0'+drawn_split;
        console->overflow_count=0;
        console->buffer_index=0;
        console->text_len=0;

        //Debug
        for (int i=0;i<100;i++) console_print("ABCDEFGHIJKLMNOPQRSTUVWXYZ",COL_WHITE,COL_BLACK,console);
    }
    else
    {
        //Resume or Redraw - reuse existing memory for console
        console=(struct ConsoleInfo *)(heap_ptr+HEAP_OBJECTS+sizeof(uint32_t));
    }

    //Redraw screen but only spare pixels on edges. Letters redrawn below.
    draw_rect(pos.x,pos.y,width,height,CMD_COL_BG,CMD_COL_BG);

    //Set coordinates, width, and height based on window state
    int console_width,console_x;
    if (window.split_state==WINDOW_HSPLIT)
    {
        console_x=pos.x+CMD_HALF_X;
        console_width=CMD_HALF_WIDTH;
    }
    else
    {
        console_x=pos.x+CMD_WHOLE_X;
        console_width=CMD_WHOLE_WIDTH;
    }
    
    int console_height,console_y;
    if (window.split_state==WINDOW_VSPLIT)
    {
        console_y=pos.y+CMD_HALF_Y;
        console_height=CMD_HALF_HEIGHT;
    }
    else
    {
        console_y=pos.y+CMD_WHOLE_Y;
        console_height=CMD_WHOLE_HEIGHT;
    }

    //Main loop
    int modifier=MODIFIER_NONE;
    bool redraw=true;
    bool redraw_modifier=true;
    while (1)
    {
        if (redraw_modifier) draw_modifier(modifier);

        if (redraw)
        {
            //Always redraw whether START, RESUME, or REDRAW
            

            printf("overflow_count: %d\n",console->overflow_count);
            printf("buffer_index: %d\n",console->buffer_index);
            printf("text_len: %d\n",console->text_len);
            printf("text starting at 0:\n");
            for (int i=0;i<CMD_BUFFER_SIZE;i++)
            {
                if (i%console_width==0)
                    printf("\n  ");
                putchar(console->text[i]);
            }
            printf("\n  \n");


            //TODO: shorten

            //Find starting point in buffer for printing characters
            int line_length=0;
            int line_count=0;
            int buffer_counter=console->buffer_index;
            int buffer_start=buffer_counter;
            for (int i=0;i<console->text_len;i++)
            {
                buffer_counter--;
                if (buffer_counter<0) buffer_counter=CMD_BUFFER_SIZE-1;

                if (console->text[buffer_counter]=='\n')
                {
                    line_count++;
                    buffer_start-=line_length%console_width;
                    int line_length_copy=line_length;
                    line_length=0;
                    if (line_count==console_height)
                    {
                        break;
                    }
                    int new_lines=line_length_copy/console_width;
                    if (line_count+new_lines<console_height)
                    {
                        buffer_start-=new_lines*console_width;
                        buffer_start--;
                        line_count+=new_lines;
                    }
                    else
                    {
                        new_lines=console_height-line_count;
                        buffer_start-=new_lines*console_width;
                        line_count+=new_lines;
                        break;
                    }
                }
                else
                {
                    line_length++;
                }
            }
            
            if (line_length>0)
            {
                printf("line_length>0, ");
                if (line_count<console_height)
                {
                    printf("lines left, ");
                    if ((console->overflow_count+line_length)%console_width!=0)
                    {
                        printf("correction: (%d+%d)%%%d=%d, ",console->overflow_count,line_length,console_width,(console->overflow_count+line_length)%console_width);
                        buffer_start-=(console->overflow_count+line_length)%console_width;
                        line_count++;
                    }
                }
                printf("\n");
                int new_lines=line_length/console_width;
                if (line_count+new_lines<console_height)
                {
                    buffer_start-=new_lines*console_width;
                }
                else
                {
                    new_lines=console_height-line_count;
                    buffer_start-=new_lines*console_width;
                }
            }


            printf("buffer_start: %d\n",buffer_start);


            //TODO: paranoid. can buffer_start ever be less than -CMD_BUFFER_SIZE?
            bool draw_once=false;
            while (buffer_start<0)
            {
                buffer_start+=CMD_BUFFER_SIZE;
                draw_once=true;
            }

            
            printf("buffer_start: %d\n",buffer_start);
            printf("buffer_index: %d\n",console->buffer_index);


            //Draw console
            struct point text_pos={console_x,console_y};
            int blank_count=0;
            int row=0,col=0;
            while(row<console_height)
            {
                if ((blank_count>0)||((buffer_start==console->buffer_index)&&(draw_once==false)))
                {
                    text_pos=draw_char('.',text_pos,COL_GREEN,COL_BLACK,false,FONT_5x8);
                    if (blank_count>0) blank_count--;
                }
                else
                {
                    char character=console->text[buffer_start];
                    if (character=='\n')
                    {
                        blank_count=console_width-col;
                        col--;
                    }
                    else
                    {
                        uint16_t fg=console->color_fg[buffer_start];
                        uint16_t bg=console->color_bg[buffer_start];
                        text_pos=draw_char(character,text_pos,fg,bg,false,FONT_5x8);
                    }

                    buffer_start++;
                    if (buffer_start==CMD_BUFFER_SIZE) buffer_start=0;
                    draw_once=false;
                }
                col++;
                if (col==console_width)
                {
                    col=0;
                    row++;
                    text_pos.x=console_x;
                    text_pos.y+=CMD_ROW_HEIGHT;
                }
            }
                
            //Return if Redraw only
            if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;
        }
        if ((redraw)||(redraw_modifier)) dupdate();
        redraw=true;
        
        //Get key
        int old_modifier=modifier;
        int key=getkey_text(true,&modifier);
        if (old_modifier!=modifier) redraw_modifier=true;
        else redraw_modifier=false;

        //printf("key: %d %d %d modifier: %d redraw_modifier: %d\n",key,VKEY_a,VKEY_A,modifier,redraw_modifier);

        //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
        switch (key)
        {
            case VKEY_EXE:
                console_print("\n",COL_WHITE,COL_BLACK,console);
                break;
            case VKEY_a:
                printf("key a pressed\n");
                console_print("ABCDEFGHIJKLMNOPQRSTUVWXYZ",COL_WHITE,COL_BLACK,console);
                break;
            default:
                //Check for sys_keys like MENU, OFF, etc
                int return_command=sys_key_handler(key);
                if (return_command!=COMMAND_NONE) return return_command;
                redraw=false;
        }
    }

    //Shouldn't reach here - added to silence warning
    return COMMAND_DONE;
}

