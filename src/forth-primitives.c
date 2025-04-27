#include <string.h>

#include "compatibility.h"
#include "forth-primitives.h"
#include "text.h"


//Primitives
//==========

//STORE
void prim_body_store(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t address=*(uint32_t*)((engine->stack_base)|lower);
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
int prim_optimize_store(struct ForthEngine *engine){}

//C_STORE
void prim_body_c_store(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t address=*(uint32_t*)((engine->stack_base)|lower);
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
int prim_optimize_c_store(struct ForthEngine *engine){}

//W_STORE
void prim_body_w_store(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t address=*(uint32_t*)((engine->stack_base)|lower);
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
int prim_optimize_w_store(struct ForthEngine *engine){}

//TICK
void prim_body_tick(struct ForthEngine *engine){}
int prim_immediate_tick(struct ForthEngine *engine){}
int prim_compile_tick(struct ForthEngine *engine){}
int prim_optimize_tick(struct ForthEngine *engine){}

//PAREN
void prim_body_paren(struct ForthEngine *engine){}
int prim_immediate_paren(struct ForthEngine *engine){}
int prim_compile_paren(struct ForthEngine *engine){}
int prim_optimize_paren(struct ForthEngine *engine){}

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
int prim_optimize_star(struct ForthEngine *engine){}

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
int prim_optimize_star_slash(struct ForthEngine *engine){}

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
int prim_optimize_star_slash_mod(struct ForthEngine *engine){}

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
int prim_optimize_plus(struct ForthEngine *engine){}

//PLUS_LOOP
void prim_body_plus_loop(struct ForthEngine *engine){}
int prim_immediate_plus_loop(struct ForthEngine *engine){}
int prim_compile_plus_loop(struct ForthEngine *engine){}
int prim_optimize_plus_loop(struct ForthEngine *engine){}

//COMMA
void prim_body_comma(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Mask destination address
    engine->data_ptr&=engine->data_mask_32;
    //Write value
    *(int32_t*)(engine->data+engine->data_ptr)=*engine->stack;
    //Advance data pointer
    engine->data_ptr=(engine->data_ptr+sizeof(int32_t))&engine->data_mask_32;
}
int prim_optimize_comma(struct ForthEngine *engine){}

//C_COMMA
void prim_body_c_comma(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Mask destination address
    engine->data_ptr&=engine->data_mask;
    //Write value
    *(engine->data+engine->data_ptr)=*engine->stack;
    //Advance data pointer
    engine->data_ptr=(engine->data_ptr+sizeof(int8_t))&engine->data_mask;
}
int prim_optimize_c_comma(struct ForthEngine *engine){}

//W_COMMA
void prim_body_w_comma(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Mask destination address
    engine->data_ptr&=engine->data_mask_16;
    //Write value
    *(int16_t*)(engine->data+engine->data_ptr)=*engine->stack;
    //Advance data pointer
    engine->data_ptr=(engine->data_ptr+sizeof(int16_t))&engine->data_mask_16;
}
int prim_optimize_w_comma(struct ForthEngine *engine){}

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
int prim_optimize_minus(struct ForthEngine *engine){}

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
    }
}

//DOT_QUOTE
void prim_body_dot_quote(struct ForthEngine *engine){}
int prim_immediate_dot_quote(struct ForthEngine *engine){}
int prim_compile_dot_quote(struct ForthEngine *engine){}
int prim_optimize_dot_quote(struct ForthEngine *engine){}

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
int prim_optimize_slash(struct ForthEngine *engine){}

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
int prim_optimize_slash_mod(struct ForthEngine *engine){}

//COLON
void prim_body_colon(struct ForthEngine *engine){}
int prim_immediate_colon(struct ForthEngine *engine){}
int prim_compile_colon(struct ForthEngine *engine){}
int prim_optimize_colon(struct ForthEngine *engine){}

//SEMICOLON
void prim_body_semicolon(struct ForthEngine *engine){}
int prim_immediate_semicolon(struct ForthEngine *engine){}
int prim_compile_semicolon(struct ForthEngine *engine){}
int prim_optimize_semicolon(struct ForthEngine *engine){}

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
int prim_optimize_less_than(struct ForthEngine *engine){}

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
int prim_optimize_equals(struct ForthEngine *engine){}

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
int prim_optimize_greater_than(struct ForthEngine *engine){}

//TO_NUMBER
void prim_body_to_number(struct ForthEngine *engine){}
int prim_immediate_to_number(struct ForthEngine *engine){}
int prim_compile_to_number(struct ForthEngine *engine){}
int prim_optimize_to_number(struct ForthEngine *engine){}

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
int prim_optimize_question_dupe(struct ForthEngine *engine){}

//FETCH
void prim_body_fetch(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch argument
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t address=*(uint32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask_32;
    //Read from address
    int32_t value=*(int32_t*)(engine->data+address);
    //Write value to stack
    *(uint32_t*)((engine->stack_base)|lower)=value;
}
int prim_optimize_fetch(struct ForthEngine *engine){}

//C_FETCH
void prim_body_c_fetch(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch argument
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t address=*(uint32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask;
    //Read from address
    uint8_t value=*(engine->data+address);
    //Write value to stack
    *(uint32_t*)((engine->stack_base)|lower)=value;
}
int prim_optimize_c_fetch(struct ForthEngine *engine){}

//W_FETCH
void prim_body_w_fetch(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch argument
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t address=*(uint32_t*)((engine->stack_base)|lower);
    //Mask address
    address&=engine->data_mask_16;
    //Read from address
    uint16_t value=*(uint16_t*)(engine->data+address);
    //Write value to stack
    *(uint32_t*)((engine->stack_base)|lower)=value;
}
int prim_optimize_w_fetch(struct ForthEngine *engine){}

//QUIT
void prim_body_quit(struct ForthEngine *engine){}
int prim_immediate_quit(struct ForthEngine *engine){}
int prim_compile_quit(struct ForthEngine *engine){}
int prim_optimize_quit(struct ForthEngine *engine){}

//ABS
void prim_body_abs(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    if (value<0) *(int32_t*)((engine->stack_base)|lower)=-value;
}
int prim_optimize_abs(struct ForthEngine *engine){}

//ACCEPT
void prim_body_accept(struct ForthEngine *engine){}
int prim_immediate_accept(struct ForthEngine *engine){}
int prim_compile_accept(struct ForthEngine *engine){}
int prim_optimize_accept(struct ForthEngine *engine){}

//ALIGN
void prim_body_align(struct ForthEngine *engine){}
int prim_immediate_align(struct ForthEngine *engine){}
int prim_compile_align(struct ForthEngine *engine){}
int prim_optimize_align(struct ForthEngine *engine){}

//ALIGNED
void prim_body_aligned(struct ForthEngine *engine){}
int prim_immediate_aligned(struct ForthEngine *engine){}
int prim_compile_aligned(struct ForthEngine *engine){}
int prim_optimize_aligned(struct ForthEngine *engine){}

//ALLOT
void prim_body_allot(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch amount of bytes to allot
    int32_t allot_count=*engine->stack;
    engine->data_ptr=(engine->data_ptr+allot_count)&(engine->data_mask);
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
int prim_optimize_and(struct ForthEngine *engine){}

//BASE
void prim_body_base(struct ForthEngine *engine){}
int prim_immediate_base(struct ForthEngine *engine){}
int prim_compile_base(struct ForthEngine *engine){}
int prim_optimize_base(struct ForthEngine *engine){}

//BEGIN
void prim_body_begin(struct ForthEngine *engine){}
int prim_immediate_begin(struct ForthEngine *engine){}
int prim_compile_begin(struct ForthEngine *engine){}
int prim_optimize_begin(struct ForthEngine *engine){}

//B_L
void prim_body_b_l(struct ForthEngine *engine)
{
    //Write value for space character
    *engine->stack=32;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//CELLS
void prim_body_cells(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    *(int32_t*)((engine->stack_base)|lower)=value*FORTH_CELL_SIZE;
}

//CHAR
void prim_body_char(struct ForthEngine *engine){}
int prim_immediate_char(struct ForthEngine *engine){}
int prim_compile_char(struct ForthEngine *engine){}
int prim_optimize_char(struct ForthEngine *engine){}

//CONSTANT
void prim_body_constant(struct ForthEngine *engine){}
int prim_immediate_constant(struct ForthEngine *engine){}
int prim_compile_constant(struct ForthEngine *engine){}
int prim_optimize_constant(struct ForthEngine *engine){}

//C_R
void prim_body_c_r(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
        engine->print("\n");
}

//DECIMAL
void prim_body_decimal(struct ForthEngine *engine){}
int prim_immediate_decimal(struct ForthEngine *engine){}
int prim_compile_decimal(struct ForthEngine *engine){}
int prim_optimize_decimal(struct ForthEngine *engine){}

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
int prim_optimize_do(struct ForthEngine *engine){}

//DROP
void prim_body_drop(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_drop(struct ForthEngine *engine)
{
    return FORTH_RUN_ERROR_NONE;
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
int prim_optimize_dupe(struct ForthEngine *engine){}

//ELSE
void prim_body_else(struct ForthEngine *engine){}
int prim_immediate_else(struct ForthEngine *engine){}
int prim_compile_else(struct ForthEngine *engine){}
int prim_optimize_else(struct ForthEngine *engine){}

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
    }
}

//EXIT
void prim_body_exit(struct ForthEngine *engine){}
int prim_immediate_exit(struct ForthEngine *engine){}
int prim_compile_exit(struct ForthEngine *engine){}
int prim_optimize_exit(struct ForthEngine *engine){}

//FILL
void prim_body_fill(struct ForthEngine *engine){}
int prim_immediate_fill(struct ForthEngine *engine){}
int prim_compile_fill(struct ForthEngine *engine){}
int prim_optimize_fill(struct ForthEngine *engine){}

//FIND
void prim_body_find(struct ForthEngine *engine){}
int prim_immediate_find(struct ForthEngine *engine){}
int prim_compile_find(struct ForthEngine *engine){}
int prim_optimize_find(struct ForthEngine *engine){}

//HERE
void prim_body_here(struct ForthEngine *engine)
{
    //Write stack count
    *engine->stack=engine->data_ptr;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//I
void prim_body_i(struct ForthEngine *engine){}
int prim_immediate_i(struct ForthEngine *engine){}
int prim_compile_i(struct ForthEngine *engine){}
int prim_optimize_i(struct ForthEngine *engine){}

//IF
void prim_body_if(struct ForthEngine *engine){}
int prim_immediate_if(struct ForthEngine *engine){}
int prim_compile_if(struct ForthEngine *engine){}
int prim_optimize_if(struct ForthEngine *engine){}

//IMMEDIATE
void prim_body_immediate(struct ForthEngine *engine){}
int prim_immediate_immediate(struct ForthEngine *engine){}
int prim_compile_immediate(struct ForthEngine *engine){}
int prim_optimize_immediate(struct ForthEngine *engine){}

//INVERT
void prim_body_invert(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    *(int32_t*)((engine->stack_base)|lower)=value^-1;
}
int prim_optimize_invert(struct ForthEngine *engine){}

//J
void prim_body_j(struct ForthEngine *engine){}
int prim_immediate_j(struct ForthEngine *engine){}
int prim_compile_j(struct ForthEngine *engine){}
int prim_optimize_j(struct ForthEngine *engine){}

//KEY
void prim_body_key(struct ForthEngine *engine){}
int prim_immediate_key(struct ForthEngine *engine){}
int prim_compile_key(struct ForthEngine *engine){}
int prim_optimize_key(struct ForthEngine *engine){}

//LEAVE
void prim_body_leave(struct ForthEngine *engine){}
int prim_immediate_leave(struct ForthEngine *engine){}
int prim_compile_leave(struct ForthEngine *engine){}
int prim_optimize_leave(struct ForthEngine *engine){}

//LITERAL
void prim_body_literal(struct ForthEngine *engine){}
int prim_immediate_literal(struct ForthEngine *engine){}
int prim_compile_literal(struct ForthEngine *engine){}
int prim_optimize_literal(struct ForthEngine *engine){}

//LOOP
void prim_body_loop(struct ForthEngine *engine){}
int prim_immediate_loop(struct ForthEngine *engine){}
int prim_compile_loop(struct ForthEngine *engine){}
int prim_optimize_loop(struct ForthEngine *engine){}

//L_SHIFT
void prim_body_l_shift(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t arg1=*(uint32_t*)((engine->stack_base)|lower);
    uint32_t arg2=*engine->stack;
    //Write result
    *(uint32_t*)((engine->stack_base)|lower)=arg1<<arg2;
}
int prim_optimize_l_shift(struct ForthEngine *engine){}

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
int prim_optimize_max(struct ForthEngine *engine){}

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
        *(int32_t*)((engine->stack_base)|lower)=arg2;
    }
    else
    {
        //Larger value is already in place - nothing to do
    }
}
int prim_optimize_min(struct ForthEngine *engine){}

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
    //Write result
    if (arg2==0) arg2=1;
    *(int32_t*)((engine->stack_base)|lower)=arg1%arg2;
}
int prim_optimize_mod(struct ForthEngine *engine){}

//MOVE
void prim_body_move(struct ForthEngine *engine){}
int prim_immediate_move(struct ForthEngine *engine){}
int prim_compile_move(struct ForthEngine *engine){}
int prim_optimize_move(struct ForthEngine *engine){}

//NEGATE
void prim_body_negate(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    *(int32_t*)((engine->stack_base)|lower)=-value;
}
int prim_optimize_negate(struct ForthEngine *engine){}

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
int prim_optimize_or(struct ForthEngine *engine){}

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
int prim_optimize_over(struct ForthEngine *engine){}

//REPEAT
void prim_body_repeat(struct ForthEngine *engine){}
int prim_immediate_repeat(struct ForthEngine *engine){}
int prim_compile_repeat(struct ForthEngine *engine){}
int prim_optimize_repeat(struct ForthEngine *engine){}

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
int prim_optimize_rote(struct ForthEngine *engine){}

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
int prim_optimize_minus_rote(struct ForthEngine *engine){}

//R_SHIFT
void prim_body_r_shift(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t arg1=*(uint32_t*)((engine->stack_base)|lower);
    uint32_t arg2=*engine->stack;
    //Write result
    *(uint32_t*)((engine->stack_base)|lower)=arg1>>arg2;
}
int prim_optimize_r_shift(struct ForthEngine *engine){}

//S_QUOTE
void prim_body_s_quote(struct ForthEngine *engine){}
int prim_immediate_s_quote(struct ForthEngine *engine){}
int prim_compile_s_quote(struct ForthEngine *engine){}
int prim_optimize_s_quote(struct ForthEngine *engine){}

//SPACE
void prim_body_space(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
        engine->print(" ");
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
    if (space_count>0)
    {
        if (space_count>engine->max_spaces) 
        {
            //Limit spaces to print to max set when engine initialized
            space_count=engine->max_spaces;
        }
        for (int i=0;i<space_count;i++)
        {
            engine->print(" ");
        }
    }
}

//STATE
void prim_body_state(struct ForthEngine *engine){}
int prim_immediate_state(struct ForthEngine *engine){}
int prim_compile_state(struct ForthEngine *engine){}
int prim_optimize_state(struct ForthEngine *engine){}

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
int prim_optimize_swap(struct ForthEngine *engine){}

//THEN
void prim_body_then(struct ForthEngine *engine){}
int prim_immediate_then(struct ForthEngine *engine){}
int prim_compile_then(struct ForthEngine *engine){}
int prim_optimize_then(struct ForthEngine *engine){}

//TYPE
void prim_body_type(struct ForthEngine *engine){}
int prim_immediate_type(struct ForthEngine *engine){}
int prim_compile_type(struct ForthEngine *engine){}
int prim_optimize_type(struct ForthEngine *engine){}

//UNTIL
void prim_body_until(struct ForthEngine *engine){}
int prim_immediate_until(struct ForthEngine *engine){}
int prim_compile_until(struct ForthEngine *engine){}
int prim_optimize_until(struct ForthEngine *engine){}

//VARIABLE
void prim_body_variable(struct ForthEngine *engine){}
int prim_immediate_variable(struct ForthEngine *engine){}
int prim_compile_variable(struct ForthEngine *engine){}
int prim_optimize_variable(struct ForthEngine *engine){}

//VAR
void prim_body_var(struct ForthEngine *engine){}
int prim_immediate_var(struct ForthEngine *engine){}
int prim_compile_var(struct ForthEngine *engine){}
int prim_optimize_var(struct ForthEngine *engine){}

//WHILE
void prim_body_while(struct ForthEngine *engine){}
int prim_immediate_while(struct ForthEngine *engine){}
int prim_compile_while(struct ForthEngine *engine){}
int prim_optimize_while(struct ForthEngine *engine){}

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
int prim_optimize_x_or(struct ForthEngine *engine){}

//LEFT_BRACKET
void prim_body_left_bracket(struct ForthEngine *engine){}
int prim_immediate_left_bracket(struct ForthEngine *engine){}
int prim_compile_left_bracket(struct ForthEngine *engine){}
int prim_optimize_left_bracket(struct ForthEngine *engine){}

//RIGHT_BRACKET
void prim_body_right_bracket(struct ForthEngine *engine){}
int prim_immediate_right_bracket(struct ForthEngine *engine){}
int prim_compile_right_bracket(struct ForthEngine *engine){}
int prim_optimize_right_bracket(struct ForthEngine *engine){}

//BRACKET_TICK
void prim_body_bracket_tick(struct ForthEngine *engine){}
int prim_immediate_bracket_tick(struct ForthEngine *engine){}
int prim_compile_bracket_tick(struct ForthEngine *engine){}
int prim_optimize_bracket_tick(struct ForthEngine *engine){}

//BRACKET_CHAR
void prim_body_bracket_char(struct ForthEngine *engine){}
int prim_immediate_bracket_char(struct ForthEngine *engine){}
int prim_compile_bracket_char(struct ForthEngine *engine){}
int prim_optimize_bracket_char(struct ForthEngine *engine){}

//DOT_R
void prim_body_dot_r(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t spaces=*(uint32_t*)((engine->stack_base)|lower);
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
        for (int i=0;i<spaces;i++)
            engine->print(" ");
        //Output number
        engine->print(text_buffer);
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
int prim_optimize_not_equals(struct ForthEngine *engine){}

//AGAIN
void prim_body_again(struct ForthEngine *engine){}
int prim_immediate_again(struct ForthEngine *engine){}
int prim_compile_again(struct ForthEngine *engine){}
int prim_optimize_again(struct ForthEngine *engine){}

//CASE
void prim_body_case(struct ForthEngine *engine){}
int prim_immediate_case(struct ForthEngine *engine){}
int prim_compile_case(struct ForthEngine *engine){}
int prim_optimize_case(struct ForthEngine *engine){}

//FALSE
void prim_body_false(struct ForthEngine *engine)
{
    //Write value for space character
    *engine->stack=FORTH_FALSE;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_false(struct ForthEngine *engine){}

//HEX
void prim_body_hex(struct ForthEngine *engine){}
int prim_immediate_hex(struct ForthEngine *engine){}
int prim_compile_hex(struct ForthEngine *engine){}
int prim_optimize_hex(struct ForthEngine *engine){}

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
int prim_optimize_nip(struct ForthEngine *engine){}

//PICK
void prim_body_pick(struct ForthEngine *engine){}
int prim_immediate_pick(struct ForthEngine *engine){}
int prim_compile_pick(struct ForthEngine *engine){}
int prim_optimize_pick(struct ForthEngine *engine){}

//ROLL
void prim_body_roll(struct ForthEngine *engine){}
int prim_immediate_roll(struct ForthEngine *engine){}
int prim_compile_roll(struct ForthEngine *engine){}
int prim_optimize_roll(struct ForthEngine *engine){}

//S_BACKSLASH_QUOTE
void prim_body_s_backslash_quote(struct ForthEngine *engine){}
int prim_immediate_s_backslash_quote(struct ForthEngine *engine){}
int prim_compile_s_backslash_quote(struct ForthEngine *engine){}
int prim_optimize_s_backslash_quote(struct ForthEngine *engine){}

//TRUE
void prim_body_true(struct ForthEngine *engine)
{
    //Write value for space character
    *engine->stack=FORTH_TRUE;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}
int prim_optimize_true(struct ForthEngine *engine){}

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
int prim_optimize_tuck(struct ForthEngine *engine){}

//UNUSED
void prim_body_unused(struct ForthEngine *engine){}
int prim_immediate_unused(struct ForthEngine *engine){}
int prim_compile_unused(struct ForthEngine *engine){}
int prim_optimize_unused(struct ForthEngine *engine){}

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
int prim_optimize_within(struct ForthEngine *engine){}

//BACKSLASH
void prim_body_backslash(struct ForthEngine *engine){}
int prim_immediate_backslash(struct ForthEngine *engine){}
int prim_compile_backslash(struct ForthEngine *engine){}
int prim_optimize_backslash(struct ForthEngine *engine){}

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
        for (int i=0;i<stack_count;i++)
        {
            text_int32(*stack,text_buffer);
            engine->print(text_buffer);
            engine->print(" ");
            stack--;
        }
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
        uint32_t address=(*(engine->stack))&engine->data_mask_32;
        //Read from address
        int32_t value=*(int32_t*)(engine->data+address);
        //Output value
        char text_buffer[TEXT_INT32_SIZE];
        text_int32(value,text_buffer);
        engine->print(text_buffer);
        //Output space
        engine->print(" ");
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
        int32_t count=*(uint32_t*)((engine->stack_base)|lower);
        lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
        uint32_t address=*(int32_t*)((engine->stack_base)|lower);
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
                for (int j=0;j<byte_index;j++)
                {
                    //Replace unprintable characters with .
                    if ((byte_display[j]<CHAR_PRINTABLE_MIN)||(byte_display[j]>CHAR_PRINTABLE_MAX))
                    {
                        byte_display[j]='.';
                    }
                }
                //Print spaces if full line of bytes not printed
                for (int j=0;j<FORTH_DUMP_BYTES-byte_index;j++)
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
    }
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//SEE
void prim_body_see(struct ForthEngine *engine){}
int prim_immediate_see(struct ForthEngine *engine){}
int prim_compile_see(struct ForthEngine *engine){}
int prim_optimize_see(struct ForthEngine *engine){}

//WORDS
int prim_immediate_words(struct ForthEngine *engine)
{
    if (engine->print_color!=NULL)
    {
        //First, try to print in color if the color print function is defined
        engine->print_color("\n",0);
        for (int i=0;i<forth_primitives_len;i++)
        {
            engine->print_color(forth_primitives[i].name,engine->color_primitive);
            engine->print_color(" ",0);
        }
    }
    else if (engine->print!=NULL)
    {
        //If no color function, print without color if print function is defined
        engine->print("\n");
        for (int i=0;i<forth_primitives_len;i++)
        {
            engine->print(forth_primitives[i].name);
            engine->print(" ");
        }
    }
    else
    {
        //No way to print
    }
}
int prim_compile_words(struct ForthEngine *engine){}

//BYE
void prim_body_bye(struct ForthEngine *engine){}
int prim_immediate_bye(struct ForthEngine *engine){}
int prim_compile_bye(struct ForthEngine *engine){}
int prim_optimize_bye(struct ForthEngine *engine){}

//COMPARE
void prim_body_compare(struct ForthEngine *engine){}
int prim_immediate_compare(struct ForthEngine *engine){}
int prim_compile_compare(struct ForthEngine *engine){}
int prim_optimize_compare(struct ForthEngine *engine){}

//RESET
int prim_immediate_reset(struct ForthEngine *engine)
{
    forth_reset_engine_stacks(engine);
}
int prim_compile_reset(struct ForthEngine *engine){}

//Globals
//=======
const struct ForthPrimitive forth_primitives[]=
{
    {"!",1,NULL,NULL,&prim_body_store,&prim_optimize_store},
    {"C!",2,NULL,NULL,&prim_body_c_store,&prim_optimize_c_store},
    {"W!",2,NULL,NULL,&prim_body_w_store,&prim_optimize_w_store},
    //{"'",1,&prim_immediate_tick,&prim_compile_tick,&prim_body_tick,&prim_optimize_tick},
    //{"(",1,&prim_immediate_paren,&prim_compile_paren,&prim_body_paren,&prim_optimize_paren},
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
    //{":",1,&prim_immediate_colon,&prim_compile_colon,&prim_body_colon,&prim_optimize_colon},
    //{";",1,&prim_immediate_semicolon,&prim_compile_semicolon,&prim_body_semicolon,&prim_optimize_semicolon},
    {"<",1,NULL,NULL,&prim_body_less_than,&prim_optimize_less_than},
    {"=",1,NULL,NULL,&prim_body_equals,&prim_optimize_equals},
    {">",1,NULL,NULL,&prim_body_greater_than,&prim_optimize_greater_than},
    //{">NUMBER",7,&prim_immediate_to_number,&prim_compile_to_number,&prim_body_to_number,&prim_optimize_to_number},
    {"?DUP",4,NULL,NULL,&prim_body_question_dupe,&prim_optimize_question_dupe},
    {"@",1,NULL,NULL,&prim_body_fetch,&prim_optimize_fetch},
    {"C@",2,NULL,NULL,&prim_body_c_fetch,&prim_optimize_c_fetch},
    {"W@",2,NULL,NULL,&prim_body_w_fetch,&prim_optimize_w_fetch},
    //{"QUIT",4,&prim_immediate_quit,&prim_compile_quit,&prim_body_quit,&prim_optimize_quit},
    {"ABS",3,NULL,NULL,&prim_body_abs,&prim_optimize_abs},
    //{"ACCEPT",6,&prim_immediate_accept,&prim_compile_accept,&prim_body_accept,&prim_optimize_accept},
    //{"ALIGN",5,&prim_immediate_align,&prim_compile_align,&prim_body_align,&prim_optimize_align},
    //{"ALIGNED",7,&prim_immediate_aligned,&prim_compile_aligned,&prim_body_aligned,&prim_optimize_aligned},
    {"ALLOT",5,NULL,NULL,&prim_body_allot,NULL},
    {"AND",3,NULL,NULL,&prim_body_and,&prim_optimize_and},
    //{"BEGIN",5,&prim_immediate_begin,&prim_compile_begin,&prim_body_begin,&prim_optimize_begin},
    {"BL",2,NULL,NULL,&prim_body_b_l,NULL},
    {"CELLS",5,NULL,NULL,&prim_body_cells,NULL},
    //{"CHAR",4,&prim_immediate_char,&prim_compile_char,&prim_body_char,&prim_optimize_char},
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
    //{"EXIT",4,&prim_immediate_exit,&prim_compile_exit,&prim_body_exit,&prim_optimize_exit},
    //{"FILL",4,&prim_immediate_fill,&prim_compile_fill,&prim_body_fill,&prim_optimize_fill},
    {"HERE",4,NULL,NULL,&prim_body_here,NULL},
    //{"I",1,&prim_immediate_i,&prim_compile_i,&prim_body_i,&prim_optimize_i},
    //{"IF",2,&prim_immediate_if,&prim_compile_if,&prim_body_if,&prim_optimize_if},
    //{"IMMEDIATE",9,&prim_immediate_immediate,&prim_compile_immediate,&prim_body_immediate,&prim_optimize_immediate},
    //Shortcut for IMMEDIATE
    //{"IMMED",5,&prim_immediate_immediate,&prim_compile_immediate,&prim_body_immediate,&prim_optimize_immediate},
    {"INVERT",6,NULL,NULL,&prim_body_invert,&prim_optimize_invert},
    //{"J",1,&prim_immediate_j,&prim_compile_j,&prim_body_j,&prim_optimize_j},
    //{"KEY",3,&prim_immediate_key,&prim_compile_key,&prim_body_key,&prim_optimize_key},
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
    //{"REPEAT",6,&prim_immediate_repeat,&prim_compile_repeat,&prim_body_repeat,&prim_optimize_repeat},
    {"ROT",3,NULL,NULL,&prim_body_rote,&prim_optimize_rote},
    {"-ROT",4,NULL,NULL,&prim_body_minus_rote,&prim_optimize_minus_rote},
    {"RSHIFT",6,NULL,NULL,&prim_body_r_shift,&prim_optimize_r_shift},
    //{"S\"",2,&prim_immediate_s_quote,&prim_compile_s_quote,&prim_body_s_quote,&prim_optimize_s_quote},
    {"SPACE",5,NULL,NULL,&prim_body_space,NULL},
    {"SPACES",6,NULL,NULL,&prim_body_spaces,NULL},
    //{"STATE",5,&prim_immediate_state,&prim_compile_state,&prim_body_state,&prim_optimize_state},
    {"SWAP",4,NULL,NULL,&prim_body_swap,&prim_optimize_swap},
    //{"THEN",4,&prim_immediate_then,&prim_compile_then,&prim_body_then,&prim_optimize_then},
    //{"TYPE",4,&prim_immediate_type,&prim_compile_type,&prim_body_type,&prim_optimize_type},
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
    //{"BYE",3,&prim_immediate_bye,&prim_compile_bye,&prim_body_bye,&prim_optimize_bye},
    //{"COMPARE",7,&prim_immediate_compare,&prim_compile_compare,&prim_body_compare,&prim_optimize_compare},

    //Words from here are not standard forth
    {"RESET",5,&prim_immediate_reset,&prim_compile_reset,NULL,NULL},
    //output number to memory (opposite of >number)
    //. for unsigned (u. and u.r?) and hex since no BASE
    //comments? no \ on keypad but ( ) could work
    //2SWAP etc
    //adjust size of data area
    //WALIGN
    //WALIGNED
};

//Can't determine length of array primitives in other files, so calculate here
const int forth_primitives_len=(int)(ARRAY_SIZE(forth_primitives));
