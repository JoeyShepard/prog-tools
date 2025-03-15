#ifndef __GUARD_PROG_TOOLS_COMMAND
    #define __GUARD_PROG_TOOLS_COMMAND

    #include <stdint.h>
    //#include "structs.h"

    //Dimensions (may change - see manager.h):
    //- Whole:  388x204 - 64 chars, 4 pixels x 22 rows, 6 pixels (or 20 rows, 4 pixels)
    //- Vsplit: 388x100 - 64 chars, 4 pixels x 11 rows, 1 pixel  (or 10 rows, 0 pixels)
    //- Hsplit: 192x204 - 31 chars, 6 pixels x 22 rows, 6 pixels (or 20 rows, 4 pixels)
    #define MAX_COMMAND_LINE    124     //Four full lines if hsplit

    //int command_line(int command_ID, struct WindowInfo window, uint8_t *heap_ptr);

#endif
