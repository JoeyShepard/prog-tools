#include <stdint.h>

#include "forth-engine.h"
#include "structs.h"

int forth_stack_count(struct ForthEngine *engine)
{
    return FORTH_STACK_ELEMENTS-((uintptr_t)(engine->stack)-(uintptr_t)(engine->stack_base))/FORTH_CELL_SIZE-1;
}

void forth_push(struct ForthEngine *engine,int32_t value)
{
    *engine->stack=value;
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
