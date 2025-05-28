#ifndef __GUARD_PROG_TOOLS_LOGGING_CUSTOM
    #define __GUARD_PROG_TOOLS_LOGGING_CUSTOM
   
    #include "forth.h"
    #include "forth-engine.h" 
    #include "forth-primitives.h"

    void log_bytes(void *ptr,int bytes);
    void log_primitive(void(**func)(struct ForthEngine *),struct ForthCompileInfo *compile);

#endif
