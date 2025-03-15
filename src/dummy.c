//placeholder functions for menu

#include "compatibility.h"
#include "getkey.h"
#include "graphics.h"
#include "text.h"
#include "dummy.h"
#include "manager.h"
#include "structs.h"

int placeholder(int command_ID, struct WindowInfo *windows, int selected_window, const char *title)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct point pos;
    if (command_ID==COMMAND_REDRAW) pos=window_pos(window,false);
    else pos=window_pos(window,true);

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
            return COMMAND_DONE;
    }
   
    dupdate();

    int modifier=MODIFIER_NONE;
    switch (command_ID)
    {
        case COMMAND_START:
        case COMMAND_RESUME:
            while (1)
            {
                int key=getkey_text(true,&modifier);
                int return_command=sys_key_handler(key);
                if (return_command!=COMMAND_NONE) return return_command;
            }
            break;
        case COMMAND_REDRAW:
            return COMMAND_DONE;
            break;
    }

    //Shouldn't reach here - added to silence warning
    return COMMAND_DONE;
}

int command_line(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr)
{
    return placeholder(command_ID, windows, selected_window, "command line");
}

int text_editor(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr)
{
    return placeholder(command_ID, windows, selected_window, "text editor");
}

int forth(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr)
{
    return placeholder(command_ID, windows, selected_window, "Forth");
}

int python(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr)
{
    return placeholder(command_ID, windows, selected_window, "MCU-Python");
}

int help(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr)
{
    return placeholder(command_ID, windows, selected_window, "help");
}


