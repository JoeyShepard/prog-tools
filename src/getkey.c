#include <stdbool.h>
#include "command.h"
#include "compatibility.h"
#include "getkey.h"
#include "structs.h"

//Tables not externally viewable
static const int key_convert[]=
{
    0,              //0x0
    0,              //0x1
    0,              //0x2
    0,              //0x3
    0,              //0x4
    0,              //0x5
    0,              //0x6
    VKEY_ACON,      //0x7
    0,              //0x8
    0,              //0x9
    0,              //0xA
    0,              //0xB
    0,              //0xC
    0,              //0xD
    0,              //0xE
    0,              //0xF
    0,              //0x10
    VKEY_0,         //0x11
    VKEY_DOT,       //0x12
    VKEY_EXP,       //0x13
    VKEY_NEG,       //0x14
    VKEY_EXE,       //0x15
    0,              //0x16
    0,              //0x17
    0,              //0x18
    0,              //0x19
    0,              //0x1A
    0,              //0x1B
    0,              //0x1C
    0,              //0x1D
    0,              //0x1E
    0,              //0x1F
    0,              //0x20
    VKEY_1,         //0x21
    VKEY_2,         //0x22
    VKEY_3,         //0x23
    VKEY_ADD,       //0x24
    VKEY_SUB,       //0x25
    0,              //0x26
    0,              //0x27
    0,              //0x28
    0,              //0x29
    0,              //0x2A
    0,              //0x2B
    0,              //0x2C
    0,              //0x2D
    0,              //0x2E
    0,              //0x2F
    0,              //0x30
    VKEY_4,         //0x31
    VKEY_5,         //0x32
    VKEY_6,         //0x33
    VKEY_MUL,       //0x34
    VKEY_DIV,       //0x35
    0,              //0x36
    0,              //0x37
    0,              //0x38
    0,              //0x39
    0,              //0x3A
    0,              //0x3B
    0,              //0x3C
    0,              //0x3D
    0,              //0x3E
    0,              //0x3F
    0,              //0x40
    VKEY_7,         //0x41
    VKEY_8,         //0x42
    VKEY_9,         //0x43
    VKEY_DEL,       //0x44
    0,              //0x45
    0,              //0x46
    0,              //0x47
    0,              //0x48
    0,              //0x49
    0,              //0x4A
    0,              //0x4B
    0,              //0x4C
    0,              //0x4D
    0,              //0x4E
    0,              //0x4F
    0,              //0x50
    VKEY_FRAC,      //0x51
    VKEY_FD,        //0x52
    VKEY_LEFTP,     //0x53
    VKEY_RIGHTP,    //0x54
    VKEY_COMMA,     //0x55
    VKEY_ARROW,     //0x56
    0,              //0x57
    0,              //0x58
    0,              //0x59
    0,              //0x5A
    0,              //0x5B
    0,              //0x5C
    0,              //0x5D
    0,              //0x5E
    0,              //0x5F
    0,              //0x60
    VKEY_XOT,       //0x61
    VKEY_LOG,       //0x62
    VKEY_LN,        //0x63
    VKEY_SIN,       //0x64
    VKEY_COS,       //0x65
    VKEY_TAN,       //0x66
    0,              //0x67
    0,              //0x68
    0,              //0x69
    0,              //0x6A
    0,              //0x6B
    0,              //0x6C
    0,              //0x6D
    0,              //0x6E
    0,              //0x6F
    0,              //0x70
    VKEY_ALPHA,     //0x71
    VKEY_SQUARE,    //0x72
    VKEY_POWER,     //0x73
    VKEY_EXIT,      //0x74
    VKEY_DOWN,      //0x75
    VKEY_RIGHT,     //0x76
    0,              //0x77
    0,              //0x78
    0,              //0x79
    0,              //0x7A
    0,              //0x7B
    0,              //0x7C
    0,              //0x7D
    0,              //0x7E
    0,              //0x7F
    0,              //0x80
    VKEY_SHIFT,     //0x81
    VKEY_OPTN,      //0x82
    VKEY_VARS,      //0x83
    VKEY_MENU,      //0x84
    VKEY_LEFT,      //0x85
    VKEY_UP,        //0x86
    0,              //0x87
    0,              //0x88
    0,              //0x89
    0,              //0x8A
    0,              //0x8B
    0,              //0x8C
    0,              //0x8D
    0,              //0x8E
    0,              //0x8F
    0,              //0x90
    VKEY_F1,        //0x91
    VKEY_F2,        //0x92
    VKEY_F3,        //0x93
    VKEY_F4,        //0x94
    VKEY_F5,        //0x95
    VKEY_F6,        //0x96
};


//Externally visible tables
const int key_shifted[]=
{
    VKEY_NONE,
    VKEY_ACOFF,         //VKEY_ACON     ->  VKEY_ACOFF
    VKEY_IMAG,          //VKEY_0        -> VKEY_IMAG
    VKEY_EQUAL,         //VKEY_DOT      -> VKEY_EQUAL
    VKEY_PI,            //VKEY_EXP      -> VKEY_PI
    VKEY_ANS,           //VKEY_NEG      -> VKEY_ANS
    VKEY_SHIFT_EXE,     //VKEY_EXE      -> VKEY_SHIFT_EXE
    VKEY_LIST,          //VKEY_1        -> VKEY_LIST
    VKEY_MAT,           //VKEY_2        -> VKEY_MAT
    VKEY_NONE,          //VKEY_3        -> VKEY_NONE
    VKEY_LSBRACKET,     //VKEY_ADD      -> VKEY_LSBRACKET
    VKEY_RSBRACKET,     //VKEY_SUB      -> VKEY_RSBRACKET
    VKEY_CATALOG,       //VKEY_4        -> VKEY_CATALOG
    VKEY_FORMAT,        //VKEY_5        -> VKEY_FORMAT
    VKEY_NONE,          //VKEY_6        -> VKEY_NONE
    VKEY_LCBRACKET,     //VKEY_MUL      -> VKEY_LCBRACKET
    VKEY_RCBRACKET,     //VKEY_DIV      -> VKEY_RCBRACKET
    VKEY_CAPTURE,       //VKEY_7        -> VKEY_CAPTURE
    VKEY_CLIP,          //VKEY_8        -> VKEY_CLIP
    VKEY_PASTE,         //VKEY_9        -> VKEY_PASTE
    VKEY_INS,           //VKEY_DEL      -> VKEY_INS
    VKEY_SHIFT_FRAC,    //VKEY_FRAC     -> VKEY_SHIFT_FRAC
    VKEY_SHIFT_FD,      //VKEY_FD       -> VKEY_SHIFT_FD
    VKEY_CUBE_ROOT,     //VKEY_LEFTP    -> VKEY_CUBE_ROOT
    VKEY_1_X,           //VKEY_RIGHTP   -> VKEY_1_X
    VKEY_NEXT_SCREEN,   //VKEY_COMMA    -> VKEY_NEXT_SCREEN
    VKEY_SWAP_SCREEN,   //VKEY_ARROW    -> VKEY_SWAP_SCREEN
    VKEY_ANGLE,         //VKEY_XOT      -> VKEY_ANGLE
    VKEY_10_X,          //VKEY_LOG      -> VKEY_10_X
    VKEY_E_X,           //VKEY_LN       -> VKEY_E_X
    VKEY_ASIN,          //VKEY_SIN      -> VKEY_ASIN
    VKEY_ACOS,          //VKEY_COS      -> VKEY_ACOS
    VKEY_ATAN,          //VKEY_TA       -> VKEY_ATAN
    VKEY_A_LOCK,        //VKEY_ALPHA    -> VKEY_A_LOCK
    VKEY_SQRT,          //VKEY_SQUARE   -> VKEY_SQRT
    VKEY_X_ROOT,        //VKEY_POWER    -> VKEY_X_ROOT
    VKEY_QUIT,          //VKEY_EXIT     -> VKEY_QUIT
    VKEY_SHIFT_DOWN,    //VKEY_DOWN     -> VKEY_SHIFT_DOWN
    VKEY_SHIFT_RIGHT,   //VKEY_RIGHT    -> VKEY_SHIFT_RIGHT
    VKEY_SHIFT,
    VKEY_SHIFT_OPTN,    //VKEY_OPTN     -> VKEY_SHIFT_OPTN
    VKEY_PRGM,          //VKEY_VARS     -> VKEY_PRGM
    VKEY_SET_UP,        //VKEY_MENU     -> VKEY_SET_UP
    VKEY_SHIFT_LEFT,    //VKEY_LEFT     -> VKEY_SHIFT_LEFT
    VKEY_SHIFT_UP,      //VKEY_UP       -> VKEY_SHIFT_UP
    VKEY_SHIFT_F1,      //VKEY_F1       -> VKEY_SHIFT_F1
    VKEY_SHIFT_F2,      //VKEY_F2       -> VKEY_SHIFT_F2
    VKEY_SHIFT_F3,      //VKEY_F3       -> VKEY_SHIFT_F3
    VKEY_SHIFT_F4,      //VKEY_F4       -> VKEY_SHIFT_F4
    VKEY_SHIFT_F5,      //VKEY_F5       -> VKEY_SHIFT_F5
    VKEY_SHIFT_F6,      //VKEY_F6       -> VKEY_SHIFT_F6
};

const int key_upper[]=
{
    VKEY_NONE,
    VKEY_ACON,
    VKEY_Z,             //VKEY_0        -> VKEY_Z
    VKEY_SPACE,         //VKEY_DOT      -> VKEY_SPACE
    VKEY_QUOTE,         //VKEY_EXP      -> VKEY_QUOTE
    VKEY_NEG,
    VKEY_EXE,
    VKEY_U,             //VKEY_1        -> VKEY_U
    VKEY_V,             //VKEY_2        -> VKEY_V
    VKEY_W,             //VKEY_3        -> VKEY_W
    VKEY_X,             //VKEY_ADD      -> VKEY_X
    VKEY_Y,             //VKEY_SUB      -> VKEY_Y
    VKEY_P,             //VKEY_4        -> VKEY_P
    VKEY_Q,             //VKEY_5        -> VKEY_Q
    VKEY_R,             //VKEY_6        -> VKEY_R
    VKEY_S,             //VKEY_MUL      -> VKEY_S
    VKEY_T,             //VKEY_DIV      -> VKEY_T
    VKEY_M,             //VKEY_7        -> VKEY_M
    VKEY_N,             //VKEY_8        -> VKEY_N
    VKEY_O,             //VKEY_9        -> VKEY_O
    VKEY_UNDO,          //VKEY_DEL      -> VKEY_UNDO
    VKEY_G,             //VKEY_FRAC     -> VKEY_G
    VKEY_H,             //VKEY_FD       -> VKEY_H
    VKEY_I,             //VKEY_LEFTP    -> VKEY_I
    VKEY_J,             //VKEY_RIGHTP   -> VKEY_J
    VKEY_K,             //VKEY_COMMA    -> VKEY_K
    VKEY_L,             //VKEY_ARROW    -> VKEY_L
    VKEY_A,             //VKEY_XOT      -> VKEY_A
    VKEY_B,             //VKEY_LOG      -> VKEY_B
    VKEY_C,             //VKEY_LN       -> VKEY_C
    VKEY_D,             //VKEY_SIN      -> VKEY_D
    VKEY_E,             //VKEY_COS      -> VKEY_E
    VKEY_F,             //VKEY_TA       -> VKEY_F
    VKEY_ALPHA,
    VKEY_RADIAN,        //VKEY_SQUARE   -> VKEY_RADIAN
    VKEY_THETA,         //VKEY_POWER    -> VKEY_THETA
    VKEY_EXIT,
    VKEY_DOWN,
    VKEY_RIGHT,
    VKEY_SHIFT,
    VKEY_OPTN,
    VKEY_VARS,
    VKEY_MENU,
    VKEY_LEFT,
    VKEY_UP,
    VKEY_F1,
    VKEY_F2,
    VKEY_F3,
    VKEY_F4,
    VKEY_F5,
    VKEY_F6,
};

const int key_lower[]=
{
    VKEY_NONE,
    VKEY_ACON,
    VKEY_z,             //VKEY_0        -> VKEY_z
    VKEY_SPACE,         //VKEY_DOT      -> VKEY_SPACE
    VKEY_QUOTE,         //VKEY_EXP      -> VKEY_QUOTE
    VKEY_NEG,
    VKEY_EXE,
    VKEY_u,             //VKEY_1        -> VKEY_u
    VKEY_v,             //VKEY_2        -> VKEY_v
    VKEY_w,             //VKEY_3        -> VKEY_w
    VKEY_x,             //VKEY_ADD      -> VKEY_x
    VKEY_y,             //VKEY_SUB      -> VKEY_y
    VKEY_p,             //VKEY_4        -> VKEY_p
    VKEY_q,             //VKEY_5        -> VKEY_q
    VKEY_r,             //VKEY_6        -> VKEY_r
    VKEY_s,             //VKEY_MUL      -> VKEY_s
    VKEY_t,             //VKEY_DIV      -> VKEY_t
    VKEY_m,             //VKEY_7        -> VKEY_m
    VKEY_n,             //VKEY_8        -> VKEY_n
    VKEY_o,             //VKEY_9        -> VKEY_o
    VKEY_UNDO,          //VKEY_DEL      -> VKEY_UNDO
    VKEY_g,             //VKEY_FRAC     -> VKEY_g
    VKEY_h,             //VKEY_FD       -> VKEY_h
    VKEY_i,             //VKEY_LEFTP    -> VKEY_i
    VKEY_j,             //VKEY_RIGHTP   -> VKEY_j
    VKEY_k,             //VKEY_COMMA    -> VKEY_k
    VKEY_l,             //VKEY_ARROW    -> VKEY_l
    VKEY_a,             //VKEY_XOT      -> VKEY_a
    VKEY_b,             //VKEY_LOG      -> VKEY_b
    VKEY_c,             //VKEY_LN       -> VKEY_c
    VKEY_d,             //VKEY_SIN      -> VKEY_d
    VKEY_e,             //VKEY_COS      -> VKEY_e
    VKEY_f,             //VKEY_TA       -> VKEY_f
    VKEY_ALPHA,
    VKEY_RADIAN,        //VKEY_SQUARE   -> VKEY_RADIAN
    VKEY_THETA,         //VKEY_POWER    -> VKEY_THETA
    VKEY_EXIT,
    VKEY_DOWN,
    VKEY_RIGHT,
    VKEY_SHIFT,
    VKEY_OPTN,
    VKEY_VARS,
    VKEY_MENU,
    VKEY_LEFT,
    VKEY_UP,
    VKEY_F1,
    VKEY_F2,
    VKEY_F3,
    VKEY_F4,
    VKEY_F5,
    VKEY_F6,
};

const int key_printable[]=
{
    0,      //VKEY_NONE
    0,      //VKEY_ACON
    '0',    //VKEY_0
    '.',    //VKEY_DOT
    0,      //VKEY_EXP
    0,      //VKEY_NEG
    0,      //VKEY_EXE
    '1',    //VKEY_1
    '2',    //VKEY_2
    '3',    //VKEY_3
    '+',    //VKEY_ADD
    '-',    //VKEY_SUB
    '4',    //VKEY_4
    '5',    //VKEY_5
    '6',    //VKEY_6
    '*',    //VKEY_MUL
    '/',    //VKEY_DIV
    '7',    //VKEY_7
    '8',    //VKEY_8
    '9',    //VKEY_9
    0,      //VKEY_DEL
    0,      //VKEY_FRAC
    0,      //VKEY_FD
    '(',    //VKEY_LEFTP
    ')',    //VKEY_RIGHTP
    ',',    //VKEY_COMMA
    0,      //VKEY_ARROW
    0,      //VKEY_XOT
    0,      //VKEY_LOG
    0,      //VKEY_LN
    0,      //VKEY_SIN
    0,      //VKEY_COS
    0,      //VKEY_TA
    0,      //VKEY_ALPHA
    0,      //VKEY_SQUARE
    '^',    //VKEY_POWER
    0,      //VKEY_EXIT
    0,      //VKEY_DOWN
    0,      //VKEY_RIGHT
    0,      //VKEY_SHIFT
    0,      //VKEY_OPTN
    0,      //VKEY_VARS
    0,      //VKEY_MENU
    0,      //VKEY_LEFT
    0,      //VKEY_UP
    0,      //VKEY_F1
    0,      //VKEY_F2
    0,      //VKEY_F3
    0,      //VKEY_F4
    0,      //VKEY_F5
    0,      //VKEY_F6
};

const int key_printable_shifted[]=
{
    0,      //VKEY_NONE
    0,      //VKEY_ACON
    0,      //VKEY_0
    '=',    //VKEY_DOT
    0,      //VKEY_EXP
    0,      //VKEY_NEG
    0,      //VKEY_EXE
    0,      //VKEY_1
    0,      //VKEY_2
    0,      //VKEY_3
    '[',    //VKEY_ADD
    ']',    //VKEY_SUB
    0,      //VKEY_4
    0,      //VKEY_5
    0,      //VKEY_6
    '{',    //VKEY_MUL
    '}',    //VKEY_DIV
    0,      //VKEY_7
    0,      //VKEY_8
    0,      //VKEY_9
    0,      //VKEY_DEL
    0,      //VKEY_FRAC
    0,      //VKEY_FD
    0,      //VKEY_LEFTP
    0,      //VKEY_RIGHTP
    0,      //VKEY_COMMA
    0,      //VKEY_ARROW
    0,      //VKEY_XOT
    0,      //VKEY_LOG
    0,      //VKEY_LN
    0,      //VKEY_SIN
    0,      //VKEY_COS
    0,      //VKEY_TA
    0,      //VKEY_ALPHA
    0,      //VKEY_SQUARE
    0,      //VKEY_POWER
    0,      //VKEY_EXIT
    0,      //VKEY_DOWN
    0,      //VKEY_RIGHT
    0,      //VKEY_SHIFT
    0,      //VKEY_OPTN
    0,      //VKEY_VARS
    0,      //VKEY_MENU
    0,      //VKEY_LEFT
    0,      //VKEY_UP
    0,      //VKEY_F1
    0,      //VKEY_F2
    0,      //VKEY_F3
    0,      //VKEY_F4
    0,      //VKEY_F5
    0,      //VKEY_F6
};

const int key_printable_upper[]=
{
    0,      //VKEY_NONE
    0,      //VKEY_ACON
    'Z',    //VKEY_0
    ' ',    //VKEY_DOT
    '"',    //VKEY_EXP
    '-',    //VKEY_NEG
    0,      //VKEY_EXE
    'U',    //VKEY_1
    'V',    //VKEY_2
    'W',    //VKEY_3
    'X',    //VKEY_ADD
    'Y',    //VKEY_SUB
    'P',    //VKEY_4
    'Q',    //VKEY_5
    'R',    //VKEY_6
    'S',    //VKEY_MUL
    'T',    //VKEY_DIV
    'M',    //VKEY_7
    'N',    //VKEY_8
    'O',    //VKEY_9
    0,      //VKEY_DEL
    'G',    //VKEY_FRAC
    'H',    //VKEY_FD
    'I',    //VKEY_LEFTP
    'J',    //VKEY_RIGHTP
    'K',    //VKEY_COMMA
    'L',    //VKEY_ARROW
    'A',    //VKEY_XOT
    'B',    //VKEY_LOG
    'C',    //VKEY_LN
    'D',    //VKEY_SIN
    'E',    //VKEY_COS
    'F',    //VKEY_TA
    0,      //VKEY_ALPHA
    0,      //VKEY_SQUARE
    0,      //VKEY_POWER
    0,      //VKEY_EXIT
    0,      //VKEY_DOWN
    0,      //VKEY_RIGHT
    0,      //VKEY_SHIFT
    0,      //VKEY_OPTN
    0,      //VKEY_VARS
    0,      //VKEY_MENU
    0,      //VKEY_LEFT
    0,      //VKEY_UP
    0,      //VKEY_F1
    0,      //VKEY_F2
    0,      //VKEY_F3
    0,      //VKEY_F4
    0,      //VKEY_F5
    0,      //VKEY_F6
};

const int key_printable_lower[]=
{
    0,      //VKEY_NONE
    0,      //VKEY_ACON
    'z',    //VKEY_0
    ' ',    //VKEY_DOT
    '"',    //VKEY_EXP
    '-',    //VKEY_NEG
    0,      //VKEY_EXE
    'u',    //VKEY_1
    'v',    //VKEY_2
    'w',    //VKEY_3
    'x',    //VKEY_ADD
    'y',    //VKEY_SUB
    'p',    //VKEY_4
    'q',    //VKEY_5
    'r',    //VKEY_6
    's',    //VKEY_MUL
    't',    //VKEY_DIV
    'm',    //VKEY_7
    'n',    //VKEY_8
    'o',    //VKEY_9
    0,      //VKEY_DEL
    'g',    //VKEY_FRAC
    'h',    //VKEY_FD
    'i',    //VKEY_LEFTP
    'j',    //VKEY_RIGHTP
    'k',    //VKEY_COMMA
    'l',    //VKEY_ARROW
    'a',    //VKEY_XOT
    'b',    //VKEY_LOG
    'c',    //VKEY_LN
    'd',    //VKEY_SIN
    'e',    //VKEY_COS
    'f',    //VKEY_TA
    0,      //VKEY_ALPHA
    0,      //VKEY_SQUARE
    0,      //VKEY_POWER
    0,      //VKEY_EXIT
    0,      //VKEY_DOWN
    0,      //VKEY_RIGHT
    0,      //VKEY_SHIFT
    0,      //VKEY_OPTN
    0,      //VKEY_VARS
    0,      //VKEY_MENU
    0,      //VKEY_LEFT
    0,      //VKEY_UP
    0,      //VKEY_F1
    0,      //VKEY_F2
    0,      //VKEY_F3
    0,      //VKEY_F4
    0,      //VKEY_F5
    0,      //VKEY_F6
};

int getkey_wrapper(bool wait)
{
    if (wait)
    {
        //Wait for keypress

        //Worked on calculator but menu key didn't work
        /*
        key_event_t e;
        e=getkey_opt(GETKEY_ARGS,NULL);
        return key_convert[e.key];
        */
        int timeout=1;
        key_event_t e;
        while (true)
        {
            e=getkey_opt(GETKEY_ARGS,&timeout);
            if (e.type!=KEYEV_NONE) return key_convert[e.key];
            delay();
        }
    }
    else
    {
        //Don't wait for keypress
        int timeout=1;
        key_event_t e;
        e=getkey_opt(GETKEY_ARGS,&timeout);
        if (e.type!=KEYEV_NONE) return key_convert[e.key];
        return key_convert[0];
    }

}

