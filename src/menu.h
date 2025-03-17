#ifndef __GUARD_PROG_TOOLS_MENU
    #define __GUARD_PROG_TOOLS_MENU

    #include "structs.h"

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
    #define PROG_COL2_ID        ID_6502_EMU     //Last menu item before mocing to second column

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
