#ifndef __GUARD_PROG_TOOLS_FORTH_ENGINE
    #define __GUARD_PROG_TOOLS_FORTH_ENGINE

    #include <stdint.h>

    #include "forth-primitives.h"

    #define FORTH_CELL_SIZE     ((int)sizeof(int32_t))

    #define FORTH_STACK_ELEMENTS    256
    #define FORTH_STACK_BEGIN       0
    #define FORTH_STACK_END         (FORTH_STACK_BEGIN+FORTH_CELL_SIZE*FORTH_STACK_ELEMENTS)
    #define FORTH_RSTACK_ELEMENTS   256
    #define FORTH_RSTACK_BEGIN      FORTH_STACK_END
    #define FORTH_RSTACK_END        (FORTH_RSTACK_BEGIN+FORTH_CELL_SIZE*FORTH_RSTACK_ELEMENTS)

    //Primitves assume stacks are aligned to their sizes, so calculated size here must be power of two
    #define FORTH_STACK_SIZE        (FORTH_CELL_SIZE*FORTH_STACK_ELEMENTS)
    #define FORTH_RSTACK_SIZE       (FORTH_CELL_SIZE*FORTH_RSTACK_ELEMENTS)

    //Masks for wrapping stack addresses
    #define FORTH_STACK_MASK        (FORTH_STACK_SIZE-1)
    #define FORTH_RSTACK_MASK       (FORTH_RSTACK_SIZE-1)


    //Functions
    //=========
    int forth_process_source(const char *source);

#endif
