#ifndef __GUARD_PROG_TOOLS_FORTH_PRIMITIVES
    #define __GUARD_PROG_TOOLS_FORTH_PRIMITIVES

    #include <stdint.h>

    #include "structs.h"

    //structs
    struct ForthPrimitive
    {
        const char *name;
        uint8_t len;
        void (*function)(struct ForthEngine *engine);
    };

    //Globals
    extern const struct ForthPrimitive forth_primitives[];
    extern const int forth_primitives_len;

    //Functions
    void forth_prim_store(struct ForthEngine *engine);
    void forth_prim_c_store(struct ForthEngine *engine);
    void forth_prim_w_store(struct ForthEngine *engine);
    void forth_prim_tick(struct ForthEngine *engine);
    void forth_prim_paren(struct ForthEngine *engine);
    void forth_prim_star(struct ForthEngine *engine);
    void forth_prim_star_slash(struct ForthEngine *engine);
    void forth_prim_star_slash_mod(struct ForthEngine *engine);
    void forth_prim_plus(struct ForthEngine *engine);
    void forth_prim_plus_loop(struct ForthEngine *engine);
    void forth_prim_comma(struct ForthEngine *engine);
    void forth_prim_c_comma(struct ForthEngine *engine);
    void forth_prim_w_comma(struct ForthEngine *engine);
    void forth_prim_minus(struct ForthEngine *engine);
    void forth_prim_dot(struct ForthEngine *engine);
    void forth_prim_dot_quote(struct ForthEngine *engine);
    void forth_prim_slash(struct ForthEngine *engine);
    void forth_prim_slash_mod(struct ForthEngine *engine);
    void forth_prim_colon(struct ForthEngine *engine);
    void forth_prim_semicolon(struct ForthEngine *engine);
    void forth_prim_less_than(struct ForthEngine *engine);
    void forth_prim_equals(struct ForthEngine *engine);
    void forth_prim_greater_than(struct ForthEngine *engine);
    void forth_prim_to_number(struct ForthEngine *engine);
    void forth_prim_question_dupe(struct ForthEngine *engine);
    void forth_prim_fetch(struct ForthEngine *engine);
    void forth_prim_c_fetch(struct ForthEngine *engine);
    void forth_prim_w_fetch(struct ForthEngine *engine);
    void forth_prim_quit(struct ForthEngine *engine);
    void forth_prim_abs(struct ForthEngine *engine);
    void forth_prim_accept(struct ForthEngine *engine);
    void forth_prim_align(struct ForthEngine *engine);
    void forth_prim_aligned(struct ForthEngine *engine);
    void forth_prim_allot(struct ForthEngine *engine);
    void forth_prim_and(struct ForthEngine *engine);
    void forth_prim_base(struct ForthEngine *engine);
    void forth_prim_begin(struct ForthEngine *engine);
    void forth_prim_b_l(struct ForthEngine *engine);
    void forth_prim_cells(struct ForthEngine *engine);
    void forth_prim_char(struct ForthEngine *engine);
    void forth_prim_constant(struct ForthEngine *engine);
    void forth_prim_c_r(struct ForthEngine *engine);
    void forth_prim_decimal(struct ForthEngine *engine);
    void forth_prim_depth(struct ForthEngine *engine);
    void forth_prim_do(struct ForthEngine *engine);
    void forth_prim_drop(struct ForthEngine *engine);
    void forth_prim_dupe(struct ForthEngine *engine);
    void forth_prim_else(struct ForthEngine *engine);
    void forth_prim_emit(struct ForthEngine *engine);
    void forth_prim_evaluate(struct ForthEngine *engine);
    void forth_prim_exit(struct ForthEngine *engine);
    void forth_prim_fill(struct ForthEngine *engine);
    void forth_prim_find(struct ForthEngine *engine);
    void forth_prim_here(struct ForthEngine *engine);
    void forth_prim_i(struct ForthEngine *engine);
    void forth_prim_if(struct ForthEngine *engine);
    void forth_prim_immediate(struct ForthEngine *engine);
    void forth_prim_invert(struct ForthEngine *engine);
    void forth_prim_j(struct ForthEngine *engine);
    void forth_prim_key(struct ForthEngine *engine);
    void forth_prim_leave(struct ForthEngine *engine);
    void forth_prim_literal(struct ForthEngine *engine);
    void forth_prim_loop(struct ForthEngine *engine);
    void forth_prim_l_shift(struct ForthEngine *engine);
    void forth_prim_max(struct ForthEngine *engine);
    void forth_prim_min(struct ForthEngine *engine);
    void forth_prim_mod(struct ForthEngine *engine);
    void forth_prim_move(struct ForthEngine *engine);
    void forth_prim_negate(struct ForthEngine *engine);
    void forth_prim_or(struct ForthEngine *engine);
    void forth_prim_over(struct ForthEngine *engine);
    void forth_prim_repeat(struct ForthEngine *engine);
    void forth_prim_rote(struct ForthEngine *engine);
    void forth_prim_minus_rote(struct ForthEngine *engine);
    void forth_prim_r_shift(struct ForthEngine *engine);
    void forth_prim_s_quote(struct ForthEngine *engine);
    void forth_prim_space(struct ForthEngine *engine);
    void forth_prim_spaces(struct ForthEngine *engine);
    void forth_prim_state(struct ForthEngine *engine);
    void forth_prim_swap(struct ForthEngine *engine);
    void forth_prim_then(struct ForthEngine *engine);
    void forth_prim_type(struct ForthEngine *engine);
    void forth_prim_until(struct ForthEngine *engine);
    void forth_prim_variable(struct ForthEngine *engine);
    void forth_prim_var(struct ForthEngine *engine);
    void forth_prim_while(struct ForthEngine *engine);
    void forth_prim_x_or(struct ForthEngine *engine);
    void forth_prim_left_bracket(struct ForthEngine *engine);
    void forth_prim_right_bracket(struct ForthEngine *engine);
    void forth_prim_bracket_tick(struct ForthEngine *engine);
    void forth_prim_bracket_char(struct ForthEngine *engine);
    void forth_prim_dot_r(struct ForthEngine *engine);
    void forth_prim_not_equals(struct ForthEngine *engine);
    void forth_prim_again(struct ForthEngine *engine);
    void forth_prim_case(struct ForthEngine *engine);
    void forth_prim_false(struct ForthEngine *engine);
    void forth_prim_hex(struct ForthEngine *engine);
    void forth_prim_nip(struct ForthEngine *engine);
    void forth_prim_pick(struct ForthEngine *engine);
    void forth_prim_roll(struct ForthEngine *engine);
    void forth_prim_s_backslash_quote(struct ForthEngine *engine);
    void forth_prim_true(struct ForthEngine *engine);
    void forth_prim_tuck(struct ForthEngine *engine);
    void forth_prim_unused(struct ForthEngine *engine);
    void forth_prim_within(struct ForthEngine *engine);
    void forth_prim_backslash(struct ForthEngine *engine);
    void forth_prim_dot_s(struct ForthEngine *engine);
    void forth_prim_question(struct ForthEngine *engine);
    void forth_prim_dump(struct ForthEngine *engine);
    void forth_prim_see(struct ForthEngine *engine);
    void forth_prim_words(struct ForthEngine *engine);
    void forth_prim_state(struct ForthEngine *engine);
    void forth_prim_bye(struct ForthEngine *engine);
    void forth_prim_compare(struct ForthEngine *engine);

#endif
