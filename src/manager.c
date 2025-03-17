#include "compatibility.h"
#include "getkey.h"
#include "graphics.h"
#include "manager.h"
#include "mem.h"
#include "menu.h"
#include "structs.h"
#include "text.h"


//Global variables
//================
uint16_t manager_colors[]=
{
    C_RGB(0,COL_1_4,COL_MID),       //Blue
    C_RGB(COL_1_4,COL_MID,0),       //Green
    C_RGB(COL_MID,COL_MID,0),       //Yellow
    C_RGB(COL_MID,COL_1_4,0),       //Orange
    C_RGB(COL_MID,0,0),             //Red
    C_RGB(COL_MID,0,COL_MID),       //Purple
};

//Functions
//=========
void window_manager()
{
    int modifier=MODIFIER_NONE;
    int selected_window=0;

    //Initialize windows
    struct WindowInfo windows[TAB_COUNT];
    for (int i=0;i<TAB_COUNT;i++)
    {
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
        draw_splits(windows,selected_window);
        dupdate();

        //Pass control to selected program including menu handler
        int split_state=windows[selected_window].split_state;
        int selected_split=0;
        if (split_state==WINDOW_WHOLE) selected_split=0;
        else selected_split=windows[selected_window].selected_split;
        int new_program_ID=windows[selected_window].split[selected_split].ID;
   
        int return_command=(*menu_functions[new_program_ID])(COMMAND_RESUME,windows,selected_window);

        //Process return from program
        switch (return_command)
        {
            case COMMAND_EXIT:
                //Program done executing
                windows[selected_window].split[windows[selected_window].selected_split].ID=ID_NONE;

                //Free memory
                new_split_mem(windows[selected_window].tab_index,windows[selected_window].selected_split,get_split_heap());
                break;
            case COMMAND_MENU:
                //Save here if necessary
                gint_osmenu();
                break;
            case COMMAND_OFF:
                //Save here too to be safe
                gint_poweroff(true);
                break;
            case COMMAND_TAB1:
            case COMMAND_TAB2:
            case COMMAND_TAB3:
            case COMMAND_TAB4:
            case COMMAND_TAB5:
            case COMMAND_TAB6:
                selected_window=return_command-COMMAND_TAB1;
                break;
            case COMMAND_SWAP:
                //shift+XOT - switch selected window split
                if (windows[selected_window].split_state!=WINDOW_WHOLE)
                {
                    windows[selected_window].selected_split^=1;
                }
                break;
        }
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

void draw_splits(struct WindowInfo *windows, int selected_window)
{
    struct WindowInfo window=windows[selected_window];

    if (window.split_state==WINDOW_WHOLE)
    {
        //No spits to draw if only one screen
        return;
    }

    //Only draw deselected split
    int deselected_split=window.selected_split^1;
    (*menu_functions[window.split[deselected_split].ID])(COMMAND_REDRAW,windows,selected_window);
}

void draw_titles(struct WindowInfo windows[],int selected_window)
{
    struct point pos={TAB_START_X,TAB_START_Y};
    char title_buffer[TAB_TITLE_LEN];
    title_buffer[1]=':';
    title_buffer[TAB_TITLE_LEN-1]=0;
    for (int i=0;i<TAB_COUNT;i++)
    {
        int16_t outline;
        if (i==selected_window) outline=COL_TAB_SEL;
        else outline=COL_TAB_NO_SEL;
        
        title_buffer[0]='1'+i;
        int title_ID=windows[i].split[windows[i].selected_split].ID;
        for (int j=0;j<TAB_TITLE_LEN-3;j++)
        {
            title_buffer[j+2]=program_titles[title_ID][j];
        }
        pos=outline_text(title_buffer,pos,outline,manager_colors[i],outline,false,FONT_5x8);
    }
}

void draw_manager(struct WindowInfo windows[],int modifier,int selected_window)
{
    //Clear screen
    dclear(COL_BLACK);

    //Status area
    draw_rect(STATUS_X,STATUS_Y,STATUS_WIDTH,STATUS_HEIGHT,COL_MOD_BG,COL_MOD_BG);
    draw_modifier(modifier);

    //Tab titles
    draw_titles(windows,selected_window);

    //Outside border
    for (int j=0;j<BORDER_SIZE;j++)
    {
        draw_rect(BORDER_X+j,BORDER_Y+j,DWIDTH-j*2,DHEIGHT-j*2-BORDER_Y,manager_colors[selected_window],-1);
    }
    
    if (windows[selected_window].split_state==WINDOW_VSPLIT)
    {
        //Vertical split 
        for (int j=0;j<BORDER_SIZE;j++)
        {
            //Draw horizontal bar
            draw_line_horz(BORDER_VSPLIT_X0,BORDER_VSPLIT_X1,BORDER_VSPLIT_Y+j,manager_colors[selected_window]);
        }

        if (windows[selected_window].selected_split==0)
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
    else if (windows[selected_window].split_state==WINDOW_HSPLIT)
    {
        //Horizontal split
        for (int j=0;j<BORDER_SIZE;j++)
        {
            //Draw vertical bar
            draw_line_vert(BORDER_HSPLIT_X+j,BORDER_HSPLIT_Y0,BORDER_HSPLIT_Y1,manager_colors[selected_window]);
        }

        if (windows[selected_window].selected_split==0)
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

struct point window_pos(struct WindowInfo window,bool selected)
{
    int selected_split=window.selected_split;
    if (selected==false) selected_split^=1;

    struct point pos;
    switch (window.split_state)
    {
        case WINDOW_WHOLE:
            pos.x=WINDOW_WHOLE_X0;
            pos.y=WINDOW_WHOLE_Y0;
            break;
        case WINDOW_VSPLIT:
            pos.x=WINDOW_VSPLIT_X0;
            if (selected_split==0) pos.y=WINDOW_VSPLIT_TOP_Y0;
            else pos.y=WINDOW_VSPLIT_BOTTOM_Y0;
            break;
        case WINDOW_HSPLIT:
            pos.y=WINDOW_HSPLIT_Y0;
            if (selected_split==0) pos.x=WINDOW_HSPLIT_LEFT_X0;
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

