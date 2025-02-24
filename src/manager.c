#include "command.h"
#include "compatibility.h"
#include "dummy.h"
#include "error.h"
#include "getkey.h"
#include "graphics.h"
#include "manager.h"
#include "text.h"

static uint16_t manager_colors[]=
{
    C_RGB(0,COL_1_4,COL_MID),       //Blue
    C_RGB(COL_1_4,COL_MID,0),       //Green
    C_RGB(COL_MID,COL_MID,0),       //Yellow
    C_RGB(COL_MID,COL_1_4,0),       //Orange
    C_RGB(COL_MID,0,0),             //Red
    C_RGB(COL_MID,0,COL_MID),       //Purple
};

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

const int (*menu_functions[])(int command_ID, struct WindowInfo window, uint8_t *heap_ptr)=
{
    &command_line,
    &text_editor,
    &forth,
    &python,
    NULL,
    NULL,
    NULL,
    &help
};

void window_manager()
{
    int modifier=MODIFIER_NONE;
    int selected_window=0;

    //Initialize windows
    struct WindowInfo windows[TAB_COUNT];
    for (int i=0;i<TAB_COUNT;i++)
    {
        windows[i].title[0]='1'+i;
        windows[i].title[1]=':';
        for (int j=2;j<TAB_TITLE_LEN-1;j++)
        {
            windows[i].title[j]=' ';
        }
        windows[i].title[TAB_TITLE_LEN-1]=0;
        windows[i].split_state=WINDOW_WHOLE;
        windows[i].selected_split=0;
        windows[i].split[0].ID=ID_NONE;
        windows[i].split[1].ID=ID_NONE;
        windows[i].split[0].menu_selection=0;
        windows[i].split[1].menu_selection=0;
        windows[i].tab_index=i;
    }

    //TODO: remove
    windows[1].split_state=WINDOW_VSPLIT;
    windows[1].selected_split=0;
    windows[2].split_state=WINDOW_VSPLIT;
    windows[2].selected_split=1;
    windows[3].split_state=WINDOW_HSPLIT;
    windows[3].selected_split=0;
    windows[4].split_state=WINDOW_HSPLIT;
    windows[4].selected_split=1;

    //Main loop
    while (true)
    {
        //Render graphics
        draw_manager(windows,modifier,selected_window);
        draw_splits(windows[selected_window]);
        dupdate();

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
            
            //Used below, slightly more readable
            int *menu_selection=&windows[selected_window].split[windows[selected_window].selected_split].menu_selection;

            //Process EXE key to reuse logic below for menu, off, etc keys
            if (modified_key==VKEY_EXE)
            {
                modified_key=VKEY_NONE;
                switch (*menu_selection)
                {
                    case ID_COMMAND_LINE:
                    case ID_TEXT_EDITOR:
                    case ID_FORTH:
                    case ID_MCU_PYTHON:
                    case ID_HELP:
                        int return_command=(*menu_functions[*menu_selection])(COMMAND_START,windows[selected_window],NULL);
                        switch (return_command)
                        {
                            case COMMAND_EXIT:
                                //Program done executing
                                windows[selected_window].split[windows[selected_window].selected_split].ID=ID_NONE;
                                //TODO: free memory
                                break;
                            case COMMAND_MENU:
                                modified_key=VKEY_MENU;
                                break;
                            case COMMAND_OFF:
                                modified_key=VKEY_ACOFF;
                                break;
                            case COMMAND_SWAP:
                                modified_key=VKEY_ANGLE;
                                break;
                            case COMMAND_TAB1:
                                modified_key=VKEY_F1;
                                break;
                            case COMMAND_TAB2:
                                modified_key=VKEY_F2;
                                break;
                            case COMMAND_TAB3:
                                modified_key=VKEY_F3;
                                break;
                            case COMMAND_TAB4:
                                modified_key=VKEY_F4;
                                break;
                            case COMMAND_TAB5:
                                modified_key=VKEY_F5;
                                break;
                            case COMMAND_TAB6:
                                modified_key=VKEY_F6;
                                break;
                        }
                        break;
                }
            }

            //Process keypress
            switch (modified_key)
            {
                case VKEY_EXIT:
                    //Exit if on PC
                    wrapper_exit();
                    break;
                case VKEY_MENU:
                    //Save here if necessary
                    gint_osmenu();
                    break;
                case VKEY_ACOFF:
                    //Save here too to be safe
                    gint_poweroff(true);
                    break;
                case VKEY_F1:
                    selected_window=0;
                    break;
                case VKEY_F2:
                    selected_window=1;
                    break;
                case VKEY_F3:
                    selected_window=2;
                    break;
                case VKEY_F4:
                    selected_window=3;
                    break;
                case VKEY_F5:
                    selected_window=4;
                    break;
                case VKEY_F6:
                    selected_window=5;
                    break;
                case VKEY_ANGLE:
                    //shift+XOT - switch selected window split
                    if (windows[selected_window].split_state!=WINDOW_WHOLE)
                    {
                        windows[selected_window].selected_split^=1;
                    }
                    break;
                case VKEY_UP:
                    (*menu_selection)--;
                    if ((*menu_selection)<0) *menu_selection=PROG_LIST_LEN-1;
                    break;
                case VKEY_DOWN:
                    (*menu_selection)++;
                    if (*menu_selection==PROG_LIST_LEN) *menu_selection=0;
                    break;
            }
        }
        delay();
    }
}

int update_modifier(int modifier,int key)
{
    if (key==VKEY_ALPHA)
    {
        switch (modifier) 
        {
            case MODIFIER_NONE:
                return MODIFIER_ALPHA_LOWER;
            case MODIFIER_ALPHA_LOWER:
                return MODIFIER_ALPHA_UPPER;
            case MODIFIER_ALPHA_LOWER_LOCK:
            case MODIFIER_ALPHA_UPPER:
            case MODIFIER_ALPHA_UPPER_LOCK:
                return MODIFIER_NONE;
            case MODIFIER_SHIFT_NONE:
                return MODIFIER_ALPHA_LOWER_LOCK;
            case MODIFIER_SHIFT_ALPHA_LOWER:
            case MODIFIER_SHIFT_ALPHA_LOWER_LOCK:
                return MODIFIER_ALPHA_LOWER_LOCK;
            case MODIFIER_SHIFT_ALPHA_UPPER:
            case MODIFIER_SHIFT_ALPHA_UPPER_LOCK:
                return MODIFIER_ALPHA_UPPER_LOCK;
        }
    }
    else if (key==VKEY_SHIFT)
    {
        switch (modifier) 
        {
            case MODIFIER_NONE:
                return MODIFIER_SHIFT_NONE;
            case MODIFIER_ALPHA_LOWER:
                return MODIFIER_SHIFT_ALPHA_LOWER;
            case MODIFIER_ALPHA_LOWER_LOCK:
                return MODIFIER_SHIFT_ALPHA_LOWER_LOCK;
            case MODIFIER_ALPHA_UPPER:
                return MODIFIER_SHIFT_ALPHA_UPPER;
            case MODIFIER_ALPHA_UPPER_LOCK:
                return MODIFIER_SHIFT_ALPHA_UPPER_LOCK;
            case MODIFIER_SHIFT_NONE:
            case MODIFIER_SHIFT_ALPHA_LOWER:
                return MODIFIER_NONE;
            case MODIFIER_SHIFT_ALPHA_LOWER_LOCK:
                return MODIFIER_ALPHA_LOWER_LOCK;
            case MODIFIER_SHIFT_ALPHA_UPPER:
                return MODIFIER_NONE;
            case MODIFIER_SHIFT_ALPHA_UPPER_LOCK:
                return MODIFIER_ALPHA_UPPER_LOCK;
        }
    }

    return modifier;
}

int current_modifier(int modifier)
{
    switch (modifier)
    {
        case MODIFIER_NONE:
            return MODIFIER_NONE;
        case MODIFIER_ALPHA_LOWER:
        case MODIFIER_ALPHA_LOWER_LOCK:
            return MODIFIER_ALPHA_LOWER;
        case MODIFIER_ALPHA_UPPER:
        case MODIFIER_ALPHA_UPPER_LOCK:
            return MODIFIER_ALPHA_UPPER;
        case MODIFIER_SHIFT_NONE:
        case MODIFIER_SHIFT_ALPHA_LOWER:
        case MODIFIER_SHIFT_ALPHA_LOWER_LOCK:
        case MODIFIER_SHIFT_ALPHA_UPPER:
        case MODIFIER_SHIFT_ALPHA_UPPER_LOCK:
            return MODIFIER_SHIFT_NONE;
    }
    return modifier;
}

int use_modifier(int modifier)
{
    switch (modifier)
    {
        case MODIFIER_NONE:
            return MODIFIER_NONE;
        case MODIFIER_ALPHA_LOWER:
            return MODIFIER_NONE;
        case MODIFIER_ALPHA_LOWER_LOCK:
            return MODIFIER_ALPHA_LOWER_LOCK;
        case MODIFIER_ALPHA_UPPER:
            return MODIFIER_NONE;
        case MODIFIER_ALPHA_UPPER_LOCK:
            return MODIFIER_ALPHA_UPPER_LOCK;
        case MODIFIER_SHIFT_NONE:
            return MODIFIER_NONE;
        case MODIFIER_SHIFT_ALPHA_LOWER:
            return MODIFIER_NONE;
        case MODIFIER_SHIFT_ALPHA_LOWER_LOCK:
            return MODIFIER_ALPHA_LOWER_LOCK;
        case MODIFIER_SHIFT_ALPHA_UPPER:
            return MODIFIER_NONE;
        case MODIFIER_SHIFT_ALPHA_UPPER_LOCK:
            return MODIFIER_ALPHA_UPPER_LOCK;
    }
    return modifier;
}

int modify_keypress(int modifier, int key)
{
    switch(modifier)
    {
        case MODIFIER_NONE:
            return key;
        case MODIFIER_ALPHA_LOWER:
            return key_lower[key];
        case MODIFIER_ALPHA_UPPER:
            return key_upper[key];
        case MODIFIER_SHIFT_NONE:
            return key_shifted[key];
        default:
            return key;
    }
}

void draw_modifier(int modifier)
{
    struct point pos={0,0};
    char text[2]=" ";

    //Draw shift key
    switch (modifier)
    {
        case MODIFIER_NONE:
        case MODIFIER_ALPHA_LOWER:
        case MODIFIER_ALPHA_LOWER_LOCK:
        case MODIFIER_ALPHA_UPPER:
        case MODIFIER_ALPHA_UPPER_LOCK:
            text[0]=' ';
            pos=outline_text(text,pos,COL_MOD_BG,COL_MOD_BG,COL_MOD_BG,false,FONT_5x8);
            break;
        case MODIFIER_SHIFT_NONE:
        case MODIFIER_SHIFT_ALPHA_LOWER:
        case MODIFIER_SHIFT_ALPHA_LOWER_LOCK:
        case MODIFIER_SHIFT_ALPHA_UPPER:
        case MODIFIER_SHIFT_ALPHA_UPPER_LOCK:
            text[0]='S';
            pos=outline_text(text,pos,COL_SHIFT_BG,COL_SHIFT,COL_SHIFT_BG,false,FONT_5x8);
            break;
    }

    //Draw alpha modifier
    switch (modifier)
    {
        case MODIFIER_NONE:
        case MODIFIER_SHIFT_NONE:
            text[0]=' ';
            outline_text(text,pos,COL_MOD_BG,COL_MOD_BG,COL_MOD_BG,false,FONT_5x8);
            break;
        case MODIFIER_ALPHA_LOWER:
        case MODIFIER_SHIFT_ALPHA_LOWER:
            text[0]='a';
            outline_text(text,pos,COL_ALPHA,COL_ALPHA_BG,COL_ALPHA,false,FONT_5x8);
            break;
        case MODIFIER_ALPHA_LOWER_LOCK:
        case MODIFIER_SHIFT_ALPHA_LOWER_LOCK:
            text[0]='a';
            outline_text(text,pos,COL_ALPHA_BG,COL_ALPHA,COL_ALPHA,false,FONT_5x8);
            break;
        case MODIFIER_ALPHA_UPPER:
        case MODIFIER_SHIFT_ALPHA_UPPER:
            text[0]='A';
            outline_text(text,pos,COL_ALPHA,COL_ALPHA_BG,COL_ALPHA,false,FONT_5x8);
            break;
        case MODIFIER_ALPHA_UPPER_LOCK:
        case MODIFIER_SHIFT_ALPHA_UPPER_LOCK:
            text[0]='A';
            outline_text(text,pos,COL_ALPHA_BG,COL_ALPHA,COL_ALPHA,false,FONT_5x8);
            break;
    }
}

void draw_splits(struct WindowInfo window)
{
    int menu_x;
    int menu_y;
    bool enabled;

    for (int i=0;i<SPLIT_COUNT;i++)
    {
        if ((i==1)&&(window.split_state==WINDOW_WHOLE))
        {
            //Only draw one window if no split
            break;
        }

        //Draw deselected menu as gray    
        if ((window.split_state!=WINDOW_WHOLE)&&(window.selected_split!=i)) enabled=false;
        else enabled=true;
        
        //Draw splits
        switch (window.split[i].ID)
        {
            case ID_NONE:
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
                    if (i==0) window_y=WINDOW_VSPLIT_TOP_Y0;
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
                    if (i==0) window_x=WINDOW_HSPLIT_LEFT_X0;
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
                    if (j==window.split[i].menu_selection)
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
                break;
            case ID_COMMAND_LINE:
            case ID_TEXT_EDITOR:
            case ID_FORTH:
            case ID_MCU_PYTHON:
            case ID_HELP:
                (*menu_functions[window.split[i].ID])(COMMAND_REDRAW,window,NULL);
                break;
        }   //switch for split's ID
    }
}

void draw_manager(struct WindowInfo windows[],int modifier,int selected_window)
{
    //Clear screen
    dclear(COL_BLACK);

    //Status area
    draw_rect(STATUS_X,STATUS_Y,STATUS_WIDTH,STATUS_HEIGHT,COL_MOD_BG,COL_MOD_BG);
    draw_modifier(modifier);

    struct point pos={TAB_START_X,TAB_START_Y};
    for (int i=0;i<TAB_COUNT;i++)
    {
        int16_t outline;
        if (i==selected_window) outline=COL_TAB_SEL;
        else outline=COL_TAB_NO_SEL;
        
        //Draw tab title
        pos=outline_text(windows[i].title,pos,outline,manager_colors[i],outline,false,FONT_5x8);

        if (i==selected_window)
        {
            //Outside border
            for (int j=0;j<BORDER_SIZE;j++)
            {
                draw_rect(BORDER_X+j,BORDER_Y+j,DWIDTH-j*2,DHEIGHT-j*2-BORDER_Y,manager_colors[i],-1);
            }
            
            if (windows[i].split_state==WINDOW_VSPLIT)
            {
                //Vertical split 
                for (int j=0;j<BORDER_SIZE;j++)
                {
                    //Draw horizontal bar
                    draw_line_horz(BORDER_VSPLIT_X0,BORDER_VSPLIT_X1,BORDER_VSPLIT_Y+j,manager_colors[i]);
                }

                if (windows[i].selected_split==0)
                {
                    //Top window selected
                    draw_rect(SEL_VSPLIT_X,SEL_VSPLIT_Y0,SEL_VSPLIT_WIDTH,SEL_VSPLIT_HEIGHT,SEL_COLOR,-1);
                }
                else
                {
                    //Bottom window selected
                    draw_rect(SEL_VSPLIT_X,SEL_VSPLIT_Y1,SEL_VSPLIT_WIDTH,SEL_VSPLIT_HEIGHT,SEL_COLOR,-1);
                }
            }
            else if (windows[i].split_state==WINDOW_HSPLIT)
            {
                //Horizontal split
                for (int j=0;j<BORDER_SIZE;j++)
                {
                    //Draw vertical bar
                    draw_line_vert(BORDER_HSPLIT_X+j,BORDER_HSPLIT_Y0,BORDER_HSPLIT_Y1,manager_colors[i]);
                }

                if (windows[i].selected_split==0)
                {
                    //Left window selected
                    draw_rect(SEL_HSPLIT_X0,SEL_HSPLIT_Y,SEL_HSPLIT_WIDTH,SEL_HSPLIT_HEIGHT,SEL_COLOR,-1);
                }
                else
                {
                    //Right window selected
                    draw_rect(SEL_HSPLIT_X1,SEL_HSPLIT_Y,SEL_HSPLIT_WIDTH,SEL_HSPLIT_HEIGHT,SEL_COLOR,-1);
                }
            }
        }
    }
}

struct point window_pos(struct WindowInfo window)
{
    struct point pos;
    switch (window.split_state)
    {
        case WINDOW_WHOLE:
            pos.x=WINDOW_WHOLE_X0;
            pos.y=WINDOW_WHOLE_Y0;
            break;
        case WINDOW_VSPLIT:
            pos.x=WINDOW_VSPLIT_X0;
            if (window.selected_split==0) pos.y=WINDOW_VSPLIT_TOP_Y0;
            else pos.y=WINDOW_VSPLIT_BOTTOM_Y0;
            break;
        case WINDOW_HSPLIT:
            pos.y=WINDOW_HSPLIT_Y0;
            if (window.selected_split==0) pos.x=WINDOW_HSPLIT_LEFT_X0;
            else pos.x=WINDOW_HSPLIT_RIGHT_X0;
            break;
    }

    return pos;
}
int window_width(struct WindowInfo window)
{
    switch (window.split_state)
    {
        case WINDOW_WHOLE:
        case WINDOW_VSPLIT:
            return WINDOW_WHOLE_WIDTH;
        case WINDOW_HSPLIT:
            return WINDOW_HSPLIT_WIDTH;
        default:
            return 0;
    }
}

int window_height(struct WindowInfo window)
{
    switch (window.split_state)
    {
        case WINDOW_WHOLE:
        case WINDOW_HSPLIT:
            return WINDOW_WHOLE_HEIGHT;
        case WINDOW_VSPLIT:
            return WINDOW_VSPLIT_HEIGHT;
        default:
            return 0;
    }
}

