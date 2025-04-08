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
#include "menu.h"
#include "structs.h"

int memory_manager(int command_ID, struct WindowInfo *windows, int selected_window)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct Point pos;
    if (command_ID==COMMAND_REDRAW) pos=window_pos(window,false);
    else pos=window_pos(window,true);

    //Always redraw whether START, RESUME, or REDRAW
    draw_rect(pos.x,pos.y,width,height,COL_MEM_MGR_BG,COL_MEM_MGR_BG);
    draw_text("Memory manager",pos,COL_MEM_MGR_FG,COL_MEM_MGR_BG,true,FONT_5x8);
    
    //Heap memory
    pos.y+=MEM_MGR_OUTLINE_HEIGHT;
    struct Point new_pos;
    char int32_buffer[TEXT_INT32_COMMAS_SIZE];
    new_pos=draw_text("Heap used: ",pos,COL_MEM_MGR_FG,COL_MEM_MGR_BG,false,FONT_5x8);
    text_int32_commas(heap_used(),int32_buffer);
    new_pos=draw_text(int32_buffer,new_pos,COL_MEM_MGR_FG,COL_MEM_MGR_BG,false,FONT_5x8);
    new_pos=draw_text(" bytes",new_pos,COL_MEM_MGR_FG,COL_MEM_MGR_BG,false,FONT_5x8);

    pos.y+=MEM_MGR_TEXT_HEIGHT;
    new_pos=draw_text("Heap free: ",pos,COL_MEM_MGR_FG,COL_MEM_MGR_BG,false,FONT_5x8);
    text_int32_commas(heap_left(),int32_buffer);
    new_pos=draw_text(int32_buffer,new_pos,COL_MEM_MGR_FG,COL_MEM_MGR_BG,false,FONT_5x8);
    new_pos=draw_text(" bytes",new_pos,COL_MEM_MGR_FG,COL_MEM_MGR_BG,false,FONT_5x8);

    //Calculate space used by each tab/split for use below
    uint32_t split_mem[TAB_COUNT][SPLIT_COUNT]={0};
    uint8_t *split_ptr=heap;
    for (int tab=0;tab<TAB_COUNT;tab++)
    {
        for (int split=0;split<SPLIT_COUNT;split++)
        {
            uint32_t current_tab=split_ptr[HEAP_TAB]; 
            uint32_t current_split=split_ptr[HEAP_SPLIT]; 
            split_mem[current_tab][current_split]=*(uint32_t *)split_ptr;
            split_ptr+=*(uint32_t *)split_ptr;
        }
    }

    //Splits and tabs
    pos.y+=MEM_MGR_TEXT_HEIGHT;
    new_pos=pos;
    for (int tab=0;tab<TAB_COUNT;tab++)
    {
        for (int split=0;split<SPLIT_COUNT;split++)
        {
            if (split==0)
            {
                new_pos.x=pos.x;

                //Print tab number
                char print_buffer[]={tab+'1',':',0};
                new_pos=draw_text(print_buffer,new_pos,COL_MEM_MGR_FG,manager_colors[tab],false,FONT_5x8);
            }
            else new_pos.x+=MEM_MGR_COL2_SPACING;
            
            //Print program name
            const char *prog_name;
            if (windows[tab].split[split].ID==ID_NONE) prog_name="   --   ";
            else prog_name=program_titles[windows[tab].split[split].ID];
            new_pos=draw_text(prog_name,new_pos,COL_MEM_MGR_FG,manager_colors[tab],false,FONT_5x8);

            //Print memory used for each tab/split
            char mem_buffer[TEXT_INT32_HUMAN_SIZE];
            mem_buffer[TEXT_INT32_HUMAN_SIZE-1]=0;
            char num_buffer[TEXT_INT32_HUMAN_SIZE];
            text_int32_human(split_mem[tab][split],num_buffer);
            int num_buffer_index=0;
            for (int i=0;i<TEXT_INT32_HUMAN_SIZE-1;i++)
            {
                if (num_buffer[num_buffer_index])
                {
                    mem_buffer[i]=num_buffer[num_buffer_index];
                    num_buffer_index++;
                }
                else mem_buffer[i]=' ';
            }
            new_pos=draw_text(mem_buffer,new_pos,COL_MEM_MGR_FG,manager_colors[tab],false,FONT_5x8);
        }
        new_pos.y+=MEM_MGR_TEXT_HEIGHT;
    }
    dupdate();

    //Redraw only - exit
    if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;

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

