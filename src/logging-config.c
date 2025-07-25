#include "compatibility.h"
#include "logging.h"
#include "macros.h"

void log_config()
{
    log_off_all();
    
    int log_points[]=
    {
        //LOGGING_NONE,
        //LOGGING_FORTH_ACTION_COLON,
        //LOGGING_FORTH_ACTION_COMPACT,
        //LOGGING_FORTH_ACTION_CONSTANT,
        //LOGGING_FORTH_ACTION_CREATE,
        //LOGGING_FORTH_ACTION_PREPARE_WORD,
        //LOGGING_FORTH_ACTION_QUOTE_COMMON,
        //LOGGING_FORTH_ACTION_SOURCE_PRE,
        //LOGGING_FORTH_ACTION_SEMICOLON,
        //LOGGING_FORTH_ACTION_VARIABLE,
        //LOGGING_FORTH_ALLOT,
        //LOGGING_FORTH_COMPILE_PRIMITIVE,
        //LOGGING_FORTH_EXECUTE_SECONDARY,
        //LOGGING_FORTH_EXPAND_DEFINITIONS,
        //LOGGING_FORTH_PRIM_HIDDEN_S_QUOTE,
        //LOGGING_FORTH_PRIM_HIDDEN_DOT_QUOTE,
        //LOGGING_FORTH_RESUME_REDRAW,
        //LOGGING_FORTH_UPDATE_COMP_PTRS,
        //LOGGING_FORTH_WRITE_DEF_PRIM,

        //LOGGING_MEM_OBJECT_ADDRESS,
        //LOGGING_MEM_EXPAND_OBJECT,
    };

    for (int i=0;i<ARRAY_LEN(log_points);i++)
    {
        log_on(log_points[i]);
    }
}
