#include <string.h>

//TODO: remove
#include <stdio.h>

#include "forth-check.h"
#include "forth-jit.h"
#include "forth-mem.h"
#include "forth-primitives.h"
#include "logging.h"
#include "logging-custom.h"
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

int jit_stack_init(struct ForthJitStack *stack)
{
    stack->sp=FORTH_JIT_STACK_START;
    stack->sp_min=stack->sp;
    stack->sp_max=stack->sp;
    for (int i=0;i<FORTH_JIT_STACK_SIZE;i++)
    {
        stack->elements[i].type=STACK_INITIAL;
        stack->elements[i].id=i;
    }
}

struct ForthJitStackElement jit_stack_pop(struct ForthJitStack *stack,int *error)
{
    if (*error!=FORTH_JIT_ERROR_NONE) 
    {
        //If a prior call set the error code, exit early
        return (struct ForthJitStackElement){STACK_NONE,0};
    }
    if (stack->sp==FORTH_JIT_STACK_MIN)
    {
        *error=FORTH_JIT_ERROR_UNDERFLOW;
        return (struct ForthJitStackElement){STACK_NONE,0};
    }
    else
    {
        stack->sp--;
        if (stack->sp<stack->sp_min) stack->sp_min=stack->sp;
        return stack->elements[stack->sp];
    }
}

void jit_stack_push(struct ForthJitStackElement element,struct ForthJitStack *stack,int *error)
{
    if (*error!=FORTH_JIT_ERROR_NONE) 
    {
        //If a prior call set the error code, exit early
        return;
    }
    if (stack->sp==FORTH_JIT_STACK_MAX)
    {
        *error=FORTH_JIT_ERROR_OVERFLOW;
        return;
    }
    else
    {
        stack->elements[stack->sp]=element;
        stack->sp++;
        if (stack->sp>stack->sp_max) stack->sp_max=stack->sp;
        return;
    }
}

int forth_jit(struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_JIT,"forth_jit");

    /*
    START HERE
    - scan all secondaries
      - add to list also
      - note jump targets
        - ok to put into constants?
          - if holding ssas, const, and jump targets, need struct of unions and renaming
    - - rescan and generate code
      - output const pool
    */

    struct ForthWordHeader *word=compile->words->header;
    while (1)
    {
        if (word->last==true)
        {
            //Logging
            log_text("finished processing secondaries\n");

            //Empty header found - done looping
            break;
        }

        //Logging
        log_text("scanning secondary %s (ID %d, %d bytes)\n",word->name,word->ID,word->definition_size);
        switch(word->type)
        {
            case FORTH_SECONDARY_WORD:
                log_text("type: FORTH_SECONDARY_WORD\n");
                break;
            case FORTH_SECONDARY_CONSTANT:
                log_text("type: FORTH_SECONDARY_CONSTANT\n");
                break;
            case FORTH_SECONDARY_CREATE:
                log_text("type: FORTH_SECONDARY_CREATE\n");
                break;
            case FORTH_SECONDARY_VARIABLE:
                log_text("type: FORTH_SECONDARY_VARIABLE\n");
                break;
            case FORTH_SECONDARY_UNDEFINED:
                log_text("type: FORTH_SECONDARY_UNDEFINED\n");
                break;
        }

        if (word->type==FORTH_SECONDARY_WORD)
        {
            //Scan secondary to find jump offsets
            unsigned char *address=(unsigned char *)word->address;
            for (int i=0;i<word->definition_size;i+=sizeof(forth_prim_t))
            {
                //Logging
                log_primitive((forth_prim_t *)(address+i),compile->words->header);

                //Skip constants embedded in thread
                START HERE
            }
        }
        else
        {
            //No JIT for CONST, CREATE, VAR, or UNDEFINED since will be inlined in WORD
        }

        //Next secondary
        word++;

        //Logging
        log_text("\n");
    }

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
    {prim_store,            ID_PRIM_STORE,              PRIM_NONE, 0,       true,  2, 0, NULL},
    {prim_c_store,          ID_PRIM_C_STORE,            PRIM_NONE, 0,       true,  2, 0, NULL},
    {prim_w_store,          ID_PRIM_W_STORE,            PRIM_NONE, 0,       true,  2, 0, NULL},
    {prim_star,             ID_PRIM_STAR,               PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_star_slash,       ID_PRIM_STAR_SLASH,         PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_star_slash_mod,   ID_PRIM_STAR_SLASH_MOD,     PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_plus,             ID_PRIM_PLUS,               PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_comma,            ID_PRIM_COMMA,              PRIM_NONE, 0,       true,  1, 0, NULL},
    {prim_c_comma,          ID_PRIM_C_COMMA,            PRIM_NONE, 0,       true,  1, 0, NULL},
    {prim_w_comma,          ID_PRIM_W_COMMA,            PRIM_NONE, 0,       true,  1, 0, NULL},
    {prim_minus,            ID_PRIM_MINUS,              PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_dot,              ID_PRIM_DOT,                PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_u_dot,            ID_PRIM_U_DOT,              PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_x_dot,            ID_PRIM_X_DOT,              PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_slash,            ID_PRIM_SLASH,              PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_slash_mod,        ID_PRIM_SLASH_MOD,          PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_less_than,        ID_PRIM_LESS_THAN,          PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_equals,           ID_PRIM_EQUALS,             PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_greater_than,     ID_PRIM_GREATER_THAN,       PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_to_number,        ID_PRIM_TO_NUMBER,          PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_number_to,        ID_PRIM_NUMBER_TO,          PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_to_hex,           ID_PRIM_TO_HEX,             PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_hex_to,           ID_PRIM_HEX_TO,             PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_question_dupe,    ID_PRIM_QUESTION_DUPE,      PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_fetch,            ID_PRIM_FETCH,              PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_c_fetch,          ID_PRIM_C_FETCH,            PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_w_fetch,          ID_PRIM_W_FETCH,            PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_quit,             ID_PRIM_QUIT,               PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_abs,              ID_PRIM_ABS,                PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_accept,           ID_PRIM_ACCEPT,             PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_align,            ID_PRIM_ALIGN,              PRIM_NONE, 0,       true,  0, 0, NULL},
    {prim_aligned ,         ID_PRIM_ALIGNED ,           PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_allot,            ID_PRIM_ALLOT,              PRIM_NONE, 0,       true,  1, 0, NULL},
    {prim_and,              ID_PRIM_AND,                PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_b_l,              ID_PRIM_B_L,                PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_bounds,           ID_PRIM_BOUNDS,             PRIM_NONE, 0,       true,  2, 2, NULL},
    {prim_cells,            ID_PRIM_CELLS,              PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_c_r,              ID_PRIM_C_R,                PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_depth,            ID_PRIM_DEPTH,              PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_drop,             ID_PRIM_DROP,               PRIM_NONE, 0,       true,  1, 0, prim_drop_model},
    {prim_two_drop,         ID_PRIM_TWO_DROP,           PRIM_NONE, 0,       true,  2, 0, prim_two_drop_model},
    {prim_dupe,             ID_PRIM_DUPE,               PRIM_NONE, 0,       true,  1, 2, prim_dupe_model},
    {prim_two_dupe,         ID_PRIM_TWO_DUPE,           PRIM_NONE, 0,       true,  2, 4, prim_two_dupe_model},
    {prim_emit,             ID_PRIM_EMIT,               PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_erase,            ID_PRIM_ERASE,              PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_execute,          ID_PRIM_EXECUTE,            PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_hidden_done,      ID_PRIM_HIDDEN_DONE,        PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_fill,             ID_PRIM_FILL,               PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_here,             ID_PRIM_HERE,               PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_i,                ID_PRIM_I,                  PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_invert,           ID_PRIM_INVERT,             PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_j,                ID_PRIM_J,                  PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_key,              ID_PRIM_KEY,                PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_l_shift,          ID_PRIM_L_SHIFT,            PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_max,              ID_PRIM_MAX,                PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_min,              ID_PRIM_MIN,                PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_mod,              ID_PRIM_MOD,                PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_move,             ID_PRIM_MOVE,               PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_negate,           ID_PRIM_NEGATE,             PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_or,               ID_PRIM_OR,                 PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_over,             ID_PRIM_OVER,               PRIM_NONE, 0,       true,  2, 3, prim_over_model},
    {prim_two_over,         ID_PRIM_TWO_OVER,           PRIM_NONE, 0,       true,  4, 6, prim_two_over_model},
    {prim_page,             ID_PRIM_PAGE,               PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_rote,             ID_PRIM_ROTE,               PRIM_NONE, 0,       true,  3, 3, prim_rote_model},
    {prim_minus_rote,       ID_PRIM_MINUS_ROTE,         PRIM_NONE, 0,       true,  3, 3, prim_minus_rote_model},
    {prim_r_shift,          ID_PRIM_R_SHIFT,            PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_space,            ID_PRIM_SPACE,              PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_spaces,           ID_PRIM_SPACES,             PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_swap,             ID_PRIM_SWAP,               PRIM_NONE, 0,       true,  2, 2, prim_swap_model},
    {prim_two_swap,         ID_PRIM_TWO_SWAP,           PRIM_NONE, 0,       true,  4, 4, prim_two_swap_model},
    {prim_type,             ID_PRIM_TYPE,               PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_u_less_than,      ID_PRIM_U_LESS_THAN,        PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_u_greater_than,   ID_PRIM_U_GREATER_THAN,     PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_x_or,             ID_PRIM_X_OR,               PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_dot_r,            ID_PRIM_DOT_R,              PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_u_dot_r,          ID_PRIM_U_DOT_R,            PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_x_dot_r,          ID_PRIM_X_DOT_R,            PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_not_equals,       ID_PRIM_NOT_EQUALS,         PRIM_NONE, 0,       true,  2, 1, NULL},
    {prim_false,            ID_PRIM_FALSE,              PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_nip,              ID_PRIM_NIP,                PRIM_NONE, 0,       true,  2, 1, prim_nip_model},
    {prim_true,             ID_PRIM_TRUE,               PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_tuck,             ID_PRIM_TUCK,               PRIM_NONE, 0,       true,  2, 3, prim_tuck_model},
    {prim_unused,           ID_PRIM_UNUSED,             PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_within,           ID_PRIM_WITHIN,             PRIM_NONE, 0,       true,  3, 1, NULL},
    {prim_dot_s,            ID_PRIM_DOT_S,              PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_question,         ID_PRIM_QUESTION,           PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_dump,             ID_PRIM_DUMP,               PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_bye,              ID_PRIM_BYE,                PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_reset,            ID_PRIM_RESET,              PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_walign,           ID_PRIM_WALIGN,             PRIM_NONE, 0,       true,  0, 0, NULL},
    {prim_waligned,         ID_PRIM_WALIGNED,           PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_printable,        ID_PRIM_PRINTABLE,          PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_cxt,              ID_PRIM_CXT,                PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_wxt,              ID_PRIM_WXT,                PRIM_NONE, 0,       true,  1, 1, NULL},
    {prim_perf,             ID_PRIM_PERF,               PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_size,             ID_PRIM_SIZE,               PRIM_NONE, 0,       true,  0, 1, NULL},
    {prim_hidden_do,        ID_PRIM_HIDDEN_DO,          PRIM_NONE, 0,       false, 0, 0, NULL},
    {prim_hidden_dot_quote, ID_PRIM_HIDDEN_DOT_QUOTE,   PRIM_MULT, 0,       false, 0, 0, NULL},
    {prim_hidden_if,        ID_PRIM_HIDDEN_IF,          PRIM_ARG, 0,        false, 0, 0, NULL},
    {prim_hidden_jump,      ID_PRIM_HIDDEN_JUMP,        PRIM_ARG, 0,        false, 0, 0, NULL},
    {prim_hidden_leave,     ID_PRIM_HIDDEN_LEAVE,       PRIM_ARG, 0,        false, 0, 0, NULL},
    {prim_hidden_loop,      ID_PRIM_HIDDEN_LOOP,        PRIM_ARG, 0,        false, 0, 0, NULL},
    {prim_hidden_plus_loop, ID_PRIM_HIDDEN_PLUS_LOOP,   PRIM_ARG, 0,        false, 0, 0, NULL},
    {prim_hidden_push,      ID_PRIM_HIDDEN_PUSH,        PRIM_ARG, 0,        true,  0, 1, NULL},
    {prim_hidden_push_check,ID_PRIM_HIDDEN_PUSH_CHECK,  PRIM_ARG, 0,        true,  0, 1, NULL},
    {prim_hidden_s_quote,   ID_PRIM_HIDDEN_S_QUOTE,     PRIM_MULT, 0,       false, 0, 0, NULL},
    {prim_hidden_secondary, ID_PRIM_HIDDEN_SECONDARY,   PRIM_ARG, 0,        false, 0, 0, NULL},
    {prim_locals_copy,      ID_PRIM_LOCALS_COPY,        PRIM_ARG, 0,        true,  0, 0, NULL},
    {prim_locals_zero,      ID_PRIM_LOCALS_ZERO,        PRIM_ARG, 0,        true,  0, 0, NULL},
    {prim_local_fetch0,     ID_PRIM_LOCAL_FETCH0,       PRIM_FETCH, 0,      true,  0, 1, NULL},
    {prim_local_fetch1,     ID_PRIM_LOCAL_FETCH1,       PRIM_FETCH, 1,      true,  0, 1, NULL},
    {prim_local_fetch2,     ID_PRIM_LOCAL_FETCH2,       PRIM_FETCH, 2,      true,  0, 1, NULL},
    {prim_local_fetch3,     ID_PRIM_LOCAL_FETCH3,       PRIM_FETCH, 3,      true,  0, 1, NULL},
    {prim_local_fetch4,     ID_PRIM_LOCAL_FETCH4,       PRIM_FETCH, 4,      true,  0, 1, NULL},
    {prim_local_fetch5,     ID_PRIM_LOCAL_FETCH5,       PRIM_FETCH, 5,      true,  0, 1, NULL},
    {prim_local_fetch6,     ID_PRIM_LOCAL_FETCH6,       PRIM_FETCH, 6,      true,  0, 1, NULL},
    {prim_local_fetch7,     ID_PRIM_LOCAL_FETCH7,       PRIM_FETCH, 7,      true,  0, 1, NULL},
    {prim_local_fetch8,     ID_PRIM_LOCAL_FETCH8,       PRIM_FETCH, 8,      true,  0, 1, NULL},
    {prim_local_fetch9,     ID_PRIM_LOCAL_FETCH9,       PRIM_FETCH, 9,      true,  0, 1, NULL},
    {prim_local_fetch10,    ID_PRIM_LOCAL_FETCH10,      PRIM_FETCH, 10,     true,  0, 1, NULL},
    {prim_local_fetch11,    ID_PRIM_LOCAL_FETCH11,      PRIM_FETCH, 11,     true,  0, 1, NULL},
    {prim_local_fetch12,    ID_PRIM_LOCAL_FETCH12,      PRIM_FETCH, 12,     true,  0, 1, NULL},
    {prim_local_fetch13,    ID_PRIM_LOCAL_FETCH13,      PRIM_FETCH, 13,     true,  0, 1, NULL},
    {prim_local_fetch14,    ID_PRIM_LOCAL_FETCH14,      PRIM_FETCH, 14,     true,  0, 1, NULL},
    {prim_local_fetch15,    ID_PRIM_LOCAL_FETCH15,      PRIM_FETCH, 15,     true,  0, 1, NULL},
    {prim_local_fetch16,    ID_PRIM_LOCAL_FETCH16,      PRIM_FETCH, 16,     true,  0, 1, NULL},
    {prim_local_fetch17,    ID_PRIM_LOCAL_FETCH17,      PRIM_FETCH, 17,     true,  0, 1, NULL},
    {prim_local_fetch18,    ID_PRIM_LOCAL_FETCH18,      PRIM_FETCH, 18,     true,  0, 1, NULL},
    {prim_local_fetch19,    ID_PRIM_LOCAL_FETCH19,      PRIM_FETCH, 19,     true,  0, 1, NULL},
    {prim_local_fetch20,    ID_PRIM_LOCAL_FETCH20,      PRIM_FETCH, 20,     true,  0, 1, NULL},
    {prim_local_fetch21,    ID_PRIM_LOCAL_FETCH21,      PRIM_FETCH, 21,     true,  0, 1, NULL},
    {prim_local_fetch22,    ID_PRIM_LOCAL_FETCH22,      PRIM_FETCH, 22,     true,  0, 1, NULL},
    {prim_local_fetch23,    ID_PRIM_LOCAL_FETCH23,      PRIM_FETCH, 23,     true,  0, 1, NULL},
    {prim_local_fetch24,    ID_PRIM_LOCAL_FETCH24,      PRIM_FETCH, 24,     true,  0, 1, NULL},
    {prim_local_fetch25,    ID_PRIM_LOCAL_FETCH25,      PRIM_FETCH, 25,     true,  0, 1, NULL},
    {prim_local_fetch26,    ID_PRIM_LOCAL_FETCH26,      PRIM_FETCH, 26,     true,  0, 1, NULL},
    {prim_local_fetch27,    ID_PRIM_LOCAL_FETCH27,      PRIM_FETCH, 27,     true,  0, 1, NULL},
    {prim_local_fetch28,    ID_PRIM_LOCAL_FETCH28,      PRIM_FETCH, 28,     true,  0, 1, NULL},
    {prim_local_fetch29,    ID_PRIM_LOCAL_FETCH29,      PRIM_FETCH, 29,     true,  0, 1, NULL},
    {prim_local_fetch30,    ID_PRIM_LOCAL_FETCH30,      PRIM_FETCH, 30,     true,  0, 1, NULL},
    {prim_local_fetch31,    ID_PRIM_LOCAL_FETCH31,      PRIM_FETCH, 31,     true,  0, 1, NULL},
    {prim_local_store0,     ID_PRIM_LOCAL_STORE0,       PRIM_STORE, 0,      true,  1, 0, NULL},
    {prim_local_store1,     ID_PRIM_LOCAL_STORE1,       PRIM_STORE, 1,      true,  1, 0, NULL},
    {prim_local_store2,     ID_PRIM_LOCAL_STORE2,       PRIM_STORE, 2,      true,  1, 0, NULL},
    {prim_local_store3,     ID_PRIM_LOCAL_STORE3,       PRIM_STORE, 3,      true,  1, 0, NULL},
    {prim_local_store4,     ID_PRIM_LOCAL_STORE4,       PRIM_STORE, 4,      true,  1, 0, NULL},
    {prim_local_store5,     ID_PRIM_LOCAL_STORE5,       PRIM_STORE, 5,      true,  1, 0, NULL},
    {prim_local_store6,     ID_PRIM_LOCAL_STORE6,       PRIM_STORE, 6,      true,  1, 0, NULL},
    {prim_local_store7,     ID_PRIM_LOCAL_STORE7,       PRIM_STORE, 7,      true,  1, 0, NULL},
    {prim_local_store8,     ID_PRIM_LOCAL_STORE8,       PRIM_STORE, 8,      true,  1, 0, NULL},
    {prim_local_store9,     ID_PRIM_LOCAL_STORE9,       PRIM_STORE, 9,      true,  1, 0, NULL},
    {prim_local_store10,    ID_PRIM_LOCAL_STORE10,      PRIM_STORE, 10,     true,  1, 0, NULL},
    {prim_local_store11,    ID_PRIM_LOCAL_STORE11,      PRIM_STORE, 11,     true,  1, 0, NULL},
    {prim_local_store12,    ID_PRIM_LOCAL_STORE12,      PRIM_STORE, 12,     true,  1, 0, NULL},
    {prim_local_store13,    ID_PRIM_LOCAL_STORE13,      PRIM_STORE, 13,     true,  1, 0, NULL},
    {prim_local_store14,    ID_PRIM_LOCAL_STORE14,      PRIM_STORE, 14,     true,  1, 0, NULL},
    {prim_local_store15,    ID_PRIM_LOCAL_STORE15,      PRIM_STORE, 15,     true,  1, 0, NULL},
    {prim_local_store16,    ID_PRIM_LOCAL_STORE16,      PRIM_STORE, 16,     true,  1, 0, NULL},
    {prim_local_store17,    ID_PRIM_LOCAL_STORE17,      PRIM_STORE, 17,     true,  1, 0, NULL},
    {prim_local_store18,    ID_PRIM_LOCAL_STORE18,      PRIM_STORE, 18,     true,  1, 0, NULL},
    {prim_local_store19,    ID_PRIM_LOCAL_STORE19,      PRIM_STORE, 19,     true,  1, 0, NULL},
    {prim_local_store20,    ID_PRIM_LOCAL_STORE20,      PRIM_STORE, 20,     true,  1, 0, NULL},
    {prim_local_store21,    ID_PRIM_LOCAL_STORE21,      PRIM_STORE, 21,     true,  1, 0, NULL},
    {prim_local_store22,    ID_PRIM_LOCAL_STORE22,      PRIM_STORE, 22,     true,  1, 0, NULL},
    {prim_local_store23,    ID_PRIM_LOCAL_STORE23,      PRIM_STORE, 23,     true,  1, 0, NULL},
    {prim_local_store24,    ID_PRIM_LOCAL_STORE24,      PRIM_STORE, 24,     true,  1, 0, NULL},
    {prim_local_store25,    ID_PRIM_LOCAL_STORE25,      PRIM_STORE, 25,     true,  1, 0, NULL},
    {prim_local_store26,    ID_PRIM_LOCAL_STORE26,      PRIM_STORE, 26,     true,  1, 0, NULL},
    {prim_local_store27,    ID_PRIM_LOCAL_STORE27,      PRIM_STORE, 27,     true,  1, 0, NULL},
    {prim_local_store28,    ID_PRIM_LOCAL_STORE28,      PRIM_STORE, 28,     true,  1, 0, NULL},
    {prim_local_store29,    ID_PRIM_LOCAL_STORE29,      PRIM_STORE, 29,     true,  1, 0, NULL},
    {prim_local_store30,    ID_PRIM_LOCAL_STORE30,      PRIM_STORE, 30,     true,  1, 0, NULL},
    {prim_local_store31,    ID_PRIM_LOCAL_STORE31,      PRIM_STORE, 31,     true,  1, 0, NULL},
    {prim_check_0_0,        ID_PRIM_CHECK_0_0,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_0_1,        ID_PRIM_CHECK_0_1,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_0_2,        ID_PRIM_CHECK_0_2,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_0_3,        ID_PRIM_CHECK_0_3,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_0_4,        ID_PRIM_CHECK_0_4,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_0_5,        ID_PRIM_CHECK_0_5,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_0_6,        ID_PRIM_CHECK_0_6,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_0_7,        ID_PRIM_CHECK_0_7,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_1_0,        ID_PRIM_CHECK_1_0,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_1_1,        ID_PRIM_CHECK_1_1,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_1_2,        ID_PRIM_CHECK_1_2,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_1_3,        ID_PRIM_CHECK_1_3,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_1_4,        ID_PRIM_CHECK_1_4,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_1_5,        ID_PRIM_CHECK_1_5,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_1_6,        ID_PRIM_CHECK_1_6,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_1_7,        ID_PRIM_CHECK_1_7,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_2_0,        ID_PRIM_CHECK_2_0,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_2_1,        ID_PRIM_CHECK_2_1,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_2_2,        ID_PRIM_CHECK_2_2,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_2_3,        ID_PRIM_CHECK_2_3,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_2_4,        ID_PRIM_CHECK_2_4,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_2_5,        ID_PRIM_CHECK_2_5,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_2_6,        ID_PRIM_CHECK_2_6,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_2_7,        ID_PRIM_CHECK_2_7,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_3_0,        ID_PRIM_CHECK_3_0,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_3_1,        ID_PRIM_CHECK_3_1,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_3_2,        ID_PRIM_CHECK_3_2,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_3_3,        ID_PRIM_CHECK_3_3,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_3_4,        ID_PRIM_CHECK_3_4,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_3_5,        ID_PRIM_CHECK_3_5,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_3_6,        ID_PRIM_CHECK_3_6,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_3_7,        ID_PRIM_CHECK_3_7,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_4_0,        ID_PRIM_CHECK_4_0,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_4_1,        ID_PRIM_CHECK_4_1,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_4_2,        ID_PRIM_CHECK_4_2,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_4_3,        ID_PRIM_CHECK_4_3,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_4_4,        ID_PRIM_CHECK_4_4,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_4_5,        ID_PRIM_CHECK_4_5,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_4_6,        ID_PRIM_CHECK_4_6,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_4_7,        ID_PRIM_CHECK_4_7,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_5_0,        ID_PRIM_CHECK_5_0,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_5_1,        ID_PRIM_CHECK_5_1,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_5_2,        ID_PRIM_CHECK_5_2,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_5_3,        ID_PRIM_CHECK_5_3,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_5_4,        ID_PRIM_CHECK_5_4,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_5_5,        ID_PRIM_CHECK_5_5,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_5_6,        ID_PRIM_CHECK_5_6,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_5_7,        ID_PRIM_CHECK_5_7,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_6_0,        ID_PRIM_CHECK_6_0,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_6_1,        ID_PRIM_CHECK_6_1,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_6_2,        ID_PRIM_CHECK_6_2,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_6_3,        ID_PRIM_CHECK_6_3,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_6_4,        ID_PRIM_CHECK_6_4,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_6_5,        ID_PRIM_CHECK_6_5,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_6_6,        ID_PRIM_CHECK_6_6,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_6_7,        ID_PRIM_CHECK_6_7,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_7_0,        ID_PRIM_CHECK_7_0,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_7_1,        ID_PRIM_CHECK_7_1,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_7_2,        ID_PRIM_CHECK_7_2,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_7_3,        ID_PRIM_CHECK_7_3,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_7_4,        ID_PRIM_CHECK_7_4,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_7_5,        ID_PRIM_CHECK_7_5,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_7_6,        ID_PRIM_CHECK_7_6,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    {prim_check_7_7,        ID_PRIM_CHECK_7_7,          PRIM_IGNORE, 0,     true,  0, 0, NULL},
    };

const int forth_jit_functions_len=ARRAY_LEN(forth_jit_functions);

