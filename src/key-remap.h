#ifndef __GUARD_PROG_TOOLS_KEY_REMAP
    #define __GUARD_PROG_TOOLS_KEY_REMAP

    #include "compatibility.h"
    #include "getkey.h"

    //Remap keys on PC only for easiee debugging. Not used on calculator.
    extern struct KeyRemap forth_keys[];
    
    //Remap keys on calculator keypad for keys that don't exist like : and !
    int forth_key_remap();
#endif
