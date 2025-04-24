#ifndef __GUARD_PROG_TOOLS_FORTH_ENGINE
    #define __GUARD_PROG_TOOLS_FORTH_ENGINE

    #include <stdint.h>

    #include "forth-primitives.h"
    #include "structs.h"

    #define FORTH_FALSE             0
    #define FORTH_TRUE              -1

    #define FORTH_CELL_SIZE         ((int)sizeof(int32_t))

    #define FORTH_STACK_ELEMENTS    256
    #define FORTH_RSTACK_ELEMENTS   256

    //Primitves assume stacks are aligned to their sizes, so calculated size here must be power of two
    #define FORTH_STACK_SIZE        (FORTH_CELL_SIZE*FORTH_STACK_ELEMENTS)
    #define FORTH_RSTACK_SIZE       (FORTH_CELL_SIZE*FORTH_RSTACK_ELEMENTS)

    #define FORTH_STACK_OFFSET      0
    #define FORTH_STACK_ADDRESS     (xram+FORTH_STACK_OFFSET)
    #define FORTH_STACK_END         (FORTH_STACK_ADDRESS+FORTH_STACK_SIZE)
    #define FORTH_RSTACK_ADDRESS    FORTH_STACK_END
    #define FORTH_RSTACK_END        (FORTH_RSTACK_ADDRESS+FORTH_RSTACK_SIZE)

    //Masks for wrapping stack addresses
    #define FORTH_STACK_MASK        (FORTH_STACK_SIZE-1)
    #define FORTH_RSTACK_MASK       (FORTH_RSTACK_SIZE-1)

    enum ForthEngineErrors
    {
        FORTH_RUN_ERROR_NONE
    };

    //Functions
    //=========
    int forth_stack_count(struct ForthEngine *engine);
    void forth_push(struct ForthEngine *engine,int32_t value);
    

#endif
