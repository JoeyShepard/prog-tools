#ifndef __GUARD_PROG_TOOLS_FORTH_ENGINE
    #define __GUARD_PROG_TOOLS_FORTH_ENGINE

    #include <stdint.h>

    #include "forth-compatibility.h"

    #define FORTH_FALSE             0
    #define FORTH_TRUE              -1

    #define FORTH_CELL_SIZE         ((int)sizeof(int32_t))

    //Primitves assume stacks are aligned to their sizes, so calculated size here must be power of two
    #define FORTH_STACK_SIZE        (FORTH_CELL_SIZE*FORTH_STACK_ELEMENTS)
    #define FORTH_RSTACK_SIZE       (FORTH_CELL_SIZE*FORTH_RSTACK_ELEMENTS)
    #define FORTH_LOCALS_SIZE       (FORTH_CELL_SIZE*FORTH_LOCALS_ELEMENTS)

    #define FORTH_STACK_OFFSET      0
    #define FORTH_STACK_ADDRESS     (FORTH_COMPAT_STACKS+FORTH_STACK_OFFSET)
    #define FORTH_STACK_END         (FORTH_STACK_ADDRESS+FORTH_STACK_SIZE)
    #define FORTH_RSTACK_ADDRESS    FORTH_STACK_END
    #define FORTH_RSTACK_END        (FORTH_RSTACK_ADDRESS+FORTH_RSTACK_SIZE)
    #define FORTH_LOCALS_ADDRESS    FORTH_RSTACK_END
    #define FORTH_LOCALS_END        (FORTH_LOCALS_ADDRESS+FORTH_LOCALS_SIZE)

    //Masks for wrapping stack addresses
    #define FORTH_STACK_MASK        (FORTH_STACK_SIZE-1)
    #define FORTH_RSTACK_MASK       (FORTH_RSTACK_SIZE-1)

    //Masks for aligning data access
    #define FORTH_MASK_16           (~1)
    #define FORTH_MASK_32           (~3)
    
    //Actions for outer interpreter to perform
    enum ForthCompileActions
    {
        FORTH_ACTION_NONE,
        FORTH_ACTION_COLON,
        FORTH_ACTION_SEMICOLON,
        FORTH_ACTION_CHAR,
        FORTH_ACTION_PAREN,
        FORTH_ACTION_WORDS
    };

    enum ForthEngineErrors
    {
        FORTH_ENGINE_ERROR_NONE,
        FORTH_ENGINE_ERROR_INTERPRET_ONLY,
        FORTH_ENGINE_ERROR_COMPILE_ONLY
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
        FORTH_SECONDARY_WORD
    };

    struct ForthEngine
    {
        //Data stack
        uintptr_t stack_base;
        int32_t *stack;
        uint32_t stack_count;

        //Return stack
        uintptr_t rstack_base;
        int32_t *rstack;
        uint32_t rstack_count;

        //Data area - like dictionary but no definitions stored there
        uint8_t *data;          //Pointer to memory occupied by data area
        uint32_t data_size;
        uint32_t data_index;    //Index into memory pointed to be *data
        uint32_t data_mask;
        uint32_t data_mask_16;
        uint32_t data_mask_32;

        //Compilation
        bool state;
        bool in_bracket;
        int word_action;

        //Execution
        bool executing;
        void (**address)(struct ForthEngine *engine);
        uint32_t word_index;

        //Errors - compilation or state error
        int32_t error;

        //Compatibility functions - set at initialization so engine can adapt to different systems
        void (*print)(const char *text);
        void (*print_color)(const char *text,color_t color);
        int32_t (*input)(int32_t text_address,char *text_base,int32_t max_chars,uint32_t mask);
        int32_t (*getkey)(bool blocking);
        int32_t (*printable)(int32_t key);
        void (*update_screen)();
        void (*update_modifiers)();
        void (*clear_console)();

        //Compatibility parameters
        int32_t max_spaces;
        int32_t screen_width;
        int32_t screen_height;
    };

    struct ForthWordHeader
    {
        void (**address)(struct ForthEngine *engine);   //Target address within definitions memory
        uint32_t offset;                                //Offset into definitions of target address
        uint32_t definition_size;
        uint16_t header_size;               //Size of this header entry - ie sizeof(ForthWordHeader)+sizeof(name[])
        uint16_t ID;                        //ID assigned to each user-defined word
        uint8_t type;                       //User-defined word, variable, constant, etc
        uint8_t name_len;
        //Flexible Array Member - memory allocated after struct holds name
        char name[];
    };

    //Functions
    //=========
    void forth_init_engine(struct ForthEngine *engine,
        //Stacks
        uintptr_t stack_base,
        uintptr_t rstack_base,
        uint32_t stack_count,
        uint32_t rstack_count,
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
    void forth_reload_engine(struct ForthEngine *engine,uint8_t *data);
    void forth_reset_engine(struct ForthEngine *engine);
    void forth_reset_engine_stacks(struct ForthEngine *engine);
    void forth_engine_pre_exec(struct ForthEngine *engine);
    int32_t forth_stack_count(struct ForthEngine *engine);
    void forth_push(struct ForthEngine *engine,int32_t value);
    
#endif
