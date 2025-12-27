#ifndef __GUARD_PROG_TOOLS_MENU
    #define __GUARD_PROG_TOOLS_MENU

    #include "structs.h"

    //Colors - menu 
    #define COL_MENU_BG             C_RGB(COL_3_4,COL_3_4,COL_3_4)
    #define COL_MENU_TEXT           COL_BLACK
    #define COL_MENU_SEL_TEXT       COL_WHITE
    #define COL_MENU_DISABLED_TEXT  C_RGB(16,16,16)     //Disabled (ie Close option when full screen)

    #define COL_MENU_DE_BG          C_RGB(10,10,10)
    #define COL_MENU_DE_TEXT        C_RGB(3,3,3)
    #define COL_MENU_DE_SEL_TEXT    C_RGB(14,14,14)
    #define COL_MENU_DE_SEL_FILL    C_RGB(6,6,6)

    enum ProgramList
    {
        ID_COMMAND_LINE,
        ID_TEXT_EDITOR,
        ID_FORTH,
        ID_MCU_PYTHON,
        ID_MSP430_EMU,
        ID_6502_EMU,
        ID_SPLIT_VERTICALLY,
        ID_SPLIT_HORIZONTALLY,
        ID_CLOSE_SPLIT,
        ID_MEMORY_MANAGER,
        ID_HELP,
        //ID_NONE should come last - no menu text
        ID_NONE,
    };
    
    //Programs
    #define PROG_LIST_LEN       ((int)(sizeof(program_list)/sizeof(program_list[0])))
    #define PROG_COL2_ID        ID_6502_EMU     //Last menu item before moving to second column

    //Menus
    #define MENU_X_OFFSET       4
    #define MENU_X_OFFSET2      140
    #define MENU_Y_OFFSET       2
    #define MENU_HEIGHT         11
    #define MENU_BUFFER         30

    //Global variables
    extern int (*menu_functions[])(int command_ID, struct WindowInfo *window, int selected_window);
    extern const char *program_titles[];

    //Functions
    void draw_menu(struct WindowInfo window, bool enabled);
    int menu_handler(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
