//Compatibility layer for Forth engine so engine can be reused on different systems

#ifndef __GUARD_PROG_TOOLS_FORTH_COMPATIBILITY
    #define __GUARD_PROG_TOOLS_FORTH_COMPATIBILITY
    
    #include "compatibility.h"
    #include "structs.h"

    #define FORTH_WORD_MAX          16      //Max size of word in source
    
    //Element count must be power of 2!
    #define FORTH_STACK_ELEMENTS    256
    #define FORTH_RSTACK_ELEMENTS   256
    #define FORTH_COMPAT_STACKS     xram    //Pointer to memory where stack and rstack are stored
    #define FORTH_MAX_SPACES        1500    //Max for SPACES primitive
    #define FORTH_DUMP_MAX_LINES    20      //Max lines for dump
    #define FORTH_DUMP_BYTES        8       //Bytes to show per line

    extern struct ConsoleInfo *forth_print_console;

    void forth_print(const char *text);
    void forth_print_color(const char *text,color_t color);

#endif
