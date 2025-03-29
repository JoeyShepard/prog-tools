#ifndef __GUARD_PROG_TOOLS_COMMAND
    #define __GUARD_PROG_TOOLS_COMMAND

    #include <stdint.h>

    #include "compatibility.h"
    #include "structs.h"

    //Dimensions (may change - see manager.h):
    //- Whole:  388x204 - 64 chars, 4 pixels x 22 rows, 6 pixels (or 20 rows, 4 pixels)
    //- Vsplit: 388x100 - 64 chars, 4 pixels x 11 rows, 1 pixel  (or 10 rows, 0 pixels)
    //- Hsplit: 192x204 - 31 chars, 6 pixels x 22 rows, 6 pixels (or 20 rows, 4 pixels)

    //Screen
    #define CMD_WHOLE_WIDTH     64
    #define CMD_WHOLE_HEIGHT    22
    #define CMD_WHOLE_X         1
    #define CMD_WHOLE_Y         2

    #define CMD_HALF_WIDTH      31
    #define CMD_HALF_HEIGHT     11
    #define CMD_HALF_X          2
    #define CMD_HALF_Y          0
    
    #define CMD_ROW_HEIGHT      9

    #define CMD_COL_FG          COL_WHITE
    #define CMD_COL_BG          COL_BLACK
   
    #define CMD_BUFFER_SIZE     (CMD_WHOLE_WIDTH*CMD_WHOLE_HEIGHT+CMD_WHOLE_HEIGHT)

    //Heap memory
    #define CMD_ID_CONSOLE      0

    //Console
    #define CMD_INPUT_MAX       124     //Four full lines of text input if hsplit
    
    //History
    #define CMD_HIST_COUNT      10

    struct ConsoleChar
    {
        char character;
        color_t fg;
        color_t bg;
    };

    struct ConsoleInput
    {
        struct ConsoleChar text[CMD_INPUT_MAX];
        int len;
        int start;
        int cursor;
    };

    struct ConsoleInfo
    {
        //Console output
        struct ConsoleChar text[CMD_BUFFER_SIZE];
        int text_len;
        uint32_t overflow_count;
        int buffer_index;

        //Input line
        struct ConsoleInput input;
        struct ConsoleInput input_copy;
        bool reset_input;
        int modifier;
        bool input_copied;

        //History
        struct ConsoleInput history[CMD_HIST_COUNT];
        int history_index;
        int history_count;
        int history_read_count;
    };

    int command_line(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
