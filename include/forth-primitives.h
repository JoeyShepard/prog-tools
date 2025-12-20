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

    //Primitives visible externally (but hidden from user)
    void prim_hidden_do(struct ForthEngine *engine);
    void prim_hidden_done(struct ForthEngine *engine);
    void prim_hidden_dot_quote(struct ForthEngine *engine);
    void prim_hidden_if(struct ForthEngine *engine);
    void prim_hidden_jump(struct ForthEngine *engine);
    void prim_hidden_leave(struct ForthEngine *engine);
    void prim_hidden_loop(struct ForthEngine *engine);
    void prim_hidden_plus_loop(struct ForthEngine *engine);
    void prim_hidden_push(struct ForthEngine *engine);
    void prim_hidden_s_quote(struct ForthEngine *engine);
    void prim_hidden_secondary(struct ForthEngine *engine);

    //Forth NEXT - define once here in case logging needs to change
    #define FORTH_NEXT                                      \
        /*Logging*/                                         \
        log_text("address: %p [",engine->address);          \
        log_bytes(engine->address,32);                      \
        log_text_raw("]\n");                                \
        /*log_primitive(engine->address,word_headers);*/    \
        log_text_raw("\n");                                 \
                                                            \
        /*Jump to primitive function*/                      \
        engine->address++;                                  \
        __attribute__((musttail)) return (*engine->address)(engine);

#endif
