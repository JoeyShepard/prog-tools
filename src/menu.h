#ifndef __GUARD_PROG_TOOLS_MENU
    #define __GUARD_PROG_TOOLS_MENU

    #include "structs.h"

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
    
    //Programs
    #define PROG_LIST_LEN       ((int)(sizeof(program_list)/sizeof(program_list[0])))

    //Global variables
    extern const char *program_list[];
    extern const int program_IDs[];
    extern int (*menu_functions[])(int command_ID, struct WindowInfo *window, int selected_window, uint8_t *heap_ptr);

    //Functions
    void draw_menu(struct WindowInfo window, bool enabled);
    int menu_handler(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr);

#endif
