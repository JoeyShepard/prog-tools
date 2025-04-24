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
        //Data stack
        uintptr_t stack_base;
        int32_t *stack;

        //Return stack
        uintptr_t rstack_base;
        int32_t *rstack;

        //Data area - like dictionary but no definitions stored there
        uint8_t *data;

        //Compilation flags
        uint8_t state;

        //Compatibility functions - set at initialization so engine can adapt to different systems
        void (*print)(const char *text);
        int32_t max_spaces;
    };

#endif
