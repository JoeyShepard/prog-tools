#ifndef __GUARD_PROG_TOOLS_FORTH_PRIMITIVES
    #define __GUARD_PROG_TOOLS_FORTH_PRIMITIVES

    #include <stdint.h>

    #include "forth-engine.h"
    #include "structs.h"

    //structs
    struct ForthPrimitive
    {
        const char *name;
        uint8_t len;
        int (*immediate)(struct ForthEngine *engine);
        int (*compile)(struct ForthEngine *engine);
        void (*body)(struct ForthEngine *engine);
    };

    //Globals
    extern const struct ForthPrimitive forth_primitives[];
    extern const int forth_primitives_len;

    //EXECUTE primitive has special handling so expose function externally
    int prim_immediate_execute(struct ForthEngine *engine);

    //Primitives visible externally (but hidden from user)
    void prim_hidden_do(struct ForthEngine *engine);
    void prim_hidden_done(struct ForthEngine *engine);
    void prim_hidden_dot_quote(struct ForthEngine *engine);
    void prim_hidden_i(struct ForthEngine *engine);
    void prim_hidden_if(struct ForthEngine *engine);
    void prim_hidden_j(struct ForthEngine *engine);
    void prim_hidden_jump(struct ForthEngine *engine);
    void prim_hidden_leave(struct ForthEngine *engine);
    void prim_hidden_loop(struct ForthEngine *engine);
    void prim_hidden_plus_loop(struct ForthEngine *engine);
    void prim_hidden_push(struct ForthEngine *engine);
    void prim_hidden_s_quote(struct ForthEngine *engine);
    void prim_hidden_secondary(struct ForthEngine *engine);

    //Primitives called at compile time and visible externally (but hidden from user)
    int prim_compile_only(struct ForthEngine *engine);
    int prim_interpret_only(struct ForthEngine *engine);

#endif
