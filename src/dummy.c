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
#include "structs.h"

int placeholder(int command_ID, struct WindowInfo *windows, int selected_window, const char *title)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct Point pos;
    int drawn_split;
    if (command_ID==COMMAND_REDRAW) 
    {
        drawn_split=window.selected_split^1;
        pos=window_pos(window,false);
    }
    else
    {
        drawn_split=window.selected_split;
        pos=window_pos(window,true);
    }

    //Always redraw whether START, RESUME, or REDRAW
    draw_rect(pos.x,pos.y,width,height,COL_BLACK,COL_BLACK);
    draw_text(title,pos,COL_GREEN,-1,false,FONT_5x8);
    pos.y+=10;

    switch (command_ID)
    {
        case COMMAND_START:
            draw_text("Start",pos,COL_GREEN,-1,false,FONT_5x8);
            break;
        case COMMAND_RESUME:
            draw_text("Resume",pos,COL_GREEN,-1,false,FONT_5x8);
            break;
        case COMMAND_REDRAW:
            draw_text("Redraw",pos,COL_GREEN,-1,false,FONT_5x8);
            //Return if only redrawing
            return COMMAND_DONE;
    }
    pos.y+=10;
    dupdate();

    //Start or Resume
    int modifier=MODIFIER_NONE;
    bool redraw=true;

    //Heap memory
    select_heap(window.tab_index,drawn_split);
    uint8_t *heap_ptr=get_split_heap();


    if (command_ID==COMMAND_START) 
        add_object((window.tab_index*2+window.selected_split)*40,heap_ptr);


    while (1)
    {
        if (redraw)
        {

        }
        redraw=true;
        
        int key=getkey_text(true,&modifier,NULL);

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

int text_editor(int command_ID, struct WindowInfo *windows, int selected_window)
{
    return placeholder(command_ID, windows, selected_window, "Text editor");
}

int python(int command_ID, struct WindowInfo *windows, int selected_window)
{
    return placeholder(command_ID, windows, selected_window, "MCU Python");
}

int emu_msp430(int command_ID, struct WindowInfo *windows, int selected_window)
{
    return placeholder(command_ID, windows, selected_window, "MSP430 emulator");
}

int emu_6502(int command_ID, struct WindowInfo *windows, int selected_window)
{
    return placeholder(command_ID, windows, selected_window, "6502 emulator");
}

int help(int command_ID, struct WindowInfo *windows, int selected_window)
{
    return placeholder(command_ID, windows, selected_window, "Help");
}

