#ifndef __GUARD_PROG_TOOLS_FORTH
    #define __GUARD_PROG_TOOLS_FORTH

    #include <stdalign.h>
    #include <stdint.h>

    #include "compatibility.h"
    #include "console.h"
    #include "forth-compatibility.h"
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
    #define FORTH_ID_WORD_IDS       2
    #define FORTH_MEM_DEFINITIONS   1024    //For both of these, allocate this amount initially then add this     
    #define FORTH_MEM_WORD_IDS      256     //much when memory runs out. Exact amount not important - prevents
                                            //copying whole dictionary every time new word added.

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
    #define FORTH_DATA_SIZE     0x10000


    //enums
    //=====
    enum ForthParse
    {
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
        FORTH_TYPE_PRIMATIVE,
        FORTH_TYPE_SECONDARY,
        FORTH_TYPE_NOT_FOUND,
        //Partial types used only for parsing
        FORTH_TYPE_NONE,
        FORTH_TYPE_MINUS,
        FORTH_TYPE_0,
        FORTH_TYPE_0x,
        FORTH_TYPE_OTHER,
    };

    //Note different from enum ForthEngineErrors
    enum ForthCompileErrors
    {
        FORTH_ERROR_NONE,
        FORTH_ERROR_TOO_LONG,
        FORTH_ERROR_INTERNAL,
        FORTH_ERROR_ENGINE
    };

    //structs
    struct ForthWordHeader
    {
        uint32_t size;
        uint32_t ID;
        uint8_t word_type;
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

        //Whether to draw stack in console
        bool draw_stack;

        //Memory for Forth programs to use - must be aligned for int32_t access
        //TODO: might be nice to have data size be adjustable
        alignas(uint32_t) uint8_t data[FORTH_DATA_SIZE];

        //Copy of both stacks. Copied to XRAM at runtime.
        alignas(uint32_t) uint8_t stack_copy[FORTH_STACK_SIZE];
        alignas(uint32_t) uint8_t rstack_copy[FORTH_RSTACK_SIZE];
        alignas(uint32_t) uint8_t locals_copy[FORTH_LOCALS_SIZE];

        //Data for Forth Engine
        struct ForthEngine engine;
    };

    //Functions
    //=========
    int forth(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
