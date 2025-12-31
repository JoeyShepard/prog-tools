#ifndef __GUARD_PROG_TOOLS_FORTH_CHECK
    #define __GUARD_PROG_TOOLS_FORTH_CHECK

    #include "forth-engine.h"

    #define FORTH_CHECK_MAX     8

    void prim_check_0_0(struct ForthEngine *engine);
    void prim_check_0_1(struct ForthEngine *engine);
    void prim_check_0_2(struct ForthEngine *engine);
    void prim_check_0_3(struct ForthEngine *engine);
    void prim_check_0_4(struct ForthEngine *engine);
    void prim_check_0_5(struct ForthEngine *engine);
    void prim_check_0_6(struct ForthEngine *engine);
    void prim_check_0_7(struct ForthEngine *engine);
    void prim_check_1_0(struct ForthEngine *engine);
    void prim_check_1_1(struct ForthEngine *engine);
    void prim_check_1_2(struct ForthEngine *engine);
    void prim_check_1_3(struct ForthEngine *engine);
    void prim_check_1_4(struct ForthEngine *engine);
    void prim_check_1_5(struct ForthEngine *engine);
    void prim_check_1_6(struct ForthEngine *engine);
    void prim_check_1_7(struct ForthEngine *engine);
    void prim_check_2_0(struct ForthEngine *engine);
    void prim_check_2_1(struct ForthEngine *engine);
    void prim_check_2_2(struct ForthEngine *engine);
    void prim_check_2_3(struct ForthEngine *engine);
    void prim_check_2_4(struct ForthEngine *engine);
    void prim_check_2_5(struct ForthEngine *engine);
    void prim_check_2_6(struct ForthEngine *engine);
    void prim_check_2_7(struct ForthEngine *engine);
    void prim_check_3_0(struct ForthEngine *engine);
    void prim_check_3_1(struct ForthEngine *engine);
    void prim_check_3_2(struct ForthEngine *engine);
    void prim_check_3_3(struct ForthEngine *engine);
    void prim_check_3_4(struct ForthEngine *engine);
    void prim_check_3_5(struct ForthEngine *engine);
    void prim_check_3_6(struct ForthEngine *engine);
    void prim_check_3_7(struct ForthEngine *engine);
    void prim_check_4_0(struct ForthEngine *engine);
    void prim_check_4_1(struct ForthEngine *engine);
    void prim_check_4_2(struct ForthEngine *engine);
    void prim_check_4_3(struct ForthEngine *engine);
    void prim_check_4_4(struct ForthEngine *engine);
    void prim_check_4_5(struct ForthEngine *engine);
    void prim_check_4_6(struct ForthEngine *engine);
    void prim_check_4_7(struct ForthEngine *engine);
    void prim_check_5_0(struct ForthEngine *engine);
    void prim_check_5_1(struct ForthEngine *engine);
    void prim_check_5_2(struct ForthEngine *engine);
    void prim_check_5_3(struct ForthEngine *engine);
    void prim_check_5_4(struct ForthEngine *engine);
    void prim_check_5_5(struct ForthEngine *engine);
    void prim_check_5_6(struct ForthEngine *engine);
    void prim_check_5_7(struct ForthEngine *engine);
    void prim_check_6_0(struct ForthEngine *engine);
    void prim_check_6_1(struct ForthEngine *engine);
    void prim_check_6_2(struct ForthEngine *engine);
    void prim_check_6_3(struct ForthEngine *engine);
    void prim_check_6_4(struct ForthEngine *engine);
    void prim_check_6_5(struct ForthEngine *engine);
    void prim_check_6_6(struct ForthEngine *engine);
    void prim_check_6_7(struct ForthEngine *engine);
    void prim_check_7_0(struct ForthEngine *engine);
    void prim_check_7_1(struct ForthEngine *engine);
    void prim_check_7_2(struct ForthEngine *engine);
    void prim_check_7_3(struct ForthEngine *engine);
    void prim_check_7_4(struct ForthEngine *engine);
    void prim_check_7_5(struct ForthEngine *engine);
    void prim_check_7_6(struct ForthEngine *engine);
    void prim_check_7_7(struct ForthEngine *engine);

    extern void (*forth_checks[FORTH_CHECK_MAX][FORTH_CHECK_MAX])(struct ForthEngine *engine);

#endif
