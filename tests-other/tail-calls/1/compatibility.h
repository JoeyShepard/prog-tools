#ifndef __GUARD_CG50_SDL2_COMPATIBILITY
    #define __GUARD_CG50_SDL2_COMPATIBILITY

    #include <stdbool.h>
    #include <stdint.h>

    #include "types.h"

    //Elements common to calculator and PC versions
    #define HEAP_SIZE       0x200000
    #define XRAM_SIZE       0x2000  //8K
    #define YRAM_SIZE       0x2000  //8K

    #define COL_MAX         0x1F
    #define COL_1_4         0x8
    #define COL_MID         0x10
    #define COL_3_4         0x18
    #define COL_7_8         0x1C

    #ifndef C_RGB
        #define C_RGB(r,g,b) (((r) << 11) | ((g) << 6) | (b))
    #endif

    //Note these are not the 9860 compatible colors from gint!
    #define COL_WHITE       C_RGB(COL_MAX,COL_MAX,COL_MAX)
    #define COL_BLACK       C_RGB(0,0,0)
    #define COL_GRAY        C_RGB(COL_MID,COL_MID,COL_MID)
    #define COL_RED         C_RGB(COL_MAX,0,0)
    #define COL_GREEN       C_RGB(0,COL_MAX,0)
    #define COL_BLUE        C_RGB(0,0,COL_MAX)
    #define COL_YELLOW      C_RGB(COL_MAX,COL_MAX,0)
    #define COL_MAGENTA     C_RGB(COL_MAX,0,COL_MAX)
    #define COL_CYAN        C_RGB(0,COL_MAX,COL_MAX)

    #define COL_PURPLE      C_RGB(COL_3_4,0,COL_3_4)
    #define COL_ORANGE      C_RGB(COL_MAX,COL_MID,0)
    //TODO: doesn't -1 as int16_t (ie color_t) also encode as transparent?
    //Compatibility functions take color as int32_t to pass transparency as 0xFFFFFFFF
    #define COL_TRANS       -1  

    //Key remapping for PC so typing is easier
    struct KeyRemap
    {
        int key;
        int modifier;
        int new_key;
    };

    //Global variables
    extern uint8_t *heap;
    extern uint8_t *xram;
    extern uint8_t *yram;
    //Copy of address from malloc later passed to free
    extern uint8_t *xram_base;
    extern uint8_t *yram_base;
    //Whether ON key is currently down - updated in interrupt on calculator and thread on PC
    extern volatile bool *on_key_pressed;
    extern volatile bool *on_key_executing;
    
    //Functions common to PC and CG50 (some are empty)
    void setup(int scale_factor,int tick_ms);
    void delay();
    void wrapper_exit();
    void wrapper_screenshot();
    int wrapper_pc_key();
    int wrapper_remap_key(int modifier,int key,struct KeyRemap *keys);
    char *wrapper_normalize_path(const char *path,int local_path_max);

    #ifdef CG50
        //Compiling for calculator. CG50 defined in CMakeLists.txt.

        #include <gint/display.h>
        #include <gint/gint.h>
        #include <gint/keyboard.h>

    #else
        //Compiling for PC using SDL2 wrapper

        //Constants from gint
        #define DWIDTH          396
        #define DHEIGHT         224

        enum
        {
            KEY_F1		= 0x91,
            KEY_F2		= 0x92,
            KEY_F3		= 0x93,
            KEY_F4		= 0x94,
            KEY_F5		= 0x95,
            KEY_F6		= 0x96,

            KEY_SHIFT	= 0x81,
            KEY_OPTN	= 0x82, //todo
            KEY_VARS	= 0x83, //todo
            KEY_MENU	= 0x84, //todo
            KEY_LEFT	= 0x85,
            KEY_UP		= 0x86,

            KEY_ALPHA	= 0x71,
            KEY_SQUARE	= 0x72, //todo
            KEY_POWER	= 0x73, //todo
            KEY_EXIT	= 0x74,
            KEY_DOWN	= 0x75,
            KEY_RIGHT	= 0x76,

            KEY_XOT		= 0x61,
            KEY_LOG		= 0x62,
            KEY_LN		= 0x63,
            KEY_SIN		= 0x64,
            KEY_COS		= 0x65,
            KEY_TAN		= 0x66,

            KEY_FRAC	= 0x51,
            KEY_FD		= 0x52,
            KEY_LEFTP	= 0x53,
            KEY_RIGHTP	= 0x54,
            KEY_COMMA	= 0x55,
            KEY_ARROW	= 0x56,

            KEY_7		= 0x41,
            KEY_8		= 0x42,
            KEY_9		= 0x43,
            KEY_DEL		= 0x44,
            /* AC/ON has keycode 0x07 instead of 0x45 */

            KEY_4		= 0x31,
            KEY_5		= 0x32,
            KEY_6		= 0x33,
            KEY_MUL		= 0x34,
            KEY_DIV		= 0x35,

            KEY_1		= 0x21,
            KEY_2		= 0x22,
            KEY_3		= 0x23,
            KEY_ADD		= 0x24,
            KEY_SUB		= 0x25,

            KEY_0		= 0x11,
            KEY_DOT		= 0x12,
            KEY_EXP		= 0x13,
            KEY_NEG		= 0x14, //todo
            KEY_EXE		= 0x15,

            KEY_ACON	= 0x07  //todo
        };

        //Dummy macros for gint_world_switch
        #define gint_world_switch(x) x
        #define GINT_CALL(x,y) x(y)

        //Constants needed for wrapper
        #define WINDOW_TITLE    "SDL2 wrapper for fx-CG50"
        
        //structs
        #ifndef uint
            typedef unsigned int uint;
        #endif
        typedef struct
        {
            uint time	:16;/* Time of event, unique over short periods */

            uint		:2;	/* Reserved for future use */

            uint mod	:1;	/* Whether modifiers are used */
            uint shift	:1;	/* If mod=1, whether SHIFT was pressed */
            uint alpha	:1;	/* If mod=1, whether ALPHA was pressed */

            uint type	:3;	/* Type of key event */
            uint key	:8;	/* Hit key */

        } key_event_t;
        
        enum
        {
            KEYEV_NONE   = 0,	/* No event available (poll() only) */
            KEYEV_DOWN   = 1,	/* Key was pressed */
            KEYEV_UP     = 2,	/* Key was released */
            KEYEV_HOLD   = 3,	/* A key that was pressed has been held down */
            KEYEV_OSMENU = 4,	/* We went to the main menu and back */
        };

        enum {
            /* Enable modifiers keys */
            GETKEY_MOD_SHIFT      = 0x0001,
            GETKEY_MOD_ALPHA      = 0x0002,
            /* SHIFT + OPTN (requires GETKEY_MOD_SHIFT) or LIGHT toggles backlight */
            GETKEY_BACKLIGHT      = 0x0004,
            /* MENU triggers a task switch and displays the main menu */
            GETKEY_MENU           = 0x0008,
            /* Repeat arrow keys, or even all keys */
            GETKEY_REP_ARROWS     = 0x0010,
            GETKEY_REP_ALL        = 0x0020,
            /* Enable custom repeat profiles; see getkey_set_repeat_profile() */
            GETKEY_REP_PROFILE    = 0x0040,
            /* Enable application shortcuts; see getkey_set_feature_function() */
            GETKEY_FEATURES       = 0x0080,
            /* After coming back from the main menu, redraw the screen with dupdate */
            GETKEY_MENU_DUPDATE   = 0x0100,
            /* After coming back from the main menu, send a KEYEV_OSMENU event */
            GETKEY_MENU_EVENT     = 0x0200,
            /* Enable power off with SHIFT + AC/ON */
            GETKEY_POWEROFF       = 0x0400,

            /* No modifiers */
            GETKEY_NONE           = 0x0000,
            /* Default settings of getkey() */
            GETKEY_DEFAULT        = 0x05df,
        };

        //gint replacement functions
        void dgetvram(uint16_t **main, uint16_t **secondary);
        void dclear(uint16_t color);
        void dupdate(void);
        key_event_t getkey_opt(int options, volatile int *timeout);
        void gint_osmenu();
        void gint_poweroff(bool show_logo);
        char *fs_path_normalize(char const *path);

    #endif
#endif

