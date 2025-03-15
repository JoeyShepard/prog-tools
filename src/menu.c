//TODO: copied from manager.c - don't need all of these
#include "compatibility.h"
#include "dummy.h"
#include "error.h"
#include "getkey.h"
#include "graphics.h"
#include "manager.h"
#include "menu.h"
#include "structs.h"
#include "text.h"

const char *program_list[]=
{
    "command line",
    "text editor",
    "Forth",
    "MCU Python",
    "split vertically",
    "split horizontally",
    "close",
    "help"
};

const int program_IDs[]=
{
    ID_COMMAND_LINE,
    ID_TEXT_EDITOR,
    ID_FORTH,
    ID_MCU_PYTHON,
    ID_SPLIT_VERTICALLY,
    ID_SPLIT_HORIZONTALLY,
    ID_CLOSE_SPLIT,
    ID_HELP
};

int (*menu_functions[])(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr)=
{
    &command_line,
    &text_editor,
    &forth,
    &python,
    NULL,
    NULL,
    NULL,
    &help,
    
    //Menu handler comes at end
    &menu_handler
};

void draw_menu(struct WindowInfo window, bool enabled)
{
    int menu_x;
    int menu_y;
    int drawn_split=0;
   
    if (enabled)
    {
        drawn_split=window.selected_split;
    }
    else
    {
        //Drawing deselected menu
        drawn_split=window.selected_split^1;
    }

    if (window.split_state==WINDOW_WHOLE)
    {
        //Whole window - no split
        draw_rect(WINDOW_WHOLE_X0,WINDOW_WHOLE_Y0,WINDOW_WHOLE_WIDTH,WINDOW_WHOLE_HEIGHT,COL_MENU_BG,COL_MENU_BG);

        menu_x=WINDOW_WHOLE_X0;
        menu_y=WINDOW_WHOLE_Y0;
    }
    else if (window.split_state==WINDOW_VSPLIT)
    {
        //Windows split vertically
        int window_y;
        if (drawn_split==0) window_y=WINDOW_VSPLIT_TOP_Y0;
        else window_y=WINDOW_VSPLIT_BOTTOM_Y0;
        menu_x=WINDOW_VSPLIT_X0;
        menu_y=window_y;
        if (enabled)
            draw_rect(WINDOW_VSPLIT_X0,window_y,WINDOW_VSPLIT_WIDTH,WINDOW_VSPLIT_HEIGHT,COL_MENU_BG,COL_MENU_BG);
        else draw_rect(WINDOW_VSPLIT_X0,window_y,WINDOW_VSPLIT_WIDTH,WINDOW_VSPLIT_HEIGHT,COL_MENU_DE_BG,COL_MENU_DE_BG);
    }
    else if (window.split_state==WINDOW_HSPLIT)
    {
        //Windows split horizontally
        int window_x;
        if (drawn_split==0) window_x=WINDOW_HSPLIT_LEFT_X0;
        else window_x=WINDOW_HSPLIT_RIGHT_X0;
        menu_x=window_x;
        menu_y=WINDOW_HSPLIT_Y0;

        if (enabled)
            draw_rect(window_x,WINDOW_HSPLIT_Y0,WINDOW_HSPLIT_WIDTH,WINDOW_HSPLIT_HEIGHT,COL_MENU_BG,COL_MENU_BG);
        else draw_rect(window_x,WINDOW_HSPLIT_Y0,WINDOW_HSPLIT_WIDTH,WINDOW_HSPLIT_HEIGHT,COL_MENU_DE_BG,COL_MENU_DE_BG);
    }

    //Draw menu options
    struct point pos=
    {
        menu_x+MENU_X_OFFSET,
        menu_y+MENU_Y_OFFSET
    };

    //Loop thorugh menu options
    for (int j=0;j<PROG_LIST_LEN;j++)
    {
        char menu_print_buffer[MENU_BUFFER];
        menu_print_buffer[0]='1'+j;
        menu_print_buffer[1]=':';
        for (int k=0;k<MENU_BUFFER;k++)
        {
            //-1 for zero terminator, -2 for "1:"
            if (k==MENU_BUFFER-1-2)
            {
                //Menu text too long to fit into buffer
                error_exit(ERROR_MENU_TEXT_TOO_LONG);
            }
            if (program_list[j][k]==0)
            {
                //Hit end of copied string - done
                break;
            }
            menu_print_buffer[k+2]=program_list[j][k]; 
            menu_print_buffer[k+3]=0;
        }
        if (j==window.split[drawn_split].menu_selection)
        {
            //Selected menu option
            if (enabled)
                outline_text(menu_print_buffer,pos,COL_MENU_SEL_TEXT,manager_colors[window.tab_index],manager_colors[window.tab_index],false,FONT_5x8);
            else outline_text(menu_print_buffer,pos,COL_MENU_DE_SEL_TEXT,COL_MENU_DE_SEL_FILL,COL_MENU_DE_SEL_FILL,false,FONT_5x8);
        }
        else
        {
            //Regular menu option
            if (enabled)
                outline_text(menu_print_buffer,pos,COL_MENU_TEXT,-1,-1,false,FONT_5x8);
            else outline_text(menu_print_buffer,pos,COL_MENU_DE_TEXT,-1,-1,false,FONT_5x8);
        }
        pos.y+=MENU_HEIGHT;
    }
}

int menu_handler(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr)
{
    int modifier=MODIFIER_NONE;

    if (command_ID==COMMAND_REDRAW) 
    {
        //Redraw screen and exit
        draw_menu(windows[selected_window],false);
        return COMMAND_DONE;
    }

    int *menu_selection=&windows[selected_window].split[windows[selected_window].selected_split].menu_selection;

    //command_ID is START or RESUME - loop
    while(1)
    {
        draw_menu(windows[selected_window],true);
        draw_modifier(modifier);
        dupdate();

        //Wait for kepress
        int key=getkey_text(true,&modifier);
            
        if (key==VKEY_EXE)
        {
            switch (*menu_selection)
            {
                case ID_COMMAND_LINE:
                case ID_TEXT_EDITOR:
                case ID_FORTH:
                case ID_MCU_PYTHON:
                case ID_HELP:
                    windows[selected_window].split[windows[selected_window].selected_split].ID=*menu_selection;
                
                    return (*menu_functions[*menu_selection])(COMMAND_START,windows,selected_window,NULL);
            }
        }
        else if (key==VKEY_UP)
        {
            (*menu_selection)--;
            if ((*menu_selection)<0) *menu_selection=PROG_LIST_LEN-1;
        }
        else if (key==VKEY_DOWN)
        {
            (*menu_selection)++;
            if (*menu_selection==PROG_LIST_LEN) *menu_selection=0;
        }
        else if (key==VKEY_EXIT)
        {
            //Exit if on PC
            wrapper_exit();
        }
        else
        {
            //Handle system keys like MENU, OFF, etc in caller
            int return_command=sys_key_handler(key);
            if (return_command!=COMMAND_NONE) return return_command;
        }

        //TODO: need this??? Had in window_manager below before moving here
        //delay();
    }
}

