#include <string.h>

#include "forth-jit.h"
#include "logging.h"
#include "macros.h"

//TODO: remove
void prim_dupe(struct ForthEngine *engine);
void prim_i(struct ForthEngine *engine);
void prim_hidden_jit(struct ForthEngine *engine);

void jit_print()
{
    log_text("JIT print test\n");
}

int forth_jit(struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_JIT,"forth_jit");
    log_text("secondary:\n");
    for (int i=0;i<3;i++)
        log_text("%p: %p\n",(compile->secondary->address+i),*(compile->secondary->address+i));
    log_text("\n");

    enum
    {
        DEBUG_PRIM,
        DEBUG_U16,
        DEBUG_U32
    };
    struct DebugInfo
    {
        int type;
        union DebugUnion
        {
            forth_prim_t prim;
            uint16_t u16;
            uint32_t u32;
        } data;
    } debug[]={
        {DEBUG_PRIM,    &prim_hidden_push},
        {DEBUG_U32,     .data.u32=42},
        {DEBUG_PRIM,    &prim_hidden_jit},
        {DEBUG_U16,     .data.u16=0xe169},  //mov #69,r1
        {DEBUG_U16,     .data.u16=0x1412},  //mov.l r1,@(8,r4)

        {DEBUG_U16,     .data.u16=0x5144},  //mov.l @(16,r4),r1
        {DEBUG_U16,     .data.u16=0x710c},  //add #12,r1
        
        {DEBUG_U16,     .data.u16=0x000b},  //rts
        {DEBUG_U16,     .data.u16=0x1414},  //mov.l r1,@(16,r4)

        //{DEBUG_U16,     .data.u16=0x0009},  //nop
        
        {DEBUG_PRIM,    &prim_dupe},
        {DEBUG_PRIM,    &prim_i},
        {DEBUG_PRIM,    &prim_hidden_done},
        };

    int offset=0;
    for (int i=0;i<ARRAY_LEN(debug);i++)
    {
        switch (debug[i].type)
        {
            case DEBUG_PRIM:
                memcpy(compile->jit_data->data+offset,&debug[i].data.prim,sizeof(forth_prim_t));
                offset+=sizeof(forth_prim_t);
                break;
            case DEBUG_U16:
                memcpy(compile->jit_data->data+offset,&debug[i].data.u16,sizeof(uint16_t));
                offset+=sizeof(uint16_t);
                break;
            case DEBUG_U32:
                memcpy(compile->jit_data->data+offset,&debug[i].data.u32,sizeof(uint32_t));
                offset+=sizeof(uint32_t);
                break;
        }
    }

    log_text("check:\n");
    forth_prim_t *debug_prim=(forth_prim_t *)compile->jit_data->data;
    for (int i=0;i<10;i++)
        log_text("%p: %010p\n",debug_prim+i,*(debug_prim+i));
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

