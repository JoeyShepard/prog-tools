#include <string.h>

#include "compatibility.h"
#include "forth-primitives.h"
#include "text.h"


//Internal primitives - not visible to user
//=========================================

//Push next cell in dictionary to stack
void prim_hidden_push(struct ForthEngine *engine)
{
    //Fetch number which is stored after pointer to current word
    int32_t num=*(int32_t *)(engine->address+1);

    //Increment thread pointer to account for number
    engine->address=(void (**)(struct ForthEngine *engine))(((int32_t *)engine->address)+1);

    //Push number to stack
    *engine->stack=num;
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//Call next cell in dictionary as user-defined word
void prim_hidden_secondary(struct ForthEngine *engine)
{
    //Fetch offset into list of word headers where address of secondary is stored. Offset is after pointer to current word.
    uint32_t offset=*(uint32_t *)(engine->address+1);

    //Increment thread pointer to account for number
    engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);

    //Increase word index so tagged R-stack addresses can be linked to word they belong to
    engine->word_index++;

    //Push current thread pointer address to R-stack
    forth_rstack_push((uintptr_t)(engine->address)-(uintptr_t)(engine->word_bodies),
                        FORTH_RSTACK_RETURN,engine->word_index,engine);

    //TODO: forth_rstack_push may set executing to false. any problem with code below in that case?

    //Set new execution address to address of secondary stored in word header list
    engine->address=*(void (***)(struct ForthEngine *engine))(engine->word_headers+offset);

    //Account for interpreter advancing execution address
    engine->address--;

}

//Done executing primitive
void prim_hidden_done(struct ForthEngine *engine)
{
    //Pop all R-stack values for word including return address
    while (1)
    {
        //Pop R-stack value
        engine->rstack++;

        //No need to check index since FORTH_RSTACK_RETURN only exists once per word
        if (engine->rstack->type==FORTH_RSTACK_RETURN)
        {
            //Return to calling word
            engine->address=(void (**)(struct ForthEngine *engine))(engine->word_bodies+engine->rstack->value);

            //Done searching
            break;
        }
        else if (engine->rstack->type==FORTH_RSTACK_DONE)
        {
            //Returning from top-level word - stop executing
            engine->executing=false;

            //Done searching
            break;
        }
        else
        {
            //Found loop counter or something else - keep searching
        }
    }
}


//Primitives visible to user
//==========================

//STORE
void prim_body_store(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask_32;
    //Write value to address
    *(int32_t*)(engine->data+address)=value;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_store(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//C_STORE
void prim_body_c_store(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Read 32-bit value here so no endian problems
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask;
    //Write value to address
    *(engine->data+address)=value;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_c_store(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//W_STORE
void prim_body_w_store(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Read 32-bit value here so no endian problems
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask_16;
    //Write value to address
    *(int16_t*)(engine->data+address)=value;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_w_store(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//TICK
int prim_immediate_tick(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_TICK;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_tick(struct ForthEngine *engine)
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//PAREN
int prim_immediate_paren(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_PAREN;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_paren(struct ForthEngine *engine)
{
    //Same behavior as immediate
    return prim_immediate_paren(engine);
}

//STAR
void prim_body_star(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1*arg2;
}
int prim_optimize_star(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//STAR_SLASH
void prim_body_star_slash(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t divisor=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    //Calculate
    if (divisor==0) divisor=1;
    int64_t product=(int64_t)arg1*(int64_t)arg2;
    int32_t quotient=product/(int64_t)divisor;
    //Write values to stack
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=quotient;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_star_slash(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//STAR_SLASH_MOD
void prim_body_star_slash_mod(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t divisor=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    //Calculate
    if (divisor==0) divisor=1;
    int64_t product=(int64_t)arg1*(int64_t)arg2;
    int32_t remainder=product%(int64_t)divisor;
    int32_t quotient=product/(int64_t)divisor;
    //Write values to stack
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=remainder;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=quotient;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_star_slash_mod(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//PLUS
void prim_body_plus(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1+arg2;
}
int prim_optimize_plus(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//PLUS_LOOP
void prim_body_plus_loop(struct ForthEngine *engine){}
int prim_immediate_plus_loop(struct ForthEngine *engine){}
int prim_compile_plus_loop(struct ForthEngine *engine){}
int prim_optimize_plus_loop(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//COMMA
void prim_body_comma(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Mask destination address
    engine->data_index&=engine->data_mask_32;
    //Write value
    *(int32_t*)(engine->data+engine->data_index)=*engine->stack;
    //Advance data pointer
    engine->data_index=(engine->data_index+sizeof(int32_t))&engine->data_mask_32;
}
int prim_optimize_comma(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//C_COMMA
void prim_body_c_comma(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Mask destination address
    engine->data_index&=engine->data_mask;
    //Write value
    *(engine->data+engine->data_index)=*engine->stack;
    //Advance data pointer
    engine->data_index=(engine->data_index+sizeof(int8_t))&engine->data_mask;
}
int prim_optimize_c_comma(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//W_COMMA
void prim_body_w_comma(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Mask destination address
    engine->data_index&=engine->data_mask_16;
    //Write value
    *(int16_t*)(engine->data+engine->data_index)=*engine->stack;
    //Advance data pointer
    engine->data_index=(engine->data_index+sizeof(int16_t))&engine->data_mask_16;
}
int prim_optimize_w_comma(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//MINUS
void prim_body_minus(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1-arg2;
}
int prim_optimize_minus(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//DOT
void prim_body_dot(struct ForthEngine *engine)
{
    //Update stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    if (engine->print!=NULL)
    {
        //Output number
        char text_buffer[TEXT_INT32_SIZE];
        text_int32(*engine->stack,text_buffer);
        engine->print(text_buffer);
        //Output space
        engine->print(" ");
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//DOT_QUOTE
void prim_body_dot_quote(struct ForthEngine *engine){}
int prim_immediate_dot_quote(struct ForthEngine *engine){}
int prim_compile_dot_quote(struct ForthEngine *engine){}
int prim_optimize_dot_quote(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//SLASH
void prim_body_slash(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    if (arg2==0) arg2=1;
    *(int32_t*)((engine->stack_base)|lower)=arg1/arg2;
}
int prim_optimize_slash(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//SLASH_MOD
void prim_body_slash_mod(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    //Calculate
    if (arg1==0) arg1=1;
    //Write result
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2/arg1;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2%arg1;
}
int prim_optimize_slash_mod(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//COLON
int prim_immediate_colon(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_COLON;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_colon(struct ForthEngine *engine)
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//SEMICOLON
int prim_immediate_semicolon(struct ForthEngine *engine)
{
    return FORTH_ENGINE_ERROR_COMPILE_ONLY;
}
int prim_compile_semicolon(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_SEMICOLON;
    return FORTH_ENGINE_ERROR_NONE;
}

//LESS_THAN
void prim_body_less_than(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result (note true is 1 in C but -1 in FORTH)
    *(int32_t*)((engine->stack_base)|lower)=-(arg1<arg2);
}
int prim_optimize_less_than(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//EQUALS
void prim_body_equals(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result (note true is 1 in C but -1 in FORTH)
    *(int32_t*)((engine->stack_base)|lower)=-(arg1==arg2);
}
int prim_optimize_equals(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//GREATER_THAN
void prim_body_greater_than(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result (note true is 1 in C but -1 in FORTH)
    *(int32_t*)((engine->stack_base)|lower)=-(arg1>arg2);
}
int prim_optimize_greater_than(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//TO_NUMBER - Note differs from >NUMBER in standard!
//(c-addr1 u1 - s2 c-addr2 u2) - no doubles or scratch space
void prim_body_to_number(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t count=*(uint32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Limit count so it loops through memory at most once
    if (count>=engine->data_size) count=engine->data_size;
    //Loop through characters
    int32_t result=0;
    bool negative=false;
    uint32_t unconverted_count=count;
    for (int32_t i=0;i<count;i++)
    {
        //Mask address
        address&=engine->data_mask; 
        //Fetch character
        char character=*(engine->data+address);
        if ((character=='-')&&(i==0))
        {
            //First character is - so number is negative
            negative=true;
            unconverted_count--;
        }
        else if ((character>='0')&&(character<='9'))
        {
            //Character is valid digit - add to result
            result*=10;
            result+=character-'0';
            unconverted_count--;
        }
        else
        {
            //Non number character - stop looping
            break;
        }
        address++;
    }
    //If number began with - it's negative
    if (negative==true) result*=-1;
    //Write values to stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=address;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=result;
    *(uint32_t*)(engine->stack)=unconverted_count;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//QUESTION_DUPE
void prim_body_question_dupe(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch value to duplicate
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    if (*(int32_t*)((engine->stack_base)|lower)!=0)
    {
        //Value is not zero - duplicate
        *engine->stack=*(int32_t*)((engine->stack_base)|lower);
        //Advance stack pointer
        lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
        engine->stack=(int32_t*)((engine->stack_base)|lower);
    }
}
int prim_optimize_question_dupe(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//FETCH
void prim_body_fetch(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch argument
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask_32;
    //Read from address
    int32_t value=*(int32_t*)(engine->data+address);
    //Write value to stack
    *(int32_t*)((engine->stack_base)|lower)=value;
}
int prim_optimize_fetch(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//C_FETCH
void prim_body_c_fetch(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch argument
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask;
    //Read from address
    uint8_t value=*(engine->data+address);
    //Write value to stack
    *(int32_t*)((engine->stack_base)|lower)=value;
}
int prim_optimize_c_fetch(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//W_FETCH
void prim_body_w_fetch(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch argument
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask_16;
    //Read from address
    uint16_t value=*(uint16_t*)(engine->data+address);
    //Write value to stack
    *(int32_t*)((engine->stack_base)|lower)=value;
}
int prim_optimize_w_fetch(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//QUIT
void prim_body_quit(struct ForthEngine *engine){}
int prim_immediate_quit(struct ForthEngine *engine){}
int prim_compile_quit(struct ForthEngine *engine){}
int prim_optimize_quit(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//ABS
void prim_body_abs(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    if (value<0) *(int32_t*)((engine->stack_base)|lower)=-value;
}
int prim_optimize_abs(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//ACCEPT
void prim_body_accept(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Call input routine if it exists
    if (engine->input!=NULL)
    {
        //Fetch arguments
        lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
        int32_t address=*(int32_t*)((engine->stack_base)|lower);
        int32_t count=*engine->stack;
        //Mask address
        address&=engine->data_mask;
        int32_t bytes_written=engine->input(address,engine->data,count,engine->data_mask);
        //Write result
        *(int32_t*)((engine->stack_base)|lower)=bytes_written;
    }
}

//ALIGN
void prim_body_align(struct ForthEngine *engine)
{
    int32_t remainder=engine->data_index%FORTH_CELL_SIZE;
    if (remainder>0)
    {
        //Address is not aligned - round up
        engine->data_index=(engine->data_index+FORTH_CELL_SIZE-remainder)&engine->data_mask_32;
    }
}
int prim_optimize_align(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//ALIGNED
void prim_body_aligned(struct ForthEngine *engine)
{
    //Fetch address to align
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    int32_t remainder=address%FORTH_CELL_SIZE;
    if (remainder!=0)
    {
        //Address is not aligned - round up
        address+=FORTH_CELL_SIZE-remainder;
    }
    //Write address back even if aligned so always masked
    *(int32_t*)((engine->stack_base)|lower)=(address&engine->data_mask_32);
}
int prim_optimize_aligned(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//ALLOT
void prim_body_allot(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch amount of bytes to allot
    int32_t allot_count=*engine->stack;
    engine->data_index=(engine->data_index+allot_count)&(engine->data_mask);
}

//AND
void prim_body_and(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1&arg2;
}
int prim_optimize_and(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//BEGIN
void prim_body_begin(struct ForthEngine *engine){}
int prim_immediate_begin(struct ForthEngine *engine){}
int prim_compile_begin(struct ForthEngine *engine){}
int prim_optimize_begin(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//B_L
void prim_body_b_l(struct ForthEngine *engine)
{
    //Write value for space character
    *engine->stack=32;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//BOUNDS
void prim_body_bounds(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    //Write values to stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=(arg1+arg2)&engine->data_mask;
}
int prim_optimize_bounds(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//CELLS
void prim_body_cells(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    *(int32_t*)((engine->stack_base)|lower)=value*FORTH_CELL_SIZE;
}

//CHAR
int prim_immediate_char(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_CHAR;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_char(struct ForthEngine *engine)
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//CONSTANT
void prim_body_constant(struct ForthEngine *engine){}
int prim_immediate_constant(struct ForthEngine *engine){}
int prim_compile_constant(struct ForthEngine *engine){}
int prim_optimize_constant(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//C_R
void prim_body_c_r(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
    {
        engine->print("\n");
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//DEPTH
void prim_body_depth(struct ForthEngine *engine)
{
    //Write stack count
    *engine->stack=forth_stack_count(engine);
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//DO
void prim_body_do(struct ForthEngine *engine){}
int prim_immediate_do(struct ForthEngine *engine){}
int prim_compile_do(struct ForthEngine *engine){}
int prim_optimize_do(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//DROP
void prim_body_drop(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_drop(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//DUPE
void prim_body_dupe(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Write duplicated value
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *engine->stack=*(int32_t*)((engine->stack_base)|lower);
    //Advance stack pointer
    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_dupe(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//ELSE
void prim_body_else(struct ForthEngine *engine){}
int prim_immediate_else(struct ForthEngine *engine){}
int prim_compile_else(struct ForthEngine *engine){}
int prim_optimize_else(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//EMIT
void prim_body_emit(struct ForthEngine *engine)
{
    //Update stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    if (engine->print!=NULL)
    {
        //Output character
        char text_buffer[2];
        text_buffer[0]=*engine->stack;
        text_buffer[1]=0;
        engine->print(text_buffer);
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//EXIT
void prim_body_exit(struct ForthEngine *engine){}
int prim_immediate_exit(struct ForthEngine *engine){}
int prim_compile_exit(struct ForthEngine *engine){}
int prim_optimize_exit(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//FILL
void prim_body_fill(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t character=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t count=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    if (count>0)
    {
        //Limit count so it loops through memory at most once
        if (count>=engine->data_size) count=engine->data_size;
        for (int32_t i=0;i<count;i++)
        {
            //Write byte to masked address
            address&=engine->data_mask;
            *(engine->data+address)=character;
            address++;
        }
    }
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_fill(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//FIND
void prim_body_find(struct ForthEngine *engine){}
int prim_immediate_find(struct ForthEngine *engine){}
int prim_compile_find(struct ForthEngine *engine){}
int prim_optimize_find(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//HERE
void prim_body_here(struct ForthEngine *engine)
{
    //Write stack count
    *engine->stack=engine->data_index;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//I
void prim_body_i(struct ForthEngine *engine){}
int prim_immediate_i(struct ForthEngine *engine){}
int prim_compile_i(struct ForthEngine *engine){}
int prim_optimize_i(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//IF
void prim_body_if(struct ForthEngine *engine){}
int prim_immediate_if(struct ForthEngine *engine){}
int prim_compile_if(struct ForthEngine *engine){}
int prim_optimize_if(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//IMMEDIATE
void prim_body_immediate(struct ForthEngine *engine){}
int prim_immediate_immediate(struct ForthEngine *engine){}
int prim_compile_immediate(struct ForthEngine *engine){}
int prim_optimize_immediate(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//INVERT
void prim_body_invert(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    *(int32_t*)((engine->stack_base)|lower)=value^-1;
}
int prim_optimize_invert(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//J
void prim_body_j(struct ForthEngine *engine){}
int prim_immediate_j(struct ForthEngine *engine){}
int prim_compile_j(struct ForthEngine *engine){}
int prim_optimize_j(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//KEY
void prim_body_key(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch flag - true for blocking key input, false for non-blocking
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t flag=*(int32_t*)((engine->stack_base)|lower);
    if (engine->getkey==NULL)
    {
        //No getkey routine exists - return 0
        *(int32_t*)((engine->stack_base)|lower)=0;
    }
    else
    {
        //Fetch key
        bool blocking=!(flag==0);
        int32_t key=engine->getkey(blocking);
        *(int32_t*)((engine->stack_base)|lower)=key;
        //Update modifier output
        if (engine->update_modifiers!=NULL) engine->update_modifiers();
    }
}

//LEAVE
void prim_body_leave(struct ForthEngine *engine){}
int prim_immediate_leave(struct ForthEngine *engine){}
int prim_compile_leave(struct ForthEngine *engine){}
int prim_optimize_leave(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//LITERAL
void prim_body_literal(struct ForthEngine *engine){}
int prim_immediate_literal(struct ForthEngine *engine){}
int prim_compile_literal(struct ForthEngine *engine){}
int prim_optimize_literal(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//LOOP
void prim_body_loop(struct ForthEngine *engine){}
int prim_immediate_loop(struct ForthEngine *engine){}
int prim_compile_loop(struct ForthEngine *engine){}
int prim_optimize_loop(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//L_SHIFT
void prim_body_l_shift(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1<<arg2;
}
int prim_optimize_l_shift(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//MAX
void prim_body_max(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    if (arg2>arg1)
    {
        *(int32_t*)((engine->stack_base)|lower)=arg2;
    }
    else
    {
        //Larger value is already in place - nothing to do
    }
}
int prim_optimize_max(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//MIN
void prim_body_min(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    if (arg2<arg1)
    {
        //Write smaller value to stack
        *(int32_t*)((engine->stack_base)|lower)=arg2;
    }
    else
    {
        //Larger value is already in place - nothing to do
    }
}
int prim_optimize_min(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//MOD
void prim_body_mod(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Prevent divide by zero
    if (arg2==0) arg2=1;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1%arg2;
}
int prim_optimize_mod(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//MOVE
void prim_body_move(struct ForthEngine *engine){}
int prim_immediate_move(struct ForthEngine *engine){}
int prim_compile_move(struct ForthEngine *engine){}
int prim_optimize_move(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//NEGATE
void prim_body_negate(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    *(int32_t*)((engine->stack_base)|lower)=-value;
}
int prim_optimize_negate(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//OR
void prim_body_or(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1|arg2;
}
int prim_optimize_or(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//OVER
void prim_body_over(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Write duplicated value
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *engine->stack=*(int32_t*)((engine->stack_base)|lower);
    //Advance stack pointer
    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_over(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//2OVER
void prim_body_2_over(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+4))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    //Advance stack pointer
    lower=((uintptr_t)(engine->stack-2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Write values to stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg1;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2;
}
int prim_optimize_2_over(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//PAGE
void prim_body_page(struct ForthEngine *engine)
{
    if (engine->clear_console!=NULL)
    {
        //Clear screen
        engine->clear_console();
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//REPEAT
void prim_body_repeat(struct ForthEngine *engine){}
int prim_immediate_repeat(struct ForthEngine *engine){}
int prim_compile_repeat(struct ForthEngine *engine){}
int prim_optimize_repeat(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//ROTE
void prim_body_rote(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t arg3=*(int32_t*)((engine->stack_base)|lower);
    //Write values to stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg3;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg1;
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2;
}
int prim_optimize_rote(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//MINUS_ROTE
void prim_body_minus_rote(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t arg3=*(int32_t*)((engine->stack_base)|lower);
    //Write values to stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg3;
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg1;
}
int prim_immediate_minus_rote(struct ForthEngine *engine){}
int prim_compile_minus_rote(struct ForthEngine *engine){}
int prim_optimize_minus_rote(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//R_SHIFT
void prim_body_r_shift(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1>>arg2;
}
int prim_optimize_r_shift(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//S_QUOTE
void prim_body_s_quote(struct ForthEngine *engine){}
int prim_immediate_s_quote(struct ForthEngine *engine){}
int prim_compile_s_quote(struct ForthEngine *engine){}
int prim_optimize_s_quote(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//SPACE
void prim_body_space(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
    {
        engine->print(" ");
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//SPACES
void prim_body_spaces(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch count
    int32_t space_count=*engine->stack;
    if ((space_count>0)&&(engine->print!=NULL))
    {
        if (space_count>engine->max_spaces) 
        {
            //Limit spaces to print to max set when engine initialized
            space_count=engine->max_spaces;
        }
        for (int32_t i=0;i<space_count;i++)
        {
            engine->print(" ");
        }
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//STATE
void prim_body_state(struct ForthEngine *engine){}
int prim_immediate_state(struct ForthEngine *engine){}
int prim_compile_state(struct ForthEngine *engine){}
int prim_optimize_state(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//SWAP
void prim_body_swap(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    //Write values to stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg1;
}
int prim_optimize_swap(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//ROTE
void prim_body_2_swap(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t arg3=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+4))&FORTH_STACK_MASK;
    int32_t arg4=*(int32_t*)((engine->stack_base)|lower);
    //Write values to stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg3;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg4;
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg1;
    lower=((uintptr_t)(engine->stack+4))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2;
}
int prim_optimize_2_swap(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//THEN
void prim_body_then(struct ForthEngine *engine){}
int prim_immediate_then(struct ForthEngine *engine){}
int prim_compile_then(struct ForthEngine *engine){}
int prim_optimize_then(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//TYPE
void prim_body_type(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t count=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Print characters if print function exists
    if (engine->print!=NULL)
    {
        //Limit count so it loops through memory at most once
        if (count>=engine->data_size) count=engine->data_size;
        for (int32_t i=0;i<count;i++)
        {
            //Mask address
            address&=engine->data_mask;
            //Print out character
            char text_buffer[2]={*(int32_t*)(engine->data+address),0};
            engine->print(text_buffer);
            //Next byte
            address++;
        }
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//U_LESS_THAN
void prim_body_u_less_than(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    uint32_t arg2=*engine->stack;
    //Write result (note true is 1 in C but -1 in FORTH)
    *(int32_t*)((engine->stack_base)|lower)=-(arg1<arg2);
}
int prim_optimize_u_less_than(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//U_GREATER_THAN
void prim_body_u_greater_than(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    uint32_t arg2=*engine->stack;
    //Write result (note true is 1 in C but -1 in FORTH)
    *(int32_t*)((engine->stack_base)|lower)=-(arg1>arg2);
}
int prim_optimize_u_greater_than(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//UNTIL
void prim_body_until(struct ForthEngine *engine){}
int prim_immediate_until(struct ForthEngine *engine){}
int prim_compile_until(struct ForthEngine *engine){}
int prim_optimize_until(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//VARIABLE
void prim_body_variable(struct ForthEngine *engine){}
int prim_immediate_variable(struct ForthEngine *engine){}
int prim_compile_variable(struct ForthEngine *engine){}
int prim_optimize_variable(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//WHILE
void prim_body_while(struct ForthEngine *engine){}
int prim_immediate_while(struct ForthEngine *engine){}
int prim_compile_while(struct ForthEngine *engine){}
int prim_optimize_while(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//X_OR
void prim_body_x_or(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result
    *(int32_t*)((engine->stack_base)|lower)=arg1^arg2;
}
int prim_optimize_x_or(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//LEFT_BRACKET
void prim_body_left_bracket(struct ForthEngine *engine){}
int prim_immediate_left_bracket(struct ForthEngine *engine){}
int prim_compile_left_bracket(struct ForthEngine *engine){}
int prim_optimize_left_bracket(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//RIGHT_BRACKET
void prim_body_right_bracket(struct ForthEngine *engine){}
int prim_immediate_right_bracket(struct ForthEngine *engine){}
int prim_compile_right_bracket(struct ForthEngine *engine){}
int prim_optimize_right_bracket(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//BRACKET_TICK
void prim_body_bracket_tick(struct ForthEngine *engine){}
int prim_immediate_bracket_tick(struct ForthEngine *engine){}
int prim_compile_bracket_tick(struct ForthEngine *engine){}
int prim_optimize_bracket_tick(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//BRACKET_CHAR
void prim_body_bracket_char(struct ForthEngine *engine){}
int prim_immediate_bracket_char(struct ForthEngine *engine){}
int prim_compile_bracket_char(struct ForthEngine *engine){}
int prim_optimize_bracket_char(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//DOT_R
void prim_body_dot_r(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t spaces=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);

    if (engine->print!=NULL)
    {
        //Convert number to text
        char text_buffer[TEXT_INT32_SIZE];
        text_int32(value,text_buffer);
        //Output leading spaces
        if (strlen(text_buffer)>spaces) spaces=0;
        else spaces-=strlen(text_buffer);
        if (spaces>FORTH_MAX_SPACES) spaces=FORTH_MAX_SPACES;
        for (int32_t i=0;i<spaces;i++)
            engine->print(" ");
        //Output number
        engine->print(text_buffer);
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//NOT_EQUALS
void prim_body_not_equals(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    int32_t arg2=*engine->stack;
    //Write result (note true is 1 in C but -1 in FORTH)
    *(int32_t*)((engine->stack_base)|lower)=-(arg1!=arg2);
}
int prim_optimize_not_equals(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//AGAIN
void prim_body_again(struct ForthEngine *engine){}
int prim_immediate_again(struct ForthEngine *engine){}
int prim_compile_again(struct ForthEngine *engine){}
int prim_optimize_again(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//CASE
void prim_body_case(struct ForthEngine *engine){}
int prim_immediate_case(struct ForthEngine *engine){}
int prim_compile_case(struct ForthEngine *engine){}
int prim_optimize_case(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//FALSE
void prim_body_false(struct ForthEngine *engine)
{
    //Write value for space character
    *engine->stack=FORTH_FALSE;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_false(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//NIP
void prim_body_nip(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Copy value on stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=*engine->stack;
}
int prim_optimize_nip(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//PICK
void prim_body_pick(struct ForthEngine *engine){}
int prim_immediate_pick(struct ForthEngine *engine){}
int prim_compile_pick(struct ForthEngine *engine){}
int prim_optimize_pick(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//ROLL
void prim_body_roll(struct ForthEngine *engine){}
int prim_immediate_roll(struct ForthEngine *engine){}
int prim_compile_roll(struct ForthEngine *engine){}
int prim_optimize_roll(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//S_BACKSLASH_QUOTE
void prim_body_s_backslash_quote(struct ForthEngine *engine){}
int prim_immediate_s_backslash_quote(struct ForthEngine *engine){}
int prim_compile_s_backslash_quote(struct ForthEngine *engine){}
int prim_optimize_s_backslash_quote(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//TRUE
void prim_body_true(struct ForthEngine *engine)
{
    //Write value for space character
    *engine->stack=FORTH_TRUE;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_true(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//TUCK
void prim_body_tuck(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t arg1=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t arg2=*(int32_t*)((engine->stack_base)|lower);
    //Write values to stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg2;
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    *(int32_t*)((engine->stack_base)|lower)=arg1;
    *engine->stack=arg1;
    //Advance stack pointer
    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_tuck(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//UNUSED
void prim_body_unused(struct ForthEngine *engine){}
int prim_immediate_unused(struct ForthEngine *engine){}
int prim_compile_unused(struct ForthEngine *engine){}
int prim_optimize_unused(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//WITHIN
void prim_body_within(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t max=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t min=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    //Write value to stack
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    if ((value>=min)&&(value<=max)) *(int32_t*)((engine->stack_base)|lower)=FORTH_TRUE;
    else *(int32_t*)((engine->stack_base)|lower)=FORTH_FALSE;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_within(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//DOT_S
void prim_body_dot_s(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
    {
        char text_buffer[TEXT_INT32_SIZE];
        int stack_count=forth_stack_count(engine);
        engine->print("<");
        text_int32(stack_count,text_buffer);
        engine->print(text_buffer);
        engine->print("> ");
        int32_t *stack=engine->stack+stack_count;
        for (int32_t i=0;i<stack_count;i++)
        {
            text_int32(*stack,text_buffer);
            engine->print(text_buffer);
            engine->print(" ");
            stack--;
        }
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//QUESTION
void prim_body_question(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    if (engine->print!=NULL)
    {
        //Read and mask address
        int32_t address=(*(engine->stack))&engine->data_mask_32;
        //Read from address
        int32_t value=*(int32_t*)(engine->data+address);
        //Output value
        char text_buffer[TEXT_INT32_SIZE];
        text_int32(value,text_buffer);
        engine->print(text_buffer);
        //Output space
        engine->print(" ");
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//DUMP
void prim_body_dump(struct ForthEngine *engine)
{
    uintptr_t lower;
    if (engine->print!=NULL)
    {
        //Fetch arguments
        lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
        int32_t count=*(int32_t*)((engine->stack_base)|lower);
        lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
        int32_t address=*(int32_t*)((engine->stack_base)|lower);
        //Fetch and print bytes
        bool newline=true;
        char byte_display[FORTH_DUMP_BYTES+1];
        int byte_index=0;
        int line_count=0;
        for (int32_t i=0;i<count;i++)
        {
            //Mask address
            address&=engine->data_mask;
            if (newline)
            {
                //Print address
                engine->print("\n");
                char address_buffer[7]; //Six hex digits plus null terminator
                text_hex32(address,address_buffer,6);
                engine->print(address_buffer);
                engine->print(":");
            }
            //Print byte
            uint8_t byte=*(engine->data+address);
            char text_buffer[3];    //Two hex digits per byte plus null terminator
            text_hex32(byte,text_buffer,2);
            engine->print(text_buffer);
            //Print characters for bytes
            byte_display[byte_index]=byte;
            byte_index++;
            if ((byte_index==FORTH_DUMP_BYTES)||(i==count-1))
            {
                //End of line reached or out of bytes
                byte_display[byte_index]=0;
                for (int32_t j=0;j<byte_index;j++)
                {
                    //Replace unprintable characters with .
                    if ((byte_display[j]<CHAR_PRINTABLE_MIN)||(byte_display[j]>CHAR_PRINTABLE_MAX))
                    {
                        byte_display[j]='.';
                    }
                }
                //Print spaces if full line of bytes not printed
                for (int32_t j=0;j<FORTH_DUMP_BYTES-byte_index;j++)
                {
                    engine->print("   ");
                }
                //Print characters
                engine->print("  ");
                engine->print(byte_display);
                //Limit number of lines printed
                line_count++;
                if ((line_count==FORTH_DUMP_MAX_LINES)&&(i!=count-1))
                {
                    engine->print("\nOutput truncated");
                    break;
                }
                //Reset for next line
                byte_index=0;
                newline=true;
            }
            else
            {
                //Byte limit for line not reached - print space between bytes
                engine->print(" ");
                newline=false;
            }

            address++;
        }
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//SEE
void prim_body_see(struct ForthEngine *engine){}
int prim_immediate_see(struct ForthEngine *engine){}
int prim_compile_see(struct ForthEngine *engine){}
int prim_optimize_see(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//WORDS
int prim_immediate_words(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_WORDS;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_words(struct ForthEngine *engine)
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//BYE
void prim_body_bye(struct ForthEngine *engine)
{
    engine->exit_program=true;
    engine->executing=false;
}

//COMPARE
void prim_body_compare(struct ForthEngine *engine){}
int prim_immediate_compare(struct ForthEngine *engine){}
int prim_compile_compare(struct ForthEngine *engine){}
int prim_optimize_compare(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//RESET
int prim_immediate_reset(struct ForthEngine *engine)
{
    forth_reset_engine_stacks(engine);
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_reset(struct ForthEngine *engine){}

//WALIGN
void prim_body_walign(struct ForthEngine *engine)
{
    //Round up to even address
    engine->data_index=(engine->data_index+(engine->data_index&1))&engine->data_mask_16;
}
int prim_optimize_walign(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//WALIGNED
void prim_body_waligned(struct ForthEngine *engine)
{
    //Fetch address to align
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Round up to even address
    address+=address&1;
    //Write address back even if aligned so always masked
    *(int32_t*)((engine->stack_base)|lower)=(address&engine->data_mask_16);
}
int prim_optimize_waligned(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//PRINTABLE
void prim_body_printable(struct ForthEngine *engine)
{
    //Fetch key to look up
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t key=*(int32_t*)((engine->stack_base)|lower);

    if (engine->printable!=NULL)
    {
        //Return printable character for key
        *(int32_t*)((engine->stack_base)|lower)=engine->printable(key);
    }
    else
    {
        //No printable function - return 0
        *(int32_t*)((engine->stack_base)|lower)=0;
    }
}

//ERASE
void prim_body_erase(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t count=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    if (count>0)
    {
        //Limit count so it loops through memory at most once
        if (count>=engine->data_size) count=engine->data_size;
        for (int32_t i=0;i<count;i++)
        {
            //Write byte to masked address
            address&=engine->data_mask;
            *(engine->data+address)=0;
            address++;
        }
    }
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_erase(struct ForthEngine *engine)
{
    engine=engine;
    return 0;
}

//Globals
//=======
const struct ForthPrimitive forth_primitives[]=
{
    {"!",1,NULL,NULL,&prim_body_store,&prim_optimize_store},
    {"C!",2,NULL,NULL,&prim_body_c_store,&prim_optimize_c_store},
    {"W!",2,NULL,NULL,&prim_body_w_store,&prim_optimize_w_store},
    {"'",1,&prim_immediate_tick,&prim_compile_tick,NULL,NULL},
    {"(",1,&prim_immediate_paren,&prim_compile_paren,NULL,NULL},
    {"*",1,NULL,NULL,&prim_body_star,&prim_optimize_star},
    {"*/",2,NULL,NULL,&prim_body_star_slash,&prim_optimize_star_slash},
    {"*/MOD",5,NULL,NULL,&prim_body_star_slash_mod,&prim_optimize_star_slash_mod},
    {"+",1,NULL,NULL,&prim_body_plus,&prim_optimize_plus},
    //{"+LOOP",5,&prim_immediate_plus_loop,&prim_compile_plus_loop,&prim_body_plus_loop,&prim_optimize_plus_loop},
    {",",1,NULL,NULL,&prim_body_comma,&prim_optimize_comma},
    {"C,",2,NULL,NULL,&prim_body_c_comma,&prim_optimize_c_comma},
    {"W,",2,NULL,NULL,&prim_body_w_comma,&prim_optimize_w_comma},
    {"-",1,NULL,NULL,&prim_body_minus,&prim_optimize_minus},
    {".",1,NULL,NULL,&prim_body_dot,NULL},
    //{".\"",2,&prim_immediate_dot_quote,&prim_compile_dot_quote,&prim_body_dot_quote,&prim_optimize_dot_quote},
    {"/",1,NULL,NULL,&prim_body_slash,&prim_optimize_slash},
    {"/MOD",4,NULL,NULL,&prim_body_slash_mod,&prim_optimize_slash_mod},
    {":",1,&prim_immediate_colon,&prim_compile_colon,NULL,NULL},
    {";",1,&prim_immediate_semicolon,&prim_compile_semicolon,NULL,NULL},
    {"<",1,NULL,NULL,&prim_body_less_than,&prim_optimize_less_than},
    {"=",1,NULL,NULL,&prim_body_equals,&prim_optimize_equals},
    {">",1,NULL,NULL,&prim_body_greater_than,&prim_optimize_greater_than},
    {">NUMBER",7,NULL,NULL,&prim_body_to_number,NULL},
    //Shortcut for >NUMBER
    {">NUM",4,NULL,NULL,&prim_body_to_number,NULL},
    {"?DUP",4,NULL,NULL,&prim_body_question_dupe,&prim_optimize_question_dupe},
    {"@",1,NULL,NULL,&prim_body_fetch,&prim_optimize_fetch},
    {"C@",2,NULL,NULL,&prim_body_c_fetch,&prim_optimize_c_fetch},
    {"W@",2,NULL,NULL,&prim_body_w_fetch,&prim_optimize_w_fetch},
    //{"QUIT",4,&prim_immediate_quit,&prim_compile_quit,&prim_body_quit,&prim_optimize_quit},
    {"ABS",3,NULL,NULL,&prim_body_abs,&prim_optimize_abs},
    {"ACCEPT",6,NULL,NULL,&prim_body_accept,NULL},
    {"ALIGN",5,NULL,NULL,&prim_body_align,&prim_optimize_align},
    {"ALIGNED",7,NULL,NULL,&prim_body_aligned,&prim_optimize_aligned},
    {"ALLOT",5,NULL,NULL,&prim_body_allot,NULL},
    {"AND",3,NULL,NULL,&prim_body_and,&prim_optimize_and},
    //{"BEGIN",5,&prim_immediate_begin,&prim_compile_begin,&prim_body_begin,&prim_optimize_begin},
    {"BL",2,NULL,NULL,&prim_body_b_l,NULL},
    {"BOUNDS",6,NULL,NULL,&prim_body_bounds,&prim_optimize_bounds},
    {"CELLS",5,NULL,NULL,&prim_body_cells,NULL},
    {"CHAR",4,&prim_immediate_char,&prim_compile_char,NULL,NULL},
    //{"CONSTANT",8,&prim_immediate_constant,&prim_compile_constant,&prim_body_constant,&prim_optimize_constant},
    //Shortcut for CONSTANT
    //{"CONST",5,&prim_immediate_const,&prim_compile_const,&prim_body_const,&prim_optimize_const},
    {"CR",2,NULL,NULL,&prim_body_c_r,NULL},
    {"DEPTH",5,NULL,NULL,&prim_body_depth,NULL},
    //{"DO",2,&prim_immediate_do,&prim_compile_do,&prim_body_do,&prim_optimize_do},
    {"DROP",4,NULL,NULL,&prim_body_drop,&prim_optimize_drop},
    {"DUP",3,NULL,NULL,&prim_body_dupe,&prim_optimize_dupe},
    //{"ELSE",4,&prim_immediate_else,&prim_compile_else,&prim_body_else,&prim_optimize_else},
    {"EMIT",4,NULL,NULL,&prim_body_emit,NULL},
    {"ERASE",5,NULL,NULL,&prim_body_erase,&prim_optimize_erase},
    //{"EXIT",4,&prim_immediate_exit,&prim_compile_exit,&prim_body_exit,&prim_optimize_exit},
    {"FILL",4,NULL,NULL,&prim_body_fill,&prim_optimize_fill},
    {"HERE",4,NULL,NULL,&prim_body_here,NULL},
    //{"I",1,&prim_immediate_i,&prim_compile_i,&prim_body_i,&prim_optimize_i},
    //{"IF",2,&prim_immediate_if,&prim_compile_if,&prim_body_if,&prim_optimize_if},
    //{"IMMEDIATE",9,&prim_immediate_immediate,&prim_compile_immediate,&prim_body_immediate,&prim_optimize_immediate},
    //Shortcut for IMMEDIATE
    //{"IMMED",5,&prim_immediate_immediate,&prim_compile_immediate,&prim_body_immediate,&prim_optimize_immediate},
    {"INVERT",6,NULL,NULL,&prim_body_invert,&prim_optimize_invert},
    //{"J",1,&prim_immediate_j,&prim_compile_j,&prim_body_j,&prim_optimize_j},
    {"KEY",3,NULL,NULL,&prim_body_key,NULL},
    //{"LEAVE",5,&prim_immediate_leave,&prim_compile_leave,&prim_body_leave,&prim_optimize_leave},
    //{"LITERAL",7,&prim_immediate_literal,&prim_compile_literal,&prim_body_literal,&prim_optimize_literal},
    //Shortcut for LIT
    //{"LIT",3,&prim_immediate_literal,&prim_compile_literal,&prim_body_literal,&prim_optimize_literal},
    //{"LOOP",4,&prim_immediate_loop,&prim_compile_loop,&prim_body_loop,&prim_optimize_loop},
    {"LSHIFT",6,NULL,NULL,&prim_body_l_shift,&prim_optimize_l_shift},
    {"MAX",3,NULL,NULL,&prim_body_max,&prim_optimize_max},
    {"MIN",3,NULL,NULL,&prim_body_min,&prim_optimize_min},
    {"MOD",3,NULL,NULL,&prim_body_mod,&prim_optimize_mod},
    //{"MOVE",4,&prim_immediate_move,&prim_compile_move,&prim_body_move,&prim_optimize_move},
    {"NEGATE",6,NULL,NULL,&prim_body_negate,&prim_optimize_negate},
    {"OR",2,NULL,NULL,&prim_body_or,&prim_optimize_or},
    {"OVER",4,NULL,NULL,&prim_body_over,&prim_optimize_over},
    {"2OVER",5,NULL,NULL,&prim_body_2_over,&prim_optimize_2_over},
    {"PAGE",4,NULL,NULL,&prim_body_page,NULL},
    //{"REPEAT",6,&prim_immediate_repeat,&prim_compile_repeat,&prim_body_repeat,&prim_optimize_repeat},
    {"ROT",3,NULL,NULL,&prim_body_rote,&prim_optimize_rote},
    {"-ROT",4,NULL,NULL,&prim_body_minus_rote,&prim_optimize_minus_rote},
    {"RSHIFT",6,NULL,NULL,&prim_body_r_shift,&prim_optimize_r_shift},
    //{"S\"",2,&prim_immediate_s_quote,&prim_compile_s_quote,&prim_body_s_quote,&prim_optimize_s_quote},
    {"SPACE",5,NULL,NULL,&prim_body_space,NULL},
    {"SPACES",6,NULL,NULL,&prim_body_spaces,NULL},
    //{"STATE",5,&prim_immediate_state,&prim_compile_state,&prim_body_state,&prim_optimize_state},
    {"SWAP",4,NULL,NULL,&prim_body_swap,&prim_optimize_swap},
    {"2SWAP",5,NULL,NULL,&prim_body_2_swap,&prim_optimize_2_swap},
    //{"THEN",4,&prim_immediate_then,&prim_compile_then,&prim_body_then,&prim_optimize_then},
    {"TYPE",4,NULL,NULL,&prim_body_type,NULL},
    {"U<",2,NULL,NULL,&prim_body_u_less_than,&prim_optimize_u_less_than},
    {"U>",2,NULL,NULL,&prim_body_u_greater_than,&prim_optimize_u_greater_than},
    //{"UNTIL",5,&prim_immediate_until,&prim_compile_until,&prim_body_until,&prim_optimize_until},
    //{"VARIABLE",8,&prim_immediate_variable,&prim_compile_variable,&prim_body_variable,&prim_optimize_variable},
    //Shortcut for VARIABLE
    //{"VAR",3,&prim_immediate_variable,&prim_compile_variable,&prim_body_variable,&prim_optimize_variable},
    //{"WHILE",5,&prim_immediate_while,&prim_compile_while,&prim_body_while,&prim_optimize_while},
    {"XOR",3,NULL,NULL,&prim_body_x_or,&prim_optimize_x_or},
    //{"[",1,&prim_immediate_left_bracket,&prim_compile_left_bracket,&prim_body_left_bracket,&prim_optimize_left_bracket},
    //{"]",1,&prim_immediate_right_bracket,&prim_compile_right_bracket,&prim_body_right_bracket,&prim_optimize_right_bracket},
    //{"[']",3,&prim_immediate_bracket_tick,&prim_compile_bracket_tick,&prim_body_bracket_tick,&prim_optimize_bracket_tick},
    //{"[CHAR]",6,&prim_immediate_bracket_char,&prim_compile_bracket_char,&prim_body_bracket_char,&prim_optimize_bracket_char},
    {".R",2,NULL,NULL,&prim_body_dot_r,NULL},
    {"<>",2,NULL,NULL,&prim_body_not_equals,&prim_optimize_not_equals},
    //{"AGAIN",5,&prim_immediate_again,&prim_compile_again,&prim_body_again,&prim_optimize_again},
    //{"CASE",4,&prim_immediate_case,&prim_compile_case,&prim_body_case,&prim_optimize_case},
    //{"ENDCASE",7,&prim_immediate_endcase,&prim_compile_endcase,&prim_body_endcase,&prim_optimize_endcase},
    //{"OF",2,&prim_immediate_of,&prim_compile_of,&prim_body_of,&prim_optimize_of},
    //{"ENDOF",5,&prim_immediate_endof,&prim_compile_endof,&prim_body_endof,&prim_optimize_endof},
    {"FALSE",5,NULL,NULL,&prim_body_false,&prim_optimize_false},
    {"NIP",3,NULL,NULL,&prim_body_nip,&prim_optimize_nip},
    //{"PICK",4,&prim_immediate_pick,&prim_compile_pick,&prim_body_pick,&prim_optimize_pick},
    //{"ROLL",4,&prim_immediate_roll,&prim_compile_roll,&prim_body_roll,&prim_optimize_roll},
    //{"S\"",3,&prim_immediate_s_backslash_quote,&prim_compile_s_backslash_quote,&prim_body_s_backslash_quote,&prim_optimize_s_backslash_quote},
    {"TRUE",4,NULL,NULL,&prim_body_true,&prim_optimize_true},
    {"TUCK",4,NULL,NULL,&prim_body_tuck,&prim_optimize_tuck},
    //{"UNUSED",6,&prim_immediate_unused,&prim_compile_unused,&prim_body_unused,&prim_optimize_unused},
    {"WITHIN",6,NULL,NULL,&prim_body_within,&prim_optimize_within},
    {".S",2,NULL,NULL,&prim_body_dot_s,NULL},
    {"?",1,NULL,NULL,&prim_body_question,NULL},
    {"DUMP",4,NULL,NULL,&prim_body_dump,NULL},
    //{"SEE",3,&prim_immediate_see,&prim_compile_see,&prim_body_see,&prim_optimize_see},
    {"WORDS",5,&prim_immediate_words,&prim_compile_words,NULL,NULL},
    {"BYE",3,NULL,NULL,&prim_body_bye,NULL},
    //{"COMPARE",7,&prim_immediate_compare,&prim_compile_compare,&prim_body_compare,&prim_optimize_compare},

    //digit?

    //Words from here are not standard forth
    {"RESET",5,&prim_immediate_reset,&prim_compile_reset,NULL,NULL},
    {"WALIGN",6,NULL,NULL,&prim_body_walign,&prim_optimize_walign},
    {"WALIGNED",8,NULL,NULL,&prim_body_waligned,&prim_optimize_waligned},
    {"PRINTABLE",9,NULL,NULL,&prim_body_printable,NULL},

    //help
    //output number to memory (opposite of >number. number> ? >text ?)
    //output hex to memory (>hex ?)
    //. for unsigned (u. and u.r?) and hex since no BASE
    //adjust size of data area
    //may need to add combined primitives back in depending on optimizer (0= 1+ etc)

    //May add but not sure yet
    //cleave ??
    //search ??
    //wordsize
    //disasm - just see? edit?
};

//Can't determine length of array primitives in other files, so calculate here
const int forth_primitives_len=(int)(ARRAY_SIZE(forth_primitives));
