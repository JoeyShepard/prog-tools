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

int command_line(int command_ID, struct WindowInfo *windows, int selected_window)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct point pos;
    if (command_ID==COMMAND_REDRAW) pos=window_pos(window,false);
    else pos=window_pos(window,true);

    //Heap memory
    select_heap(window.tab_index,window.selected_split);
    uint8_t *heap_ptr=get_split_heap();
    struct ConsoleInfo *console;

    if (command_ID==COMMAND_START) 
    {
        //Start - allocate memory for console
        console=(struct ConsoleInfo *)add_object(sizeof(struct ConsoleInfo),heap_ptr);

        //Set default values for console
        for (int index=0;index<CMD_WHOLE_HEIGHT*CMD_WHOLE_WIDTH;index++)
        {
            console->text[index]=(index)%26+'A';
            console->color_fg[index]=C_RGB(COL_MAX,0,index%COL_MAX);
            int gray=index%COL_1_4;
            console->color_bg[index]=C_RGB(gray,gray,gray);
        }
    }
    else
    {
        //Resume or Redraw - reuse existing memory for console
        console=(struct ConsoleInfo *)(heap_ptr+HEAP_OBJECTS+sizeof(uint32_t));
    }

    //Redraw screen but only spare pixels on edges. Only letters redrawn below.
    draw_rect(pos.x,pos.y,width,height,CMD_COL_BG,CMD_COL_BG);

    //Main loop
    int modifier=MODIFIER_NONE;
    bool redraw=true;
    while (1)
    {
        if (redraw)
        {
            //Always redraw whether START, RESUME, or REDRAW
            struct point text_pos=pos;
            text_pos.x+=CMD_WHOLE_X;
            text_pos.y+=CMD_WHOLE_Y;
            int char_index=0;
            for (int row=0;row<CMD_WHOLE_HEIGHT;row++)
            {
                for (int col=0;col<CMD_WHOLE_WIDTH;col++)
                {

                    START HERE
                    - count forward from beginning of buffer
                      - count rest of line if \n
                    - after total, start at beginning and move forward to find starting point

                    char character=console->text[char_index];
                    uint16_t fg=console->color_fg[char_index];
                    uint16_t bg=console->color_bg[char_index];
                    text_pos=draw_char(character,text_pos,fg,bg,false,FONT_5x8);
                    char_index++;
                }
                text_pos.x=pos.x+CMD_WHOLE_X;
                text_pos.y+=CMD_ROW_HEIGHT;
            }
            dupdate();

            //Retrun if Redraw only
            if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;
        }
        redraw=true;
        
        int key=getkey_text(true,&modifier);

        //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
        switch (key)
        {
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

