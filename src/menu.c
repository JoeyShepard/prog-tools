//TODO: copied from manager.c - don't need all of these
#include <string.h>

#include "compatibility.h"
#include "dummy.h"
#include "error.h"
#include "getkey.h"
#include "graphics.h"
#include "manager.h"
#include "mem.h"
#include "memory_manager.h"
#include "menu.h"
#include "structs.h"
#include "text.h"
    
static const char *menu_keys="1234567890+";

static const char *program_list[]=
{
    "Calculator shell",
    "Text editor",
    "Forth",
    "MCU Python",
    "MSP430 emulator",
    "6502 emulator",
    "Split vertically",
    "Split horizontally",
    "Close",
    "Memory manager",
    "Help",
};

//Each entry needs ot be 8 characters
const char *program_titles[]=
{
    "Shell   ",
    "Editor  ",
    "Forth   ",
    "Python  ",
    "MSP430  ",
    "6502    ",
    NULL,
    NULL,
    NULL,
    "Memory  ",
    "Help    ",
    //None - show menu
    "        "
};


int (*menu_functions[])(int command_ID, struct WindowInfo *windows, int selected_window)=
{
    &command_line,
    &text_editor,
    &forth,
    &python,
    &emu_msp430,
    &emu_6502,
    NULL,
    NULL,
    NULL,
    &memory_manager,
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
        menu_print_buffer[0]=menu_keys[j];
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
            {
                //Gray out option if necessary - ie Close option when full screen
                int32_t text_color=COL_MENU_TEXT;
                if (window.split_state==WINDOW_WHOLE)
                {
                    if (j==ID_CLOSE_SPLIT) text_color=COL_MENU_DISABLED_TEXT;
                }
                else
                {
                    if ((j==ID_SPLIT_VERTICALLY)||(j==ID_SPLIT_HORIZONTALLY)) text_color=COL_MENU_DISABLED_TEXT;
                }
                outline_text(menu_print_buffer,pos,text_color,-1,-1,false,FONT_5x8);
            }
            else outline_text(menu_print_buffer,pos,COL_MENU_DE_TEXT,-1,-1,false,FONT_5x8);
        }
        
        //Put half of menu items in second column if split horizontally
        if ((j==PROG_COL2_ID)&&(window.split_state==WINDOW_VSPLIT))
        {
            pos.x=menu_x+MENU_X_OFFSET2;
            pos.y=menu_y+MENU_Y_OFFSET;
        }
        else pos.y+=MENU_HEIGHT;
    }
}

bool menu_disabled(struct WindowInfo window,int menu_selection)
{
    if ((window.split_state==WINDOW_WHOLE)&&(menu_selection==ID_CLOSE_SPLIT)) return true;
    else if ((window.split_state!=WINDOW_WHOLE)&&(menu_selection==ID_SPLIT_VERTICALLY)) return true;
    else if ((window.split_state!=WINDOW_WHOLE)&&(menu_selection==ID_SPLIT_HORIZONTALLY)) return true;
    else return false;
}

int menu_handler(int command_ID, struct WindowInfo *windows, int selected_window)
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
        
        //First, check for menu keys. Simplifies checks for keys like 0 and + after 9.
        for (size_t i=0;i<strlen(menu_keys);i++)
        {
            if (menu_keys[i]==key_printable[key]) 
            {
                //Match found. Record selection and process below with VKEY_EXE.
                *menu_selection=i;
                key=VKEY_MENU_SELECTION;
                break;
            }
        }

        //Next, check for all other keys
        switch (key)
        {
            case VKEY_MENU_SELECTION:
                //See above - menu key (1-9,0,+) pressed. *menu_selection set above.
                //Fall through!
            case VKEY_EXE:
                switch (*menu_selection)
                {
                    case ID_COMMAND_LINE:
                    case ID_TEXT_EDITOR:
                    case ID_FORTH:
                    case ID_MCU_PYTHON:
                    case ID_MSP430_EMU:
                    case ID_6502_EMU:
                    case ID_MEMORY_MANAGER:
                    case ID_HELP:
                        windows[selected_window].split[windows[selected_window].selected_split].ID=*menu_selection;
                    
                        //Redraw to show new title
                        draw_titles(windows,selected_window);

                        return (*menu_functions[*menu_selection])(COMMAND_START,windows,selected_window);
                    case ID_SPLIT_VERTICALLY:
                    case ID_SPLIT_HORIZONTALLY:
                        if (windows[selected_window].split_state==WINDOW_WHOLE)
                        {
                            if (*menu_selection==ID_SPLIT_VERTICALLY) windows[selected_window].split_state=WINDOW_VSPLIT;
                            else if (*menu_selection==ID_SPLIT_HORIZONTALLY) windows[selected_window].split_state=WINDOW_HSPLIT;
                            windows[selected_window].split[1].ID=ID_NONE;
                            windows[selected_window].split[1].menu_selection=0;
                            windows[selected_window].selected_split=1;
                            *menu_selection=0;
                            return COMMAND_DONE;    //Manager will redraw windows and return to menu
                        }
                        break;
                    case ID_CLOSE_SPLIT:
                        if (windows[selected_window].split_state!=WINDOW_WHOLE)
                        {
                            if (windows[selected_window].selected_split==0)
                            {
                                windows[selected_window].split_state=WINDOW_WHOLE;

                                //Closing top split so need to move bottom split to full screen
                                //(or closing left split and moving right split)
                                uint8_t *split_ptr=heap;
                                for (int i=0;i<TAB_COUNT*SPLIT_COUNT;i++)
                                {
                                    if (split_ptr[HEAP_TAB]==windows[selected_window].tab_index)
                                    {
                                        //Swap split IDs for heap memory
                                        split_ptr[HEAP_SPLIT]^=1;
                                    }
                                    split_ptr+=*(uint32_t *)split_ptr;
                                }

                                //Copy menu selection and ID
                                windows[selected_window].split[0].ID=windows[selected_window].split[1].ID;
                                windows[selected_window].split[1].ID=ID_NONE;
                                int *new_menu_selection=&windows[selected_window].split[0].menu_selection;
                                *new_menu_selection=windows[selected_window].split[1].menu_selection;
                                while (menu_disabled(windows[selected_window],*new_menu_selection))
                                {
                                    //If new menu selection is disabled, go to next selection
                                    (*new_menu_selection)++;
                                    if (*new_menu_selection==PROG_LIST_LEN) *new_menu_selection=0;
                                }
                            }
                            else
                            {
                                //Closing bottom split
                                windows[selected_window].selected_split=0;
                                windows[selected_window].split_state=WINDOW_WHOLE;
                            }
                            return COMMAND_DONE;    //Manager will redraw windows and return to menu
                        }
                        break;
                }
                break;
            case VKEY_UP:
                do
                {
                    (*menu_selection)--;
                    if ((*menu_selection)<0) *menu_selection=PROG_LIST_LEN-1;

                    //Skip grayed out menu items
                } while (menu_disabled(windows[selected_window],*menu_selection));
                break;
            case VKEY_DOWN:
                do
                {
                    (*menu_selection)++;
                    if (*menu_selection==PROG_LIST_LEN) *menu_selection=0;

                    //Skip grayed out menu items
                } while(menu_disabled(windows[selected_window],*menu_selection));
                break;
            case VKEY_LEFT:
                if (windows[selected_window].split_state==WINDOW_VSPLIT)
                {
                    if (*menu_selection>PROG_COL2_ID)
                    {
                        *menu_selection-=PROG_COL2_ID+1;
                        if (*menu_selection>PROG_COL2_ID)
                        {
                            //If second column is longer, jump to last item on left
                            *menu_selection=PROG_COL2_ID;
                        }
                    }
                }
                break;
            case VKEY_RIGHT:
                if (windows[selected_window].split_state==WINDOW_VSPLIT)
                {
                    if (*menu_selection<=PROG_COL2_ID)
                    {
                        *menu_selection+=PROG_COL2_ID+1;
                        if (*menu_selection>=PROG_LIST_LEN)
                        {
                            //If first column is longer, jump to last item on right
                            *menu_selection=PROG_LIST_LEN-1;
                        }
                        while (menu_disabled(windows[selected_window],*menu_selection))
                        {
                            //Skip disabled menu options 
                            (*menu_selection)++;
                        }
                    }
                }
                break;
            case VKEY_EXIT:
                //Exit if on PC
                wrapper_exit();
                break;
            default:
                //Handle system keys like MENU, OFF, etc in caller
                int return_command=sys_key_handler(key);
                if (return_command!=COMMAND_NONE) return return_command;
        }

        //TODO: need this??? Had in window_manager below before moving here
        //delay();
    }
}

