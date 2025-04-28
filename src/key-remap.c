#include "getkey.h"
#include "key-remap.h"

struct KeyRemap forth_keys[]=
{
    {4,     MODIFIER_NONE,          VKEY_a},
    {4,     MODIFIER_ALPHA_LOWER,   VKEY_a},
    {4,     MODIFIER_ALPHA_UPPER,   VKEY_A},
    {5,     MODIFIER_NONE,          VKEY_b},
    {5,     MODIFIER_ALPHA_LOWER,   VKEY_b},
    {5,     MODIFIER_ALPHA_UPPER,   VKEY_B},
    {6,     MODIFIER_NONE,          VKEY_c},
    {6,     MODIFIER_ALPHA_LOWER,   VKEY_c},
    {6,     MODIFIER_ALPHA_UPPER,   VKEY_C},
    {7,     MODIFIER_NONE,          VKEY_d},
    {7,     MODIFIER_ALPHA_LOWER,   VKEY_d},
    {7,     MODIFIER_ALPHA_UPPER,   VKEY_D},
    {8,     MODIFIER_NONE,          VKEY_e},
    {8,     MODIFIER_ALPHA_LOWER,   VKEY_e},
    {8,     MODIFIER_ALPHA_UPPER,   VKEY_E},
    {9,     MODIFIER_NONE,          VKEY_f},
    {9,     MODIFIER_ALPHA_LOWER,   VKEY_f},
    {9,     MODIFIER_ALPHA_UPPER,   VKEY_F},
    {10,    MODIFIER_NONE,          VKEY_g},
    {10,    MODIFIER_ALPHA_LOWER,   VKEY_g},
    {10,    MODIFIER_ALPHA_UPPER,   VKEY_G},
    {11,    MODIFIER_NONE,          VKEY_h},
    {11,    MODIFIER_ALPHA_LOWER,   VKEY_h},
    {11,    MODIFIER_ALPHA_UPPER,   VKEY_H},
    {12,    MODIFIER_NONE,          VKEY_i},
    {12,    MODIFIER_ALPHA_LOWER,   VKEY_i},
    {12,    MODIFIER_ALPHA_UPPER,   VKEY_I},
    {13,    MODIFIER_NONE,          VKEY_j},
    {13,    MODIFIER_ALPHA_LOWER,   VKEY_j},
    {13,    MODIFIER_ALPHA_UPPER,   VKEY_J},
    {14,    MODIFIER_NONE,          VKEY_k},
    {14,    MODIFIER_ALPHA_LOWER,   VKEY_k},
    {14,    MODIFIER_ALPHA_UPPER,   VKEY_K},
    {15,    MODIFIER_NONE,          VKEY_l},
    {15,    MODIFIER_ALPHA_LOWER,   VKEY_l},
    {15,    MODIFIER_ALPHA_UPPER,   VKEY_L},
    {16,    MODIFIER_NONE,          VKEY_m},
    {16,    MODIFIER_ALPHA_LOWER,   VKEY_m},
    {16,    MODIFIER_ALPHA_UPPER,   VKEY_M},
    {17,    MODIFIER_NONE,          VKEY_n},
    {17,    MODIFIER_ALPHA_LOWER,   VKEY_n},
    {17,    MODIFIER_ALPHA_UPPER,   VKEY_N},
    {18,    MODIFIER_NONE,          VKEY_o},
    {18,    MODIFIER_ALPHA_LOWER,   VKEY_o},
    {18,    MODIFIER_ALPHA_UPPER,   VKEY_O},
    {19,    MODIFIER_NONE,          VKEY_p},
    {19,    MODIFIER_ALPHA_LOWER,   VKEY_p},
    {19,    MODIFIER_ALPHA_UPPER,   VKEY_P},
    {20,    MODIFIER_NONE,          VKEY_q},
    {20,    MODIFIER_ALPHA_LOWER,   VKEY_q},
    {20,    MODIFIER_ALPHA_UPPER,   VKEY_Q},
    {21,    MODIFIER_NONE,          VKEY_r},
    {21,    MODIFIER_ALPHA_LOWER,   VKEY_r},
    {21,    MODIFIER_ALPHA_UPPER,   VKEY_R},
    {22,    MODIFIER_NONE,          VKEY_s},
    {22,    MODIFIER_ALPHA_LOWER,   VKEY_s},
    {22,    MODIFIER_ALPHA_UPPER,   VKEY_S},
    {23,    MODIFIER_NONE,          VKEY_t},
    {23,    MODIFIER_ALPHA_LOWER,   VKEY_t},
    {23,    MODIFIER_ALPHA_UPPER,   VKEY_T},
    {24,    MODIFIER_NONE,          VKEY_u},
    {24,    MODIFIER_ALPHA_LOWER,   VKEY_u},
    {24,    MODIFIER_ALPHA_UPPER,   VKEY_U},
    {25,    MODIFIER_NONE,          VKEY_v},
    {25,    MODIFIER_ALPHA_LOWER,   VKEY_v},
    {25,    MODIFIER_ALPHA_UPPER,   VKEY_V},
    {26,    MODIFIER_NONE,          VKEY_w},
    {26,    MODIFIER_ALPHA_LOWER,   VKEY_w},
    {26,    MODIFIER_ALPHA_UPPER,   VKEY_W},
    {27,    MODIFIER_NONE,          VKEY_x},
    {27,    MODIFIER_ALPHA_LOWER,   VKEY_x},
    {27,    MODIFIER_ALPHA_UPPER,   VKEY_X},
    {28,    MODIFIER_NONE,          VKEY_y},
    {28,    MODIFIER_ALPHA_LOWER,   VKEY_y},
    {28,    MODIFIER_ALPHA_UPPER,   VKEY_Y},
    {29,    MODIFIER_NONE,          VKEY_z},
    {29,    MODIFIER_ALPHA_LOWER,   VKEY_z},
    {29,    MODIFIER_ALPHA_UPPER,   VKEY_Z},

    {30,    MODIFIER_ALPHA_LOWER,   VKEY_1},            //1
    {30,    MODIFIER_ALPHA_UPPER,   VKEY_1},            //1
    {30,    MODIFIER_SHIFT_NONE,    VKEY_EXCLAMATION},  //1 -> !
    {31,    MODIFIER_ALPHA_LOWER,   VKEY_2},            //2
    {31,    MODIFIER_ALPHA_UPPER,   VKEY_2},            //2
    {31,    MODIFIER_SHIFT_NONE,    VKEY_AT},           //2 -> @
    {32,    MODIFIER_ALPHA_LOWER,   VKEY_3},            //3
    {32,    MODIFIER_ALPHA_UPPER,   VKEY_3},            //3
    {33,    MODIFIER_ALPHA_LOWER,   VKEY_4},            //4
    {33,    MODIFIER_ALPHA_UPPER,   VKEY_4},            //4
    {34,    MODIFIER_ALPHA_LOWER,   VKEY_5},            //5
    {34,    MODIFIER_ALPHA_UPPER,   VKEY_5},            //5
    {35,    MODIFIER_ALPHA_LOWER,   VKEY_6},            //6
    {35,    MODIFIER_ALPHA_UPPER,   VKEY_6},            //6
    {36,    MODIFIER_ALPHA_LOWER,   VKEY_7},            //7
    {36,    MODIFIER_ALPHA_UPPER,   VKEY_7},            //7
    {37,    MODIFIER_ALPHA_LOWER,   VKEY_8},            //8
    {37,    MODIFIER_ALPHA_UPPER,   VKEY_8},            //8
    {37,    MODIFIER_SHIFT_NONE,    VKEY_MUL},          //8 -> *
    {38,    MODIFIER_ALPHA_LOWER,   VKEY_9},            //9
    {38,    MODIFIER_ALPHA_UPPER,   VKEY_9},            //9
    {38,    MODIFIER_SHIFT_NONE,    VKEY_LEFTP},        //9 -> (
    {39,    MODIFIER_ALPHA_LOWER,   VKEY_0},            //0
    {39,    MODIFIER_ALPHA_UPPER,   VKEY_0},            //0
    {39,    MODIFIER_SHIFT_NONE,    VKEY_RIGHTP},       //0 -> )

    {44,    MODIFIER_NONE,          VKEY_SPACE},        //Space
    {44,    MODIFIER_ALPHA_LOWER,   VKEY_SPACE},        //Space
    {44,    MODIFIER_ALPHA_UPPER,   VKEY_SPACE},        //Space
    {44,    MODIFIER_SHIFT_NONE,    VKEY_SPACE},        //Space

    {45,    MODIFIER_NONE,          VKEY_SUB},          //-
    {45,    MODIFIER_ALPHA_LOWER,   VKEY_SUB},          //-
    {45,    MODIFIER_ALPHA_UPPER,   VKEY_SUB},          //-
    {46,    MODIFIER_NONE,          VKEY_EQUAL},        //=
    {46,    MODIFIER_ALPHA_LOWER,   VKEY_EQUAL},        //=
    {46,    MODIFIER_ALPHA_UPPER,   VKEY_EQUAL},        //=
    {46,    MODIFIER_SHIFT_NONE,    VKEY_ADD},          //= -> +
    {47,    MODIFIER_ALPHA_LOWER,   VKEY_LCBRACKET},    //[
    {47,    MODIFIER_ALPHA_UPPER,   VKEY_LCBRACKET},    //[
    {47,    MODIFIER_NONE,          VKEY_LCBRACKET},    //[
    {47,    MODIFIER_SHIFT_NONE,    VKEY_LSBRACKET},    //[ -> {
    {48,    MODIFIER_NONE,          VKEY_RCBRACKET},    //]
    {48,    MODIFIER_ALPHA_LOWER,   VKEY_RCBRACKET},    //]
    {48,    MODIFIER_ALPHA_UPPER,   VKEY_RCBRACKET},    //]
    {48,    MODIFIER_SHIFT_NONE,    VKEY_RSBRACKET},    //] -> }
    {51,    MODIFIER_NONE,          VKEY_SEMICOLON},    //;
    {51,    MODIFIER_ALPHA_LOWER,   VKEY_SEMICOLON},    //;
    {51,    MODIFIER_ALPHA_UPPER,   VKEY_SEMICOLON},    //;
    {51,    MODIFIER_SHIFT_NONE,    VKEY_COLON},        //; -> :
    {52,    MODIFIER_NONE,          VKEY_APOSTROPHE},   //'
    {52,    MODIFIER_ALPHA_LOWER,   VKEY_APOSTROPHE},   //'
    {52,    MODIFIER_ALPHA_UPPER,   VKEY_APOSTROPHE},   //'
    {52,    MODIFIER_SHIFT_NONE,    VKEY_QUOTE},        //' -> "
    {54,    MODIFIER_NONE,          VKEY_COMMA},        //,
    {54,    MODIFIER_ALPHA_LOWER,   VKEY_COMMA},        //,
    {54,    MODIFIER_ALPHA_UPPER,   VKEY_COMMA},        //,
    {54,    MODIFIER_SHIFT_NONE,    VKEY_LESS_THAN},    //, -> <
    {55,    MODIFIER_NONE,          VKEY_DOT},          //.
    {55,    MODIFIER_ALPHA_LOWER,   VKEY_DOT},          //.
    {55,    MODIFIER_ALPHA_UPPER,   VKEY_DOT},          //.
    {55,    MODIFIER_SHIFT_NONE,    VKEY_GREATER_THAN}, //. -> >
    {56,    MODIFIER_NONE,          VKEY_DIV},          // /
    {56,    MODIFIER_ALPHA_LOWER,   VKEY_DIV},          // /
    {56,    MODIFIER_ALPHA_UPPER,   VKEY_DIV},          // /
    {56,    MODIFIER_SHIFT_NONE,    VKEY_QUESTION},     // / -> ?

    //Marks end of list - DO NOT REMOVE!
    {0,0,0}
};

int forth_key_remap(int key)
{
    //Remap keys for characters not on keypad
    if (key==VKEY_RADIAN) key=VKEY_EXCLAMATION;
    else if (key==VKEY_THETA) key=VKEY_AT;
    else if (key==VKEY_LN) key=VKEY_APOSTROPHE;
    else if (key==VKEY_SIN) key=VKEY_QUESTION;
    else if (key==VKEY_COS) key=VKEY_COLON;
    else if (key==VKEY_TAN) key=VKEY_SEMICOLON;
    else if (key==VKEY_IMAG) key=VKEY_LESS_THAN;
    else if (key==VKEY_PI) key=VKEY_GREATER_THAN;

    //Remap existing keys on keypad for convenience
    if (key==VKEY_XOT) key=VKEY_x;
    else if (key==VKEY_NEG) key=VKEY_SPACE;

    return key;
}
