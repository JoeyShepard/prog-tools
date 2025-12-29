#ifndef __GUARD_PROG_TOOLS_FORTH_JIT
    #define __GUARD_PROG_TOOLS_FORTH_JIT

    #include <stdint.h>

    #include "forth.h"

    #define FORTH_JIT_STACK_SIZE    32

    enum
    {
        FORTH_JIT_ERROR_NONE,
        FORTH_JIT_ERROR_OVERFLOW,
        FORTH_JIT_ERROR_UNDERFLOW,
    };

    enum
    {
        FORTH_JIT_EMPTY,    //Reclaimed after being used previously
        FORTH_JIT_CONST_
    };

    enum
    {
        ID_PRIM_STORE,
        ID_PRIM_C_STORE,
        ID_PRIM_W_STORE,
        ID_PRIM_STAR,
        ID_PRIM_STAR_SLASH,
        ID_PRIM_STAR_SLASH_MOD,
        ID_PRIM_PLUS,
        ID_PRIM_COMMA,
        ID_PRIM_C_COMMA,
        ID_PRIM_W_COMMA,
        ID_PRIM_MINUS,
        ID_PRIM_DOT,
        ID_PRIM_U_DOT,
        ID_PRIM_X_DOT,
        ID_PRIM_SLASH,
        ID_PRIM_SLASH_MOD,
        ID_PRIM_LESS_THAN,
        ID_PRIM_EQUALS,
        ID_PRIM_GREATER_THAN,
        ID_PRIM_TO_NUMBER,
        ID_PRIM_NUMBER_TO,
        ID_PRIM_TO_HEX,
        ID_PRIM_HEX_TO,
        ID_PRIM_QUESTION_DUPE,
        ID_PRIM_FETCH,
        ID_PRIM_C_FETCH,
        ID_PRIM_W_FETCH,
        ID_PRIM_QUIT,
        ID_PRIM_ABS,
        ID_PRIM_ACCEPT,
        ID_PRIM_ALIGN,
        ID_PRIM_ALIGNED ,
        ID_PRIM_ALLOT,
        ID_PRIM_AND,
        ID_PRIM_B_L,
        ID_PRIM_BOUNDS,
        ID_PRIM_CELLS,
        ID_PRIM_C_R,
        ID_PRIM_DEPTH,
        ID_PRIM_DROP,
        ID_PRIM_TWO_DROP,
        ID_PRIM_DUPE,
        ID_PRIM_TWO_DUPE,
        ID_PRIM_EMIT,
        ID_PRIM_ERASE,
        ID_PRIM_EXECUTE,
        ID_PRIM_HIDDEN_DONE,
        ID_PRIM_FILL,
        ID_PRIM_HERE,
        ID_PRIM_I,
        ID_PRIM_INVERT,
        ID_PRIM_J,
        ID_PRIM_KEY,
        ID_PRIM_L_SHIFT,
        ID_PRIM_MAX,
        ID_PRIM_MIN,
        ID_PRIM_MOD,
        ID_PRIM_MOVE,
        ID_PRIM_NEGATE,
        ID_PRIM_OR,
        ID_PRIM_OVER,
        ID_PRIM_TWO_OVER,
        ID_PRIM_PAGE,
        ID_PRIM_ROTE,
        ID_PRIM_MINUS_ROTE,
        ID_PRIM_R_SHIFT,
        ID_PRIM_SPACE,
        ID_PRIM_SPACES,
        ID_PRIM_SWAP,
        ID_PRIM_TWO_SWAP,
        ID_PRIM_TYPE,
        ID_PRIM_U_LESS_THAN,
        ID_PRIM_U_GREATER_THAN,
        ID_PRIM_X_OR,
        ID_PRIM_DOT_R,
        ID_PRIM_U_DOT_R,
        ID_PRIM_X_DOT_R,
        ID_PRIM_NOT_EQUALS,
        ID_PRIM_FALSE,
        ID_PRIM_NIP,
        ID_PRIM_TRUE,
        ID_PRIM_TUCK,
        ID_PRIM_UNUSED,
        ID_PRIM_WITHIN,
        ID_PRIM_DOT_S,
        ID_PRIM_QUESTION,
        ID_PRIM_DUMP,
        ID_PRIM_BYE,
        ID_PRIM_RESET,
        ID_PRIM_WALIGN,
        ID_PRIM_WALIGNED,
        ID_PRIM_PRINTABLE,
        ID_PRIM_CXT,
        ID_PRIM_WXT,
        ID_PRIM_PERF,
        ID_PRIM_SIZE,
        ID_PRIM_HIDDEN_DO,
        ID_PRIM_HIDDEN_DOT_QUOTE,
        ID_PRIM_HIDDEN_IF,
        ID_PRIM_HIDDEN_JUMP,
        ID_PRIM_HIDDEN_LEAVE,
        ID_PRIM_HIDDEN_LOOP,
        ID_PRIM_HIDDEN_PLUS_LOOP,
        ID_PRIM_HIDDEN_PUSH,
        ID_PRIM_HIDDEN_S_QUOTE,
        ID_PRIM_HIDDEN_SECONDARY,
        ID_PRIM_LOCALS_COPY,
        ID_PRIM_LOCALS_ZERO,
        ID_PRIM_LOCAL_FETCH0,
        ID_PRIM_LOCAL_FETCH1,
        ID_PRIM_LOCAL_FETCH2,
        ID_PRIM_LOCAL_FETCH3,
        ID_PRIM_LOCAL_FETCH4,
        ID_PRIM_LOCAL_FETCH5,
        ID_PRIM_LOCAL_FETCH6,
        ID_PRIM_LOCAL_FETCH7,
        ID_PRIM_LOCAL_FETCH8,
        ID_PRIM_LOCAL_FETCH9,
        ID_PRIM_LOCAL_FETCH10,
        ID_PRIM_LOCAL_FETCH11,
        ID_PRIM_LOCAL_FETCH12,
        ID_PRIM_LOCAL_FETCH13,
        ID_PRIM_LOCAL_FETCH14,
        ID_PRIM_LOCAL_FETCH15,
        ID_PRIM_LOCAL_FETCH16,
        ID_PRIM_LOCAL_FETCH17,
        ID_PRIM_LOCAL_FETCH18,
        ID_PRIM_LOCAL_FETCH19,
        ID_PRIM_LOCAL_FETCH20,
        ID_PRIM_LOCAL_FETCH21,
        ID_PRIM_LOCAL_FETCH22,
        ID_PRIM_LOCAL_FETCH23,
        ID_PRIM_LOCAL_FETCH24,
        ID_PRIM_LOCAL_FETCH25,
        ID_PRIM_LOCAL_FETCH26,
        ID_PRIM_LOCAL_FETCH27,
        ID_PRIM_LOCAL_FETCH28,
        ID_PRIM_LOCAL_FETCH29,
        ID_PRIM_LOCAL_FETCH30,
        ID_PRIM_LOCAL_FETCH31,
        ID_PRIM_LOCAL_STORE0,
        ID_PRIM_LOCAL_STORE1,
        ID_PRIM_LOCAL_STORE2,
        ID_PRIM_LOCAL_STORE3,
        ID_PRIM_LOCAL_STORE4,
        ID_PRIM_LOCAL_STORE5,
        ID_PRIM_LOCAL_STORE6,
        ID_PRIM_LOCAL_STORE7,
        ID_PRIM_LOCAL_STORE8,
        ID_PRIM_LOCAL_STORE9,
        ID_PRIM_LOCAL_STORE10,
        ID_PRIM_LOCAL_STORE11,
        ID_PRIM_LOCAL_STORE12,
        ID_PRIM_LOCAL_STORE13,
        ID_PRIM_LOCAL_STORE14,
        ID_PRIM_LOCAL_STORE15,
        ID_PRIM_LOCAL_STORE16,
        ID_PRIM_LOCAL_STORE17,
        ID_PRIM_LOCAL_STORE18,
        ID_PRIM_LOCAL_STORE19,
        ID_PRIM_LOCAL_STORE20,
        ID_PRIM_LOCAL_STORE21,
        ID_PRIM_LOCAL_STORE22,
        ID_PRIM_LOCAL_STORE23,
        ID_PRIM_LOCAL_STORE24,
        ID_PRIM_LOCAL_STORE25,
        ID_PRIM_LOCAL_STORE26,
        ID_PRIM_LOCAL_STORE27,
        ID_PRIM_LOCAL_STORE28,
        ID_PRIM_LOCAL_STORE29,
        ID_PRIM_LOCAL_STORE30,
        ID_PRIM_LOCAL_STORE31,
    };

    enum
    {
        LOCAL_NONE,
        LOCAL_FETCH,
        LOCAL_STORE
    };

    struct ForthJitData
    {
        uint32_t index;
        uint32_t bytes_left;
        unsigned char data[];
    };

    struct ForthJitIDs
    {
        uint32_t bytes_left;
        uint32_t element_count;
        forth_prim_t address[];
    };
    
    struct ForthJitConstants
    {
        uint32_t bytes_left;
        uint32_t index;
        struct ForthJitElement
        {
            enum
            {
                FORTH_JIT_CONST,
            } type;
            uint8_t id;
        } elements[];
    };

    struct ForthJitGeneric
    {
        size_t mem_size;
        int ID;
        uint32_t *bytes_left;
        unsigned char *data;
        uint32_t *index;
    };

    struct ForthJitFuncInfo
    {
        forth_prim_t prim;
        uint8_t prim_ID;
        uint8_t local;
        uint8_t local_ID;
        bool optimizable;
        uint8_t pop;
        uint8_t push;
        void (*model)();
    };

    struct ForthJitStackElement
    {
        enum 
        {
            STACK_NONE,
            STACK_CONST,
            STACK_INITIAL,
            STACK_LOCAL,
            STACK_SSA,
        } type;
        union
        {
            int32_t const_value;
            int32_t id;
        };
    };

    struct ForthJitStack
    {
        int sp;
        int sp_min;
        int sp_max;
        struct ForthJitStackElement elements[FORTH_JIT_STACK_SIZE];
    };

    //Functions
    //=========
    int forth_jit(struct ForthCompileInfo *compile);
    int forth_jit_free(struct ForthCompileInfo *compile);

    extern const struct ForthJitFuncInfo forth_jit_functions[];
    extern const int forth_jit_functions_len;

#endif
