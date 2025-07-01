#include "compatibility.h"
#include "getkey.h"
#include "key-remap.h"

int forth_key_remap(int key)
{
    //Remap keys for characters not on keypad
    if (key==VKEY_XOT) key=VKEY_AT;
    else if (key==VKEY_LOG) key=VKEY_EXCLAMATION;
    else if (key==VKEY_LN) key=VKEY_COLON;
    else if (key==VKEY_SIN) key=VKEY_SEMICOLON;
    else if (key==VKEY_COS) key=VKEY_APOSTROPHE;
    else if (key==VKEY_TAN) key=VKEY_QUESTION;
    else if (key==key_shifted[VKEY_XOT]) key=VKEY_HASH;
    else if (key==key_shifted[VKEY_LOG]) key=VKEY_DOLLAR;
    else if (key==key_shifted[VKEY_LN]) key=VKEY_PERCENT;
    else if (key==key_shifted[VKEY_SIN]) key=VKEY_AMPERSAND;
    else if (key==key_shifted[VKEY_COS]) key=VKEY_PIPE;
    else if (key==key_shifted[VKEY_TAN]) key=VKEY_BACKSLASH;
    else if (key==key_shifted[VKEY_0]) key=VKEY_LESS_THAN;
    else if (key==key_shifted[VKEY_EXP]) key=VKEY_GREATER_THAN;
    //Remap existing keys on keypad for convenience
    else if (key==VKEY_SQUARE) key=VKEY_x;
    else if (key==key_lower[VKEY_SQUARE]) key=VKEY_x;
    else if (key==key_upper[VKEY_SQUARE]) key=VKEY_x;
    else if (key==VKEY_NEG) key=VKEY_SPACE;
    else if (key==key_shifted[VKEY_NEG]) key=VKEY_UNDERSCORE;

    return key;
}
