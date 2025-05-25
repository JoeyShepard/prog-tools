#ifndef __GUARD_PROG_TOOLS_DEBUG
    #define __GUARD_PROG_TOOLS_DEBUG

    #include <stdint.h>
    
    #include "forth.h"
    #include "forth-engine.h"
    #include "forth-process.h"

    void debug_heap();
    void debug_dump(void *mem,uint32_t count);
    void debug_words(struct ForthCompileInfo *compile);
    void debug_primitive(void(*func)(struct ForthEngine *));

#endif
