#ifndef __GUARD_PROG_TOOLS_FORTH
    #define __GUARD_PROG_TOOLS_FORTH

    #include <stdint.h>

    #include "compatibility.h"
    #include "console.h"
    #include "structs.h"

    //Shell colors
    #define FORTH_COL_FG        COL_WHITE
    #define FORTH_COL_BG        COL_BLACK
   
    #define FORTH_COL_ERR_FG    SHELL_COL_FG
    #define FORTH_COL_ERR_BG    SHELL_COL_BG

    //Heap memory
    #define FORTH_ID_CONSOLE    0

    //Console
    #define FORTH_INPUT_MAX         248     //Eight full lines of text input if hsplit
    #define FORTH_CONSOLE_STRING    "Forth for fx-CG50\n"
   
    //History
    #define FORTH_HIST_COUNT    10

    //enums
    //=====

    //Custom struct to save everything to heap
    struct ForthInfo
    {
        struct ConsoleInfo console; 
        
        //Custom size memory used by console above
        struct ConsoleChar input_text[FORTH_INPUT_MAX];
        struct ConsoleChar input_copy_text[FORTH_INPUT_MAX];
        struct ConsoleInput history[FORTH_HIST_COUNT];
        struct ConsoleChar history_texts[FORTH_HIST_COUNT*FORTH_INPUT_MAX];
    };


    //Functions
    //=========
    int forth(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
