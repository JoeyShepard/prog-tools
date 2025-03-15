#ifndef __GUARD_PROG_TOOLS_DUMMY
    #define __GUARD_PROG_TOOLS_DUMMY
   
    #include <stdint.h>
    #include "structs.h"

    int command_line(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr);
    int text_editor(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr);
    int forth(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr);
    int python(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr);
    int help(int command_ID, struct WindowInfo *windows, int selected_window, uint8_t *heap_ptr);

#endif
