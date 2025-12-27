#include <string.h>

#include "forth-jit.h"
#include "logging.h"

int forth_jit(struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_JIT,"forth_jit");
    
    forth_prim_t prim=&prim_hidden_push;
    memcpy(compile->jit_data,&prim,sizeof(prim));
    int32_t value=42;
    memcpy(compile->jit_data+4,&value,sizeof(value));
    prim=&prim_hidden_done;
    memcpy(compile->jit_data+8,&prim,sizeof(prim));

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

