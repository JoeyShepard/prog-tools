#ifndef __GUARD_PROG_TOOLS_LOGGING
    #define __GUARD_PROG_TOOLS_LOGGING

    #include "logging-custom.h"

    #ifdef CG50
        //Compiling for calculator - remove all log functions
        
        #define log_header()        {}
        #define init_logging(...)   {}
        #define log_on(...)         {}
        #define log_off(...)        {}
        #define log_on_all(...)     {}
        #define log_off_all(...)    {}
        #define log_check(...)      {}
        #define log_push(...)       {}
        #define log_pop(...)        {}
        #define log_text(...)       {}
        #define log_text_raw(...)   {}
        #define log_none(...)       {}

    #else

        #include <stdbool.h>

        enum LoggingPoints
        {
            LOGGING_NONE,
            LOGGING_CONSOLE_TEXT,
            LOGGING_FORTH_ACTION_COLON,
            LOGGING_FORTH_ACTION_COMPACT,
            LOGGING_FORTH_ACTION_CONSTANT,
            LOGGING_FORTH_ACTION_CREATE,
            LOGGING_FORTH_ACTION_PREPARE_WORD,
            LOGGING_FORTH_ACTION_QUOTE_COMMON,
            LOGGING_FORTH_ACTION_SOURCE_PRE,
            LOGGING_FORTH_ACTION_SEMICOLON,
            LOGGING_FORTH_ACTION_VARIABLE,
            LOGGING_FORTH_ALLOT,
            LOGGING_FORTH_COMPILE_PRIMITIVE,
            LOGGING_FORTH_EXECUTE_SECONDARY,
            LOGGING_FORTH_EXPAND_DEFINITIONS,
            LOGGING_FORTH_OBJECT_ADDRESS,
            LOGGING_FORTH_PRIM_HIDDEN_DOT_QUOTE,
            LOGGING_FORTH_PRIM_HIDDEN_S_QUOTE,
            LOGGING_FORTH_RESUME_REDRAW,
            LOGGING_FORTH_UPDATE_COMP_PTRS,
            LOGGING_FORTH_WRITE_DEF_PRIM,

            LOGGING_MEM_EXPAND_OBJECT,
            LOGGING_MEM_OBJECT_ADDRESS,

            //TODO:
            LOGGING_FORTH_KEYS,

            //Count of points in enum 
            LOGGING_POINTS_COUNT
        };

        //Functions for PC only
        void init_logging(const char *new_path);
        void log_header();
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
#endif
