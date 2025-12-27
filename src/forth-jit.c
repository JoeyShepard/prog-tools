#include <string.h>

#include "forth-jit.h"
#include "logging.h"

int forth_jit(struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_JIT,"forth_jit");
    for (int i=0;i<3;i++)
        log_text("%p: %p\n",(compile->secondary->address+i),*(compile->secondary->address+i));
    log_text("\n");

    forth_prim_t prim=&prim_hidden_push;
    memcpy(compile->jit_data->data,&prim,sizeof(prim));
    log_text("writing %p to %p\n",prim,compile->jit_data->data);

    int32_t value=42;
    memcpy(compile->jit_data->data+4,&value,sizeof(value));
    log_text("writing %d to %p\n",value,compile->jit_data->data+4);
    
    //Machine code
    uint16_t code=0xe169;

    prim=&prim_hidden_done;
    memcpy(compile->jit_data->data+8,&prim,sizeof(prim));
    log_text("writing %p to %p\n",prim,compile->jit_data->data+8);

    forth_prim_t *debug=(forth_prim_t *)compile->jit_data->data;
    for (int i=0;i<3;i++)
        log_text("%p: %p\n",debug+i,*(debug+i));
    log_text("\n");

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

