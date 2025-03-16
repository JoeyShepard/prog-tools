//placeholder functions for menu
#include <string.h>

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
            dupdate();

            char hex_buffer[TEXT_HEX32_SIZE];

            //Heap address
            text_hex32((uint32_t)heap,hex_buffer,8);
            pos.y+=10;
            draw_text(hex_buffer,pos,COL_WHITE,-1,false,FONT_5x8);
            dupdate();
            
            //memcpy uint32
            uint32_t a=0x12345678;
            uint32_t b;
            memcpy(&b,&a,sizeof(uint32_t));
            text_hex32(b,hex_buffer,8);
            pos.y+=10;
            draw_text(hex_buffer,pos,COL_WHITE,-1,false,FONT_5x8);
            dupdate();

            //memcpy uint32 to uint8
            uint8_t test_array[7];
            a=0x12345678;
            memcpy(test_array,&a,sizeof(uint32_t));
            a=0x4567890A;
            memcpy(test_array+1,&a,sizeof(uint32_t));
            a=0x7890ABCD;
            memcpy(test_array+2,&a,sizeof(uint32_t));
            a=0xABCDEF0;
            memcpy(test_array+3,&a,sizeof(uint32_t));
            pos.y+=10;
            draw_text("Values written",pos,COL_WHITE,-1,false,FONT_5x8);
            dupdate();

            //check values
            pos.y+=10;
            struct point pos_save=pos;
            for (int i=0;i<7;i++)
            {
                text_hex32(*(test_array+i),hex_buffer,2); 
                pos=draw_text(hex_buffer,pos,COL_WHITE,-1,false,FONT_5x8);
                pos=draw_text(" ",pos,COL_WHITE,-1,false,FONT_5x8);
            }
            pos=pos_save;

            //memcpy uint8 to uint32
            for (int i;i<4;i++)
            {
                memcpy(&b,test_array+i,sizeof(uint32_t));
                text_hex32(b,hex_buffer,8);
                pos.y+=10;
                draw_text(hex_buffer,pos,COL_WHITE,-1,false,FONT_5x8);
                dupdate();
            }

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


