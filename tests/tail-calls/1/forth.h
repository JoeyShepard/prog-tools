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
    #define FORTH_ID_WORD_HEADERS   3
    #define FORTH_ID_WORD_NAMES     4
    #define FORTH_ID_CONTROL_STACK  5
    #define FORTH_MEM_DATA          0x2000  //Initial value - can change programmatically

    //TODO: restore
    //#define FORTH_MEM_DEFINITIONS   1024    //For these four, allocate this amount initially then add this     
    //#define FORTH_MEM_WORD_HEADERS  512     //much when memory runs out. Exact amount not important - prevents
    //#define FORTH_MEM_WORD_NAMES    512     //copying whole dictionary every time new word added.

    #define FORTH_MEM_DEFINITIONS   128     //For these four, allocate this amount initially then add this     
    #define FORTH_MEM_WORD_HEADERS  128     //much when memory runs out. Exact amount not important - prevents
    #define FORTH_MEM_WORD_NAMES    64      //copying whole dictionary every time new word added.

    #define FORTH_MEM_CONTROL_STACK 512

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
    #define FORTH_LEGEND_OFFSET_X           5
    #define FORTH_LEGEND_OFFSET_Y           3
    #define FORTH_SUGGESTION_OFFSET_Y       2
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
        FORTH_ERROR_AGAIN_WITHOUT_BEGIN,
        FORTH_ERROR_CONTROL_UNDERFLOW,
        FORTH_ERROR_DEFINTION_OPEN,
        FORTH_ERROR_ELSE_WITHOUT_IF,
        FORTH_ERROR_ENGINE,
        FORTH_ERROR_INT32_RANGE,
        FORTH_ERROR_INTERNAL,
        FORTH_ERROR_INVALID_NAME,
        FORTH_ERROR_LOOP_WITHOUT_DO,
        FORTH_ERROR_MEMORY_OTHER,
        FORTH_ERROR_MISSING_QUOTE,
        FORTH_ERROR_NO_WORD,
        FORTH_ERROR_NOT_BETWEEN_BRACKETS,
        FORTH_ERROR_NOT_FOUND,
        FORTH_ERROR_ON_KEY,
        FORTH_ERROR_OUT_OF_MEMORY,
        FORTH_ERROR_REPEAT_WITHOUT_WHILE,
        FORTH_ERROR_THEN_WITHOUT_IF,
        FORTH_ERROR_TOO_LONG,
        FORTH_ERROR_UNTERMINATED_BEGIN,
        FORTH_ERROR_UNTERMINATED_CASE,
        FORTH_ERROR_UNTERMINATED_OF,
        FORTH_ERROR_UNTERMINATED_DO,
        FORTH_ERROR_UNTERMINATED_IF,
        FORTH_ERROR_UNTERMINATED_ELSE,
        FORTH_ERROR_UNTERMINATED_WHILE,
        FORTH_ERROR_UNTIL_WITHOUT_BEGIN,
        FORTH_ERROR_WHILE_WITHOUT_BEGIN,
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
        struct ForthEngine *engine;
        struct ForthEngine engine_copy;
    };

    struct ForthDefinitionsInfo
    {
        uint32_t index; 
        uint32_t bytes_left;
        //Flexible Array Member - memory allocated after struct holds definition data
        uint8_t data[];
    };

    struct ForthWordHeaderInfo
    {
        uint32_t index;
        uint32_t bytes_left;
        struct ForthWordHeader header[];
    };

    struct ForthWordNameInfo
    {
        uint32_t index;
        uint32_t bytes_left;
        char names[];
    };

    struct ForthControlElement
    {
        uint32_t index;
        uint8_t type;
    };

    struct ForthControlInfo
    {
        uint32_t index;
        uint32_t bytes_left;
        struct ForthControlElement elements[];
    };

    struct ForthCompileInfo
    {
        const char *error_word;
        uint8_t *data;
        struct ForthDefinitionsInfo *definitions;
        struct ForthWordHeaderInfo *words;
        struct ForthWordNameInfo *word_names;
        struct ForthControlInfo *control_stack;
        uint8_t *heap_ptr;
        int primitive_ID;
        struct ForthWordHeader *secondary;
        uint32_t secondary_index;
        uint32_t word_len;
        struct ForthWordHeader *colon_word;
        uint32_t colon_word_index;
        bool colon_word_exists;
        uint32_t delete_offset;
        uint32_t delete_size;
        uint32_t save_offset;
        uint32_t save_definition_size;
        uint8_t save_type;
    };


    //Functions
    //=========
    int forth(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
