//structs shared between headers (ie not all structs stored here)

#ifndef __GUARD_PROG_TOOLS_STRUCTS
    #define __GUARD_PROG_TOOLS_STRUCTS

    #include <stdint.h>

    #define TAB_TITLE_LEN       11      //Title size including x: and terminating 0

    struct Point
    {
        int x;
        int y;
    };

    struct WindowInfo
    {
        int split_state;
        int selected_split;
        struct SplitInfo
        {
            int ID;
            int menu_selection;
        } split[2];
        int tab_index;
    };

    struct ForthEngine
    {
        int32_t *stack_upper;
        int32_t *stack;
        int32_t *rstack_upper;
        int32_t *rstack;
        uint8_t *data;
    };

#endif
