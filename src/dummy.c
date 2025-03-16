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
            //Return if only redrawing
            return COMMAND_DONE;
    }
    dupdate();

    //Start or Resume so enter input loop
    pos.y+=10;
    select_heap(window.tab_index,window.selected_split);
    uint8_t *heap_ptr=get_split_heap();
    int modifier=MODIFIER_NONE;
    bool redraw=true;
    while (1)
    {
        if (redraw)
        {
            struct point new_pos=pos;
            char num_buffer[TEXT_INT32_SIZE];
            uint8_t *obj_ptr=heap_ptr+HEAP_OBJECTS;

            //Heap left
            new_pos=pos;
            new_pos=draw_text("Heap left: ",new_pos,COL_WHITE,COL_BLACK,false,FONT_5x8);
            text_int32(heap_left(),num_buffer);
            draw_text(num_buffer,new_pos,COL_WHITE,COL_BLACK,false,FONT_5x8);
            dupdate();

            //debug_heap(0);

            //Objects
            new_pos.y+=10;
            new_pos.x=pos.x;
            obj_ptr=heap_ptr+HEAP_OBJECTS;
            int obj_count=0;
            while(*(uint32_t *)obj_ptr)
            {
                obj_count++;
                obj_ptr+=*(uint32_t *)obj_ptr;

            }
            new_pos=draw_text("Object count: ",new_pos,COL_WHITE,COL_BLACK,false,FONT_5x8);
            text_int32(obj_count,num_buffer);
            draw_text(num_buffer,new_pos,COL_WHITE,COL_BLACK,false,FONT_5x8);
            dupdate();
            
            new_pos.y+=10;
            new_pos.x=pos.x;
            new_pos=draw_text("Objects total size: ",new_pos,COL_WHITE,COL_BLACK,false,FONT_5x8);
            text_int32(obj_ptr-heap_ptr-HEAP_OBJECTS,num_buffer);
            draw_text(num_buffer,new_pos,COL_WHITE,COL_BLACK,false,FONT_5x8);
            dupdate();

            //Check object values
            new_pos.y+=10;
            new_pos.x=pos.x;
            obj_ptr=heap_ptr+HEAP_OBJECTS;

            int search_val=(window.tab_index<<4)|window.selected_split;
            //printf("Expecting %X\n",search_val);
            while(*(uint32_t *)obj_ptr)
            {
                //printf("%p: %X\n",obj_ptr,*(uint32_t *)obj_ptr);
                //printf("(@%p = %X)\n",obj_ptr+*(uint32_t *)obj_ptr,*(uint32_t *)(obj_ptr+*(uint32_t *)obj_ptr));
                uint8_t *start_ptr=obj_ptr+4;
                obj_ptr+=*(uint32_t *)obj_ptr;
                //printf(" - %p: ",start_ptr);
                for (;start_ptr<obj_ptr;start_ptr++)
                {
                    if (*start_ptr!=search_val)
                    {
                        struct point error_pos={0,0};
                        draw_text("ERROR: test values don't match!",error_pos,COL_WHITE,COL_RED,false,FONT_5x8);
                        getkey_wrapper(true);
                        getkey_wrapper(true);
                        getkey_wrapper(true);

                        return COMMAND_DONE;
                    }
                }
            }
            //printf("\n");
            new_pos=draw_text("Test values match",new_pos,COL_WHITE,COL_BLACK,false,FONT_5x8);
        }
        redraw=true;
        
        int key=getkey_text(true,&modifier);

        //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
        switch (key)
        {
            case VKEY_EXE:
                int obj_size=((window.tab_index+1)*10+window.selected_split)*4;
                uint8_t *debug_ptr=add_object(obj_size,heap_ptr);
                int search_val=(window.tab_index<<4)|window.selected_split;

                //printf("New object - writing %d to %p %X times\n\n",search_val,debug_ptr,obj_size);

                for (int i=0;i<obj_size;i++)
                {
                    *debug_ptr=search_val;
                    debug_ptr++;
                }
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


