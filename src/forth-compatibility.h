//Compatibility layer for Forth engine so engine can be reused on different systems

#ifndef __GUARD_PROG_TOOLS_FORTH_COMPATIBILITY
    #define __GUARD_PROG_TOOLS_FORTH_COMPATIBILITY
    
    #include "compatibility.h"
    #include "console.h"
    #include "structs.h"

    #define FORTH_WORD_MAX          16      //Max size of word in source
    
    //Element count must be power of 2!
    #define FORTH_STACK_ELEMENTS    256
    #define FORTH_RSTACK_ELEMENTS   256
    #define FORTH_COMPAT_STACKS     xram    //Pointer to memory where stack and rstack are stored
    #define FORTH_MAX_SPACES        1500    //Max for SPACES primitive
    #define FORTH_DUMP_MAX_LINES    20      //Max lines for DUMP
    #define FORTH_DUMP_BYTES        8       //Bytes for DUMP to show per line
    #define FORTH_SCREEN_WIDTH      CONS_WHOLE_WIDTH    //Width in characters of screen for WORDS
    #define FORTH_ACCEPT_MAX        1000    //Max length in characters of buffer for ACCEPT

    extern struct ConsoleInfo *forth_console;

    void forth_print(const char *text);
    void forth_print_color(const char *text,color_t color);
    int32_t forth_accept(int32_t text_address,char *text_base,int32_t max_chars,uint32_t data_mask);
    int32_t forth_getkey(bool blocking);
    int32_t forth_printable(int32_t key);

#endif
