#ifndef __GUARD_PROG_TOOLS_MANAGER
    #define __GUARD_PROG_TOOLS_MANAGER

    #include "compatibility.h"
    #include "structs.h"

    ///Colors - modifiers
    #define COL_ALPHA           C_RGB(COL_3_4,0,0)
    #define COL_ALPHA_BG        COL_WHITE
    #define COL_SHIFT           C_RGB(COL_3_4,COL_3_4,0)
    #define COL_SHIFT_BG        COL_BLACK
    #define COL_MOD_BG          C_RGB(COL_MID,COL_MID,COL_MID)

    //Colors - tabs
    #define COL_TAB_SEL         COL_WHITE
    #define COL_TAB_NO_SEL      COL_BLACK

    //Status area
    #define STATUS_X            0
    #define STATUS_Y            0

    //Tabs
    #define STATUS_WIDTH        18
    #define STATUS_HEIGHT       12
    #define TAB_START_X         18
    #define TAB_START_Y         0
    #define TAB_HEIGHT          12
    //#define TAB_TITLE_LEN       11      //Moved to structs.h
    #define TAB_COUNT           6

    //Splits
    #define SPLIT_COUNT         2

    //Border
    #define BORDER_SIZE         4
    #define BORDER_X            0
    #define BORDER_Y            12
    #define BORDER_VSPLIT_X0    BORDER_SIZE
    #define BORDER_VSPLIT_X1    (DWIDTH-BORDER_SIZE-1)
    #define BORDER_VSPLIT_Y     (BORDER_Y+(DHEIGHT-BORDER_Y)/2-BORDER_SIZE/2)
    #define BORDER_HSPLIT_X     (BORDER_X+(DWIDTH-BORDER_X)/2-BORDER_SIZE/2)
    #define BORDER_HSPLIT_Y0    (BORDER_SIZE+BORDER_Y)
    #define BORDER_HSPLIT_Y1    (DHEIGHT-BORDER_SIZE-1)

    //Window selectors
    #define SEL_COLOR           COL_WHITE
    #define SEL_VSPLIT_X        2
    #define SEL_VSPLIT_Y0       (TAB_HEIGHT+2)
    #define SEL_VSPLIT_Y1       (TAB_HEIGHT+(DHEIGHT-TAB_HEIGHT)/2)
    #define SEL_VSPLIT_WIDTH    (DWIDTH-4)
    #define SEL_VSPLIT_HEIGHT   ((DHEIGHT-TAB_HEIGHT)/2-2)
    #define SEL_HSPLIT_X0       2
    #define SEL_HSPLIT_X1       (DWIDTH/2)
    #define SEL_HSPLIT_Y        (TAB_HEIGHT+2)
    #define SEL_HSPLIT_WIDTH    (DWIDTH/2-2)
    #define SEL_HSPLIT_HEIGHT   ((DHEIGHT-TAB_HEIGHT)-4)

    //Window dimensions
    #define WINDOW_WHOLE_X0     BORDER_SIZE
    #define WINDOW_WHOLE_X1     (DWIDTH-BORDER_SIZE-1)
    #define WINDOW_WHOLE_WIDTH  (WINDOW_WHOLE_X1-WINDOW_WHOLE_X0+1)
    #define WINDOW_WHOLE_Y0     (BORDER_SIZE+TAB_HEIGHT)
    #define WINDOW_WHOLE_Y1     (DHEIGHT-BORDER_SIZE-1)
    #define WINDOW_WHOLE_HEIGHT (WINDOW_WHOLE_Y1-WINDOW_WHOLE_Y0+1)

    #define WINDOW_VSPLIT_X0            WINDOW_WHOLE_X0
    #define WINDOW_VSPLIT_X1            WINDOW_WHOLE_X1
    #define WINDOW_VSPLIT_WIDTH         WINDOW_WHOLE_WIDTH
    #define WINDOW_VSPLIT_TOP_Y0        WINDOW_WHOLE_Y0
    #define WINDOW_VSPLIT_TOP_Y1        (TAB_HEIGHT+(DHEIGHT-TAB_HEIGHT)/2)
    #define WINDOW_VSPLIT_HEIGHT        ((DHEIGHT-TAB_HEIGHT-BORDER_SIZE*3)/2)
    #define WINDOW_VSPLIT_BOTTOM_Y0     (DHEIGHT-WINDOW_VSPLIT_HEIGHT-BORDER_SIZE) 
    #define WINDOW_VSPLIT_BOTTOM_Y1     WINDOW_WHOLE_Y1

    #define WINDOW_HSPLIT_WIDTH         ((DWIDTH-BORDER_SIZE*3)/2)
    #define WINDOW_HSPLIT_LEFT_X0       WINDOW_WHOLE_X0
    #define WINDOW_HSPLIT_LEFT_X1       (BORDER_SIZE*2+WINDOW_HSPLIT_WIDTH)
    #define WINDOW_HSPLIT_RIGHT_X0      (DWIDTH-BORDER_SIZE-WINDOW_HSPLIT_WIDTH)
    #define WINDOW_HSPLIT_RIGHT_X1      (DWIDTH-BORDER_SIZE)
    #define WINDOW_HSPLIT_Y0            WINDOW_WHOLE_Y0
    #define WINDOW_HSPLIT_Y1            WINDOW_WHOLE_Y1
    #define WINDOW_HSPLIT_HEIGHT        WINDOW_WHOLE_HEIGHT
   
    //Window dimensions from above
    //Whole:  388x204
    //Vsplit: 388x100
    //Hsplit: 192x204

    enum WindowSplitStates
    {
        WINDOW_WHOLE,
        WINDOW_VSPLIT,
        WINDOW_HSPLIT,
    };

    enum ProgramCommands
    {   
        //Sent by manager to program
        COMMAND_START,
        COMMAND_RESUME,
        COMMAND_REDRAW,

        //Sent by program back to manager
        COMMAND_DONE,
        COMMAND_EXIT,
        COMMAND_MENU,
        COMMAND_OFF,
        COMMAND_SWAP,
        COMMAND_TAB1,
        COMMAND_TAB2,
        COMMAND_TAB3,
        COMMAND_TAB4,
        COMMAND_TAB5,
        COMMAND_TAB6,
        COMMAND_NONE,   //No match in sys_key_handler

        //Errors
        COMMAND_ERROR_OUT_OF_MEM
    };
    
    //Global variables
    extern color_t manager_colors[];

    //Functions
    void window_manager();
    void draw_modifier(int modifier);
    void draw_splits(struct WindowInfo *windows,int selected_window);
    void draw_titles(struct WindowInfo *windows,int selected_window);
    void draw_manager(struct WindowInfo *windows,int modifier,int selected_window);
    struct point window_pos(struct WindowInfo window,bool selected);
    int window_width(struct WindowInfo window);
    int window_height(struct WindowInfo window);

#endif
