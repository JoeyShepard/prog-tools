#ifndef __GUARD_PROG_TOOLS_ERROR
    #define __GUARD_PROG_TOOLS_ERROR

    #include "structs.h"

    #define ERROR_COL_BG    COL_RED
    #define ERROR_COL_FG    COL_WHITE

    #define ERROR_SPACING_Y 12

    enum ErrorNumbers
    {
        //error_exit - fatal, stop executing
        ERROR_NONE,
        ERROR_FONT_NOT_FOUND,
        ERROR_MENU_TEXT_TOO_LONG,
        ERROR_UNALIGNED_WRITE,
        ERROR_BAD_HEAP_ID,

        //error_screen - not fatal, show screen then return to menu
        ERROR_OUT_OF_MEMORY
    };

    void error_exit(int error);
    void error_screen(int error,struct Point pos,int width,int height);

#endif
