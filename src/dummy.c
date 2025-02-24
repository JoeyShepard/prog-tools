//placeholder functions for menu

#include <stdbool.h>
#include <stdint.h>
#include "compatibility.h"
#include "getkey.h"
#include "graphics.h"
#include "text.h"
#include "dummy.h"
#include "manager.h"
#include "structs.h"

int placeholder(int command_ID, struct WindowInfo window, const char *title)
{
    struct point pos=window_pos(window);
    int width=window_width(window);
    int height=window_height(window);

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
            break;
    }
   
    dupdate();

    int modifier=MODIFIER_NONE;
    switch (command_ID)
    {
        case COMMAND_START:
        case COMMAND_RESUME:
            while (1)
            {
                //Wait for kepress
                int key=getkey_wrapper(true);
                if ((key==VKEY_ALPHA)||(key==VKEY_SHIFT))
                {
                    //Modifier key pressed
                    modifier=update_modifier(modifier,key);
                }
                else
                {
                    //Non-modifier key pressed
                    int key_modifier=current_modifier(modifier);
                    modifier=use_modifier(modifier);
                    int modified_key=modify_keypress(key_modifier,key);
                    
                    switch (modified_key)
                    {
                        case VKEY_EXIT:
                            return COMMAND_EXIT;
                        case VKEY_MENU:
                            return COMMAND_MENU;
                        case VKEY_ACOFF:
                            return COMMAND_OFF;
                        case VKEY_ANGLE:
                            //shift+XOT - switch selected window split
                            if (window.split_state!=WINDOW_WHOLE) return COMMAND_SWAP;
                            break;
                        case VKEY_F1:
                            return COMMAND_TAB1;
                        case VKEY_F2:
                            return COMMAND_TAB2;
                        case VKEY_F3:
                            return COMMAND_TAB3;
                        case VKEY_F4:
                            return COMMAND_TAB4;
                        case VKEY_F5:
                            return COMMAND_TAB5;
                        case VKEY_F6:
                            return COMMAND_TAB6;
                    }
                }
            }
            break;
        case COMMAND_REDRAW:
            return COMMAND_DONE;
            break;
    }
}

int command_line(int command_ID, struct WindowInfo window, uint8_t *heap_ptr)
{
    placeholder(command_ID, window, "text editor");
}

int text_editor(int command_ID, struct WindowInfo window, uint8_t *heap_ptr)
{
    placeholder(command_ID, window, "text editor");
}

int forth(int command_ID, struct WindowInfo window, uint8_t *heap_ptr)
{
    placeholder(command_ID, window, "Forth");
}

int python(int command_ID, struct WindowInfo window, uint8_t *heap_ptr)
{
    placeholder(command_ID, window, "MCU-Python");
}

int help(int command_ID, struct WindowInfo window, uint8_t *heap_ptr)
{
    placeholder(command_ID, window, "help");
}


