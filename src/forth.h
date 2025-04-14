#ifndef __GUARD_PROG_TOOLS_FORTH
    #define __GUARD_PROG_TOOLS_FORTH

    #include <stdint.h>

    #include "compatibility.h"
    #include "console.h"
    #include "forth-primitives.h"
    #include "structs.h"

    //Colors
    #define FORTH_COL_FG        COL_WHITE
    #define FORTH_COL_BG        COL_BLACK
   
    #define FORTH_COL_ERR_FG    FORTH_COL_FG
    #define FORTH_COL_ERR_BG    FORTH_COL_BG

    //#define FORTH_COL_LIGHT
    #ifdef FORTH_COL_LIGHT
        #define FORTH_COL_NUMBER    C_RGB(COL_MID,COL_MAX,COL_MID)  //Green 
        #define FORTH_COL_HEX       C_RGB(COL_MID,COL_MAX,COL_MAX)  //Cyan
        #define FORTH_COL_PRIMITIVE C_RGB(COL_MAX,COL_MID,COL_MAX)  //Magenta
        #define FORTH_COL_SECONDARY C_RGB(COL_MID,COL_MID,COL_MAX)  //Blue
        #define FORTH_COL_NOT_FOUND C_RGB(COL_MAX,COL_MAX,COL_MID)  //Yellow
    #else
        #define FORTH_COL_NUMBER    C_RGB(COL_1_4,COL_MAX,COL_1_4)  //Green 
        #define FORTH_COL_HEX       C_RGB(COL_1_4,COL_MAX,COL_MAX)  //Cyan
        #define FORTH_COL_PRIMITIVE C_RGB(COL_MAX,COL_1_4,COL_MAX)  //Magenta
        #define FORTH_COL_SECONDARY C_RGB(COL_1_4,COL_MID,COL_MAX)  //Blue (same as above, otherwise too dark
        #define FORTH_COL_NOT_FOUND C_RGB(COL_MAX,COL_MAX,COL_1_4)  //Yellow
    #endif

    #define FORTH_COL_TYPING    COL_WHITE
    //Should never happen but just in case
    #define FORTH_COL_NONE      COL_WHITE

    //Heap memory
    #define FORTH_ID_CONSOLE    0

    //Console
    #define FORTH_INPUT_MAX         248     //Eight full lines of text input if hsplit
    #define FORTH_CONSOLE_STRING    "Forth for fx-CG50\n"
   
    //History
    #define FORTH_HIST_COUNT    10

    //Forth
    #define FORTH_WORD_MAX      16
    #define FORTH_PROMPT        ">" 

    //enums
    //=====
    enum ForthParse
    {
        FORTH_PARSE_NONE,
        FORTH_PARSE_WORD
    };
    enum ForthCharClass
    {
        FORTH_CHAR_MINUS,
        FORTH_CHAR_0,
        FORTH_CHAR_1_9,
        FORTH_CHAR_A_F,
        FORTH_CHAR_G_Z,
        FORTH_CHAR_x,
        FORTH_CHAR_OTHER,
    };

    enum ForthTextType
    {
        //Full types
        FORTH_TYPE_NUMBER,
        FORTH_TYPE_HEX,
        FORTH_TYPE_PRIMARY,
        FORTH_TYPE_SECONDARY,
        FORTH_NOT_FOUND,
        //Partial types used only for parsing
        FORTH_TYPE_NONE,
        FORTH_TYPE_MINUS,
        FORTH_TYPE_0,
        FORTH_TYPE_0x,
        FORTH_TYPE_OTHER
    };

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
