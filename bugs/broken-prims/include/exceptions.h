#ifndef __GUARD_PROG_TOOLS_EXCEPTIONS
    #define __GUARD_PROG_TOOLS_EXCEPTIONS
    
    #include <stdbool.h>

    #define EXCEPTION_WADDERR       0x100
    #define EXCEPTION_RADDERR       0x0E0

    extern volatile bool address_exception;

    void setup_exception_handling();

#endif
