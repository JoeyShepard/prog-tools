#include <stdint.h>

#include "forth-engine.h"
#include "logging.h"
#include "structs.h"

//Called only once when program first starts
void forth_init_engine(struct ForthEngine *engine,
    //Stacks
    void *stack_base,
    void *rstack_base,
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
    engine->stack_base=(uintptr_t)stack_base;
    engine->rstack_base=(struct ForthRStackElement *)rstack_base;

    //Init Forth engine parameters
    engine->stack_count=stack_count;
    engine->rstack_count=rstack_count;
    //Size must be power of 2 for mask to work correctly
    forth_gen_masks(engine,data_size);

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

    //Clear performance counter value
    engine->perf_value=0;
}

void forth_gen_masks(struct ForthEngine *engine,uint32_t data_size)
{
    engine->data_size=data_size;
    engine->data_mask=data_size-1;
    engine->data_index&=engine->data_mask;
    engine->data_mask_16=(engine->data_mask)&FORTH_MASK_16;
    engine->data_mask_32=(engine->data_mask)&FORTH_MASK_32;
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
//TODO: anything else to add? see how used in forth.c
//TODO: combine with execute_secondary and/or create execute_primitive
void forth_engine_pre_exec(struct ForthEngine *engine)
{
    //Word may request caller perform action
    engine->word_action=FORTH_ACTION_NONE;

    //Word may set error
    engine->error=FORTH_ENGINE_ERROR_NONE;

    //Index to identify values on R stack
    engine->word_index=0;

    //Loop counters
    engine->loop_i=0;
    engine->loop_i_max=0;
    engine->loop_j=0;
    engine->loop_j_max=0;

    //Reset Forth return stack
    engine->rstack=engine->rstack_base+engine->rstack_count-1;
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

int32_t forth_pop(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    return *engine->stack;
}

void forth_rstack_push(int32_t value,int32_t value_max,uint8_t type,uint32_t index,struct ForthEngine *engine)
{
    if (engine->rstack<engine->rstack_base)
    {
        //Out of R-stack memory - abort
        engine->error=FORTH_ENGINE_ERROR_RSTACK_FULL;
        engine->executing=false;
    }
    else
    {
        //Push new values to R-stack
        engine->rstack->value=value;
        engine->rstack->value_max=value_max;
        engine->rstack->type=type;
        engine->rstack->index=index;

        //Decrease R-stack pointer to next element
        engine->rstack--;
    }
}

int forth_execute_secondary(struct ForthEngine *engine,struct ForthWordHeader *secondary,struct ForthWordHeader *colon_word,
                            struct ForthWordHeader *word_headers,uint32_t word_count,uint8_t *word_bodies)
{
    if (secondary->type==FORTH_SECONDARY_UNDEFINED)
    {
        //Error - secondary has header but hasn't been defined (ie included in other word)
        engine->error=FORTH_ENGINE_ERROR_UNDEFINED;
        engine->error_word=secondary->name;
    }
    else if (((engine->state==FORTH_STATE_INTERPRET)&&(engine->in_bracket==true))&&(colon_word==secondary))
    {
        //Error - can't run word between [ and ] if word is still being defined
        engine->error=FORTH_ENGINE_ERROR_SECONDARY_IN_BRACKET;
        engine->error_word=secondary->name;
    }
    else
    {
        //Prepare engine to run secondary
        forth_engine_pre_exec(engine);
        engine->executing=true;
        engine->address=secondary->address;
        engine->word_headers=word_headers;
        engine->word_bodies=word_bodies;
        engine->word_count=word_count;

        //Mark end of R-stack so interpreter can stop executing when it returns from top-level word
        forth_rstack_push(0,0,FORTH_RSTACK_DONE,engine->word_index,engine);

        //Point to engine->executing flag so interrupt can set to false when ON pressed
        on_key_executing=&engine->executing;

        //Logging
        log_push(LOGGING_FORTH_EXECUTE_SECONDARY,"execute_secondary");

        //Start measuring performance in case needed by Forth word PERF
        wrapper_perf_start(&engine->perf_counter); 

        //Execute primitives
        while(engine->executing)
        {
            //Logging
            log_text("address: %p [",engine->address);
            log_bytes(engine->address,32);
            log_text_raw("]\n");
            log_primitive(engine->address,word_headers); 
            log_text_raw("\n");

            //Jump to primitive function
            (*engine->address)(engine);
            engine->address++;
        }

        //Record run-time from performance counter
        engine->perf_value=wrapper_perf_stop(&engine->perf_counter); 

        //Clear address so interrupt doesn't set when ON pressed - address on engine->executing changes
        on_key_executing=NULL;

        //Stop logging
        log_pop();
    }

    //Flag error if any
    return engine->error;
}

