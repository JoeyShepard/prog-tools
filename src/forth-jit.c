#include <string.h>

#include "forth-jit.h"
#include "forth-mem.h"
#include "logging.h"
#include "macros.h"
#include "mem.h"

void set_jit_data(struct ForthJitGeneric *settings,struct ForthCompileInfo *compile)
{
    settings->data=compile->jit_data->data;
    settings->index=&compile->jit_data->index;
    settings->mem_size=FORTH_MEM_JIT_DATA;
    settings->ID=FORTH_ID_JIT_DATA;
    settings->bytes_left=&compile->jit_data->bytes_left;
}

int expand_jit_data(uint32_t size,struct ForthCompileInfo *compile)
{
    struct ForthJitGeneric settings;
    set_jit_data(&settings,compile);
    return expand_generic(size,settings.mem_size,settings.ID,settings.bytes_left,compile);
}

int write_jit_primitive(forth_prim_t value,struct ForthCompileInfo *compile)
{
    struct ForthJitGeneric settings;
    set_jit_data(&settings,compile);
    return write_generic((generic_t)value,sizeof(value),settings.data,settings.index,settings.mem_size,
                            settings.ID,settings.bytes_left,compile);
}

int forth_jit(struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_JIT,"forth_jit");

    /*
    START HERE
    - figure out how to handle IF (ie WHILE/AGAIN)
      - no matching primitive, just target so hard to adjust
      - in the case of IF, can't adjust until done with code gen following
      - store adjusted jump distances with constants?
      - prob need to scan whole secondary recording jump targets
        - yes since need to end optmizing at BEGIN
    */

    


    //Logging
    log_pop();

    int FORTH_ERROR_NONE;
}

int forth_jit_free(struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_JIT_FREE,"forth_jit_free");

    //Logging
    log_pop();

    int FORTH_ERROR_NONE;
}

