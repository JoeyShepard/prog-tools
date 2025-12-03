#include "forth-engine.h"
#include "forth-locals.h"
#include "forth-optimize.h"
#include "forth-primitives.h"


int forth_optimize(uint8_t *target, uint8_t *data, size_t data_size)
{
    //TODO: better place than stack?
    uint8_t code_mem[FORTH_OPT_CODE_SIZE];
    int code_index=0;
    //struct ssa_mem[FORTH_OPT_CODE_SIZE];
    //int ssa_index=0;

    return 0;
}

