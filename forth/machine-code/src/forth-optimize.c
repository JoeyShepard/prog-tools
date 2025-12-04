#include "forth-engine.h"
#include "forth-locals.h"
#include "forth-optimize.h"
#include "forth-primitives.h"
#include "logging.h"


int forth_optimize(uint8_t *optimized, int opt_size, uint8_t *data, int data_size)
{
    log_push(LOGGING_FORTH_OPT_OPTIMIZE,"forth_optimize");

    //TODO: better place than stack?
    uint8_t code_mem[FORTH_OPT_CODE_SIZE];
    int code_index=0;
    //struct ssa_mem[FORTH_OPT_CODE_SIZE];
    //int ssa_index=0;

    log_pop();

    return 0;
}

