#ifndef __GUARD_PROG_TOOLS_MANAGER
    #define __GUARD_PROG_TOOLS_MANAGER

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

    //Colors - menu 
    #define COL_MENU_BG         C_RGB(COL_3_4,COL_3_4,COL_3_4)
    #define COL_MENU_TEXT       COL_BLACK
    #define COL_MENU_SEL_TEXT   COL_WHITE

    #define COL_MENU_DE_BG          C_RGB(10,10,10)
    #define COL_MENU_DE_TEXT        C_RGB(3,3,3)
    #define COL_MENU_DE_SEL_TEXT    C_RGB(14,14,14)
    #define COL_MENU_DE_SEL_FILL    C_RGB(6,6,6)

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

    //Menus
    #define MENU_X_OFFSET       4
    #define MENU_Y_OFFSET       2
    #define MENU_HEIGHT         11
    #define MENU_BUFFER         30

    //Programs
    #define PROG_LIST_LEN       ((int)(sizeof(program_list)/sizeof(program_list[0])))

    enum ModifierStates
    {
        MODIFIER_NONE,
        MODIFIER_ALPHA_LOWER,
        MODIFIER_ALPHA_LOWER_LOCK,
        MODIFIER_ALPHA_UPPER,
        MODIFIER_ALPHA_UPPER_LOCK,
        MODIFIER_SHIFT_NONE,
        MODIFIER_SHIFT_ALPHA_LOWER,
        MODIFIER_SHIFT_ALPHA_LOWER_LOCK,
        MODIFIER_SHIFT_ALPHA_UPPER,
        MODIFIER_SHIFT_ALPHA_UPPER_LOCK,
    };

    enum WindowSplitStates
    {
        WINDOW_WHOLE,
        WINDOW_VSPLIT,
        WINDOW_HSPLIT,
    };

    enum ProgramList
    {
        ID_COMMAND_LINE,
        ID_TEXT_EDITOR,
        ID_FORTH,
        ID_MCU_PYTHON,
        ID_SPLIT_VERTICALLY,
        ID_SPLIT_HORIZONTALLY,
        ID_CLOSE_SPLIT,
        ID_HELP,
        //ID_NONE should come last - no menu text
        ID_NONE,
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

        //Errors
        COMMAND_ERROR_OUT_OF_MEM
    };
    
    //Global variables
    extern const char *program_list[];
    extern const int program_IDs[];
    extern const int (*menu_functions[])(int command_ID, struct WindowInfo window, uint8_t *heap_ptr);

    //Functions
    void window_manager();
    //Update modifier depending on key pressed
    int update_modifier(int modifier,int key);
    //Return none, lower, upper, or shift depending on modifier state
    int current_modifier(int modifier);
    //Mark modifier as used and return new state
    int use_modifier(int modifier);
    //Return modified key
    int modify_keypress(int modifier, int key);
    void draw_modifier(int modifier);
    void draw_splits(struct WindowInfo window);
    void draw_manager(struct WindowInfo windows[],int modifier,int selected_window);
    struct point window_pos(struct WindowInfo window);
    int window_width(struct WindowInfo window);
    int window_height(struct WindowInfo window);

#endif
