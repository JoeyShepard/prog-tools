#ifndef __GUARD_PROG_TOOLS_FORTH_PRIMITIVES
    #define __GUARD_PROG_TOOLS_FORTH_PRIMITIVES

    #include <stdint.h>

    #include "forth-engine.h"

    void prim_hidden_push(struct ForthEngine *engine);
    void prim_body_store(struct ForthEngine *engine);
    void prim_body_c_store(struct ForthEngine *engine);;
    void prim_body_w_store(struct ForthEngine *engine);
    void prim_body_star(struct ForthEngine *engine);
    void prim_body_star_slash(struct ForthEngine *engine);
    void prim_body_star_slash_mod(struct ForthEngine *engine);
    void prim_body_plus(struct ForthEngine *engine);
    void prim_body_minus(struct ForthEngine *engine);
    void prim_body_slash(struct ForthEngine *engine);
    void prim_body_slash_mod(struct ForthEngine *engine);
    void prim_body_less_than(struct ForthEngine *engine);
    void prim_body_equals(struct ForthEngine *engine);
    void prim_body_greater_than(struct ForthEngine *engine);
    void prim_body_fetch(struct ForthEngine *engine);
    void prim_body_c_fetch(struct ForthEngine *engine);
    void prim_body_w_fetch(struct ForthEngine *engine);
    void prim_body_abs(struct ForthEngine *engine);
    void prim_body_and(struct ForthEngine *engine);
    void prim_body_bounds(struct ForthEngine *engine);
    void prim_body_cells(struct ForthEngine *engine);
    void prim_body_drop(struct ForthEngine *engine);
    void prim_body_two_drop(struct ForthEngine *engine);
    void prim_body_dupe(struct ForthEngine *engine);
    void prim_body_two_dupe(struct ForthEngine *engine);
    void prim_body_invert(struct ForthEngine *engine);
    void prim_body_l_shift(struct ForthEngine *engine);
    void prim_body_max(struct ForthEngine *engine);
    void prim_body_min(struct ForthEngine *engine);
    void prim_body_mod(struct ForthEngine *engine);
    void prim_body_negate(struct ForthEngine *engine);
    void prim_body_or(struct ForthEngine *engine);
    void prim_body_over(struct ForthEngine *engine);
    void prim_body_two_over(struct ForthEngine *engine);
    void prim_body_rote(struct ForthEngine *engine);
    void prim_body_minus_rote(struct ForthEngine *engine);
    void prim_body_r_shift(struct ForthEngine *engine);
    void prim_body_swap(struct ForthEngine *engine);
    void prim_body_two_swap(struct ForthEngine *engine);
    void prim_body_u_less_than(struct ForthEngine *engine);
    void prim_body_u_greater_than(struct ForthEngine *engine);
    void prim_body_x_or(struct ForthEngine *engine);
    void prim_body_not_equals(struct ForthEngine *engine);
    void prim_body_false(struct ForthEngine *engine);
    void prim_body_nip(struct ForthEngine *engine);
    void prim_body_true(struct ForthEngine *engine);
    void prim_body_tuck(struct ForthEngine *engine);
    int prim_compile_to(struct ForthEngine *engine);
    void prim_body_cxt(struct ForthEngine *engine);
    void prim_body_wxt(struct ForthEngine *engine);

#endif
