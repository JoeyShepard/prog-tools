
#include "logging.h"

#ifdef CG50
    //Compiling for calculator

    //Only useful function on calculator - used in code blocks so they can be optimized out
    bool log_enabled()
    {
        return false;
    }

    //Empty functions that are optimized out since no logging on calculator


#else
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>

    #include "logging-config.h"

    #define LOG_STACK_COUNT     256

    //Global variables not visible outside of file
    const char *log_path;
    bool log_list[LOGGING_POINTS_COUNT];
    int log_selected;
    int log_stack[LOG_STACK_COUNT];
    int log_index;

    //Functions
    bool log_enabled()
    {
        return true;
    }

    void init_logging(const char *new_path)
    {
        //Save path for other files to use
        log_path=new_path;

        //No log selected
        log_selected=LOGGING_NONE;

        //Turn off all logs by default
        log_off_all();

        //Initialize log stack
        log_index=0;

        //Configure logs in separate logging-config.c
        log_config();

        //Start logging new session
        log_none("\n\n");
        log_none("LOGGING RESTARTED\n");
        log_none("=================\n");
    }

    void log_on(int point)
    {
        if (point<LOGGING_POINTS_COUNT)
        {
            log_list[point]=true;
        }
        else
        {
            log_none("Error: log point out of range - %d\n",point);
            exit(1);
        }
    }

    void log_off(int point)
    {
        if (point<LOGGING_POINTS_COUNT)
        {
            log_list[point]=false;
        }
        else
        {
            log_none("Error: log point out of range - %d\n",point);
            exit(1);
        }
    }

    void log_on_all()
    {
        for (int i=0;i<LOGGING_POINTS_COUNT;i++)
            log_list[i]=true;
    }
    
    void log_off_all()
    {
        for (int i=0;i<LOGGING_POINTS_COUNT;i++)
            log_list[i]=false;
    }

    bool log_check(int point)
    {
        return log_list[point];
    }
    
    void log_push(int point,const char *title)
    {
        if (point<LOGGING_POINTS_COUNT)
        {
            if (log_index==LOG_STACK_COUNT-1)
            {
                log_none("Error: out of log stack space. Missing call to log_pop?\n");
                exit(1);
            }
            log_stack[log_index]=log_selected;
            log_index++;
            log_selected=point;
            if (title==NULL) return;
            if (*title==0) return;
            for (int i=1;i<log_index;i++)
                if (log_check(log_stack[i])) log_text_raw("  ");
            log_text_raw(title);
            log_text_raw("\n");
        }
        else
        {
            log_none("Error: log point out of range - %d\n",point);
            exit(1);
        }
    }

    void log_pop()
    {
        if (log_index==0)
        {
            log_none("Error: log stack underflow. Too many calls to log pop?\n");
            exit(1);
        }
        log_index--;
        log_selected=log_stack[log_index];
    }

    void log_text(const char *fmt,...)
    {
        //Only print log if enabled unless LOGGING_NONE which is always printed
        if ((log_selected!=LOGGING_NONE)&&(log_list[log_selected]==false)) return;
        
        //Indentation
        for (int i=1;i<log_index;i++)
            if (log_check(log_stack[i])) log_text_raw("  ");
        if (log_index!=0) log_text_raw("- ");

        //Open logging file for append
        FILE *fptr=fopen(log_path,"a");
        if (fptr==NULL)
        {
            printf("Error - unable to open log file: %s\n",log_path);
            exit(1);
        }

        //Write data to file
        va_list args;
        va_start(args,fmt);
        vfprintf(fptr,fmt,args);
        va_end(args);

        //Close file
        fclose(fptr);
    }

    void log_text_raw(const char *fmt,...)
    {
        //Only print log if enabled unless LOGGING_NONE which is always printed
        if ((log_selected!=LOGGING_NONE)&&(log_list[log_selected]==false)) return;
        
        //Open logging file for append
        FILE *fptr=fopen(log_path,"a");
        if (fptr==NULL)
        {
            printf("Error - unable to open log file: %s\n",log_path);
            exit(1);
        }

        //Write data to file
        va_list args;
        va_start(args,fmt);
        vfprintf(fptr,fmt,args);
        va_end(args);

        //Close file
        fclose(fptr);
    }

    void log_none(const char *fmt,...)
    {
        //Passing var_args to log_text didn't work so copy here

        //Open logging file for append
        FILE *fptr=fopen(log_path,"a");
        if (fptr==NULL)
        {
            printf("Error - unable to open log file: %s\n",log_path);
            exit(1);
        }

        //Write data to file
        va_list args;
        va_start(args,fmt);
        vfprintf(fptr,fmt,args);
        va_end(args);

        //Close file
        fclose(fptr);
    }

#endif

