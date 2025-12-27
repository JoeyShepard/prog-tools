#include "forth-check.h"
#include "forth-primitives.h"

//Does nothing but easier to use than restructure compiler. Also, only a block with only ALIGN/WALIGN can generate this, so unlikely
    //to ever be generated.
void prim_check_0_0(struct ForthEngine *engine)
{
    FORTH_NEXT
}

void prim_check_0_1(struct ForthEngine *engine)		
{		
	if (engine->stack_index>=FORTH_STACK_ELEMENTS)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_0_2(struct ForthEngine *engine)		
{		
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_0_3(struct ForthEngine *engine)		
{		
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_0_4(struct ForthEngine *engine)		
{		
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_0_5(struct ForthEngine *engine)		
{		
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_0_6(struct ForthEngine *engine)		
{		
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_0_7(struct ForthEngine *engine)		
{		
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_1_0(struct ForthEngine *engine)		
{		
	if (engine->stack_index<1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_1_1(struct ForthEngine *engine)		
{		
	if (engine->stack_index<1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_1_2(struct ForthEngine *engine)		
{		
	if (engine->stack_index<1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_1_3(struct ForthEngine *engine)		
{		
	if (engine->stack_index<1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_1_4(struct ForthEngine *engine)		
{		
	if (engine->stack_index<1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_1_5(struct ForthEngine *engine)		
{		
	if (engine->stack_index<1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_1_6(struct ForthEngine *engine)		
{		
	if (engine->stack_index<1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_1_7(struct ForthEngine *engine)		
{		
	if (engine->stack_index<1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_2_0(struct ForthEngine *engine)		
{		
	if (engine->stack_index<2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_2_1(struct ForthEngine *engine)		
{		
	if (engine->stack_index<2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_2_2(struct ForthEngine *engine)		
{		
	if (engine->stack_index<2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_2_3(struct ForthEngine *engine)		
{		
	if (engine->stack_index<2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_2_4(struct ForthEngine *engine)		
{		
	if (engine->stack_index<2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_2_5(struct ForthEngine *engine)		
{		
	if (engine->stack_index<2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_2_6(struct ForthEngine *engine)		
{		
	if (engine->stack_index<2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_2_7(struct ForthEngine *engine)		
{		
	if (engine->stack_index<2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_3_0(struct ForthEngine *engine)		
{		
	if (engine->stack_index<3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_3_1(struct ForthEngine *engine)		
{		
	if (engine->stack_index<3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_3_2(struct ForthEngine *engine)		
{		
	if (engine->stack_index<3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_3_3(struct ForthEngine *engine)		
{		
	if (engine->stack_index<3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_3_4(struct ForthEngine *engine)		
{		
	if (engine->stack_index<3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_3_5(struct ForthEngine *engine)		
{		
	if (engine->stack_index<3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_3_6(struct ForthEngine *engine)		
{		
	if (engine->stack_index<3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_3_7(struct ForthEngine *engine)		
{		
	if (engine->stack_index<3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_4_0(struct ForthEngine *engine)		
{		
	if (engine->stack_index<4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_4_1(struct ForthEngine *engine)		
{		
	if (engine->stack_index<4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_4_2(struct ForthEngine *engine)		
{		
	if (engine->stack_index<4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_4_3(struct ForthEngine *engine)		
{		
	if (engine->stack_index<4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_4_4(struct ForthEngine *engine)		
{		
	if (engine->stack_index<4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_4_5(struct ForthEngine *engine)		
{		
	if (engine->stack_index<4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_4_6(struct ForthEngine *engine)		
{		
	if (engine->stack_index<4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_4_7(struct ForthEngine *engine)		
{		
	if (engine->stack_index<4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_5_0(struct ForthEngine *engine)		
{		
	if (engine->stack_index<5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_5_1(struct ForthEngine *engine)		
{		
	if (engine->stack_index<5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_5_2(struct ForthEngine *engine)		
{		
	if (engine->stack_index<5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_5_3(struct ForthEngine *engine)		
{		
	if (engine->stack_index<5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_5_4(struct ForthEngine *engine)		
{		
	if (engine->stack_index<5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_5_5(struct ForthEngine *engine)		
{		
	if (engine->stack_index<5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_5_6(struct ForthEngine *engine)		
{		
	if (engine->stack_index<5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_5_7(struct ForthEngine *engine)		
{		
	if (engine->stack_index<5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_6_0(struct ForthEngine *engine)		
{		
	if (engine->stack_index<6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_6_1(struct ForthEngine *engine)		
{		
	if (engine->stack_index<6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_6_2(struct ForthEngine *engine)		
{		
	if (engine->stack_index<6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_6_3(struct ForthEngine *engine)		
{		
	if (engine->stack_index<6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_6_4(struct ForthEngine *engine)		
{		
	if (engine->stack_index<6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_6_5(struct ForthEngine *engine)		
{		
	if (engine->stack_index<6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_6_6(struct ForthEngine *engine)		
{		
	if (engine->stack_index<6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_6_7(struct ForthEngine *engine)		
{		
	if (engine->stack_index<6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_7_0(struct ForthEngine *engine)		
{		
	if (engine->stack_index<7)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_7_1(struct ForthEngine *engine)		
{		
	if (engine->stack_index<7)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_7_2(struct ForthEngine *engine)		
{		
	if (engine->stack_index<7)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-1)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_7_3(struct ForthEngine *engine)		
{		
	if (engine->stack_index<7)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-2)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_7_4(struct ForthEngine *engine)		
{		
	if (engine->stack_index<7)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-3)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_7_5(struct ForthEngine *engine)		
{		
	if (engine->stack_index<7)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-4)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_7_6(struct ForthEngine *engine)		
{		
	if (engine->stack_index<7)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-5)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		
		
void prim_check_7_7(struct ForthEngine *engine)		
{		
	if (engine->stack_index<7)	
	{	
		engine->error=FORTH_ENGINE_ERROR_UNDERFLOW;
		engine->executing=false;
        return;
	}	
	if (engine->stack_index>=FORTH_STACK_ELEMENTS-6)	
	{	
		engine->error=FORTH_ENGINE_ERROR_OVERFLOW;
		engine->executing=false;
        return;
	}	

    FORTH_NEXT
}		

void (*forth_checks[FORTH_CHECK_MAX][FORTH_CHECK_MAX])(struct ForthEngine *engine)=
{
    {prim_check_0_0, prim_check_0_1, prim_check_0_2, prim_check_0_3, prim_check_0_4, prim_check_0_5, prim_check_0_6, prim_check_0_7},
    {prim_check_1_0, prim_check_1_1, prim_check_1_2, prim_check_1_3, prim_check_1_4, prim_check_1_5, prim_check_1_6, prim_check_1_7},
    {prim_check_2_0, prim_check_2_1, prim_check_2_2, prim_check_2_3, prim_check_2_4, prim_check_2_5, prim_check_2_6, prim_check_2_7},
    {prim_check_3_0, prim_check_3_1, prim_check_3_2, prim_check_3_3, prim_check_3_4, prim_check_3_5, prim_check_3_6, prim_check_3_7},
    {prim_check_4_0, prim_check_4_1, prim_check_4_2, prim_check_4_3, prim_check_4_4, prim_check_4_5, prim_check_4_6, prim_check_4_7},
    {prim_check_5_0, prim_check_5_1, prim_check_5_2, prim_check_5_3, prim_check_5_4, prim_check_5_5, prim_check_5_6, prim_check_5_7},
    {prim_check_6_0, prim_check_6_1, prim_check_6_2, prim_check_6_3, prim_check_6_4, prim_check_6_5, prim_check_6_6, prim_check_6_7},
    {prim_check_7_0, prim_check_7_1, prim_check_7_2, prim_check_7_3, prim_check_7_4, prim_check_7_5, prim_check_7_6, prim_check_7_7},
};
