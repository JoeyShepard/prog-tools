#include <stdio.h>
#include <string.h>

#include "compatibility.h"
#include "forth-action-list.h" 
#include "forth-primitives.h"
#include "logging.h"
#include "macros.h"
#include "text.h"

//TODO: remove
#include "test.h"

//TODO: remove
#define address(x) ((uintptr_t)x)>>24, (((uintptr_t)x)>>16)&0xFF, (((uintptr_t)x)>>8)&0xFF, ((uintptr_t)x)&0xFF

typedef int (*f_t)(void);
f_t *f;

int f1(){ return 12; }
int f3(){ return 56; }
int f_exec()
{
    f++;
    __attribute__((musttail)) return ((f_t)f)();
}

void jit_test2()
{
    //sh4eb machine code
    char test_code[64]={
        address(f1),
        address(f_exec),
        0x00, 0x0B, //rts
        0xE0, 0x2A, //mov #42,r0
        address(f3),
        address(NULL),
        };

    //Copy machine code to memory
    memcpy(heap,test_code,sizeof(test_code));
    
    f=(f_t*)heap;
    while(1)
    {
        if (*f==NULL) break;
        printf("f: %p, f1: %p, f3: %p\n",f,f1,f3);
        int result=(*f)();
        printf("%d\n",result);
        f++;
    }
}






//Internal primitives - not visible to user
//=========================================
void prim_hidden_do(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch loop values
    int32_t loop_min=engine->stack[engine->stack_index-1];
    int32_t loop_max=engine->stack[engine->stack_index-2];
    
    //Update stack pointer
    engine->stack_index-=2;

    //Push existing J counter to R-stack
    if (engine->rstack<engine->rstack_base)
    {
        //Out of R-stack memory - abort
        engine->error=FORTH_ENGINE_ERROR_RSTACK_FULL;
        engine->executing=false;
    }
    else
    {
        //Push J counter to R-stack
        engine->rstack->value=engine->loop_j;
        engine->rstack->value_max=engine->loop_j_max;
        engine->rstack->type=FORTH_RSTACK_DO_LOOP;
        engine->rstack->index=engine->word_index;;

        //Decrease R-stack pointer to next element
        engine->rstack--;

        //Copy I counter to J counter
        engine->loop_j=engine->loop_i;
        engine->loop_j_max=engine->loop_i_max;

        //Set new I counter
        engine->loop_i=loop_min;
        engine->loop_i_max=loop_max;
    }

    FORTH_NEXT
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

            //Restore any locals memory used
            engine->locals_stack+=engine->rstack->locals_count;

            //Done searching
            break;
        }
        else if (engine->rstack->type==FORTH_RSTACK_DONE)
        {
            //Returning from top-level word - stop executing
            engine->executing=false;
            return;
        }
        else
        {
            //Found loop counter or something else - keep searching
        }
    }

    FORTH_NEXT
}

//Print out characters stored in thread
void prim_hidden_dot_quote(struct ForthEngine *engine)
{
    //Length of quote appears after primitive
    uint32_t quote_length=*(uint32_t *)(engine->address+1);

    //Characters start after that
    const char *text=((char *)(engine->address+1))+sizeof(uint32_t);

    //Logging
    log_push(LOGGING_FORTH_PRIM_HIDDEN_DOT_QUOTE,"prim_hidden_dot_quote");
    log_text("engine->address: %p\n",engine->address);
    log_text("length address: %p\n",(uint32_t *)(engine->address+1));
    log_text("quote_length: %u\n",quote_length);
    log_text("text: %p\n",text);

    //Loop through and print characters
    char buffer[2];
    buffer[1]=0;
    for (uint32_t i=0;i<quote_length;i++)
    {
        //Logging
        log_text("character: %c (%d)\n",*text,*text);

        if (engine->print!=NULL)
        {
            buffer[0]=*text;
            engine->print(buffer);

            //Logging
            log_text("printed: %s\n",buffer);
        }

        //Advance to next character
        text++;
    }

    //Update screen
    if (engine->update_screen!=NULL) engine->update_screen();

    //Logging
    log_text("text after printing: %p\n",text);

    //Align address pointer
    uint32_t ptr_size=sizeof(void(*)(struct ForthEngine *engine));
    text+=(ptr_size-(quote_length%ptr_size))%ptr_size;
    engine->address=((void (**)(struct ForthEngine *engine))text)-1;

    //Logging
    log_text("ptr_size: %u\n",ptr_size);
    log_text("new text: %p\n",text);
    log_text("new engine->address: %p\n",engine->address);

    //Logging
    log_pop();

    FORTH_NEXT
}


//Test value on stack and jump if not 0
void prim_hidden_if(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch value from stack to test
    engine->stack_index--;
    int32_t test_value=engine->stack[engine->stack_index];

    //Skip to ELSE or THEN if stack value not true
    if (test_value==0)
    {
        //Jump taken - fetch offset which is stored after pointer to current word
        int32_t offset=*(int32_t *)(engine->address+1);
        engine->address=(void (**)(struct ForthEngine *))((char *)engine->address+offset);
    }
    else
    {
        //Jump not taken - increment thread pointer to account for offset stored after primitive
        engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);
    }

    FORTH_NEXT
}

//Jump to different part of thread
void prim_hidden_jump(struct ForthEngine *engine)
{
    //Fetch offset which is stored after pointer to current word and jump
    int32_t offset=*(int32_t *)(engine->address+1);
    engine->address=(void (**)(struct ForthEngine *))((char *)engine->address+offset);

    FORTH_NEXT
}

void prim_hidden_leave(struct ForthEngine *engine)
{
    //Copy J counter to I counter
    engine->loop_i=engine->loop_j;
    engine->loop_i_max=engine->loop_j_max;

    //Pop structure from R-stack to restore J counter
    engine->rstack++;
    engine->loop_j=engine->rstack->value;
    engine->loop_j_max=engine->rstack->value_max;

    //Fetch offset which is stored after pointer to current word and jump
    int32_t offset=*(int32_t *)(engine->address+1);
    engine->address=(void (**)(struct ForthEngine *))((char *)engine->address+offset);

    FORTH_NEXT
}

void prim_hidden_loop(struct ForthEngine *engine)
{
    //Increment loop counter
    engine->loop_i++;

    //Jump back to DO if done looping
    if (engine->loop_i!=engine->loop_i_max)
    {
        //Jump taken - fetch offset which is stored after pointer to current word
        int32_t offset=*(int32_t *)(engine->address+1);
        engine->address=(void (**)(struct ForthEngine *))((char *)engine->address+offset);
    }
    else
    {
        //Jump not taken - increment thread pointer to account for offset stored after primitive
        engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);

        //Copy J counter to I counter
        engine->loop_i=engine->loop_j;
        engine->loop_i_max=engine->loop_j_max;

        //Pop structure from R-stack to restore J counter
        engine->rstack++;
        engine->loop_j=engine->rstack->value;
        engine->loop_j_max=engine->rstack->value_max;
    }

    FORTH_NEXT
}

void prim_hidden_plus_loop(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Increment loop counter
    engine->stack_index--;
    engine->loop_i+=engine->stack[engine->stack_index];

    //Jump back to DO if done looping
    if (engine->loop_i<engine->loop_i_max)
    {
        //Jump taken - fetch offset which is stored after pointer to current word
        int32_t offset=*(int32_t *)(engine->address+1);
        engine->address=(void (**)(struct ForthEngine *))((char *)engine->address+offset);
    }
    else
    {
        //Jump not taken - increment thread pointer to account for offset stored after primitive
        engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);

        //Copy J counter to I counter
        engine->loop_i=engine->loop_j;
        engine->loop_i_max=engine->loop_j_max;

        //Pop structure from R-stack to restore J counter
        engine->rstack++;
        engine->loop_j=engine->rstack->value;
        engine->loop_j_max=engine->rstack->value_max;
    }

    FORTH_NEXT
}

//Push next cell in dictionary to stack
void prim_hidden_push(struct ForthEngine *engine)
{
    //Fetch number which is stored after pointer to current word
    int32_t num=*(int32_t *)(engine->address+1);

    //Increment thread pointer to account for number
    engine->address=(void (**)(struct ForthEngine *engine))(((int32_t *)engine->address)+1);

    //Push number to stack
    engine->stack[engine->stack_index]=num;
    engine->stack_index++;

    FORTH_NEXT
}

//Write characters to data memory
void prim_hidden_s_quote(struct ForthEngine *engine)
{
    if (engine->stack_index>=(FORTH_STACK_ELEMENTS-1))
    {
        //Overflow
        engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
        engine->executing=false;
        return;
    }

    //Length of quote appears after primitive
    uint32_t quote_length=*(uint32_t *)(engine->address+1);

    //Characters start after that
    const char *text=((char *)(engine->address+1))+sizeof(uint32_t);

    //Return address to stack at end
    uint32_t address=engine->data_index;

    //Logging
    log_push(LOGGING_FORTH_PRIM_HIDDEN_S_QUOTE,"prim_hidden_s_quote");
    log_text("engine->address: %p\n",engine->address);
    log_text("length address: %p\n",(uint32_t *)(engine->address+1));
    log_text("quote_length: %u\n",quote_length);
    log_text("text: %p\n",text);

    //Loop through characters
    for (uint32_t i=0;i<quote_length;i++)
    {
        //Logging
        log_text("character: %c (%d)\n",*text,*text);

        //Write character to data memory
        *(engine->data+engine->data_index)=*text;

        //Advance data pointer
        engine->data_index=(engine->data_index+sizeof(char))&engine->data_mask;

        //Advance to next character
        text++;
    }

    //Logging
    log_text("text: %p\n",text);

    //Align address pointer
    uint32_t ptr_size=sizeof(void(*)(struct ForthEngine *engine));
    text+=(ptr_size-(quote_length%ptr_size))%ptr_size;
    engine->address=((void (**)(struct ForthEngine *engine))text)-1;

    //Logging
    log_text("ptr_size: %u\n",ptr_size);
    log_text("new text: %p\n",text);
    log_text("new engine->address: %p\n",engine->address);

    //Write return values to stack
    engine->stack[engine->stack_index]=address;
    engine->stack_index++;
    engine->stack[engine->stack_index]=quote_length;
    engine->stack_index++;

    //Logging
    log_pop();

    FORTH_NEXT
}

//TODO: IMPORTANT - any changes here also apply to inlined copy in prim_exec!
//Call secondary which may be user-defined word or variable
void prim_hidden_secondary(struct ForthEngine *engine)
{
    //Fetch index of word header in header list. Index is after pointer to current word.
    uint32_t index=*(uint32_t *)(engine->address+1);

    //Increment thread pointer to account for fetched offset
    engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);

    //Figure out if secondary is user-defined word or variable - slower but necessary to support redefining words
    struct ForthWordHeader *secondary=&engine->word_headers[index];
    if (secondary->type==FORTH_SECONDARY_UNDEFINED)
    {
        //Error - word referenced in word but never defined
        engine->error=FORTH_ENGINE_ERROR_UNDEFINED;
        engine->error_word=secondary->name;
        engine->executing=false;
    }
    else if ((secondary->type==FORTH_SECONDARY_CONSTANT)||(secondary->type==FORTH_SECONDARY_CREATE)||
            (secondary->type==FORTH_SECONDARY_VARIABLE))
    {
        //These are actually words that can be executed but faster to extract value and push here manually instead
        if (engine->stack_index>=(FORTH_STACK_ELEMENTS))
        {
            //Overflow
            engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
            engine->executing=false;
            return;
        }

        //Extract number
        int32_t num=*(int32_t *)(secondary->address+1);
        
        //Push number to stack
        engine->stack[engine->stack_index]=num;
        engine->stack_index++;
    }
    else
    {
        //Push word return address to R-stack - faster to inline than call forth_rstack_push
        if (engine->rstack<engine->rstack_base)
        {
            //Error - out of R-stack memory. Abort.
            engine->error=FORTH_ENGINE_ERROR_RSTACK_FULL;
            engine->executing=false;
        }
        else
        {
            //Increase word index so tagged R-stack addresses can be linked to word they belong to
            engine->word_index++;

            //Push new values to R-stack
            engine->rstack->value=(uintptr_t)(engine->address)-(uintptr_t)(engine->word_bodies);
            engine->rstack->type=FORTH_RSTACK_RETURN;
            engine->rstack->index=engine->word_index;
            engine->rstack->locals_count=secondary->locals_count;

            //Make room for locals
            engine->locals_stack-=secondary->locals_count;
            if (engine->locals_stack<engine->locals_base)
            {
                //Error - out of local stack memory. Abort.
                engine->error=FORTH_ENGINE_ERROR_LOCAL_STACK_FULL;
                engine->executing=false;
            }

            //Decrease R-stack pointer to next element
            engine->rstack--;

            //Set new execution address to address of secondary stored in word header list
            engine->address=secondary->address;

            //Account for interpreter advancing execution address
            engine->address--;
        }
    }

    FORTH_NEXT
}

//Jump to JIT code
void prim_hidden_jit(struct ForthEngine *engine)
{
    //__attribute__((musttail)) return *((void (**)(struct ForthEngine *))(engine->address+1))(engine);
}

//Primitives visible to user
//==========================

//STORE
void prim_store(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    uint32_t address=engine->stack[engine->stack_index];
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];

    //Mask address
    address&=engine->data_mask_32;
    
    //Write value to address
    *(int32_t*)(engine->data+address)=value;

    FORTH_NEXT
}

//C_STORE
void prim_c_store(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    uint32_t address=engine->stack[engine->stack_index];
    
    //Read 32-bit value here so no endian problems
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];
    
    //Mask address
    address&=engine->data_mask;
    
    //Write value to address
    *(engine->data+address)=value;

    FORTH_NEXT
}

//W_STORE
void prim_w_store(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    uint32_t address=engine->stack[engine->stack_index];
    
    //Read 32-bit value here so no endian problems
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];
    
    //Mask address
    address&=engine->data_mask_16;
    
    //Write value to address
    *(int16_t*)(engine->data+address)=value;

    FORTH_NEXT
}

//STAR
void prim_star(struct ForthEngine *engine)
{
    //TODO: time -- vs offset vs -- then ++ vs pointer from array
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    engine->stack[engine->stack_index-1]=arg1*arg2;

    FORTH_NEXT
}

//STAR_SLASH
void prim_star_slash(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t divisor=engine->stack[engine->stack_index];
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Calculate
    if (divisor==0) divisor=1;
    int64_t product=(int64_t)arg1*(int64_t)arg2;
    int32_t quotient=product/(int64_t)divisor;
    
    //Write result
    engine->stack[engine->stack_index-1]=quotient;

    FORTH_NEXT
}

//STAR_SLASH_MOD
void prim_star_slash_mod(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t divisor=engine->stack[engine->stack_index];
    int32_t arg2=engine->stack[engine->stack_index-1];
    int32_t arg1=engine->stack[engine->stack_index-2];

    //Calculate
    if (divisor==0) divisor=1;
    int64_t product=(int64_t)arg1*(int64_t)arg2;
    int32_t remainder=product%(int64_t)divisor;
    int32_t quotient=product/(int64_t)divisor;
    
    //Write results to stack
    engine->stack[engine->stack_index-1]=quotient;
    engine->stack[engine->stack_index-2]=remainder;

    FORTH_NEXT
}

//PLUS
void prim_plus(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    engine->stack[engine->stack_index-1]=arg1+arg2;

    FORTH_NEXT
}

//COMMA
void prim_comma(struct ForthEngine *engine)
{
    //Mask destination address
    engine->data_index&=engine->data_mask_32;
    
    //Write value
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];
    *(int32_t*)(engine->data+engine->data_index)=value;
    
    //Advance data pointer
    engine->data_index=(engine->data_index+sizeof(int32_t))&engine->data_mask_32;

    FORTH_NEXT
}

//C_COMMA
void prim_c_comma(struct ForthEngine *engine)
{
    //Mask destination address
    engine->data_index&=engine->data_mask;
    
    //Write value
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];
    *(int8_t*)(engine->data+engine->data_index)=value;
    
    //Advance data pointer
    engine->data_index=(engine->data_index+sizeof(int8_t))&engine->data_mask;

    FORTH_NEXT
}

//W_COMMA
void prim_w_comma(struct ForthEngine *engine)
{
    //Mask destination address
    engine->data_index&=engine->data_mask_16;
    
    //Write value
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];
    *(int16_t*)(engine->data+engine->data_index)=value;
    
    //Advance data pointer
    engine->data_index=(engine->data_index+sizeof(int8_t))&engine->data_mask_16;

    FORTH_NEXT
}

//MINUS
void prim_minus(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    engine->stack[engine->stack_index-1]=arg1-arg2;

    FORTH_NEXT
}

//DOT
void prim_dot(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Update stack pointer
    engine->stack_index--;

    //TODO: printing was failing until added printf line inside if below. removed printf and bug did not reappear.
    //Print if print function defined
    if (engine->print!=NULL)
    {
        //Output number
        char text_buffer[TEXT_INT32_SIZE];
        text_int32(engine->stack[engine->stack_index],text_buffer);
        engine->print(text_buffer);

        //Output space
        engine->print(" ");
        
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//U_DOT
void prim_u_dot(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Update stack pointer
    engine->stack_index--;

    //Print if print function defined
    if (engine->print!=NULL)
    {
        //Output number
        char text_buffer[TEXT_UINT32_SIZE];
        text_uint32(engine->stack[engine->stack_index],text_buffer);
        engine->print(text_buffer);
        
        //Output space
        engine->print(" ");
        
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//X_DOT
void prim_x_dot(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Update stack pointer
    engine->stack_index--;

    //Print if print function defined
    if (engine->print!=NULL)
    {
        //Output number
        char text_buffer[TEXT_UINT32_SIZE];
        text_hex32(engine->stack[engine->stack_index],text_buffer);
        engine->print(text_buffer);
        
        //Output space
        engine->print(" ");
        
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//SLASH
void prim_slash(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    if (arg2==0) arg2=1;
    engine->stack[engine->stack_index-1]=arg1/arg2;

    FORTH_NEXT
}

//SLASH_MOD
void prim_slash_mod(struct ForthEngine *engine)
{
    //Fetch arguments
    int32_t arg2=engine->stack[engine->stack_index-1];
    int32_t arg1=engine->stack[engine->stack_index-2];

    //Write result
    if (arg2==0) arg2=1;
    engine->stack[engine->stack_index-1]=arg1/arg2;
    engine->stack[engine->stack_index-2]=arg1%arg2;

    FORTH_NEXT
}

//LESS_THAN
void prim_less_than(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result (note true is 1 in C but -1 in FORTH)
    engine->stack[engine->stack_index-1]=-(arg1<arg2);

    FORTH_NEXT
}

//EQUALS
void prim_equals(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result (note true is 1 in C but -1 in FORTH)
    engine->stack[engine->stack_index-1]=-(arg1==arg2);

    FORTH_NEXT
}

//GREATER_THAN
void prim_greater_than(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result (note true is 1 in C but -1 in FORTH)
    engine->stack[engine->stack_index-1]=-(arg1>arg2);

    FORTH_NEXT
}

//TO_NUMBER - Note differs from >NUMBER in standard!
//(c-addr1 u1 - s2 c-addr2 u2) - no doubles or scratch space
    //c-addr1 u1 - string to convert
    //s2 - int result
    //c-addr2 - first character not converted (or past end if converted all)
    //u2 - number of unconverted characters
void prim_to_number(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }
    else if (engine->stack_index>=FORTH_STACK_ELEMENTS)
    {
        //Overflow
        engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch values from stack
    uint32_t count=engine->stack[engine->stack_index-1];
    uint32_t address=engine->stack[engine->stack_index-2];

    //Limit count so it loops through memory at most once
    if (count>=engine->data_size) count=engine->data_size;
    
    //Loop through characters
    int64_t result=0;
    bool negative=false;
    uint32_t unconverted_count=count;
    uint32_t starting_address=address;
    for (uint32_t i=0;i<count;i++)
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
            if (negative==false) result+=character-'0';
            else if (negative==true) result-=character-'0';
            if ((result>UINT32_MAX)||(result<INT32_MIN))
            {
                //TODO: seems could be out of range if this size of size+1
                //Error - number is out of range
                for (int j=0;j<TEXT_INT32_SIZE-1;j++)
                {
                    //Mask address
                    starting_address&=engine->data_mask; 
                    
                    //Fetch character
                    char character=*(engine->data+starting_address);
                    
                    if (((character=='-')&&(j==0))||((character>='0')&&(character<='9')))
                    {
                        //Store character in buffer for error message
                        engine->error_num[j]=character;
                        engine->error_num[j+1]=0;
                    }

                    //Next character
                    starting_address++;
                }
                engine->error=FORTH_ENGINE_ERROR_INT32_RANGE;
                engine->executing=false;

                //Update stack pointer
                engine->stack_index-=2;

                return;
            }
            unconverted_count--;
        }
        else
        {
            //Non number character - stop looping
            break;
        }
        address++;
    }

    //Write values to stack
    engine->stack[engine->stack_index]=unconverted_count;
    engine->stack[engine->stack_index-1]=address;
    engine->stack[engine->stack_index-2]=result;

    //Update stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//TO_HEX
//(c-addr1 u1 - s2 c-addr2 u2)
void prim_to_hex(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }
    else if (engine->stack_index>=FORTH_STACK_ELEMENTS)
    {
        //Overflow
        engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch values from stack
    uint32_t count=engine->stack[engine->stack_index-1];
    uint32_t address=engine->stack[engine->stack_index-2];

    //Limit count so it loops through memory at most once
    if (count>=engine->data_size) count=engine->data_size;

    bool negative;
    uint32_t unconverted_count=count;
    uint32_t starting_address=address;

    //Check for preceding -
    if (count>=1)
    {
        //Mask address
        address&=engine->data_mask; 
        if  (*(engine->data+address)=='-')
        {
            negative=true;
            address++;
            count--;
            unconverted_count--;
        }
        else negative=false;
    }

    //Check for preceding 0x 
    if (count>=2)
    {
        uint32_t new_address=address;
        //Mask address
        new_address&=engine->data_mask; 
        if  (*(engine->data+new_address)=='0')
        {
            new_address++;
            new_address&=engine->data_mask; 
            if  (*(engine->data+new_address)=='x')
            {
                //Skip over preceding 0x
                address=new_address+1;
                count-=2;
                unconverted_count-=2;
            }
        }
    }

    //Loop through characters
    int64_t result=0;
    for (uint32_t i=0;i<count;i++)
    {
        //Mask address
        address&=engine->data_mask; 
    
        //Fetch character
        char character=*(engine->data+address);
        int digit;
        if ((character>='0')&&(character<='9'))
            digit=character-'0';
        else if ((character>='a')&&(character<='f'))
            digit=character-'a'+10;
        else if ((character>='A')&&(character<='F'))
            digit=character-'A'+10;
        else
        {
            //Non number character - stop looping
            break;
        }

        //Character is valid digit - add to result
        result*=0x10;
        if (negative==false) result+=digit;
        else if (negative==true) result-=digit;
        if ((result>UINT32_MAX)||(result<INT32_MIN))
        {
            //Error - number is out of range
            for (int j=0;j<TEXT_HEX32_SIZE-1;j++)
            {
                //Mask address
                starting_address&=engine->data_mask; 
                
                //Fetch character
                char character=*(engine->data+starting_address);
                
                if (((character=='-')&&(j==0))||
                    ((character>='0')&&(character<='9'))||
                    ((character>='A')&&(character<='F'))||
                    ((character>='a')&&(character<='f')))
                {
                    //Store character in buffer for error message
                    engine->error_num[j]=character;
                    engine->error_num[j+1]=0;
                }

                //Next character
                starting_address++;
            }
            engine->error=FORTH_ENGINE_ERROR_HEX32_RANGE;
            engine->executing=false;

            //Update stack pointer
            engine->stack_index-=2;

            return;
        }
        unconverted_count--;
        address++;
    }

    //Write values to stack
    engine->stack[engine->stack_index]=unconverted_count;
    engine->stack[engine->stack_index-1]=address;
    engine->stack[engine->stack_index-2]=result;

    //Update stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//NUMBER>
//(n c-addr - u)
void prim_number_to(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch arguments
    engine->stack_index--;
    int32_t address=engine->stack[engine->stack_index];
    int32_t num=engine->stack[engine->stack_index-1];

    //Convert number to text
    char num_buffer[TEXT_INT32_SIZE];
    text_int32(num,num_buffer);
    uint32_t num_len=strlen(num_buffer);

    //Write text to data memory
    for (uint32_t i=0;i<num_len;i++)
    {
        //Mask address
        address&=engine->data_mask; 

        //Fetch character
        *(engine->data+address)=num_buffer[i];
        
        //Next character
        address++;
    }

    //Write character count to stack
    engine->stack[engine->stack_index-1]=num_len;

    FORTH_NEXT
}

//HEX>
//(u c-addr - u) 
void prim_hex_to(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch arguments
    engine->stack_index--;
    int32_t address=engine->stack[engine->stack_index];
    int32_t num=engine->stack[engine->stack_index-1];

    //Convert number to text
    char num_buffer[TEXT_HEX32_SIZE];
    text_hex32(num,num_buffer);
    uint32_t num_len=strlen(num_buffer);

    //Write text to data memory
    for (uint32_t i=0;i<num_len;i++)
    {
        //Mask address
        address&=engine->data_mask; 

        //Fetch character
        *(engine->data+address)=num_buffer[i];
        
        //Next character
        address++;
    }

    //Write character count to stack
    engine->stack[engine->stack_index-1]=num_len;

    FORTH_NEXT
}

//QUESTION_DUPE
void prim_question_dupe(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    if (engine->stack[engine->stack_index-1]!=0)
    {
        if (engine->stack_index>=FORTH_STACK_ELEMENTS)
        {
            //Overflow
            engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
            engine->executing=false;
            return;
        }

        //Value is not zero - duplicate
        engine->stack[engine->stack_index]=engine->stack[engine->stack_index-1];

        //Advance stack pointer
        engine->stack_index++;
    }

    FORTH_NEXT
}

//FETCH
void prim_fetch(struct ForthEngine *engine)
{
    //Fetch argument
    int32_t address=engine->stack[engine->stack_index-1];

    //Mask address
    address&=engine->data_mask_32;
    
    //Read from address
    int32_t value=*(int32_t*)(engine->data+address);
    
    //Write value to stack
    engine->stack[engine->stack_index-1]=value;

    FORTH_NEXT
}

//C_FETCH
void prim_c_fetch(struct ForthEngine *engine)
{
    //Fetch argument
    int32_t address=engine->stack[engine->stack_index-1];
    
    //Mask address
    address&=engine->data_mask;
    
    //Read from address
    //TODO: isnt this int8_t in some other places?
    uint8_t value=*(engine->data+address);
    
    //Write value to stack
    engine->stack[engine->stack_index-1]=value;

    FORTH_NEXT
}

//W_FETCH
void prim_w_fetch(struct ForthEngine *engine)
{
    //Fetch argument
    int32_t address=engine->stack[engine->stack_index-1];

    //Mask address
    address&=engine->data_mask_16;
    
    //Read from address
    uint16_t value=*(uint16_t*)(engine->data+address);
    
    //Write value to stack
    engine->stack[engine->stack_index-1]=value;

    FORTH_NEXT
}

//QUIT
void prim_quit(struct ForthEngine *engine)
{
    engine->executing=false;
}

//ABS
void prim_abs(struct ForthEngine *engine)
{
    int32_t value=engine->stack[engine->stack_index-1];
    if (value<0) engine->stack[engine->stack_index-1]=-value;

    FORTH_NEXT
}

//ACCEPT
void prim_accept(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Call input routine if it exists
    if (engine->input!=NULL)
    {
        //Fetch arguments
        engine->stack_index--;
        uint32_t count=engine->stack[engine->stack_index];
        uint32_t address=engine->stack[engine->stack_index-1];
    
        //Mask address
        address&=engine->data_mask;
        uint32_t bytes_written=engine->input(address,(char *)engine->data,count,engine->data_mask);
        
        //Write result
        engine->stack[engine->stack_index-1]=bytes_written;
    }
    else
    {
        engine->stack_index--;
        engine->stack[engine->stack_index-1]=0;
    }

    FORTH_NEXT
}

//ALIGN
void prim_align(struct ForthEngine *engine)
{
    int32_t remainder=engine->data_index%FORTH_CELL_SIZE;
    if (remainder>0)
    {
        //Address is not aligned - round up
        engine->data_index=(engine->data_index+FORTH_CELL_SIZE-remainder)&engine->data_mask_32;
    }

    FORTH_NEXT
}

//ALIGNED
void prim_aligned(struct ForthEngine *engine)
{
    //Fetch address to align
    int32_t address=engine->stack[engine->stack_index-1];
    uint32_t remainder=address%FORTH_CELL_SIZE;
    if (remainder!=0)
    {
        //Address is not aligned - round up
        address+=FORTH_CELL_SIZE-remainder;
    }

    //Write address back even if aligned so always masked
    engine->stack[engine->stack_index-1]=(address&engine->data_mask_32);

    FORTH_NEXT
}

//ALLOT
void prim_allot(struct ForthEngine *engine)
{
    //Logging
    log_push(LOGGING_FORTH_ALLOT,"allot");
    log_text("data_index: %d\n",engine->data_index);

    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch amount of bytes to allot
    engine->stack_index--;
    int32_t allot_count=engine->stack[engine->stack_index];
    engine->data_index=(engine->data_index+allot_count)&(engine->data_mask);

    //Logging
    log_text("new data_index: %d\n",engine->data_index);
    log_pop();

    FORTH_NEXT
}

//AND
void prim_and(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    engine->stack[engine->stack_index-1]=arg1&arg2;

    FORTH_NEXT
}

//B_L
void prim_b_l(struct ForthEngine *engine)
{
    //Write value for space character
    engine->stack[engine->stack_index]=32;
    
    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//BOUNDS
void prim_bounds(struct ForthEngine *engine)
{
    //Fetch values from stack
    int32_t size=engine->stack[engine->stack_index-1];
    int32_t address=engine->stack[engine->stack_index-2];

    //Write values to stack
    engine->stack[engine->stack_index-1]=address;
    engine->stack[engine->stack_index-2]=(address+size)&engine->data_mask;

    FORTH_NEXT
}

//CELLS
void prim_cells(struct ForthEngine *engine)
{
    int32_t value=engine->stack[engine->stack_index-1];
    engine->stack[engine->stack_index-1]=value*FORTH_CELL_SIZE;

    FORTH_NEXT
}

//C_R
void prim_c_r(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
    {
        engine->print("\n");
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//DEPTH
void prim_depth(struct ForthEngine *engine)
{
    if (engine->stack_index>=FORTH_STACK_ELEMENTS)
    {
        //Overflow
        engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
        engine->executing=false;
        return;
    }

    //Write stack count
    engine->stack[engine->stack_index]=forth_stack_count(engine);
    
    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//DROP
void prim_drop(struct ForthEngine *engine)
{
    engine->stack_index--;

    FORTH_NEXT
}

//2DROP
void prim_two_drop(struct ForthEngine *engine)
{
    engine->stack_index-=2;

    FORTH_NEXT
}

//DUPE
void prim_dupe(struct ForthEngine *engine)
{
    //Write duplicated value
    engine->stack[engine->stack_index]=engine->stack[engine->stack_index-1];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//2DUPE
void prim_two_dupe(struct ForthEngine *engine)
{
    //Write duplicated value
    engine->stack[engine->stack_index]=engine->stack[engine->stack_index-2];
    engine->stack[engine->stack_index+1]=engine->stack[engine->stack_index-1];

    //Advance stack pointer
    engine->stack_index+=2;

    FORTH_NEXT
}

//EMIT
void prim_emit(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Update stack pointer
    engine->stack_index--;
    if (engine->print!=NULL)
    {
        //Output character
        char text_buffer[2];
        text_buffer[0]=engine->stack[engine->stack_index];
        text_buffer[1]=0;
        engine->print(text_buffer);

        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//EXECUTE
void prim_execute(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Update stack pointer
    engine->stack_index--;

    uint32_t word_ID=engine->stack[engine->stack_index];
    if (word_ID<(uint32_t)forth_primitives_len)
    {
        //TODO: checking body is enough now but recheck after all words added

        //ID on stack is primitive
        void (*body_func)(struct ForthEngine *engine)=forth_primitives[word_ID].body;
        if (body_func!=NULL)
        {
            //TODO: EXEC chain will take stack space! TCO?
            //Primitive has body - ok to execute
            body_func(engine);
        }
        else
        {
            //Error - no body present for primitive so only has immediate and/or compile behavior
            engine->error=FORTH_ENGINE_ERROR_EXECUTE_NO_BODY;
            engine->error_word=forth_primitives[word_ID].name;
            engine->executing=false;
        }
    }   
    else if (word_ID<forth_primitives_len+engine->word_count)
    {
        //ID on stack is secondary
        uint32_t secondary_id=word_ID-forth_primitives_len;

        //Same as prim_hidden_secondary - inlined for speed

        //Figure out if secondary is user-defined word or variable - slower but necessary to support redefining words
        struct ForthWordHeader *secondary=&engine->word_headers[secondary_id];
        if (secondary->type==FORTH_SECONDARY_UNDEFINED)
        {
            //Error - word referenced in word but never defined
            engine->error=FORTH_ENGINE_ERROR_UNDEFINED;
            engine->error_word=secondary->name;
            engine->executing=false;
        }
        else if ((secondary->type==FORTH_SECONDARY_CONSTANT)||(secondary->type==FORTH_SECONDARY_CREATE)||
                (secondary->type==FORTH_SECONDARY_VARIABLE))
        {
            //These are actually words that can be executed but faster to extract value and push here manually instead
            int32_t num=*(int32_t *)(secondary->address+1);
            
            //Push number to stack
            engine->stack[engine->stack_index]=num;
            engine->stack_index++;
        }
        else
        {
            //Push word return address to R-stack - faster to inline than call forth_rstack_push
            if (engine->rstack<engine->rstack_base)
            {
                //Out of R-stack memory - abort
                engine->error=FORTH_ENGINE_ERROR_RSTACK_FULL;
                engine->executing=false;
            }
            else
            {
                //Increase word index so tagged R-stack addresses can be linked to word they belong to
                engine->word_index++;

                //Push new values to R-stack
                engine->rstack->value=(uintptr_t)(engine->address)-(uintptr_t)(engine->word_bodies);
                engine->rstack->type=FORTH_RSTACK_RETURN;
                engine->rstack->index=engine->word_index;
                engine->rstack->locals_count=secondary->locals_count;

                //Make room for locals
                engine->locals_stack-=secondary->locals_count;
                if (engine->locals_stack<engine->locals_base)
                {
                    //Error - out of local stack memory. Abort.
                    engine->error=FORTH_ENGINE_ERROR_LOCAL_STACK_FULL;
                    engine->executing=false;
                }

                //Decrease R-stack pointer to next element
                engine->rstack--;

                //Set new execution address to address of secondary stored in word header list
                engine->address=secondary->address;

                //Account for interpreter advancing execution address
                engine->address--;
            }
        }
    }
    else
    {
        //Error - ID on stack is out of range
        text_uint32(word_ID,engine->error_num);
        engine->error=FORTH_ENGINE_ERROR_EXECUTE_ID;
        engine->executing=false;
    }

    FORTH_NEXT
}

//EXIT - Reuse existing code elsewhere
//Interpreting - prim_compile_only
//Compiling - prim_hidden_done

//FILL
void prim_fill(struct ForthEngine *engine)
{
    if (engine->stack_index<3)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch values from stack
    engine->stack_index--;
    int32_t character=engine->stack[engine->stack_index];
    engine->stack_index--;
    uint32_t count=engine->stack[engine->stack_index];
    engine->stack_index--;
    uint32_t address=engine->stack[engine->stack_index];

    if (count>0)
    {
        //Limit count so it loops through memory at most once
        if (count>=engine->data_size) count=engine->data_size;
        for (uint32_t i=0;i<count;i++)
        {
            //Write byte to masked address
            address&=engine->data_mask;
            *(engine->data+address)=character;
            address++;
        }
    }

    FORTH_NEXT
}

//FIND
//void prim_body_find(struct ForthEngine *engine){}
//int prim_immediate_find(struct ForthEngine *engine){}
//int prim_compile_find(struct ForthEngine *engine){}

//HERE
void prim_here(struct ForthEngine *engine)
{
    //Write stack count
    engine->stack[engine->stack_index]=engine->data_index;

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//I
void prim_i(struct ForthEngine *engine)
{
    //Push number to stack
    engine->stack[engine->stack_index]=engine->loop_i;
    engine->stack_index++;

    FORTH_NEXT
}

//INVERT
void prim_invert(struct ForthEngine *engine)
{
    int32_t value=engine->stack[engine->stack_index-1];
    engine->stack[engine->stack_index-1]=value^-1;

    FORTH_NEXT
}

//J
void prim_j(struct ForthEngine *engine)
{
    //Push number to stack
    engine->stack[engine->stack_index]=engine->loop_j;
    engine->stack_index++;

    FORTH_NEXT
}

//KEY
void prim_key(struct ForthEngine *engine)
{
    if (engine->stack_index==0)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch flag - true for blocking key input, false for non-blocking
    int32_t flag=engine->stack[engine->stack_index-1];
    if (engine->getkey==NULL)
    {
        //No getkey routine exists - return 0
        engine->stack[engine->stack_index-1]=0;
    }
    else
    {
        //Fetch key
        bool blocking=!(flag==0);
        int32_t key=engine->getkey(blocking);
        engine->stack[engine->stack_index-1]=key;

        //Update modifier output
        if (engine->update_modifiers!=NULL) engine->update_modifiers();
    }

    FORTH_NEXT
}

//L_SHIFT
void prim_l_shift(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    engine->stack[engine->stack_index-1]=arg1<<arg2;

    FORTH_NEXT
}

//MAX
void prim_max(struct ForthEngine *engine)
{
    
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    if (arg2>arg1)
    {
        engine->stack[engine->stack_index-1]=arg2;
    }
    else
    {
        //Larger value is already in place - nothing to do
    }

    FORTH_NEXT
}

//MIN
void prim_min(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    if (arg2<arg1)
    {
        //Write smaller value to stack
        engine->stack[engine->stack_index-1]=arg2;
    }
    else
    {
        //Smaller value is already in place - nothing to do
    }

    FORTH_NEXT
}

//MOD
void prim_mod(struct ForthEngine *engine)
{
    
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Prevent divide by zero
    if (arg2==0) arg2=1;
    
    //Write result
    engine->stack[engine->stack_index-1]=arg1%arg2;

    FORTH_NEXT
}

//MOVE
void prim_move(struct ForthEngine *engine)
{
    if (engine->stack_index<3)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch values from stack
    engine->stack_index--;
    uint32_t count=engine->stack[engine->stack_index];
    engine->stack_index--;
    uint32_t dest=engine->stack[engine->stack_index];
    engine->stack_index--;
    uint32_t source=engine->stack[engine->stack_index];

    //Limit count so copying loops through memory at most once
    if (count>=engine->data_size) count=engine->data_size;

    while(count>0)
    {
        //Mask source and destination addresses for wrapping
        dest&=engine->data_mask;
        source&=engine->data_mask;

        //Split up into multiple copies if either source or dest wraps during copying
        uint32_t dest_count,source_count;
        if (dest+count>engine->data_size) dest_count=engine->data_size-dest;
        else dest_count=count;
        if (source+count>engine->data_size) source_count=engine->data_size-source;
        else source_count=count;
       
        //Copy non-wrapping section
        uint32_t bytes_copied;
        if (dest_count<=source_count) bytes_copied=dest_count;
        else bytes_copied=source_count;
        memmove(engine->data+dest,engine->data+source,bytes_copied);

        //Advance for next iteration
        count-=bytes_copied;
        dest+=bytes_copied;
        source+=bytes_copied;
    }

    FORTH_NEXT
}

//NEGATE
void prim_negate(struct ForthEngine *engine)
{
    int32_t value=engine->stack[engine->stack_index-1];
    engine->stack[engine->stack_index-1]=-value;

    FORTH_NEXT
}

//OR
void prim_or(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    engine->stack[engine->stack_index-1]=arg1|arg2;

    FORTH_NEXT
}

//OVER
void prim_over(struct ForthEngine *engine)
{
    //Write duplicated value
    engine->stack[engine->stack_index]=engine->stack[engine->stack_index-2];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//2OVER
void prim_two_over(struct ForthEngine *engine)
{
    //Write duplicated value
    engine->stack[engine->stack_index]=engine->stack[engine->stack_index-4];
    engine->stack[engine->stack_index+1]=engine->stack[engine->stack_index-3];

    //Advance stack pointer
    engine->stack_index+=2;

    FORTH_NEXT
}

//PAGE
void prim_page(struct ForthEngine *engine)
{
    if (engine->clear_console!=NULL)
    {
        //Clear screen
        engine->clear_console();
        
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//ROTE
void prim_rote(struct ForthEngine *engine)
{
    //Fetch values from stack
    int32_t arg1=engine->stack[engine->stack_index-1];
    int32_t arg2=engine->stack[engine->stack_index-2];
    int32_t arg3=engine->stack[engine->stack_index-3];

    //Write values to stack
    engine->stack[engine->stack_index-1]=arg3;
    engine->stack[engine->stack_index-2]=arg1;
    engine->stack[engine->stack_index-3]=arg2;

    FORTH_NEXT
}

//MINUS_ROTE
void prim_minus_rote(struct ForthEngine *engine)
{
    //Fetch values from stack
    int32_t arg1=engine->stack[engine->stack_index-1];
    int32_t arg2=engine->stack[engine->stack_index-2];
    int32_t arg3=engine->stack[engine->stack_index-3];

    //Write values to stack
    engine->stack[engine->stack_index-1]=arg2;
    engine->stack[engine->stack_index-2]=arg3;
    engine->stack[engine->stack_index-3]=arg1;

    FORTH_NEXT
}

//R_SHIFT
void prim_r_shift(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    engine->stack[engine->stack_index-1]=arg1>>arg2;

    FORTH_NEXT
}

//SPACE
void prim_space(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
    {
        engine->print(" ");
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//SPACES
void prim_spaces(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch count
    engine->stack_index--;
    int32_t space_count=engine->stack[engine->stack_index];
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

    FORTH_NEXT
}

//SWAP
void prim_swap(struct ForthEngine *engine)
{
    //Fetch values from stack
    int32_t arg1=engine->stack[engine->stack_index-1];
    int32_t arg2=engine->stack[engine->stack_index-2];

    //Write values to stack
    engine->stack[engine->stack_index-1]=arg2;
    engine->stack[engine->stack_index-2]=arg1;

    FORTH_NEXT
}

//2SWAP
void prim_two_swap(struct ForthEngine *engine)
{
    //Fetch values from stack
    int32_t arg1=engine->stack[engine->stack_index-1];
    int32_t arg2=engine->stack[engine->stack_index-2];
    int32_t arg3=engine->stack[engine->stack_index-3];
    int32_t arg4=engine->stack[engine->stack_index-4];

    //Write values to stack
    engine->stack[engine->stack_index-1]=arg3;
    engine->stack[engine->stack_index-2]=arg4;
    engine->stack[engine->stack_index-3]=arg1;
    engine->stack[engine->stack_index-4]=arg2;

    FORTH_NEXT
}

//TYPE
void prim_type(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch arguments
    engine->stack_index--;
    uint32_t count=engine->stack[engine->stack_index];
    engine->stack_index--;
    uint32_t address=engine->stack[engine->stack_index];

    //Print characters if print function exists
    if (engine->print!=NULL)
    {
        //Limit count so it loops through memory at most once
        if (count>=engine->data_size) count=engine->data_size;
        char text_buffer[2];
        text_buffer[1]=0;
        for (uint32_t i=0;i<count;i++)
        {
            //Mask address
            address&=engine->data_mask;

            //Print out character
            text_buffer[0]=*(engine->data+address);
            engine->print(text_buffer);
            
            //Next byte
            address++;
        }
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//U_LESS_THAN
void prim_u_less_than(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    uint32_t arg2=engine->stack[engine->stack_index];
    uint32_t arg1=engine->stack[engine->stack_index-1];

    //Write result (note true is 1 in C but -1 in FORTH)
    engine->stack[engine->stack_index-1]=-(arg1<arg2);

    FORTH_NEXT
}

//U_GREATER_THAN
void prim_u_greater_than(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    uint32_t arg2=engine->stack[engine->stack_index];
    uint32_t arg1=engine->stack[engine->stack_index-1];

    //Write result (note true is 1 in C but -1 in FORTH)
    engine->stack[engine->stack_index-1]=-(arg1>arg2);

    FORTH_NEXT
}

//X_OR
void prim_x_or(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result
    engine->stack[engine->stack_index-1]=arg1^arg2;

    FORTH_NEXT
}

//DOT_R
void prim_dot_r(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch arguments
    engine->stack_index--;
    uint32_t spaces=engine->stack[engine->stack_index];
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];

    if (engine->print!=NULL)
    {
        //Convert number to text
        char text_buffer[TEXT_INT32_SIZE];
        text_int32(value,text_buffer);

        //Output leading spaces
        if (strlen(text_buffer)>spaces) spaces=0;
        else spaces-=strlen(text_buffer);
        if (spaces>FORTH_MAX_SPACES) spaces=FORTH_MAX_SPACES;
        for (uint32_t i=0;i<spaces;i++)
            engine->print(" ");

        //Output number
        engine->print(text_buffer);
        
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//U_DOT_R
void prim_u_dot_r(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch arguments
    engine->stack_index--;
    uint32_t spaces=engine->stack[engine->stack_index];
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];

    if (engine->print!=NULL)
    {
        //Convert number to text
        char text_buffer[TEXT_UINT32_SIZE];
        text_uint32(value,text_buffer);

        //Output leading spaces
        if (strlen(text_buffer)>spaces) spaces=0;
        else spaces-=strlen(text_buffer);
        if (spaces>FORTH_MAX_SPACES) spaces=FORTH_MAX_SPACES;
        for (uint32_t i=0;i<spaces;i++)
            engine->print(" ");

        //Output number
        engine->print(text_buffer);

        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//X_DOT_R
void prim_x_dot_r(struct ForthEngine *engine)
{
    if (engine->stack_index<2)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Fetch arguments
    engine->stack_index--;
    uint32_t spaces=engine->stack[engine->stack_index];
    engine->stack_index--;
    int32_t value=engine->stack[engine->stack_index];

    if (engine->print!=NULL)
    {
        //Convert number to text
        char text_buffer[TEXT_HEX32_SIZE];
        text_hex32(value,text_buffer);

        //Output leading spaces
        if (strlen(text_buffer)>spaces) spaces=0;
        else spaces-=strlen(text_buffer);
        if (spaces>FORTH_MAX_SPACES) spaces=FORTH_MAX_SPACES;
        for (uint32_t i=0;i<spaces;i++)
            engine->print(" ");

        //Output number
        engine->print(text_buffer);

        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//NOT_EQUALS
void prim_not_equals(struct ForthEngine *engine)
{
    //Fetch arguments
    engine->stack_index--;
    int32_t arg2=engine->stack[engine->stack_index];
    int32_t arg1=engine->stack[engine->stack_index-1];

    //Write result (note true is 1 in C but -1 in FORTH)
    engine->stack[engine->stack_index-1]=-(arg1!=arg2);

    FORTH_NEXT
}

//CASE
//void prim_body_case(struct ForthEngine *engine){}
//int prim_immediate_case(struct ForthEngine *engine){}
//int prim_compile_case(struct ForthEngine *engine){}

//FALSE
void prim_false(struct ForthEngine *engine)
{
    engine->stack[engine->stack_index]=FORTH_FALSE;
    engine->stack_index++;

    FORTH_NEXT
}

//NIP
void prim_nip(struct ForthEngine *engine)
{
    
    engine->stack_index--;
    engine->stack[engine->stack_index-1]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

//TRUE
void prim_true(struct ForthEngine *engine)
{
    engine->stack[engine->stack_index]=FORTH_FALSE;
    engine->stack_index++;

    FORTH_NEXT
}

//TUCK
void prim_tuck(struct ForthEngine *engine)
{
    //Fetch values from stack
    int32_t arg1=engine->stack[engine->stack_index-1];
    int32_t arg2=engine->stack[engine->stack_index-2];

    //Write values to stack
    engine->stack[engine->stack_index]=arg1;
    engine->stack[engine->stack_index-1]=arg2;
    engine->stack[engine->stack_index-2]=arg1;
    
    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//UNUSED
void prim_unused(struct ForthEngine *engine)
{
    if (engine->stack_index>=FORTH_STACK_ELEMENTS)
    {
        //Overflow
        engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
        engine->executing=false;
        return;
    }

    //Write memory amount left
    engine->stack[engine->stack_index]=engine->data_size-engine->data_index;

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//WITHIN
void prim_within(struct ForthEngine *engine)
{
    //Fetch values from stack
    engine->stack_index--;
    int32_t max=engine->stack[engine->stack_index];
    engine->stack_index--;
    int32_t min=engine->stack[engine->stack_index];
    int32_t value=engine->stack[engine->stack_index-1];
    //Write value to stack
    if ((value>=min)&&(value<=max)) engine->stack[engine->stack_index-1]=FORTH_TRUE;
    else engine->stack[engine->stack_index-1]=FORTH_FALSE;

    FORTH_NEXT
}

//DOT_S
void prim_dot_s(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
    {
        char text_buffer[TEXT_INT32_SIZE];
        int stack_count=forth_stack_count(engine);
        engine->print("<");
        text_int32(stack_count,text_buffer);
        engine->print(text_buffer);
        engine->print("> ");
        for (int32_t i=0;i<stack_count;i++)
        {
            text_int32(engine->stack[i],text_buffer);
            engine->print(text_buffer);
            engine->print(" ");
        }

        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }

    FORTH_NEXT
}

//QUESTION
void prim_question(struct ForthEngine *engine)
{
    //Update stack pointer
    engine->stack_index--;
    if (engine->print!=NULL)
    {
        //Read and mask address
        uint32_t address=(engine->stack[engine->stack_index])&engine->data_mask_32;

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

    FORTH_NEXT
}

//DUMP
void prim_dump(struct ForthEngine *engine)
{
    if (engine->print!=NULL)
    {
        //Fetch arguments
        uint32_t count=engine->stack[engine->stack_index-1];
        uint32_t address=engine->stack[engine->stack_index-2];
        
        //Fetch and print bytes
        bool newline=true;
        char byte_display[FORTH_DUMP_BYTES+1];
        uint32_t byte_index=0;
        int line_count=0;
        for (uint32_t i=0;i<count;i++)
        {
            //Mask address
            address&=engine->data_mask;
            if (newline)
            {
                //Print address
                engine->print("\n");
                char address_buffer[7]; //Six hex digits plus null terminator
                text_hex32_padded(address,address_buffer,6);
                engine->print(address_buffer);
                engine->print(": ");
            }
            
            //Print byte
            uint8_t byte=*(engine->data+address);
            char text_buffer[3];    //Two hex digits per byte plus null terminator
            text_hex32_padded(byte,text_buffer,2);
            engine->print(text_buffer);
            
            //Print characters for bytes
            byte_display[byte_index]=byte;
            byte_index++;
            if ((byte_index==FORTH_DUMP_BYTES)||(i==count-1))
            {
                //End of line reached or out of bytes
                byte_display[byte_index]=0;
                for (uint32_t j=0;j<byte_index;j++)
                {
                    //Replace unprintable characters with .
                    if ((byte_display[j]<CHAR_PRINTABLE_MIN)||((unsigned char)byte_display[j]>CHAR_PRINTABLE_MAX))
                    {
                        byte_display[j]='.';
                    }
                }
                
                //Print spaces if full line of bytes not printed
                for (uint32_t j=0;j<FORTH_DUMP_BYTES-byte_index;j++)
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
    engine->stack_index-=2;

    FORTH_NEXT
}

//SEE
//void prim_body_see(struct ForthEngine *engine){}
//int prim_immediate_see(struct ForthEngine *engine){}
//int prim_compile_see(struct ForthEngine *engine){}

//BYE
void prim_bye(struct ForthEngine *engine)
{
    engine->exit_program=true;
    engine->executing=false;

    FORTH_NEXT
}

//RESET
void prim_reset(struct ForthEngine *engine)
{
    //Reset Forth data stack
    engine->stack_index=0;

    FORTH_NEXT
}

//WALIGN
void prim_walign(struct ForthEngine *engine)
{
    //Round up to even address
    engine->data_index=(engine->data_index+(engine->data_index&1))&engine->data_mask_16;

    FORTH_NEXT
}

//WALIGNED
void prim_waligned(struct ForthEngine *engine)
{
    //Fetch address to align
    uint32_t address=engine->stack[engine->stack_index-1];

    //Round up to even address
    address+=address&1;
    
    //Write address back even if aligned so always masked
    engine->stack[engine->stack_index-1]=(address&engine->data_mask_16);

    FORTH_NEXT
}

//PRINTABLE
void prim_printable(struct ForthEngine *engine)
{
    //Fetch key to look up
    int32_t key=engine->stack[engine->stack_index-1];

    if (engine->printable!=NULL)
    {
        //Return printable character for key
        engine->stack[engine->stack_index-1]=engine->printable(key);
    }
    else
    {
        //No printable function - return 0
        engine->stack[engine->stack_index-1]=0;
    }

    FORTH_NEXT
}

//TODO: optimize
//ERASE
void prim_erase(struct ForthEngine *engine)
{
    //Fetch values from stack
    engine->stack_index--;
    uint32_t count=engine->stack[engine->stack_index];
    engine->stack_index--;
    uint32_t address=engine->stack[engine->stack_index];

    //Limit count so it loops through memory at most once
    if (count>=engine->data_size) count=engine->data_size;
    for (uint32_t i=0;i<count;i++)
    {
        //Write byte to masked address
        address&=engine->data_mask;
        *(engine->data+address)=0;
        address++;
    }

    FORTH_NEXT
}

//CXT
void prim_cxt(struct ForthEngine *engine)
{
    int32_t value=engine->stack[engine->stack_index-1];
    if (value&0x80) value|=0xFFFFFF00;
    else value&=0xFF;
    engine->stack[engine->stack_index-1]=value;

    FORTH_NEXT
}

//WXT
void prim_wxt(struct ForthEngine *engine)
{
    int32_t value=engine->stack[engine->stack_index-1];
    if (value&0x8000) value|=0xFFFF0000;
    else value&=0xFFFF;
    engine->stack[engine->stack_index-1]=value;

    FORTH_NEXT
}

//PERF
void prim_perf(struct ForthEngine *engine)
{
    if (engine->stack_index>=FORTH_STACK_ELEMENTS)
    {
        //Overflow
        engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
        engine->executing=false;
        return;
    }

    //Write performance counter
    engine->stack[engine->stack_index]=engine->perf_value;

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//SIZE
void prim_size(struct ForthEngine *engine)
{
    //Write size of Forth data memory
    engine->stack[engine->stack_index]=engine->data_size;

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//Globals
//=======
//TODO: alphabetic order
const struct ForthPrimitive forth_primitives[]=
{
    {"!",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_store,             false, 2, 0},
    {"C!",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_c_store,           false, 2, 0},
    {"W!",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_w_store,           false, 2, 0},
    {"'",1,             FORTH_ACTION_TICK,              FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"(",1,             FORTH_ACTION_PAREN,             FORTH_ACTION_PAREN,             NULL,                   true},
    {"*",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_star,              false, 2, 1},
    {"*/",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_star_slash,        false, 3, 1},
    {"*/MOD",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_star_slash_mod,    false, 3, 2},
    {"+",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_plus,              false, 2, 1},
    {"+LOOP",5,         FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_PLUS_LOOP,         NULL,                   true},
    {",",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_comma,             false, 1, 0},
    {"C,",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_c_comma,           false, 1, 0},
    {"W,",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_w_comma,           false, 1, 0},
    {"-",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_minus,             false, 2, 1},
    {"\\",1,            FORTH_ACTION_COMMENT,           FORTH_ACTION_COMMENT,           NULL,                   true},
    {".",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_dot,               true},
    {"U.",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_u_dot,             true},
    {"X.",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_x_dot,             true},
    {".\"",2,           FORTH_ACTION_DOT_QUOTE,         FORTH_ACTION_DOT_QUOTE,         NULL,                   true},
    {"/",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_slash,             false, 2, 1},
    {"/MOD",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_slash_mod,         false, 2, 2},
    {":",1,             FORTH_ACTION_COLON,             FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {";",1,             FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_SEMICOLON,         NULL,                   true},
    {"<",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_less_than,         false, 2, 1},
    {"=",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_equals,            false, 2, 1},
    {">",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_greater_than,      false, 2, 1},
    {">NUMBER",7,       FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_to_number,         true},
    {">NUM",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_to_number,         true},
    {"NUMBER>",7,       FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_number_to,         true},
    {"NUM>",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_number_to,         true},
    {">HEX",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_to_hex,            true},
    {"HEX>",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hex_to,            true},
    {"?DUP",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_question_dupe,     true},
    {"@",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_fetch,             false, 1, 1},
    {"C@",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_c_fetch,           false, 1, 1},
    {"W@",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_w_fetch,           false, 1, 1},
    {"QUIT",4,          FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_NONE,              prim_quit,              true},
    {"ABS",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_abs,               false, 1, 1},
    {"ACCEPT",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_accept,            true},
    {"ALIGN",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_align,             false, 0, 0},
    {"ALIGNED",7,       FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_aligned ,          false, 1, 1},
    {"ALLOT",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_allot,             true},
    {"AND",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_and,               false, 2, 1},
    {"BEGIN",5,         FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_BEGIN,             NULL,                   true},
    {"BL",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_b_l,               false, 0, 1},
    {"BOUNDS",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_bounds,            false, 2, 2},
    {"CELLS",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_cells,             false, 1, 1},
    {"CHAR",4,          FORTH_ACTION_CHAR,              FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"CONSTANT",8,      FORTH_ACTION_CONSTANT,          FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"CONST",5,         FORTH_ACTION_CONSTANT,          FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"CR",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_c_r,               true},
    {"CREATE",6,        FORTH_ACTION_CREATE,            FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"DEPTH",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_depth,             true},
    {"DO",2,            FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_DO,                NULL,                   true},
    {"DROP",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_drop,              false, 1, 0},
    {"2DROP",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_two_drop,          false, 2, 0},
    {"DUP",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_dupe,              false, 1, 2},
    {"2DUP",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_two_dupe,          false, 2, 4},
    {"ELSE",4,          FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_ELSE,              NULL,                   true},
    {"EMIT",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_emit,              true},
    {"ERASE",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_erase,             true},
    {"EXECUTE",7,       FORTH_ACTION_EXECUTE,           FORTH_ACTION_NONE,              prim_execute,           true},
    {"EXEC",4,          FORTH_ACTION_EXECUTE,           FORTH_ACTION_NONE,              prim_execute,           true},
    {"EXIT",4,          FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_NONE,              prim_hidden_done,       true},
    {"FILL",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_fill,              true},
    {"HERE",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_here,              false, 0, 1},
    {"I",1,             FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_NONE,              prim_i,                 false, 0, 1},
    {"IF",2,            FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_IF,                NULL,                   true},
    {"INVERT",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_invert,            false, 1, 1},
    {"J",1,             FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_NONE,              prim_j,                 false, 0, 1},
    {"KEY",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_key,               true},
    {"LEAVE",5,         FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_LEAVE,             NULL,                   true},
    {"LITERAL",7,       FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_LITERAL,           NULL,                   true},
    {"LIT",3,           FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_LITERAL,           NULL,                   true},
    {"LOOP",4,          FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_LOOP,              NULL,                   true},
    {"LSHIFT",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_l_shift,           false, 2, 1},
    {"MAX",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_max,               false, 2, 1},
    {"MIN",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_min,               false, 2, 1},
    {"MOD",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_mod,               false, 2, 1},
    {"MOVE",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_move,              true},
    {"NEGATE",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_negate,            false, 1, 1},
    {"OR",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_or,                false, 2, 1},
    {"OVER",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_over,              false, 2, 3},
    {"2OVER",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_two_over,          false, 4, 6},
    {"PAGE",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_page,              true},
    {"REPEAT",6,        FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_REPEAT,            NULL,                   true},
    {"ROT",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_rote,              false, 3, 3},
    {"-ROT",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_minus_rote,        false, 3, 3},
    {"RSHIFT",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_r_shift,           false, 2, 1},
    {"S\"",2,           FORTH_ACTION_S_QUOTE,           FORTH_ACTION_S_QUOTE,           NULL,                   true},
    {"SPACE",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_space,             true},
    {"SPACES",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_spaces,            true},
    {"SWAP",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_swap,              false, 2, 2},
    {"2SWAP",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_two_swap,          false, 4, 4},
    {"THEN",4,          FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_THEN,              NULL,                   true},
    {"TYPE",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_type,              true},
    {"U<",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_u_less_than,       false, 2, 1},
    {"U>",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_u_greater_than,    false, 2, 1},
    {"UNTIL",5,         FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_UNTIL,             NULL,                   true},
    {"VARIABLE",8,      FORTH_ACTION_VARIABLE,          FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"VAR",3,           FORTH_ACTION_VARIABLE,          FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"WHILE",5,         FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_WHILE,             NULL,                   true},
    {"XOR",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_x_or,              false, 2, 1},
    {"[",1,             FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_LEFT_BRACKET,      NULL,                   true},
    {"]",1,             FORTH_ACTION_RIGHT_BRACKET,     FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"[']",3,           FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_BRACKET_TICK,      NULL,                   true},
    {"[CHAR]",6,        FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_BRACKET_CHAR,      NULL,                   true},
    {".R",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_dot_r,             true},
    {"U.R",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_u_dot_r,           true},
    {"X.R",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_x_dot_r,           true},
    {"<>",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_not_equals,        false, 2, 1},
    {"AGAIN",5,         FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_AGAIN,             NULL,                   true},
    //{"CASE",4,prim_immediate_case,prim_compile_case,prim_case},
    //{"ENDCASE",7,prim_immediate_endcase,prim_compile_endcase,prim_endcase},
    //{"OF",2,prim_immediate_of,prim_compile_of,prim_of},
    //{"ENDOF",5,prim_immediate_endof,prim_compile_endof,prim_endof},
    {"FALSE",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_false,             false, 0, 1},
    {"NIP",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_nip,               false, 2, 1},
    {"S\\\"",3,         FORTH_ACTION_S_BACKSLASH_QUOTE, FORTH_ACTION_S_BACKSLASH_QUOTE, NULL,                   true},
    {"TRUE",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_true,              false, 0, 1},
    {"TUCK",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_tuck,              false, 2, 3},
    {"UNUSED",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_unused,            true},
    {"WITHIN",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_within,            false, 3, 1},
    {".S",2,            FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_dot_s,             true},
    {"?",1,             FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_question,          true},
    {"DUMP",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_dump,              true},
    //{"SEE",3,prim_immediate_see,prim_compile_see,prim_body_see,prim_optimize_see},
    {"WORDS",5,         FORTH_ACTION_WORDS,             FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"WORDSIZE",8,      FORTH_ACTION_WORDSIZE,          FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"BYE",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_bye,               true},
    {"{",1,             FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_LOCALS,            NULL,                   true},
    {"0{",2,            FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_LOCALS_0,          NULL,                   true},
    {"TO",2,            FORTH_ACTION_COMPILE_ONLY,      FORTH_ACTION_TO,                NULL,                   false, 1, 0},
    
    //Words from here are not standard forth
    {"RESET",5,         FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_reset,             true},
    {"WALIGN",6,        FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_walign,            false, 0, 0},
    {"WALIGNED",8,      FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_waligned,          false, 1, 1},
    {"PRINTABLE",9,     FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_printable,         false, 1, 1},
    {"CXT",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_cxt,               false, 1, 1},
    {"WXT",3,           FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_wxt,               false, 1, 1},
    {"PRIMITIVES",10,   FORTH_ACTION_PRIMITIVES,        FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"SECONDARIES",11,  FORTH_ACTION_SECONDARIES,       FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"UNDEFINED",9,     FORTH_ACTION_UNDEFINED,         FORTH_ACTION_INTERPRET_ONLY,    NULL,                   true},
    {"PERF",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_perf,              true},
    {"SIZE",4,          FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_size,              false, 0, 1},
    {"RESIZE",6,        FORTH_ACTION_RESIZE,            FORTH_ACTION_INTERPRET_ONLY,    NULL},

    //Hidden words - store here to access underflow and overflow information
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_do,         true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_done,       true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_dot_quote,  true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_if,         true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_jump,       true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_leave,      true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_loop,       true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_plus_loop,  true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_push,       false, 0, 1},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_s_quote,    true},
    {"",0,              FORTH_ACTION_NONE,              FORTH_ACTION_NONE,              prim_hidden_secondary,  true},
    //TODO: add locals


    //Word browser showing source or disassembly of all words
    //DEBUG that steps through word
        //ON should also go to debugger
        //BREAKPOINT would be good
        //shouldnt need extra debug info unless compiling to machine code
    //INCLUDE
    //help
        //with word and without
        //good to have whole different screen if without
            //list of all words with explanation and example of using at console
            //How do I... or FAQ
                //Lots of answers about how this Forth is different
            //C equivalency section
        //ALL remapped keys
    //COLD or equivalent
        //menu option?
        //RESET?

    //FIND ??
        //Note commented out definition!
    //cleave ??
    //search ??
    //:NONAME
    //SMUDGE
    //disasm - just see? edit?
        //better to have one name for both prim and secondaries
        //objdump -t shows function lengths
};

//Can't determine length of primitives array using sizeof in other files, so calculate here
const int forth_primitives_len=(int)(ARRAY_LEN(forth_primitives));

