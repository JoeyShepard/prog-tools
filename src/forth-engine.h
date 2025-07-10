#ifndef __GUARD_PROG_TOOLS_FORTH_ENGINE
    #define __GUARD_PROG_TOOLS_FORTH_ENGINE

    #include <stdint.h>

    #include "forth-compatibility.h"

    #define FORTH_FALSE             0
    #define FORTH_TRUE              -1

    #define FORTH_CELL_SIZE         ((int)sizeof(int32_t))
    struct ForthRStackElement;          //Forward declaration for struct for return stack element
    #define FORTH_RSTACK_ELEMENT_SIZE   sizeof(struct ForthRStackElement)

    //Primitves assume stacks are aligned to their sizes, so calculated size here must be power of two
    #define FORTH_STACK_SIZE        (FORTH_CELL_SIZE*FORTH_STACK_ELEMENTS)
    #define FORTH_RSTACK_SIZE       (FORTH_RSTACK_ELEMENT_SIZE*FORTH_RSTACK_ELEMENTS)
    #define FORTH_LOCALS_SIZE       (FORTH_CELL_SIZE*FORTH_LOCALS_ELEMENTS)

    //Offset past FORTH_COMPAT_STACKS where stacks start
    #define FORTH_STACK_OFFSET      0
    //Forth data stack
    #define FORTH_STACK_ADDRESS     (FORTH_COMPAT_STACKS+FORTH_STACK_OFFSET)
    #define FORTH_STACK_END         (FORTH_STACK_ADDRESS+FORTH_STACK_SIZE)
    //Forth return stack
    #define FORTH_RSTACK_ADDRESS    FORTH_STACK_END
    #define FORTH_RSTACK_END        (FORTH_RSTACK_ADDRESS+FORTH_RSTACK_SIZE)
    //Forth locals stack
    #define FORTH_LOCALS_ADDRESS    FORTH_RSTACK_END
    #define FORTH_LOCALS_END        (FORTH_LOCALS_ADDRESS+FORTH_LOCALS_SIZE)
    //Forth engine memory - should be in fastest memory with stacks
    struct ForthEngine; //Forward declaration
    #define FORTH_ENGINE_ADDRESS    FORTH_LOCALS_END
    #define FORTH_ENGINE_END        (FORTH_ENGINE_ADDRESS+sizeof(struct ForthEngine))
    //MEMORY MAY BE UNALIGNED HERE! struct ForthEngine size divisible by largest member so probably fine but just in case

    //Masks for wrapping stack addresses
    #define FORTH_STACK_MASK        (FORTH_STACK_SIZE-1)

    //Masks for aligning data access
    #define FORTH_MASK_16           (~1)
    #define FORTH_MASK_32           (~3)

    //Max number of digits to include in error message about number out of range
    #define ERROR_INT32_SIZE        12  //max 10 digits, 1 for - sign, 1 for terminator 
    
    //Actions for outer interpreter to perform
    enum ForthActions
    {
        FORTH_ACTION_NONE,
        FORTH_ACTION_AGAIN,
        FORTH_ACTION_BEGIN,
        FORTH_ACTION_BRACKET_CHAR,
        FORTH_ACTION_BRACKET_TICK,
        FORTH_ACTION_CASE,
        FORTH_ACTION_CHAR,
        FORTH_ACTION_COLON,
        FORTH_ACTION_COMMENT,
        FORTH_ACTION_CONSTANT,
        FORTH_ACTION_CREATE,
        FORTH_ACTION_DO,
        FORTH_ACTION_DOT_QUOTE,
        FORTH_ACTION_ELSE,
        FORTH_ACTION_END,
        FORTH_ACTION_ENDCASE,
        FORTH_ACTION_ENDOF,
        FORTH_ACTION_EXECUTE,
        FORTH_ACTION_I,
        FORTH_ACTION_IF,
        FORTH_ACTION_J,
        FORTH_ACTION_LEAVE,
        FORTH_ACTION_LITERAL,
        FORTH_ACTION_LOCALS,
        FORTH_ACTION_LOOP,
        FORTH_ACTION_OF,
        FORTH_ACTION_PAREN,
        FORTH_ACTION_PLUS_LOOP,
        FORTH_ACTION_PRIMITIVES,
        FORTH_ACTION_REPEAT,
        FORTH_ACTION_RESIZE,
        FORTH_ACTION_S_QUOTE,
        FORTH_ACTION_S_BACKSLASH_QUOTE,
        FORTH_ACTION_SECONDARIES,
        FORTH_ACTION_SEMICOLON,
        FORTH_ACTION_THEN,
        FORTH_ACTION_TICK,
        FORTH_ACTION_UNDEFINED,
        FORTH_ACTION_UNTIL,
        FORTH_ACTION_VARIABLE,
        FORTH_ACTION_WHILE,
        FORTH_ACTION_WORDS,
        FORTH_ACTION_WORDSIZE,
    };

    enum ForthEngineErrors
    {
        FORTH_ENGINE_ERROR_NONE,
        FORTH_ENGINE_ERROR_COMPILE_ONLY,
        FORTH_ENGINE_ERROR_EXECUTE_ID,
        FORTH_ENGINE_ERROR_EXECUTE_IN_EXECUTE,
        FORTH_ENGINE_ERROR_EXECUTE_NO_BODY,
        FORTH_ENGINE_ERROR_INT32_RANGE,
        FORTH_ENGINE_ERROR_HEX32_RANGE,
        FORTH_ENGINE_ERROR_INTERPRET_ONLY,
        FORTH_ENGINE_ERROR_RIGHT_BRACKET,
        FORTH_ENGINE_ERROR_RSTACK_FULL,
        FORTH_ENGINE_ERROR_SECONDARY_IN_BRACKET,
        FORTH_ENGINE_ERROR_UNDEFINED,
    };

    enum ForthState
    {
        FORTH_STATE_INTERPRET,  //0 is interpret per Forth standard
        FORTH_STATE_COMPILE
    };

    enum ForthObjectType
    {
        FORTH_TYPE_NUMBER,
        FORTH_TYPE_HEX,
        FORTH_TYPE_OTHER,
        FORTH_TYPE_PRIMITIVE,
        FORTH_TYPE_SECONDARY,
        FORTH_TYPE_NOT_FOUND,
        FORTH_TYPE_NONE
    };

    enum ForthSecondaryType
    {
        FORTH_SECONDARY_WORD,
        FORTH_SECONDARY_CONSTANT,
        FORTH_SECONDARY_CREATE,
        FORTH_SECONDARY_VARIABLE,
        FORTH_SECONDARY_UNDEFINED
    };

    enum ForthRStackType
    {
        FORTH_RSTACK_DONE,      //Pushed by top-level secondary. Stop executing when returning from this. 
        FORTH_RSTACK_RETURN,    //Return address to return to calling secondary.
        FORTH_RSTACK_DO_LOOP
    };

    struct ForthRStackElement
    {
        uint32_t value;
        uint32_t value_max;
        uint32_t index;         //TODO: need? can probably delete
        uint8_t type;
    };

    //Declared here for struct ForthEngine and defined below
    struct ForthWordHeader;

    struct ForthEngine
    {
        //Data stack
        uintptr_t stack_base;   //Store base as uintptr_t to do wrapping calculation on pointer
        int32_t *stack;         //Points to currently free stack element
        uint32_t stack_count;   //Count of elements allocated for stack

        //Return stack
        struct ForthRStackElement *rstack_base;
        struct ForthRStackElement *rstack;      //Points to currently free stack element
        uint32_t rstack_count;                  //Count of elements allocated for stack

        //Locals stack
        int32_t *locals_base;
        int32_t *locals_stack;
        uint32_t locals_count;

        //Loop counters
        int32_t loop_i;
        int32_t loop_i_max;
        int32_t loop_j;
        int32_t loop_j_max;

        //Data area - like dictionary but no definitions stored there
        uint8_t *data;          //Pointer to memory occupied by data area
        uint32_t data_size;
        uint32_t data_index;    //Index into memory pointed to by *data
        uint32_t data_mask;
        uint32_t data_mask_16;
        uint32_t data_mask_32;

        //TODO: see assembly - may need to change order so SH4 doesn't try to load byte by byte
        //Execution
        void (**address)(struct ForthEngine *engine);
        volatile bool executing;    //Set to false by ON in key filter - see compatibility.c
        bool exit_program;
        uint32_t word_index;
        struct ForthWordHeader *word_headers;
        uint8_t *word_bodies;
        uint32_t word_count;
        prof_t perf_counter;        //Performance counter on calculator
        uint32_t perf_value;        //Result of running performance counter

        //Compilation
        bool state;
        bool in_bracket;
        int word_action;

        //Errors - compilation or state error
        int error;
        char error_num[ERROR_INT32_SIZE];    //Buffer to print number causing error (ie too long for >NUM)
        const char *error_word;

        //Compatibility functions - set at initialization so engine can adapt to different platforms
        void (*print)(const char *text);
        void (*print_color)(const char *text,color_t color);
        int32_t (*input)(int32_t text_address,char *text_base,int32_t max_chars,uint32_t mask);
        int32_t (*getkey)(bool blocking);
        int32_t (*printable)(int32_t key);
        void (*update_screen)();
        void (*update_modifiers)();
        void (*clear_console)();

        //Compatibility parameters - adjused in forth-compatibility.h for each platform
        int32_t max_spaces;
        int32_t screen_width;
        int32_t screen_height;
    };

    struct ForthWordHeader
    {
        void (**address)(struct ForthEngine *engine);   //Target address within definitions memory
        uint32_t offset;                                //Offset into definitions of target address
        uint32_t definition_size;
        uint32_t name_offset;
        uint32_t name_len;
        char *name;
        uint16_t ID;                        //ID assigned to each user-defined word
        uint16_t locals_size;               //Size in bytes of locals memory that word uses
        uint8_t type;                       //User-defined word, variable, constant, etc
        bool last;                          //Whether this header is empty header marking end of list
        bool done;                          //Whether word is done being processed. Used to rewind if error in word.
        
    };


    //Functions
    //=========
    void forth_init_engine(struct ForthEngine *engine,
        //Stacks
        void *stack_base,
        void *rstack_base,
        void *locals_stack_base,
        uint32_t stack_count,
        uint32_t rstack_count,
        uint32_t locals_stack_count,
        //Data area
        uint32_t data_size,
        //Function pointers
        void (*print)(const char *text),
        void (*print_color)(const char *text,color_t color),
        int32_t (*forth_accept)(int32_t text_address,char *text_base,int32_t max_chars,uint32_t mask),
        int32_t (*getkey)(bool blocking),
        int32_t (*printable)(int32_t key),
        void (*update_screen)(),
        void (*update_modifiers)(),
        void (*clear_console)(),
        //Console
        int32_t max_spaces,
        int16_t screen_width,
        int16_t screen_height);
    void forth_gen_masks(struct ForthEngine *engine,uint32_t data_size);
    void forth_reload_engine(struct ForthEngine *engine,uint8_t *data);
    void forth_reset_engine(struct ForthEngine *engine);
    void forth_reset_engine_stacks(struct ForthEngine *engine);
    void forth_engine_pre_exec(struct ForthEngine *engine);
    int32_t forth_stack_count(struct ForthEngine *engine);
    void forth_push(struct ForthEngine *engine,int32_t value);
    int32_t forth_pop(struct ForthEngine *engine);
    void forth_rstack_push(int32_t value,int32_t value_ma,uint8_t type,uint32_t index,struct ForthEngine *engine);
    int forth_execute_secondary(struct ForthEngine *engine,struct ForthWordHeader *secondary,struct ForthWordHeader *colon_word,
                                struct ForthWordHeader *word_headers,uint32_t word_count,uint8_t *word_bodies);

#endif
