#include <stdint.h>

#include "forth-engine.h"
#include "structs.h"

//Called only once when program first starts
void forth_init_engine(struct ForthEngine *engine,uintptr_t stack_base,uintptr_t rstack_base,
    uint32_t stack_count,uint32_t rstack_count,uint32_t data_size)
{
    //Init Forth engine pointers (these values never change)
    engine->stack_base=stack_base;
    engine->rstack_base=rstack_base;

    //Init Forth engine parameters
    engine->stack_count=stack_count;
    engine->rstack_count=rstack_count;
    //Size must be power of 2 for mask to work correctly
    engine->data_size=data_size;
    engine->data_mask=data_size-1;
    engine->data_mask_16=(engine->data_mask)&FORTH_MASK_16;
    engine->data_mask_32=(engine->data_mask)&FORTH_MASK_32;

    //Reset stack pointers and compilation variables
    forth_reset_engine(engine);
}

//Called when program first starts and on program switch
void forth_reload_engine(struct ForthEngine *engine,uint8_t *data,void (*print)(const char *text),int32_t max_spaces)
{
    engine->data=data;
    engine->print=forth_print;
    engine->max_spaces=max_spaces;
}

//Called when program first starts and when user resets environment but not on program switch
void forth_reset_engine(struct ForthEngine *engine)
{
    //Reset engine variables
    engine->state=false;
    engine->data_ptr=0;

    //Reset stack pointers
    forth_reset_engine_stacks(engine);
}

//Called when program first starts and when user resets environment but not on program switch
void forth_reset_engine_stacks(struct ForthEngine *engine)
{
    //Reset stack pointers
    engine->stack=(int32_t*)(engine->stack_base+(engine->stack_count-1)*FORTH_CELL_SIZE);
    engine->rstack=(int32_t*)(engine->rstack_base+(engine->rstack_count-1)*FORTH_CELL_SIZE);
}

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
