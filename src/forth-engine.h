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

    #define FORTH_STACK_OFFSET      0
    #define FORTH_STACK_ADDRESS     (FORTH_COMPAT_STACKS+FORTH_STACK_OFFSET)
    #define FORTH_STACK_END         (FORTH_STACK_ADDRESS+FORTH_STACK_SIZE)
    #define FORTH_RSTACK_ADDRESS    FORTH_STACK_END
    #define FORTH_RSTACK_END        (FORTH_RSTACK_ADDRESS+FORTH_RSTACK_SIZE)

    //Masks for wrapping stack addresses
    #define FORTH_STACK_MASK        (FORTH_STACK_SIZE-1)
    #define FORTH_RSTACK_MASK       (FORTH_RSTACK_SIZE-1)

    //Masks for aligning data access
    #define FORTH_MASK_16           (~1)
    #define FORTH_MASK_32           (~3)
    
    enum ForthEngineErrors
    {
        FORTH_ENGINE_ERROR_NONE,
        FORTH_ENGINE_ERROR_IMMED_ONLY
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
        uint32_t data_ptr;      //Index into memory pointed to be *data
        uint32_t data_mask;
        uint32_t data_mask_16;
        uint32_t data_mask_32;

        //Compilation
        bool state;
        bool in_bracket;
        const char *source;
        int32_t *source_index;
        int error;

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
        int max_spaces;
        color_t color_primitive;
        int screen_width;
        int screen_height;
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
        int max_spaces,
        int screen_width,
        int screen_height,
        color_t color_primitive);
    void forth_reload_engine(struct ForthEngine *engine,uint8_t *data);
    void forth_reset_engine(struct ForthEngine *engine);
    void forth_reset_engine_stacks(struct ForthEngine *engine);
    int forth_stack_count(struct ForthEngine *engine);
    void forth_push(struct ForthEngine *engine,int32_t value);
    
#endif
