#ifndef __GUARD_PROG_TOOLS_MEMORY_MANAGER
    #define __GUARD_PROG_TOOLS_MEMORY_MANAGER
   
    #include <stdint.h>

    #include "compatibility.h"
    #include "structs.h"

    #define COL_MEM_MGR_FG          COL_WHITE
    #define COL_MEM_MGR_BG          COL_BLACK

    #define MEM_MGR_TEXT_HEIGHT     11
    #define MEM_MGR_OUTLINE_HEIGHT  (MEM_MGR_TEXT_HEIGHT+2)

    #define MEM_MGR_COL2_SPACING    8

    int memory_manager(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
