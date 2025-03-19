#ifndef __GUARD_PROG_TOOLS_COMMAND
    #define __GUARD_PROG_TOOLS_COMMAND

    #include <stdint.h>
    #include "structs.h"

    //Dimensions (may change - see manager.h):
    //- Whole:  388x204 - 64 chars, 4 pixels x 22 rows, 6 pixels (or 20 rows, 4 pixels)
    //- Vsplit: 388x100 - 64 chars, 4 pixels x 11 rows, 1 pixel  (or 10 rows, 0 pixels)
    //- Hsplit: 192x204 - 31 chars, 6 pixels x 22 rows, 6 pixels (or 20 rows, 4 pixels)
    #define CMD_LINE_MAX        124     //Four full lines if hsplit

    #define CMD_WHOLE_WIDTH     64
    #define CMD_WHOLE_HEIGHT    22
    #define CMD_WHOLE_X         2
    #define CMD_WHOLE_Y         3
    #define CMD_ROW_HEIGHT      9

    #define CMD_COL_BG          COL_BLACK
    #define CMD_COL_FG          COL_WHITE
    
    struct ConsoleInfo
    {
        char text[CMD_WHOLE_HEIGHT*CMD_WHOLE_WIDTH];
        uint16_t color_fg[CMD_WHOLE_HEIGHT*CMD_WHOLE_WIDTH];
        uint16_t color_bg[CMD_WHOLE_HEIGHT*CMD_WHOLE_WIDTH];
    };

    int command_line(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
