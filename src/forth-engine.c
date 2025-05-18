#include <stdint.h>

#include "forth-engine.h"
#include "structs.h"

//Called only once when program first starts
void forth_init_engine(struct ForthEngine *engine,
    //Stacks
    uintptr_t stack_base,
    struct ForthRStackElement *rstack_base,
    uint32_t stack_count,
    uint32_t rstack_count,
    //Data area
    uint32_t data_size,
    //Compatibility function pointers
    void (*print)(const char *text),
    void (*print_color)(const char *text,color_t color),
    int32_t (*input)(int32_t text_address,char *text_base,int32_t max_chars,uint32_t mask),
    int32_t (*getkey)(bool blocking),
    int32_t (*printable)(int32_t key),
    void (*update_screen)(),
    void (*update_modifiers)(),
    void (*clear_console)(),
    //Console
    int32_t max_spaces,
    int16_t screen_width,
    int16_t screen_height)
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

    //Compatiblity parameters that can be adjusted to work on other platforms
    engine->print=print;
    engine->print_color=print_color;
    engine->input=input;
    engine->getkey=getkey;
    engine->printable=printable;
    engine->update_screen=update_screen;
    engine->update_modifiers=update_modifiers;
    engine->clear_console=clear_console;
    engine->max_spaces=max_spaces;
    engine->screen_width=screen_width;
    engine->screen_height=screen_height;

    //Reset stack pointers and compilation variables
    forth_reset_engine(engine);
}

//Called on program switch
void forth_reload_engine(struct ForthEngine *engine,uint8_t *data)
{
    engine->data=data;
}

//Called when program first starts and when user resets environment but not on program switch
void forth_reset_engine(struct ForthEngine *engine)
{
    //Reset engine variables
    engine->state=false;
    engine->in_bracket=false;
    engine->data_index=0;
    engine->error=FORTH_ENGINE_ERROR_NONE;

    //Reset stack pointers
    forth_reset_engine_stacks(engine);
}

//Called when program first starts and when user resets environment but not on program switch
void forth_reset_engine_stacks(struct ForthEngine *engine)
{
    //Reset stack pointers
    engine->stack=(int32_t*)(engine->stack_base+(engine->stack_count-1)*FORTH_CELL_SIZE);
    engine->rstack=engine->rstack_base+engine->rstack_count-1;
}

//Called before executing word in outer interpreter (ie process_source in forth.c)
void forth_engine_pre_exec(struct ForthEngine *engine)
{
    //Word may request caller perform action
    engine->word_action=FORTH_ACTION_NONE;

    //Index to identify values on R stack
    engine->word_index=0;
}

int32_t forth_stack_count(struct ForthEngine *engine)
{
    return FORTH_STACK_ELEMENTS-((uintptr_t)(engine->stack)-(uintptr_t)(engine->stack_base))/FORTH_CELL_SIZE-1;
}

void forth_push(struct ForthEngine *engine,int32_t value)
{
    *engine->stack=value;
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

void forth_rstack_push(int32_t value,uint8_t type,uint8_t index,struct ForthEngine *engine)
{
    if (engine->rstack<engine->rstack_base)
    {
        //Out of R-stack memory - abort
        engine->error=FORTH_ENGINE_ERROR_RSTACK_FULL;
        engine->executing=false;
    }

    //Push new values to R-stack
    engine->rstack->value=value;
    engine->rstack->type=type;
    engine->rstack->index=index;

    //Decrease R-stack pointer to next element
    engine->rstack--;
}

