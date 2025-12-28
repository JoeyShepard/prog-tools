#ifndef __GUARD_PROG_TOOLS_FORTH_PRIMITIVES
    #define __GUARD_PROG_TOOLS_FORTH_PRIMITIVES

    #include <stdint.h>

    #include "forth-engine.h"
    #include "logging.h"
    #include "structs.h"

    //structs
    struct ForthPrimitive
    {
        const char *name;
        uint8_t len;
        int immediate_action;
        int compile_action;
        void (*body)(struct ForthEngine *engine);
        bool end_block;
        int pop_count;
        int push_count;
    };

    //Globals
    extern const struct ForthPrimitive forth_primitives[];
    extern const int forth_primitives_len;

    //Primitives
    void prim_store(struct ForthEngine *engine);
    void prim_c_store(struct ForthEngine *engine);
    void prim_w_store(struct ForthEngine *engine);
    void prim_star(struct ForthEngine *engine);
    void prim_star_slash(struct ForthEngine *engine);
    void prim_star_slash_mod(struct ForthEngine *engine);
    void prim_plus(struct ForthEngine *engine);
    void prim_comma(struct ForthEngine *engine);
    void prim_c_comma(struct ForthEngine *engine);
    void prim_w_comma(struct ForthEngine *engine);
    void prim_minus(struct ForthEngine *engine);
    void prim_dot(struct ForthEngine *engine);
    void prim_u_dot(struct ForthEngine *engine);
    void prim_x_dot(struct ForthEngine *engine);
    void prim_slash(struct ForthEngine *engine);
    void prim_slash_mod(struct ForthEngine *engine);
    void prim_less_than(struct ForthEngine *engine);
    void prim_equals(struct ForthEngine *engine);
    void prim_greater_than(struct ForthEngine *engine);
    void prim_to_number(struct ForthEngine *engine);
    void prim_number_to(struct ForthEngine *engine);
    void prim_to_hex(struct ForthEngine *engine);
    void prim_hex_to(struct ForthEngine *engine);
    void prim_question_dupe(struct ForthEngine *engine);
    void prim_fetch(struct ForthEngine *engine);
    void prim_c_fetch(struct ForthEngine *engine);
    void prim_w_fetch(struct ForthEngine *engine);
    void prim_quit(struct ForthEngine *engine);
    void prim_abs(struct ForthEngine *engine);
    void prim_accept(struct ForthEngine *engine);
    void prim_align(struct ForthEngine *engine);
    void prim_aligned (struct ForthEngine *engine);
    void prim_allot(struct ForthEngine *engine);
    void prim_and(struct ForthEngine *engine);
    void prim_b_l(struct ForthEngine *engine);
    void prim_bounds(struct ForthEngine *engine);
    void prim_cells(struct ForthEngine *engine);
    void prim_c_r(struct ForthEngine *engine);
    void prim_depth(struct ForthEngine *engine);
    void prim_drop(struct ForthEngine *engine);
    void prim_two_drop(struct ForthEngine *engine);
    void prim_dupe(struct ForthEngine *engine);
    void prim_two_dupe(struct ForthEngine *engine);
    void prim_emit(struct ForthEngine *engine);
    void prim_erase(struct ForthEngine *engine);
    void prim_execute(struct ForthEngine *engine);
    void prim_hidden_done(struct ForthEngine *engine);
    void prim_fill(struct ForthEngine *engine);
    void prim_here(struct ForthEngine *engine);
    void prim_i(struct ForthEngine *engine);
    void prim_invert(struct ForthEngine *engine);
    void prim_j(struct ForthEngine *engine);
    void prim_key(struct ForthEngine *engine);
    void prim_l_shift(struct ForthEngine *engine);
    void prim_max(struct ForthEngine *engine);
    void prim_min(struct ForthEngine *engine);
    void prim_mod(struct ForthEngine *engine);
    void prim_move(struct ForthEngine *engine);
    void prim_negate(struct ForthEngine *engine);
    void prim_or(struct ForthEngine *engine);
    void prim_over(struct ForthEngine *engine);
    void prim_two_over(struct ForthEngine *engine);
    void prim_page(struct ForthEngine *engine);
    void prim_rote(struct ForthEngine *engine);
    void prim_minus_rote(struct ForthEngine *engine);
    void prim_r_shift(struct ForthEngine *engine);
    void prim_space(struct ForthEngine *engine);
    void prim_spaces(struct ForthEngine *engine);
    void prim_swap(struct ForthEngine *engine);
    void prim_two_swap(struct ForthEngine *engine);
    void prim_type(struct ForthEngine *engine);
    void prim_u_less_than(struct ForthEngine *engine);
    void prim_u_greater_than(struct ForthEngine *engine);
    void prim_x_or(struct ForthEngine *engine);
    void prim_dot_r(struct ForthEngine *engine);
    void prim_u_dot_r(struct ForthEngine *engine);
    void prim_x_dot_r(struct ForthEngine *engine);
    void prim_not_equals(struct ForthEngine *engine);
    void prim_false(struct ForthEngine *engine);
    void prim_nip(struct ForthEngine *engine);
    void prim_true(struct ForthEngine *engine);
    void prim_tuck(struct ForthEngine *engine);
    void prim_unused(struct ForthEngine *engine);
    void prim_within(struct ForthEngine *engine);
    void prim_dot_s(struct ForthEngine *engine);
    void prim_question(struct ForthEngine *engine);
    void prim_dump(struct ForthEngine *engine);
    void prim_bye(struct ForthEngine *engine);
    void prim_reset(struct ForthEngine *engine);
    void prim_walign(struct ForthEngine *engine);
    void prim_waligned(struct ForthEngine *engine);
    void prim_printable(struct ForthEngine *engine);
    void prim_cxt(struct ForthEngine *engine);
    void prim_wxt(struct ForthEngine *engine);
    void prim_perf(struct ForthEngine *engine);
    void prim_size(struct ForthEngine *engine);
    void prim_hidden_do(struct ForthEngine *engine);
    void prim_hidden_dot_quote(struct ForthEngine *engine);
    void prim_hidden_if(struct ForthEngine *engine);
    void prim_hidden_jump(struct ForthEngine *engine);
    void prim_hidden_leave(struct ForthEngine *engine);
    void prim_hidden_loop(struct ForthEngine *engine);
    void prim_hidden_plus_loop(struct ForthEngine *engine);
    void prim_hidden_push(struct ForthEngine *engine);
    void prim_hidden_s_quote(struct ForthEngine *engine);
    void prim_hidden_secondary(struct ForthEngine *engine);

    //Primitives visible externally (but hidden from user)
    void prim_hidden_do(struct ForthEngine *engine);
    void prim_hidden_done(struct ForthEngine *engine);
    void prim_hidden_dot_quote(struct ForthEngine *engine);
    void prim_hidden_if(struct ForthEngine *engine);
    void prim_hidden_jump(struct ForthEngine *engine);
    void prim_hidden_jit(struct ForthEngine *engine);
    void prim_hidden_leave(struct ForthEngine *engine);
    void prim_hidden_loop(struct ForthEngine *engine);
    void prim_hidden_plus_loop(struct ForthEngine *engine);
    void prim_hidden_push(struct ForthEngine *engine);
    void prim_hidden_s_quote(struct ForthEngine *engine);
    void prim_hidden_secondary(struct ForthEngine *engine);

    //Forth NEXT - define once here in case logging needs to change
    #define FORTH_NEXT                                          \
        /*Logging*/                                             \
        log_text("address(primitive): %p [",engine->address+1); \
        log_bytes(engine->address+1,16);                        \
        log_text_raw("]\n");                                    \
        /*log_primitive(engine->address,word_headers);*/        \
        /*log_text_raw("\n");*/                                 \
                                                                \
        /*Jump to primitive function*/                          \
        engine->address++;                                      \
        __attribute__((musttail)) return (*engine->address)(engine);

#endif
