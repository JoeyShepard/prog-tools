#ifndef __GUARD_PROG_TOOLS_LOGGING
    #define __GUARD_PROG_TOOLS_LOGGING

    #include <stdbool.h>

    #include "logging-custom.h"

    enum LoggingPoints
    {
        LOGGING_NONE,
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

        //TODO:
        LOGGING_FORTH_KEYS,

        //Testing only
        LOGGING_A,
        LOGGING_B,
        LOGGING_C,

        //Count of points in enum 
        LOGGING_POINTS_COUNT
    };

    //Functions for PC and CG50
    bool log_enabled();

    //Functions for PC only
    void init_logging(const char *new_path);
    void log_on(int point);
    void log_off(int point);
    void log_on_all();
    void log_off_all();
    bool log_check(int point);
    void log_push(int point,const char *title);
    void log_pop();
    void log_text(const char *fmt,...);
    void log_text_raw(const char *fmt,...);
    void log_none(const char *fmt,...);

#endif
