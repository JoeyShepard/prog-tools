#include "forth-engine.h"
#include "forth-primitives.h"

//Initialize locals
//=================
void prim_locals_copy(struct ForthEngine *engine)
{
    //Fetch count and offset which are stored after pointer to current word
    uint32_t num=*(uint32_t *)(engine->address+1);
    int count=num>>16;
    int offset=num&0xFFFF;

    //Increment thread pointer to account for number
    //TODO: remove
    //engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);
    engine->address=(forth_prim_t *)(((uint32_t *)engine->address)+1);
    
    if (engine->stack_index<count)
    {
        //Underflow
        engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
        engine->executing=false;
        return;
    }

    //Pop values from stack to locals
    int32_t temp_index=engine->stack_index;
    int32_t *temp_stack=engine->stack;
    for (int i=0;i<count;i++)
    {
        //Adjust stack pointer
        temp_index--;

        //Copy value from stack to local
        engine->locals_stack[offset]=temp_stack[temp_index];
        offset--;
    }

    //Update stack pointer from temporary copy
    engine->stack_index=temp_index;

    FORTH_NEXT
}

void prim_locals_zero(struct ForthEngine *engine)
{
    //Fetch count and offset which are stored after pointer to current word
    uint32_t num=*(uint32_t *)(engine->address+1);
    int count=num>>16;
    int offset=num&0xFFFF;

    //Increment thread pointer to account for number
    engine->address=(void (**)(struct ForthEngine *engine))(((uint32_t *)engine->address)+1);
    
    //Initialize locals to 0
    for (int i=0;i<count;i++)
    {
        engine->locals_stack[offset]=0;
        offset--;
    }

    FORTH_NEXT
}

//Fetch locals - hardcoded for all 32 possibilities
//=================================================
void prim_local_fetch0(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[0];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch1(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[1];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch2(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[2];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch3(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[3];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch4(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[4];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch5(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[5];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch6(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[6];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch7(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[7];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch8(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[8];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch9(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[9];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch10(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[10];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch11(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[11];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch12(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[12];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch13(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[13];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch14(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[14];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch15(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[15];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch16(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[16];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch17(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[17];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch18(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[18];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch19(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[19];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch20(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[20];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch21(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[21];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch22(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[22];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch23(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[23];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch24(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[24];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch25(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[25];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch26(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[26];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch27(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[27];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch28(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[28];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch29(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[29];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch30(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[30];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

void prim_local_fetch31(struct ForthEngine *engine)
{
    //Write local value to stack
    engine->stack[engine->stack_index]=engine->locals_stack[31];

    //Advance stack pointer
    engine->stack_index++;

    FORTH_NEXT
}

//Store locals - hardcoded for all 32 possibilities
//=================================================
void prim_local_store0(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[0]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store1(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[1]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store2(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[2]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store3(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[3]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store4(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[4]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store5(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[5]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store6(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[6]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store7(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[7]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store8(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[8]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store9(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[9]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store10(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[10]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store11(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[11]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store12(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[12]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store13(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[13]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store14(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[14]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store15(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[15]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store16(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[16]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store17(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[17]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store18(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[18]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store19(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[19]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store20(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[20]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store21(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[21]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store22(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[22]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store23(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[23]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store24(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[24]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store25(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[25]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store26(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[26]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store27(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[27]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store28(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[28]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store29(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[29]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store30(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[30]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

void prim_local_store31(struct ForthEngine *engine)
{
    //Adjust stack pointer
    engine->stack_index--;

    //Write stack value to local
    engine->locals_stack[31]=engine->stack[engine->stack_index];

    FORTH_NEXT
}

//Externally visible tables
//=========================
void (*forth_locals_fetch[])(struct ForthEngine *engine)=
{
    prim_local_fetch0,
    prim_local_fetch1,
    prim_local_fetch2,
    prim_local_fetch3,
    prim_local_fetch4,
    prim_local_fetch5,
    prim_local_fetch6,
    prim_local_fetch7,
    prim_local_fetch8,
    prim_local_fetch9,
    prim_local_fetch10,
    prim_local_fetch11,
    prim_local_fetch12,
    prim_local_fetch13,
    prim_local_fetch14,
    prim_local_fetch15,
    prim_local_fetch16,
    prim_local_fetch17,
    prim_local_fetch18,
    prim_local_fetch19,
    prim_local_fetch20,
    prim_local_fetch21,
    prim_local_fetch22,
    prim_local_fetch23,
    prim_local_fetch24,
    prim_local_fetch25,
    prim_local_fetch26,
    prim_local_fetch27,
    prim_local_fetch28,
    prim_local_fetch29,
    prim_local_fetch30,
    prim_local_fetch31
};

void (*forth_locals_store[])(struct ForthEngine *engine)=
{
    prim_local_store0,
    prim_local_store1,
    prim_local_store2,
    prim_local_store3,
    prim_local_store4,
    prim_local_store5,
    prim_local_store6,
    prim_local_store7,
    prim_local_store8,
    prim_local_store9,
    prim_local_store10,
    prim_local_store11,
    prim_local_store12,
    prim_local_store13,
    prim_local_store14,
    prim_local_store15,
    prim_local_store16,
    prim_local_store17,
    prim_local_store18,
    prim_local_store19,
    prim_local_store20,
    prim_local_store21,
    prim_local_store22,
    prim_local_store23,
    prim_local_store24,
    prim_local_store25,
    prim_local_store26,
    prim_local_store27,
    prim_local_store28,
    prim_local_store29,
    prim_local_store30,
    prim_local_store31
};

