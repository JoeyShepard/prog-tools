//structs shared between headers

#ifndef __GUARD_PROG_TOOLS_STRUCTS
    #define __GUARD_PROG_TOOLS_STRUCTS

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

#endif
