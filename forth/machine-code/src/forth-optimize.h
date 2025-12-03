#ifndef __GUARD_PROG_TOOLS_FORTH_OPTIMIZE
    #define __GUARD_PROG_TOOLS_FORTH_OPTIMIZE

    #include <stddef.h>

    //#include "forth.h"

    #define FORTH_OPT_CODE_SIZE     1024
    #define FORTH_OPT_SSA_COUNT     32
    #define FORTH_OPT_OBJ_COUNT     32

    int forth_optimize(uint8_t *target, uint8_t *data, size_t data_size);

#endif
