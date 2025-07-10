//Compatibility layer for Forth engine so engine can be reused on different platforms

#ifndef __GUARD_PROG_TOOLS_FORTH_COMPATIBILITY
    #define __GUARD_PROG_TOOLS_FORTH_COMPATIBILITY
    
    #include "compatibility.h"
    #include "console.h"
    #include "structs.h"

    #define FORTH_WORD_MAX          16      //Max size of word in source
    
    //Element counts must be power of 2!
    #define FORTH_STACK_ELEMENTS    256     //int32_t                   1K
    //TODO: double check sizeof struct
    #define FORTH_RSTACK_ELEMENTS   256     //struct ForthRStackElement 2k
    #define FORTH_LOCALS_ELEMENTS   512     //int32_t                   2k
    #define FORTH_COMPAT_STACKS     xram    //Pointer to memory where stacks are stored
    #define FORTH_MAX_SPACES        1500    //Max for SPACES primitive
    #define FORTH_DUMP_MAX_LINES    20      //Max lines for DUMP
    #define FORTH_DUMP_BYTES        8       //Bytes for DUMP to show per line
    //TODO: input can't be larger than screen yet
    //max 54 chars wide and 11 lines tall but there MUST be text on at least first line
    #define FORTH_ACCEPT_MAX        500     //Max length in characters of buffer for ACCEPT
    #define FORTH_MEM_DATA          0x10000 //Default size of Forth data memory
    #define FORTH_MEM_DATA_MIN      0x400   //Min size of Forth data memory

    extern struct ConsoleInfo *forth_console;

    void forth_print(const char *text);
    void forth_print_color(const char *text,color_t color);
    int32_t forth_input(int32_t text_address,char *text_base,int32_t max_chars,uint32_t data_mask);
    int32_t forth_getkey(bool blocking);
    int32_t forth_printable(int32_t key);
    void forth_update_screen();
    void forth_update_modifiers();
    void forth_clear_console();

#endif
