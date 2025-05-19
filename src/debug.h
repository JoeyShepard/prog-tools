#ifndef __GUARD_PROG_TOOLS_DEBUG
    #define __GUARD_PROG_TOOLS_DEBUG

    #include <stdint.h>
    
    void debug_heap();
    void debug_dump(void *mem,uint32_t count);

#endif
