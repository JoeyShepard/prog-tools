#ifndef __GUARD_PROG_TOOLS_FORTH
    #define __GUARD_PROG_TOOLS_FORTH

    #include <stdalign.h>
    #include <stdint.h>

    #include "compatibility.h"
    #include "console.h"
    #include "forth-primitives.h"
    #include "forth-engine.h"
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
        #define FORTH_COL_ERROR     C_RGB(COL_MAX,COL_MID,COL_MID)  //Red
        #define FORTH_COL_DEF       C_RGB(COL_3_4,COL_3_4,COL_3_4)  //Definition words ; and ;
        #define FORTH_COL_STRING    C_RGB(COL_1_4,COL_MAX,COL_1_4)  //Green
        #define FORTH_COL_NEW_WORD  FORTH_COL_SECONDARY
    #else
        #define FORTH_COL_NUMBER    C_RGB(COL_1_4,COL_MAX,COL_1_4)  //Green 
        #define FORTH_COL_HEX       C_RGB(COL_1_4,COL_MAX,COL_MAX)  //Cyan
        #define FORTH_COL_PRIMITIVE C_RGB(COL_3_4,COL_1_4,COL_MAX)  //Purple
        #define FORTH_COL_SECONDARY C_RGB(COL_1_4,COL_MID,COL_MAX)  //Blue (lighter here so not too close to black)
        #define FORTH_COL_NOT_FOUND C_RGB(COL_MAX,COL_MAX,COL_1_4)  //Yellow
        #define FORTH_COL_ERROR     C_RGB(COL_MAX,COL_1_4,COL_1_4)  //Red
        #define FORTH_COL_DEF       C_RGB(COL_MID,COL_MID,COL_MID)  //Definition words ; and ;
        #define FORTH_COL_STRING    C_RGB(COL_1_4,COL_MAX,COL_1_4)  //Green
        #define FORTH_COL_NEW_WORD  FORTH_COL_SECONDARY
    #endif

    #define FORTH_COL_TYPING    COL_WHITE
    //Should never happen but just in case
    #define FORTH_COL_NONE      COL_WHITE

    //Heap memory
    #define FORTH_ID_CONSOLE        0
    #define FORTH_ID_DEFINITIONS    1
    #define FORTH_ID_CODE           2

    //Console
    #define FORTH_INPUT_MAX         248     //Eight full lines of text input if hsplit
    #define FORTH_CONSOLE_STRING    "Forth for fx-CG50\n"
   
    //History
    #define FORTH_HIST_COUNT    10

    //Forth
    #define FORTH_WORD_MAX      16
    #define FORTH_PROMPT        ">" 

    //Forth memory
    #define FORTH_DATA_SIZE     0x10000

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

    enum ForthErrors
    {
        FORTH_ERROR_NONE,
        FORTH_ERROR_TOO_LONG
    };

    //structs
    struct ForthWordHeader
    {
        uint32_t size;
        uint8_t name_len;
        //Flexible Array Member - memory allocated after struct holds name
        char name[];
    };

    //Custom struct to save data the program uses to heap
    struct ForthInfo
    {
        //Data for printing to console
        struct ConsoleInfo console; 
        
        //Custom size memory used by console above
        struct ConsoleChar input_text[FORTH_INPUT_MAX];
        struct ConsoleChar input_copy_text[FORTH_INPUT_MAX];
        struct ConsoleInput history[FORTH_HIST_COUNT];
        struct ConsoleChar history_texts[FORTH_HIST_COUNT*FORTH_INPUT_MAX];

        //Memory for Forth programs to use - must be aligned for int32_t access
        //TODO: might be nice to have data size be adjustable
        alignas(uint32_t) uint8_t data[FORTH_DATA_SIZE];

        //Copy of both stacks. Copied to XRAM at runtime.
        alignas(uint32_t) uint8_t stack_copy[FORTH_STACK_SIZE];
        alignas(uint32_t) uint8_t rstack_copy[FORTH_RSTACK_SIZE];

        //Data for Forth Engine
        struct ForthEngine engine;
    };

    //Functions
    //=========
    int forth(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
