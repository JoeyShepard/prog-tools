#ifndef __GUARD_PROG_TOOLS_LOGGING_CUSTOM
    #define __GUARD_PROG_TOOLS_LOGGING_CUSTOM
   
    #ifdef CG50
    //Compiling for calculator - header should remove all log functions on calculator

        #define log_bytes(...)      {}
        #define log_primitive(...) {}

    #else

        #include "forth.h"
        #include "forth-engine.h" 
        #include "forth-primitives.h"

        void log_bytes(void *ptr,int bytes);
        void log_primitive(void(**func)(struct ForthEngine *),struct ForthWordHeader *word_headers);
    
    #endif
#endif
