#ifndef __GUARD_PROG_TOOLS_FORTH
    #define __GUARD_PROG_TOOLS_FORTH

    #include <stdalign.h>
    #include <stdint.h>

    #include "console.h"
    #include "forth-compatibility.h"
    #include "forth-engine.h"

    //Colors
    #define FORTH_COL_FG        COL_WHITE
    #define FORTH_COL_BG        COL_BLACK
   
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
    #define FORTH_ID_DATA           1
    #define FORTH_ID_DEFINITIONS    2
    #define FORTH_ID_WORD_IDS       3
    #define FORTH_ID_CONTROL_STACK  4
    #define FORTH_MEM_DATA          0x2000  //Initial value - can change programmatically
    #define FORTH_MEM_DEFINITIONS   1024    //For these three, allocate this amount initially then add this     
    #define FORTH_MEM_WORD_IDS      1024    //much when memory runs out. Exact amount not important - prevents
    #define FORTH_MEM_CONTROL_STACK 512     //copying whole dictionary every time new word added.

    //Console
    #define FORTH_INPUT_MAX         248     //Eight full lines of text input if hsplit
    #define FORTH_CONSOLE_STRING    "Forth for fx-CG50\n"
    #define FORTH_PROMPT            ">" 
   
    //History
    #define FORTH_HIST_COUNT    10

    //Forth stack display
    #define FORTH_STACK_CHAR_WIDTH          10  //Width of stack display in characters
    #define FORTH_STACK_FONT_WIDTH          5   //5x8 font
    #define FORTH_STACK_WIDTH               ((FORTH_STACK_FONT_WIDTH+FONT_HORZ_SPACING)*FORTH_STACK_CHAR_WIDTH+FONT_HORZ_SPACING)
    #define FORTH_STACK_FG                  COL_WHITE
    #define FORTH_STACK_BG                  C_RGB(6,6,6)
    #define FORTH_STACK_BG2                 C_RGB(9,9,9)
    #define FORTH_STACK_BORDER              FORTH_STACK_BG
    #define FORTH_STACK_SHOW_COUNT          8
    //Small adjustments to align stack display and console
    #define FORTH_STACK_CONSOLE_X_OFFSET    1
    #define FORTH_STACK_WIDTH_OFFSET        1
    //Small adjustments to align key legend below stack display
    #define FORTH_LEGEND_OFFSET1            4
    #define FORTH_LEGEND_OFFSET2            7
    #define FORTH_SUGGESTION_ROW_HEIGHT     10

    //Forth memory

    //Forth primitives
    #define FORTH_PRIM_NOT_FOUND            -1

    //enums
    //=====

    //Note different from enum ForthEngineErrors!
    enum ForthCompileError
    {
        FORTH_ERROR_NONE,
        FORTH_ERROR_TOO_LONG,
        FORTH_ERROR_INTERNAL,
        FORTH_ERROR_ENGINE,
        FORTH_ERROR_NOT_FOUND,
        FORTH_ERROR_NO_WORD,
        FORTH_ERROR_INVALID_NAME,
        FORTH_ERROR_OUT_OF_MEMORY,
        FORTH_ERROR_MEMORY_OTHER,
    };


    //structs
    //=======

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

        //Whether to draw stack in console
        bool draw_stack;

        //Copy of both stacks. Copied to XRAM at runtime.
        alignas(uint32_t) uint8_t stack_copy[FORTH_STACK_SIZE];
        alignas(uint32_t) uint8_t rstack_copy[FORTH_RSTACK_SIZE];
        alignas(uint32_t) uint8_t locals_copy[FORTH_LOCALS_SIZE];

        //Data for Forth Engine
        struct ForthEngine engine;
    };

    struct ForthDefinitionsInfo
    {
        uint32_t index; 
        //TODO: still needed? transitioned secondaries to pointer to word header
        uint32_t ID;
        uint32_t bytes_left;
        //Flexible Array Member - memory allocated after struct holds definition data
        uint8_t data[];
    };

    struct ForthWordIDsInfo
    {
        uint32_t index;
        uint32_t bytes_left;
        //Flexible Array Member - memory allocated after struct holds word ID data
        uint8_t data[];
    };

    struct ForthControlElement
    {
        uint32_t index;
        uint8_t type;
    };

    //Functions
    //=========
    int forth(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
