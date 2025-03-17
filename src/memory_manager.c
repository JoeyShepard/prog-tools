//placeholder functions for menu
#include <string.h>

#include "compatibility.h"
#include "debug.h"
#include "getkey.h"
#include "graphics.h"
#include "text.h"
#include "dummy.h"
#include "manager.h"
#include "mem.h"
#include "memory_manager.h"
#include "structs.h"

int memory_manager(int command_ID, struct WindowInfo *windows, int selected_window)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct point pos;
    if (command_ID==COMMAND_REDRAW) pos=window_pos(window,false);
    else pos=window_pos(window,true);

    //Always redraw whether START, RESUME, or REDRAW
    draw_rect(pos.x,pos.y,width,height,COL_MEM_MGR_BG,COL_MEM_MGR_BG);
    outline_text("Memory manager",pos,COL_MEM_MGR_FG,-1,COL_MEM_MGR_FG,false,FONT_5x8);
    
    //Heap memory
    pos.y+=MEM_MGR_OUTLINE_HEIGHT;
    struct point new_pos;
    new_pos=draw_text("Free heap: ",pos,COL_MEM_MGR_FG,-1,false,FONT_5x8);
    char heap_buffer[TEXT_INT32_SIZE];
    text_int32(heap_left(),heap_buffer);
    char digit_buffer[2];
    digit_buffer[1]=0;
    int comma_counter=strlen(heap_buffer);
    for (int i=0;i<strlen(heap_buffer);i++)
    {
        digit_buffer[0]=heap_buffer[i];
        new_pos=draw_text(digit_buffer,new_pos,COL_MEM_MGR_FG,-1,false,FONT_5x8);
        comma_counter--;
        if ((comma_counter%3==0)&&(comma_counter))
        {
            //Print comma
            digit_buffer[0]=',';
            new_pos=draw_text(digit_buffer,new_pos,COL_MEM_MGR_FG,-1,false,FONT_5x8);
        }
    }
    new_pos=draw_text(" bytes",new_pos,COL_MEM_MGR_FG,-1,false,FONT_5x8);
    dupdate();

    //Start or Resume so enter input loop
    //Heap must be at top even if not used since will be freed on exit
    select_heap(window.tab_index,window.selected_split);
    //uint8_t *heap_ptr=get_split_heap();
    int modifier=MODIFIER_NONE;
    bool redraw=true;
    while (1)
    {
        if (redraw)
        {

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

