#include "compatibility.h"
#include "logging.h"

void log_config()
{
    log_off_all();
    
    int log_points[]=
    {
        /*
        LOGGING_FORTH_EXECUTE_SECONDARY,
        LOGGING_FORTH_COMPILE_PRIMITIVE,
        LOGGING_FORTH_WRITE_DEF_PRIM,
        LOGGING_FORTH_EXPAND_DEFINITIONS,
        LOGGING_FORTH_UPDATE_COMP_PTRS,
        LOGGING_FORTH_ACTION_COMPACT,
        LOGGING_FORTH_ACTION_PREPARE_WORD,
        LOGGING_FORTH_ACTION_VARIABLE,
        LOGGING_FORTH_ACTION_SOURCE_PRE,
        LOGGING_FORTH_ACTION_SEMICOLON,
        LOGGING_FORTH_ACTION_COLON,
        */
    };

    for (int i=0;i<ARRAY_SIZE(log_points);i++)
    {
        log_on(log_points[i]);
    }
}
