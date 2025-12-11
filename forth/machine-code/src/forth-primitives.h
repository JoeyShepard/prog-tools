#ifndef __GUARD_PROG_TOOLS_FORTH_PRIMITIVES
    #define __GUARD_PROG_TOOLS_FORTH_PRIMITIVES

    #include <stdint.h>

    #include "forth-engine.h"

    void prim_hidden_push(struct ForthEngine *engine);
    void prim_store(struct ForthEngine *engine);
    void prim_c_store(struct ForthEngine *engine);;
    void prim_w_store(struct ForthEngine *engine);
    void prim_star(struct ForthEngine *engine);
    void prim_star_slash(struct ForthEngine *engine);
    void prim_star_slash_mod(struct ForthEngine *engine);
    void prim_plus(struct ForthEngine *engine);
    void prim_minus(struct ForthEngine *engine);
    void prim_slash(struct ForthEngine *engine);
    void prim_slash_mod(struct ForthEngine *engine);
    void prim_less_than(struct ForthEngine *engine);
    void prim_equals(struct ForthEngine *engine);
    void prim_greater_than(struct ForthEngine *engine);
    void prim_fetch(struct ForthEngine *engine);
    void prim_c_fetch(struct ForthEngine *engine);
    void prim_w_fetch(struct ForthEngine *engine);
    void prim_abs(struct ForthEngine *engine);
    void prim_and(struct ForthEngine *engine);
    void prim_bounds(struct ForthEngine *engine);
    void prim_cells(struct ForthEngine *engine);
    void prim_drop(struct ForthEngine *engine);
    void prim_two_drop(struct ForthEngine *engine);
    void prim_dupe(struct ForthEngine *engine);
    void prim_two_dupe(struct ForthEngine *engine);
    void prim_invert(struct ForthEngine *engine);
    void prim_l_shift(struct ForthEngine *engine);
    void prim_max(struct ForthEngine *engine);
    void prim_min(struct ForthEngine *engine);
    void prim_mod(struct ForthEngine *engine);
    void prim_negate(struct ForthEngine *engine);
    void prim_or(struct ForthEngine *engine);
    void prim_over(struct ForthEngine *engine);
    void prim_two_over(struct ForthEngine *engine);
    void prim_rote(struct ForthEngine *engine);
    void prim_minus_rote(struct ForthEngine *engine);
    void prim_r_shift(struct ForthEngine *engine);
    void prim_swap(struct ForthEngine *engine);
    void prim_two_swap(struct ForthEngine *engine);
    void prim_u_less_than(struct ForthEngine *engine);
    void prim_u_greater_than(struct ForthEngine *engine);
    void prim_x_or(struct ForthEngine *engine);
    void prim_not_equals(struct ForthEngine *engine);
    void prim_false(struct ForthEngine *engine);
    void prim_nip(struct ForthEngine *engine);
    void prim_true(struct ForthEngine *engine);
    void prim_tuck(struct ForthEngine *engine);
    void prim_cxt(struct ForthEngine *engine);
    void prim_wxt(struct ForthEngine *engine);

#endif
