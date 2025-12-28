#include <string.h>

#include "forth-jit.h"
#include "forth-mem.h"
#include "logging.h"
#include "macros.h"
#include "mem.h"

void set_jit_data(struct ForthJitGeneric *settings,struct ForthCompileInfo *compile)
{
    settings->data=compile->jit_data->data;
    settings->index=&compile->jit_data->index;
    settings->mem_size=FORTH_MEM_JIT_DATA;
    settings->ID=FORTH_ID_JIT_DATA;
    settings->bytes_left=&compile->jit_data->bytes_left;
}

int write_jit_primitive(forth_prim_t value,struct ForthCompileInfo *compile)
{
    struct ForthJitGeneric settings;
    set_jit_data(&settings,compile);
    return write_generic((generic_t)value,sizeof(value),settings.data,settings.index,settings.mem_size,
                            settings.ID,settings.bytes_left,compile);
}

int write_jit_u32(uint32_t value,struct ForthCompileInfo *compile)
{
    struct ForthJitGeneric settings;
    set_jit_data(&settings,compile);
    return write_generic((generic_t)value,sizeof(value),settings.data,settings.index,settings.mem_size,
                            settings.ID,settings.bytes_left,compile);
}

int write_jit_i32(int32_t value,struct ForthCompileInfo *compile)
{
    struct ForthJitGeneric settings;
    set_jit_data(&settings,compile);
    return write_generic((generic_t)value,sizeof(value),settings.data,settings.index,settings.mem_size,
                            settings.ID,settings.bytes_left,compile);
}

int write_jit_u16(uint16_t value,struct ForthCompileInfo *compile)
{
    struct ForthJitGeneric settings;
    set_jit_data(&settings,compile);
    return write_generic((generic_t)value,sizeof(value),settings.data,settings.index,settings.mem_size,
                            settings.ID,settings.bytes_left,compile);
}

int forth_jit(struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_JIT,"forth_jit");

    /*
    START HERE
    - figure out how to handle IF (ie WHILE/AGAIN)
      - no matching primitive, just target so hard to adjust
      - in the case of IF, can't adjust until done with code gen following
      - store adjusted jump distances with constants?
      - prob need to scan whole secondary recording jump targets
        - yes since need to end optmizing at BEGIN
    */

    


    //Logging
    log_pop();

    int FORTH_ERROR_NONE;
}

int forth_jit_free(struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_JIT_FREE,"forth_jit_free");

    //Logging
    log_pop();

    int FORTH_ERROR_NONE;
}

void prim_drop_model(){}
void prim_two_drop_model(){}
void prim_dupe_model(){}
void prim_two_dupe_model(){}
void prim_over_model(){}
void prim_two_over_model(){}
void prim_rote_model(){}
void prim_minus_rote_model(){}
void prim_swap_model(){}
void prim_two_swap_model(){}
void prim_nip_model(){}
void prim_tuck_model(){}

const struct ForthJitFuncInfo forth_jit_functions[]={
    {prim_store,            ID_PRIM_STORE,              LOCAL_NONE, 0,      true,  2, 0, NULL},
    {prim_c_store,          ID_PRIM_C_STORE,            LOCAL_NONE, 0,      true,  2, 0, NULL},
    {prim_w_store,          ID_PRIM_W_STORE,            LOCAL_NONE, 0,      true,  2, 0, NULL},
    {prim_star,             ID_PRIM_STAR,               LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_star_slash,       ID_PRIM_STAR_SLASH,         LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_star_slash_mod,   ID_PRIM_STAR_SLASH_MOD,     LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_plus,             ID_PRIM_PLUS,               LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_comma,            ID_PRIM_COMMA,              LOCAL_NONE, 0,      true,  1, 0, NULL},
    {prim_c_comma,          ID_PRIM_C_COMMA,            LOCAL_NONE, 0,      true,  1, 0, NULL},
    {prim_w_comma,          ID_PRIM_W_COMMA,            LOCAL_NONE, 0,      true,  1, 0, NULL},
    {prim_minus,            ID_PRIM_MINUS,              LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_dot,              ID_PRIM_DOT,                LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_u_dot,            ID_PRIM_U_DOT,              LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_x_dot,            ID_PRIM_X_DOT,              LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_slash,            ID_PRIM_SLASH,              LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_slash_mod,        ID_PRIM_SLASH_MOD,          LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_less_than,        ID_PRIM_LESS_THAN,          LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_equals,           ID_PRIM_EQUALS,             LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_greater_than,     ID_PRIM_GREATER_THAN,       LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_to_number,        ID_PRIM_TO_NUMBER,          LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_number_to,        ID_PRIM_NUMBER_TO,          LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_to_hex,           ID_PRIM_TO_HEX,             LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hex_to,           ID_PRIM_HEX_TO,             LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_question_dupe,    ID_PRIM_QUESTION_DUPE,      LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_fetch,            ID_PRIM_FETCH,              LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_c_fetch,          ID_PRIM_C_FETCH,            LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_w_fetch,          ID_PRIM_W_FETCH,            LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_quit,             ID_PRIM_QUIT,               LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_abs,              ID_PRIM_ABS,                LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_accept,           ID_PRIM_ACCEPT,             LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_align,            ID_PRIM_ALIGN,              LOCAL_NONE, 0,      true,  0, 0, NULL},
    {prim_aligned,          ID_PRIM_ALIGNED ,           LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_allot,            ID_PRIM_ALLOT,              LOCAL_NONE, 0,      true,  1, 0, NULL},
    {prim_and,              ID_PRIM_AND,                LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_b_l,              ID_PRIM_B_L,                LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_bounds,           ID_PRIM_BOUNDS,             LOCAL_NONE, 0,      true,  2, 2, NULL},
    {prim_cells,            ID_PRIM_CELLS,              LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_c_r,              ID_PRIM_C_R,                LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_depth,            ID_PRIM_DEPTH,              LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_drop,             ID_PRIM_DROP,               LOCAL_NONE, 0,      true,  1, 0, prim_drop_model},
    {prim_two_drop,         ID_PRIM_TWO_DROP,           LOCAL_NONE, 0,      true,  2, 0, prim_two_drop_model},
    {prim_dupe,             ID_PRIM_DUPE,               LOCAL_NONE, 0,      true,  1, 2, prim_dupe_model},
    {prim_two_dupe,         ID_PRIM_TWO_DUPE,           LOCAL_NONE, 0,      true,  2, 4, prim_two_dupe_model},
    {prim_emit,             ID_PRIM_EMIT,               LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_erase,            ID_PRIM_ERASE,              LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_execute,          ID_PRIM_EXECUTE,            LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_done,      ID_PRIM_HIDDEN_DONE,        LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_fill,             ID_PRIM_FILL,               LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_here,             ID_PRIM_HERE,               LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_i,                ID_PRIM_I,                  LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_invert,           ID_PRIM_INVERT,             LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_j,                ID_PRIM_J,                  LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_key,              ID_PRIM_KEY,                LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_l_shift,          ID_PRIM_L_SHIFT,            LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_max,              ID_PRIM_MAX,                LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_min,              ID_PRIM_MIN,                LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_mod,              ID_PRIM_MOD,                LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_move,             ID_PRIM_MOVE,               LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_negate,           ID_PRIM_NEGATE,             LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_or,               ID_PRIM_OR,                 LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_over,             ID_PRIM_OVER,               LOCAL_NONE, 0,      true,  2, 3, prim_over_model},
    {prim_two_over,         ID_PRIM_TWO_OVER,           LOCAL_NONE, 0,      true,  4, 6, prim_two_over_model},
    {prim_page,             ID_PRIM_PAGE,               LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_rote,             ID_PRIM_ROTE,               LOCAL_NONE, 0,      true,  3, 3, prim_rote_model},
    {prim_minus_rote,       ID_PRIM_MINUS_ROTE,         LOCAL_NONE, 0,      true,  3, 3, prim_minus_rote_model},
    {prim_r_shift,          ID_PRIM_R_SHIFT,            LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_space,            ID_PRIM_SPACE,              LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_spaces,           ID_PRIM_SPACES,             LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_swap,             ID_PRIM_SWAP,               LOCAL_NONE, 0,      true,  2, 2, prim_swap_model},
    {prim_two_swap,         ID_PRIM_TWO_SWAP,           LOCAL_NONE, 0,      true,  4, 4, prim_two_swap_model},
    {prim_type,             ID_PRIM_TYPE,               LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_u_less_than,      ID_PRIM_U_LESS_THAN,        LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_u_greater_than,   ID_PRIM_U_GREATER_THAN,     LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_x_or,             ID_PRIM_X_OR,               LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_dot_r,            ID_PRIM_DOT_R,              LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_u_dot_r,          ID_PRIM_U_DOT_R,            LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_x_dot_r,          ID_PRIM_X_DOT_R,            LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_not_equals,       ID_PRIM_NOT_EQUALS,         LOCAL_NONE, 0,      true,  2, 1, NULL},
    {prim_false,            ID_PRIM_FALSE,              LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_nip,              ID_PRIM_NIP,                LOCAL_NONE, 0,      true,  2, 1, prim_nip_model},
    {prim_true,             ID_PRIM_TRUE,               LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_tuck,             ID_PRIM_TUCK,               LOCAL_NONE, 0,      true,  2, 3, prim_tuck_model},
    {prim_unused,           ID_PRIM_UNUSED,             LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_within,           ID_PRIM_WITHIN,             LOCAL_NONE, 0,      true,  3, 1, NULL},
    {prim_dot_s,            ID_PRIM_DOT_S,              LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_question,         ID_PRIM_QUESTION,           LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_dump,             ID_PRIM_DUMP,               LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_bye,              ID_PRIM_BYE,                LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_reset,            ID_PRIM_RESET,              LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_walign,           ID_PRIM_WALIGN,             LOCAL_NONE, 0,      true,  0, 0, NULL},
    {prim_waligned,         ID_PRIM_WALIGNED,           LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_printable,        ID_PRIM_PRINTABLE,          LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_cxt,              ID_PRIM_CXT,                LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_wxt,              ID_PRIM_WXT,                LOCAL_NONE, 0,      true,  1, 1, NULL},
    {prim_perf,             ID_PRIM_PERF,               LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_size,             ID_PRIM_SIZE,               LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_hidden_do,        ID_PRIM_HIDDEN_DO,          LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_dot_quote, ID_PRIM_HIDDEN_DOT_QUOTE,   LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_if,        ID_PRIM_HIDDEN_IF,          LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_jump,      ID_PRIM_HIDDEN_JUMP,        LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_leave,     ID_PRIM_HIDDEN_LEAVE,       LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_loop,      ID_PRIM_HIDDEN_LOOP,        LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_plus_loop, ID_PRIM_HIDDEN_PLUS_LOOP,   LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_push,      ID_PRIM_HIDDEN_PUSH,        LOCAL_NONE, 0,      true,  0, 1, NULL},
    {prim_hidden_s_quote,   ID_PRIM_HIDDEN_S_QUOTE,     LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_hidden_secondary, ID_PRIM_HIDDEN_SECONDARY,   LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_locals_copy,      ID_PRIM_LOCALS_COPY,        LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_locals_zero,      ID_PRIM_LOCALS_ZERO,        LOCAL_NONE, 0,      false, 0, 0, NULL},
    {prim_local_fetch0,     ID_PRIM_LOCAL_FETCH0,       LOCAL_FETCH, 0,     true,  0, 1, NULL},
    {prim_local_fetch1,     ID_PRIM_LOCAL_FETCH1,       LOCAL_FETCH, 1,     true,  0, 1, NULL},
    {prim_local_fetch2,     ID_PRIM_LOCAL_FETCH2,       LOCAL_FETCH, 2,     true,  0, 1, NULL},
    {prim_local_fetch3,     ID_PRIM_LOCAL_FETCH3,       LOCAL_FETCH, 3,     true,  0, 1, NULL},
    {prim_local_fetch4,     ID_PRIM_LOCAL_FETCH4,       LOCAL_FETCH, 4,     true,  0, 1, NULL},
    {prim_local_fetch5,     ID_PRIM_LOCAL_FETCH5,       LOCAL_FETCH, 5,     true,  0, 1, NULL},
    {prim_local_fetch6,     ID_PRIM_LOCAL_FETCH6,       LOCAL_FETCH, 6,     true,  0, 1, NULL},
    {prim_local_fetch7,     ID_PRIM_LOCAL_FETCH7,       LOCAL_FETCH, 7,     true,  0, 1, NULL},
    {prim_local_fetch8,     ID_PRIM_LOCAL_FETCH8,       LOCAL_FETCH, 8,     true,  0, 1, NULL},
    {prim_local_fetch9,     ID_PRIM_LOCAL_FETCH9,       LOCAL_FETCH, 9,     true,  0, 1, NULL},
    {prim_local_fetch10,    ID_PRIM_LOCAL_FETCH10,      LOCAL_FETCH, 10,    true,  0, 1, NULL},
    {prim_local_fetch11,    ID_PRIM_LOCAL_FETCH11,      LOCAL_FETCH, 11,    true,  0, 1, NULL},
    {prim_local_fetch12,    ID_PRIM_LOCAL_FETCH12,      LOCAL_FETCH, 12,    true,  0, 1, NULL},
    {prim_local_fetch13,    ID_PRIM_LOCAL_FETCH13,      LOCAL_FETCH, 13,    true,  0, 1, NULL},
    {prim_local_fetch14,    ID_PRIM_LOCAL_FETCH14,      LOCAL_FETCH, 14,    true,  0, 1, NULL},
    {prim_local_fetch15,    ID_PRIM_LOCAL_FETCH15,      LOCAL_FETCH, 15,    true,  0, 1, NULL},
    {prim_local_fetch16,    ID_PRIM_LOCAL_FETCH16,      LOCAL_FETCH, 16,    true,  0, 1, NULL},
    {prim_local_fetch17,    ID_PRIM_LOCAL_FETCH17,      LOCAL_FETCH, 17,    true,  0, 1, NULL},
    {prim_local_fetch18,    ID_PRIM_LOCAL_FETCH18,      LOCAL_FETCH, 18,    true,  0, 1, NULL},
    {prim_local_fetch19,    ID_PRIM_LOCAL_FETCH19,      LOCAL_FETCH, 19,    true,  0, 1, NULL},
    {prim_local_fetch20,    ID_PRIM_LOCAL_FETCH20,      LOCAL_FETCH, 20,    true,  0, 1, NULL},
    {prim_local_fetch21,    ID_PRIM_LOCAL_FETCH21,      LOCAL_FETCH, 21,    true,  0, 1, NULL},
    {prim_local_fetch22,    ID_PRIM_LOCAL_FETCH22,      LOCAL_FETCH, 22,    true,  0, 1, NULL},
    {prim_local_fetch23,    ID_PRIM_LOCAL_FETCH23,      LOCAL_FETCH, 23,    true,  0, 1, NULL},
    {prim_local_fetch24,    ID_PRIM_LOCAL_FETCH24,      LOCAL_FETCH, 24,    true,  0, 1, NULL},
    {prim_local_fetch25,    ID_PRIM_LOCAL_FETCH25,      LOCAL_FETCH, 25,    true,  0, 1, NULL},
    {prim_local_fetch26,    ID_PRIM_LOCAL_FETCH26,      LOCAL_FETCH, 26,    true,  0, 1, NULL},
    {prim_local_fetch27,    ID_PRIM_LOCAL_FETCH27,      LOCAL_FETCH, 27,    true,  0, 1, NULL},
    {prim_local_fetch28,    ID_PRIM_LOCAL_FETCH28,      LOCAL_FETCH, 28,    true,  0, 1, NULL},
    {prim_local_fetch29,    ID_PRIM_LOCAL_FETCH29,      LOCAL_FETCH, 29,    true,  0, 1, NULL},
    {prim_local_fetch30,    ID_PRIM_LOCAL_FETCH30,      LOCAL_FETCH, 30,    true,  0, 1, NULL},
    {prim_local_fetch31,    ID_PRIM_LOCAL_FETCH31,      LOCAL_FETCH, 31,    true,  0, 1, NULL},
    {prim_local_store0,     ID_PRIM_LOCAL_STORE0,       LOCAL_STORE, 0,     true,  1, 0, NULL},
    {prim_local_store1,     ID_PRIM_LOCAL_STORE1,       LOCAL_STORE, 1,     true,  1, 0, NULL},
    {prim_local_store2,     ID_PRIM_LOCAL_STORE2,       LOCAL_STORE, 2,     true,  1, 0, NULL},
    {prim_local_store3,     ID_PRIM_LOCAL_STORE3,       LOCAL_STORE, 3,     true,  1, 0, NULL},
    {prim_local_store4,     ID_PRIM_LOCAL_STORE4,       LOCAL_STORE, 4,     true,  1, 0, NULL},
    {prim_local_store5,     ID_PRIM_LOCAL_STORE5,       LOCAL_STORE, 5,     true,  1, 0, NULL},
    {prim_local_store6,     ID_PRIM_LOCAL_STORE6,       LOCAL_STORE, 6,     true,  1, 0, NULL},
    {prim_local_store7,     ID_PRIM_LOCAL_STORE7,       LOCAL_STORE, 7,     true,  1, 0, NULL},
    {prim_local_store8,     ID_PRIM_LOCAL_STORE8,       LOCAL_STORE, 8,     true,  1, 0, NULL},
    {prim_local_store9,     ID_PRIM_LOCAL_STORE9,       LOCAL_STORE, 9,     true,  1, 0, NULL},
    {prim_local_store10,    ID_PRIM_LOCAL_STORE10,      LOCAL_STORE, 10,    true,  1, 0, NULL},
    {prim_local_store11,    ID_PRIM_LOCAL_STORE11,      LOCAL_STORE, 11,    true,  1, 0, NULL},
    {prim_local_store12,    ID_PRIM_LOCAL_STORE12,      LOCAL_STORE, 12,    true,  1, 0, NULL},
    {prim_local_store13,    ID_PRIM_LOCAL_STORE13,      LOCAL_STORE, 13,    true,  1, 0, NULL},
    {prim_local_store14,    ID_PRIM_LOCAL_STORE14,      LOCAL_STORE, 14,    true,  1, 0, NULL},
    {prim_local_store15,    ID_PRIM_LOCAL_STORE15,      LOCAL_STORE, 15,    true,  1, 0, NULL},
    {prim_local_store16,    ID_PRIM_LOCAL_STORE16,      LOCAL_STORE, 16,    true,  1, 0, NULL},
    {prim_local_store17,    ID_PRIM_LOCAL_STORE17,      LOCAL_STORE, 17,    true,  1, 0, NULL},
    {prim_local_store18,    ID_PRIM_LOCAL_STORE18,      LOCAL_STORE, 18,    true,  1, 0, NULL},
    {prim_local_store19,    ID_PRIM_LOCAL_STORE19,      LOCAL_STORE, 19,    true,  1, 0, NULL},
    {prim_local_store20,    ID_PRIM_LOCAL_STORE20,      LOCAL_STORE, 20,    true,  1, 0, NULL},
    {prim_local_store21,    ID_PRIM_LOCAL_STORE21,      LOCAL_STORE, 21,    true,  1, 0, NULL},
    {prim_local_store22,    ID_PRIM_LOCAL_STORE22,      LOCAL_STORE, 22,    true,  1, 0, NULL},
    {prim_local_store23,    ID_PRIM_LOCAL_STORE23,      LOCAL_STORE, 23,    true,  1, 0, NULL},
    {prim_local_store24,    ID_PRIM_LOCAL_STORE24,      LOCAL_STORE, 24,    true,  1, 0, NULL},
    {prim_local_store25,    ID_PRIM_LOCAL_STORE25,      LOCAL_STORE, 25,    true,  1, 0, NULL},
    {prim_local_store26,    ID_PRIM_LOCAL_STORE26,      LOCAL_STORE, 26,    true,  1, 0, NULL},
    {prim_local_store27,    ID_PRIM_LOCAL_STORE27,      LOCAL_STORE, 27,    true,  1, 0, NULL},
    {prim_local_store28,    ID_PRIM_LOCAL_STORE28,      LOCAL_STORE, 28,    true,  1, 0, NULL},
    {prim_local_store29,    ID_PRIM_LOCAL_STORE29,      LOCAL_STORE, 29,    true,  1, 0, NULL},
    {prim_local_store30,    ID_PRIM_LOCAL_STORE30,      LOCAL_STORE, 30,    true,  1, 0, NULL},
    {prim_local_store31,    ID_PRIM_LOCAL_STORE31,      LOCAL_STORE, 31,    true,  1, 0, NULL},
    };

const int forth_jit_functions_len=ARRAY_LEN(forth_jit_functions);

