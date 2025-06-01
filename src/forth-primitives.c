#include <string.h>

#include "compatibility.h"
#include "forth-primitives.h"
#include "logging.h"
#include "macros.h"
#include "text.h"


//Internal primitives - not visible to user
//=========================================

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
    uint32_t ptr_len=sizeof(void(*)(struct ForthEngine *engine));
    text+=(ptr_len-(uintptr_t)text%(ptr_len))%ptr_len;
    engine->address=((void (**)(struct ForthEngine *engine))text)-1;

    //Logging
    log_text("ptr_len: %u\n",ptr_len);
    log_text("new text: %p\n",text);
    log_text("new engine->address: %p\n",engine->address);

    //Logging
    log_pop();
}

//TODO: same for other primitives? replace with 0BRANCH?
//Test value on stack and jump if not 0
void prim_hidden_if(struct ForthEngine *engine)
{
    //Fetch value from stack to test
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    int32_t test_value=*engine->stack;

    //Skip to ELSE or THEN if stack value not true
    if (test_value==0)
    {
        //Jump taken - fetch offset which is stored after pointer to current word
        uint32_t offset=*(uint32_t *)(engine->address+1);
        engine->address=(void (**)(struct ForthEngine *))((char *)engine->address+offset);
    }
    else
    {
        //Jump not taken - increment thread pointer to account for offset stored after primitive
        engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);
    }
}

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

//Write characters to data memory
void prim_hidden_s_quote(struct ForthEngine *engine)
{
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
    uint32_t ptr_len=sizeof(void(*)(struct ForthEngine *engine));
    text+=(ptr_len-(uintptr_t)text%(ptr_len))%ptr_len;
    engine->address=((void (**)(struct ForthEngine *engine))text)-1;

    //Logging
    log_text("ptr_len: %u\n",ptr_len);
    log_text("new text: %p\n",text);
    log_text("new engine->address: %p\n",engine->address);

    //Write return values to stack
    *engine->stack=address;
    uintptr_t lower;
    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    *engine->stack=quote_length;
    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);

    //Logging
    log_pop();
}

//Call secondary which may be user-defined word or variable
void prim_hidden_secondary(struct ForthEngine *engine)
{
    //Fetch index of word header in header list. Index is after pointer to current word.
    uint32_t index=*(uint32_t *)(engine->address+1);

    //Increment thread pointer to account for fetched offset
    engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);

    //Figure out if secondary is user-defined word or variable - slower but necessary to support redefining words
    struct ForthWordHeader *secondary=&engine->word_headers[index];

    //TODO: update function pointer when secondary is redefined? would eliminate if here but not sure if actually faster
    if (secondary->type==FORTH_SECONDARY_UNDEFINED)
    {
        //Error - word referenced in word but never defined
        engine->error=FORTH_ENGINE_ERROR_UNDEFINED;
        engine->error_word=secondary->name;
        engine->executing=false;
    }
    else
    {
        //Increase word index so tagged R-stack addresses can be linked to word they belong to
        engine->word_index++;

        //Push current thread pointer address to R-stack
        forth_rstack_push((uintptr_t)(engine->address)-(uintptr_t)(engine->word_bodies),
                            FORTH_RSTACK_RETURN,engine->word_index,engine);

        //TODO: forth_rstack_push may set executing to false. any problem with code below in that case?

        //Set new execution address to address of secondary stored in word header list
        engine->address=secondary->address;

        //Account for interpreter advancing execution address
        engine->address--;
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

//TICK
int prim_immediate_tick(UNUSED(struct ForthEngine *engine))
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_TICK;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_tick(UNUSED(struct ForthEngine *engine))
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

//PLUS_LOOP
//void prim_body_plus_loop(struct ForthEngine *engine){}
//int prim_immediate_plus_loop(struct ForthEngine *engine){}
//int prim_compile_plus_loop(struct ForthEngine *engine){}

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

//BACKSLASH
int prim_immediate_backslash(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_COMMENT;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_backslash(struct ForthEngine *engine)
{
    //Same behavior as immediate
    return prim_immediate_backslash(engine);
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

//U_DOT
void prim_body_u_dot(struct ForthEngine *engine)
{
    //Update stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    if (engine->print!=NULL)
    {
        //Output number
        char text_buffer[TEXT_UINT32_SIZE];
        text_uint32(*engine->stack,text_buffer);
        engine->print(text_buffer);
        //Output space
        engine->print(" ");
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//X_DOT
void prim_body_x_dot(struct ForthEngine *engine)
{
    //Update stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
    if (engine->print!=NULL)
    {
        //Output number
        char text_buffer[TEXT_HEX32_SIZE];
        text_hex32(*engine->stack,text_buffer);
        engine->print(text_buffer);
        //Output space
        engine->print(" ");
        //Update screen
        if (engine->update_screen!=NULL) engine->update_screen();
    }
}

//DOT_QUOTE
int prim_immediate_dot_quote(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_DOT_QUOTE;
    return FORTH_ENGINE_ERROR_NONE;
}

int prim_compile_dot_quote(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_DOT_QUOTE;
    return FORTH_ENGINE_ERROR_NONE;
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

//COLON
int prim_immediate_colon(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_COLON;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_colon(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//SEMICOLON
int prim_immediate_semicolon(UNUSED(struct ForthEngine *engine))
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

//TO_NUMBER - Note differs from >NUMBER in standard!
//(c-addr1 u1 - s2 c-addr2 u2) - no doubles or scratch space
void prim_body_to_number(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t count=*(uint32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    //Limit count so it loops through memory at most once
    if (count>=engine->data_size) count=engine->data_size;
    //Loop through characters
    int32_t result=0;
    bool negative=false;
    uint32_t unconverted_count=count;
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

//QUIT
//void prim_body_quit(struct ForthEngine *engine){}
//int prim_immediate_quit(struct ForthEngine *engine){}
//int prim_compile_quit(struct ForthEngine *engine){}

//ABS
void prim_body_abs(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    if (value<0) *(int32_t*)((engine->stack_base)|lower)=-value;
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
        int32_t bytes_written=engine->input(address,(char *)engine->data,count,engine->data_mask);
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

//BEGIN
//void prim_body_begin(struct ForthEngine *engine){}
//int prim_immediate_begin(struct ForthEngine *engine){}
//int prim_compile_begin(struct ForthEngine *engine){}

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
int prim_compile_char(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//CONSTANT
int prim_immediate_constant(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_CONSTANT;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_constant(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
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

//CONSTANT
int prim_immediate_create(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_CREATE;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_create(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
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
//void prim_body_do(struct ForthEngine *engine){}
//int prim_immediate_do(struct ForthEngine *engine){}
//int prim_compile_do(struct ForthEngine *engine){}

//DROP
void prim_body_drop(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
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

//ELSE
//void prim_body_else(struct ForthEngine *engine){}
//int prim_immediate_else(struct ForthEngine *engine){}
//int prim_compile_else(struct ForthEngine *engine){}

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
//void prim_body_exit(struct ForthEngine *engine){}
//int prim_immediate_exit(struct ForthEngine *engine){}
//int prim_compile_exit(struct ForthEngine *engine){}

//FILL
void prim_body_fill(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch values from stack
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t character=*(int32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    uint32_t count=*(uint32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
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
    //Update stack pointer
    lower=((uintptr_t)(engine->stack+3))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//FIND
//void prim_body_find(struct ForthEngine *engine){}
//int prim_immediate_find(struct ForthEngine *engine){}
//int prim_compile_find(struct ForthEngine *engine){}

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
//void prim_body_i(struct ForthEngine *engine){}
//int prim_immediate_i(struct ForthEngine *engine){}
//int prim_compile_i(struct ForthEngine *engine){}

//IF
int prim_immediate_if(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_COMPILE_ONLY;
}

int prim_compile_if(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_IF;
    return FORTH_ENGINE_ERROR_NONE;
}

//IMMEDIATE
//void prim_body_immediate(struct ForthEngine *engine){}
//int prim_immediate_immediate(struct ForthEngine *engine){}
//int prim_compile_immediate(struct ForthEngine *engine){}

//INVERT
void prim_body_invert(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    *(int32_t*)((engine->stack_base)|lower)=value^-1;
}

//J
//void prim_body_j(struct ForthEngine *engine){}
//int prim_immediate_j(struct ForthEngine *engine){}
//int prim_compile_j(struct ForthEngine *engine){}

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
///void prim_body_leave(struct ForthEngine *engine){}
//int prim_immediate_leave(struct ForthEngine *engine){}
//int prim_compile_leave(struct ForthEngine *engine){}

//LITERAL
int prim_immediate_literal(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_COMPILE_ONLY;
}

int prim_compile_literal(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_LITERAL;
    return FORTH_ENGINE_ERROR_NONE;
}

//LOOP
//void prim_body_loop(struct ForthEngine *engine){}
//int prim_immediate_loop(struct ForthEngine *engine){}
//int prim_compile_loop(struct ForthEngine *engine){}

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
    *(int32_t*)((engine->stack_base)|lower)=arg1<<arg2;
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

//MOVE
//void prim_body_move(struct ForthEngine *engine){}
//int prim_immediate_move(struct ForthEngine *engine){}
//int prim_compile_move(struct ForthEngine *engine){}

//NEGATE
void prim_body_negate(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    *(int32_t*)((engine->stack_base)|lower)=-value;
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
//void prim_body_repeat(struct ForthEngine *engine){}
//int prim_immediate_repeat(struct ForthEngine *engine){}
//int prim_compile_repeat(struct ForthEngine *engine){}

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
    *(int32_t*)((engine->stack_base)|lower)=arg1>>arg2;
}

//S_QUOTE
int prim_immediate_s_quote(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_S_QUOTE;
    return FORTH_ENGINE_ERROR_NONE;
}

int prim_compile_s_quote(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_S_QUOTE;
    return FORTH_ENGINE_ERROR_NONE;
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
//void prim_body_state(struct ForthEngine *engine){}
//int prim_immediate_state(struct ForthEngine *engine){}
//int prim_compile_state(struct ForthEngine *engine){}

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

//THEN
int prim_immediate_then(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_COMPILE_ONLY;
}

int prim_compile_then(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_THEN;
    return FORTH_ENGINE_ERROR_NONE;
}
//TYPE
void prim_body_type(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t count=*(uint32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
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
    uint32_t arg1=*(uint32_t*)((engine->stack_base)|lower);
    uint32_t arg2=*engine->stack;
    //Write result (note true is 1 in C but -1 in FORTH)
    *(int32_t*)((engine->stack_base)|lower)=-(arg1<arg2);
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
    uint32_t arg1=*(uint32_t*)((engine->stack_base)|lower);
    uint32_t arg2=*engine->stack;
    //Write result (note true is 1 in C but -1 in FORTH)
    *(int32_t*)((engine->stack_base)|lower)=-(arg1>arg2);
}

//UNTIL
//void prim_body_until(struct ForthEngine *engine){}
//int prim_immediate_until(struct ForthEngine *engine){}
//int prim_compile_until(struct ForthEngine *engine){}

//VARIABLE
int prim_immediate_variable(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_VARIABLE;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_variable(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//WHILE
//void prim_body_while(struct ForthEngine *engine){}
//int prim_immediate_while(struct ForthEngine *engine){}
//int prim_compile_while(struct ForthEngine *engine){}

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

//LEFT_BRACKET
int prim_immediate_left_bracket(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_COMPILE_ONLY;
}

int prim_compile_left_bracket(struct ForthEngine *engine)
{
    engine->state=FORTH_STATE_INTERPRET;
    engine->in_bracket=true;
    return FORTH_ENGINE_ERROR_NONE;
}

//RIGHT_BRACKET
int prim_immediate_right_bracket(struct ForthEngine *engine)
{
    if (engine->in_bracket==false) 
    {
        //No matching opening [
        return FORTH_ENGINE_ERROR_RIGHT_BRACKET;
    }
    else
    {
        engine->state=FORTH_STATE_COMPILE;
        return FORTH_ENGINE_ERROR_NONE;
    }
}
int prim_compile_right_bracket(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//BRACKET_TICK
int prim_compile_bracket_tick(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_BRACKET_TICK;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_immediate_bracket_tick(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_COMPILE_ONLY;
}

//BRACKET_CHAR
int prim_immediate_bracket_char(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_COMPILE_ONLY;
}
int prim_compile_bracket_char(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_BRACKET_CHAR;
    return FORTH_ENGINE_ERROR_NONE;
}

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
        for (uint32_t i=0;i<spaces;i++)
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

//U_DOT_R
void prim_body_u_dot_r(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t spaces=*(uint32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    uint32_t value=*(uint32_t*)((engine->stack_base)|lower);

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

    //Update stack pointer
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
}

//X_DOT_R
void prim_body_x_dot_r(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Fetch arguments
    lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    uint32_t spaces=*(uint32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    uint32_t value=*(uint32_t*)((engine->stack_base)|lower);

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

//AGAIN
//void prim_body_again(struct ForthEngine *engine){}
//int prim_immediate_again(struct ForthEngine *engine){}
//int prim_compile_again(struct ForthEngine *engine){}

//CASE
//void prim_body_case(struct ForthEngine *engine){}
//int prim_immediate_case(struct ForthEngine *engine){}
//int prim_compile_case(struct ForthEngine *engine){}

//FALSE
void prim_body_false(struct ForthEngine *engine)
{
    //Write value for space character
    *engine->stack=FORTH_FALSE;
    //Advance stack pointer
    uintptr_t lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
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

//PICK
//void prim_body_pick(struct ForthEngine *engine){}
//int prim_immediate_pick(struct ForthEngine *engine){}
//int prim_compile_pick(struct ForthEngine *engine){}

//ROLL
//void prim_body_roll(struct ForthEngine *engine){}
//int prim_immediate_roll(struct ForthEngine *engine){}
//int prim_compile_roll(struct ForthEngine *engine){}

//S_BACKSLASH_QUOTE
int prim_immediate_s_backslash_quote(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_S_BACKSLASH_QUOTE;
    return FORTH_ENGINE_ERROR_NONE;
}

int prim_compile_s_backslash_quote(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_S_BACKSLASH_QUOTE;
    return FORTH_ENGINE_ERROR_NONE;
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

//UNUSED
void prim_body_unused(struct ForthEngine *engine)
{
    uintptr_t lower;
    //Write memory amount left
    *engine->stack=engine->data_size-engine->data_index;
    //Advance stack pointer
    lower=((uintptr_t)(engine->stack-1))&FORTH_STACK_MASK;
    engine->stack=(int32_t*)((engine->stack_base)|lower);
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
                for (int32_t j=0;j<byte_index;j++)
                {
                    //Replace unprintable characters with .
                    if ((byte_display[j]<CHAR_PRINTABLE_MIN)||((unsigned char)byte_display[j]>CHAR_PRINTABLE_MAX))
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
//void prim_body_see(struct ForthEngine *engine){}
//int prim_immediate_see(struct ForthEngine *engine){}
//int prim_compile_see(struct ForthEngine *engine){}

//WORDS
int prim_immediate_words(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_WORDS;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_words(UNUSED(struct ForthEngine *engine))
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
//void prim_body_compare(struct ForthEngine *engine){}
//int prim_immediate_compare(struct ForthEngine *engine){}
//int prim_compile_compare(struct ForthEngine *engine){}

//RESET
void prim_body_reset(struct ForthEngine *engine)
{
    //Reset Forth data stack
    engine->stack=(int32_t*)(engine->stack_base+(engine->stack_count-1)*FORTH_CELL_SIZE);
}

//WALIGN
void prim_body_walign(struct ForthEngine *engine)
{
    //Round up to even address
    engine->data_index=(engine->data_index+(engine->data_index&1))&engine->data_mask_16;
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
    uint32_t count=*(uint32_t*)((engine->stack_base)|lower);
    lower=((uintptr_t)(engine->stack+2))&FORTH_STACK_MASK;
    int32_t address=*(int32_t*)((engine->stack_base)|lower);
    if (count>0)
    {
        //Limit count so it loops through memory at most once
        if (count>=engine->data_size) count=engine->data_size;
        for (uint32_t i=0;i<count;i++)
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

//CXT
void prim_body_cxt(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    if (value&0x80) value|=0xFFFFFF00;
    else value&=0xFF;
    *(int32_t*)((engine->stack_base)|lower)=value;
}

//WXT
void prim_body_wxt(struct ForthEngine *engine)
{
    uintptr_t lower=((uintptr_t)(engine->stack+1))&FORTH_STACK_MASK;
    int32_t value=*(int32_t*)((engine->stack_base)|lower);
    if (value&0x8000) value|=0xFFFF0000;
    else value&=0xFFFF;
    *(int32_t*)((engine->stack_base)|lower)=value;
}

//PRIMITIVES
int prim_immediate_primitives(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_PRIMITIVES;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_primitives(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//SECONDARIES
int prim_immediate_secondaries(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_SECONDARIES;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_secondaries(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//UNDEFINED
int prim_immediate_undefined(struct ForthEngine *engine)
{
    //Request outer interpreter perform function so no platform specific code in this file
    engine->word_action=FORTH_ACTION_UNDEFINED;
    return FORTH_ENGINE_ERROR_NONE;
}
int prim_compile_undefined(UNUSED(struct ForthEngine *engine))
{
    return FORTH_ENGINE_ERROR_INTERPRET_ONLY;
}

//Globals
//=======
const struct ForthPrimitive forth_primitives[]=
{
    {"!",1,NULL,NULL,&prim_body_store},
    {"C!",2,NULL,NULL,&prim_body_c_store},
    {"W!",2,NULL,NULL,&prim_body_w_store},
    {"'",1,&prim_immediate_tick,&prim_compile_tick,NULL},
    {"(",1,&prim_immediate_paren,&prim_compile_paren,NULL},
    {"*",1,NULL,NULL,&prim_body_star},
    {"*/",2,NULL,NULL,&prim_body_star_slash},
    {"*/MOD",5,NULL,NULL,&prim_body_star_slash_mod},
    {"+",1,NULL,NULL,&prim_body_plus},
    //{"+LOOP",5,&prim_immediate_plus_loop,&prim_compile_plus_loop,&prim_body_plus_loop},
    {",",1,NULL,NULL,&prim_body_comma},
    {"C,",2,NULL,NULL,&prim_body_c_comma},
    {"W,",2,NULL,NULL,&prim_body_w_comma},
    {"-",1,NULL,NULL,&prim_body_minus},
    {"\\",1,&prim_immediate_backslash,&prim_compile_backslash,NULL},
    {".",1,NULL,NULL,&prim_body_dot},
    {"U.",2,NULL,NULL,&prim_body_u_dot},
    {"X.",2,NULL,NULL,&prim_body_x_dot},
    {".\"",2,&prim_immediate_dot_quote,&prim_compile_dot_quote,NULL},
    {"/",1,NULL,NULL,&prim_body_slash},
    {"/MOD",4,NULL,NULL,&prim_body_slash_mod},
    {":",1,&prim_immediate_colon,&prim_compile_colon,NULL},
    {";",1,&prim_immediate_semicolon,&prim_compile_semicolon,NULL},
    {"<",1,NULL,NULL,&prim_body_less_than},
    {"=",1,NULL,NULL,&prim_body_equals},
    {">",1,NULL,NULL,&prim_body_greater_than},
    {">NUMBER",7,NULL,NULL,&prim_body_to_number},
    {">NUM",4,NULL,NULL,&prim_body_to_number},
    {"?DUP",4,NULL,NULL,&prim_body_question_dupe},
    {"@",1,NULL,NULL,&prim_body_fetch},
    {"C@",2,NULL,NULL,&prim_body_c_fetch},
    {"W@",2,NULL,NULL,&prim_body_w_fetch},
    //{"QUIT",4,&prim_immediate_quit,&prim_compile_quit,&prim_body_quit},
    {"ABS",3,NULL,NULL,&prim_body_abs},
    {"ACCEPT",6,NULL,NULL,&prim_body_accept},
    {"ALIGN",5,NULL,NULL,&prim_body_align},
    {"ALIGNED",7,NULL,NULL,&prim_body_aligned},
    {"ALLOT",5,NULL,NULL,&prim_body_allot},
    {"AND",3,NULL,NULL,&prim_body_and},
    //{"BEGIN",5,&prim_immediate_begin,&prim_compile_begin,&prim_body_begin},
    {"BL",2,NULL,NULL,&prim_body_b_l},
    {"BOUNDS",6,NULL,NULL,&prim_body_bounds},
    {"CELLS",5,NULL,NULL,&prim_body_cells},
    {"CHAR",4,&prim_immediate_char,&prim_compile_char,NULL},
    {"CONSTANT",8,&prim_immediate_constant,&prim_compile_constant,NULL},
    {"CONST",5,&prim_immediate_constant,&prim_compile_constant,NULL},
    {"CR",2,NULL,NULL,&prim_body_c_r},
    {"CREATE",6,&prim_immediate_create,&prim_compile_create,NULL},
    {"DEPTH",5,NULL,NULL,&prim_body_depth},
    //{"DO",2,&prim_immediate_do,&prim_compile_do,&prim_body_do},
    {"DROP",4,NULL,NULL,&prim_body_drop},
    {"DUP",3,NULL,NULL,&prim_body_dupe},
    //{"ELSE",4,&prim_immediate_else,&prim_compile_else,&prim_body_else},
    {"EMIT",4,NULL,NULL,&prim_body_emit},
    {"ERASE",5,NULL,NULL,&prim_body_erase},
    //{"EXIT",4,&prim_immediate_exit,&prim_compile_exit,&prim_body_exit},
    {"FILL",4,NULL,NULL,&prim_body_fill},
    {"HERE",4,NULL,NULL,&prim_body_here},
    //{"I",1,&prim_immediate_i,&prim_compile_i,&prim_body_i},
    {"IF",2,&prim_immediate_if,&prim_compile_if,NULL},
    {"INVERT",6,NULL,NULL,&prim_body_invert},
    //{"J",1,&prim_immediate_j,&prim_compile_j,&prim_body_j},
    {"KEY",3,NULL,NULL,&prim_body_key},
    //{"LEAVE",5,&prim_immediate_leave,&prim_compile_leave,&prim_body_leave},
    {"LITERAL",7,&prim_immediate_literal,&prim_compile_literal,NULL},
    {"LIT",3,&prim_immediate_literal,&prim_compile_literal,NULL},
    //{"LOOP",4,&prim_immediate_loop,&prim_compile_loop,&prim_body_loop},
    {"LSHIFT",6,NULL,NULL,&prim_body_l_shift},
    {"MAX",3,NULL,NULL,&prim_body_max},
    {"MIN",3,NULL,NULL,&prim_body_min},
    {"MOD",3,NULL,NULL,&prim_body_mod},
    //{"MOVE",4,&prim_immediate_move,&prim_compile_move,&prim_body_move},
    {"NEGATE",6,NULL,NULL,&prim_body_negate},
    {"OR",2,NULL,NULL,&prim_body_or},
    {"OVER",4,NULL,NULL,&prim_body_over},
    {"2OVER",5,NULL,NULL,&prim_body_2_over},
    {"PAGE",4,NULL,NULL,&prim_body_page},
    //{"REPEAT",6,&prim_immediate_repeat,&prim_compile_repeat,&prim_body_repeat},
    {"ROT",3,NULL,NULL,&prim_body_rote},
    {"-ROT",4,NULL,NULL,&prim_body_minus_rote},
    {"RSHIFT",6,NULL,NULL,&prim_body_r_shift},
    {"S\"",2,&prim_immediate_s_quote,&prim_compile_s_quote,NULL},
    {"SPACE",5,NULL,NULL,&prim_body_space},
    {"SPACES",6,NULL,NULL,&prim_body_spaces},
    //{"STATE",5,&prim_immediate_state,&prim_compile_state,&prim_body_state},
    {"SWAP",4,NULL,NULL,&prim_body_swap},
    {"2SWAP",5,NULL,NULL,&prim_body_2_swap},
    {"THEN",4,&prim_immediate_then,&prim_compile_then,NULL},
    {"TYPE",4,NULL,NULL,&prim_body_type},
    {"U<",2,NULL,NULL,&prim_body_u_less_than},
    {"U>",2,NULL,NULL,&prim_body_u_greater_than},
    //{"UNTIL",5,&prim_immediate_until,&prim_compile_until,&prim_body_until},
    {"VARIABLE",8,&prim_immediate_variable,&prim_compile_variable,NULL},
    {"VAR",3,&prim_immediate_variable,&prim_compile_variable,NULL},
    //{"WHILE",5,&prim_immediate_while,&prim_compile_while,&prim_body_while},
    {"XOR",3,NULL,NULL,&prim_body_x_or},
    {"[",1,&prim_immediate_left_bracket,&prim_compile_left_bracket,NULL},
    {"]",1,&prim_immediate_right_bracket,&prim_compile_right_bracket,NULL},
    {"[']",3,&prim_immediate_bracket_tick,&prim_compile_bracket_tick,NULL},
    {"[CHAR]",6,&prim_immediate_bracket_char,&prim_compile_bracket_char,NULL},
    {".R",2,NULL,NULL,&prim_body_dot_r},
    {"U.R",3,NULL,NULL,&prim_body_u_dot_r},
    {"X.R",3,NULL,NULL,&prim_body_x_dot_r},
    {"<>",2,NULL,NULL,&prim_body_not_equals},
    //{"AGAIN",5,&prim_immediate_again,&prim_compile_again,&prim_body_again},
    //{"CASE",4,&prim_immediate_case,&prim_compile_case,&prim_body_case},
    //{"ENDCASE",7,&prim_immediate_endcase,&prim_compile_endcase,&prim_body_endcase},
    //{"OF",2,&prim_immediate_of,&prim_compile_of,&prim_body_of},
    //{"ENDOF",5,&prim_immediate_endof,&prim_compile_endof,&prim_body_endof},
    {"FALSE",5,NULL,NULL,&prim_body_false},
    {"NIP",3,NULL,NULL,&prim_body_nip},
    {"S\\\"",3,&prim_immediate_s_backslash_quote,&prim_compile_s_backslash_quote,NULL},
    {"TRUE",4,NULL,NULL,&prim_body_true},
    {"TUCK",4,NULL,NULL,&prim_body_tuck},
    {"UNUSED",6,NULL,NULL,&prim_body_unused},
    {"WITHIN",6,NULL,NULL,&prim_body_within},
    {".S",2,NULL,NULL,&prim_body_dot_s},
    {"?",1,NULL,NULL,&prim_body_question},
    {"DUMP",4,NULL,NULL,&prim_body_dump},
    //{"SEE",3,&prim_immediate_see,&prim_compile_see,&prim_body_see,&prim_optimize_see},
    {"WORDS",5,&prim_immediate_words,&prim_compile_words,NULL},
    {"BYE",3,NULL,NULL,&prim_body_bye},
    //{"COMPARE",7,&prim_immediate_compare,&prim_compile_compare,&prim_body_compare,&prim_optimize_compare},
    

    //digit?
    //:NONAME
    //2DUP
    //2DROP

    //Words from here are not standard forth
    {"RESET",5,NULL,NULL,&prim_body_reset},
    {"WALIGN",6,NULL,NULL,&prim_body_walign},
    {"WALIGNED",8,NULL,NULL,&prim_body_waligned},
    {"PRINTABLE",9,NULL,NULL,&prim_body_printable},
    {"CXT",3,NULL,NULL,&prim_body_cxt},
    {"WXT",3,NULL,NULL,&prim_body_wxt},
    {"PRIMITIVES",10,&prim_immediate_primitives,&prim_compile_primitives,NULL},
    {"SECONDARIES",11,&prim_immediate_secondaries,&prim_compile_secondaries,NULL},
    {"UNDEFINED",9,&prim_immediate_undefined,&prim_compile_undefined,NULL},

    //DOES>
        //Actually may work though need to figure out how to handle memory
        //Problem is several words made by CREATE will all share same code
            //Biggest obstacle is making CREATE compile since breaks model
            //Need to keep compiling mechanism out of forth-engine. More vectors? Pass source to engine?
        //So, either need one common copy or new copy for each new word
        //Common copy seems unworkable since either need unnamed chunk or rely on CREATEd word which may be redefined
            //May work - mark word as from DOES> and keep reference count in unnamed chunk
        //Only way at this point then seems copy whole body into new primitive
    //DEBUG that steps through word
        //ON should also go to debugger
        //BREAKPOINT would be good
    //action to change data size
    //help
        //with word and without
        //good to have whole different screen if without
            //list of all words with explanation and example of using at console
            //How do I... or FAQ
                //Lots of answers about how this Forth is different
            //C equivalency section
        //ALL remapped keys
    //output number to memory (opposite of >number. number> ? >text ?)
    //output hex to memory (>hex ?)
    //may need to add combined primitives back in depending on optimizer (0= 1+ etc)
        //actually yes, this would probably help a lot
    //COLD or equivalent
        //menu option?

    //May add but not sure yet
    //cleave ??
    //search ??
    //wordsize
        //definitely
    //disasm - just see? edit?
        //better to have one name for both prim and secondaries
        //objdump -t shows function lengths
};

//Can't determine length of array primitives in other files, so calculate here
const int forth_primitives_len=(int)(ARRAY_SIZE(forth_primitives));

