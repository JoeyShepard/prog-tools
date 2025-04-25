#include "getkey.h"
#include "key-remap.h"

struct KeyRemap forth_keys[]=
{
    {44,    MODIFIER_NONE,          VKEY_SPACE},
    {44,    MODIFIER_ALPHA_LOWER,   VKEY_SPACE},
    {44,    MODIFIER_ALPHA_UPPER,   VKEY_SPACE},
    {44,    MODIFIER_SHIFT_NONE,    VKEY_SPACE},
    {44,    MODIFIER_NONE,          VKEY_SPACE},

    //Marks end of list - DO NOT REMOVE!
    {0,0,0}
};
