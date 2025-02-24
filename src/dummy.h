#ifndef __GUARD_PROG_TOOLS_DUMMY
    #define __GUARD_PROG_TOOLS_DUMMY
    
    int text_editor(int command_ID, struct WindowInfo window, uint8_t *heap_ptr);
    int forth(int command_ID, struct WindowInfo window, uint8_t *heap_ptr);
    int python(int command_ID, struct WindowInfo window, uint8_t *heap_ptr);
    int help(int command_ID, struct WindowInfo window, uint8_t *heap_ptr);

#endif
