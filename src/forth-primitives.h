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
        int (*optimize)(struct ForthEngine *engine);
    };

    //Globals
    extern const struct ForthPrimitive forth_primitives[];
    extern const int forth_primitives_len;

    //Primitives visible externally
    void prim_push(struct ForthEngine *engine);
    void prim_secondary(struct ForthEngine *engine);
    void prim_done(struct ForthEngine *engine);

#endif
