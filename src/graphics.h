#ifndef __GUARD_PROG_TOOLS_GRAPHICS
    #define __GUARD_PROG_TOOLS_GRAPHICS

    #include <stdint.h>

    #include "compatibility.h"

    extern uint16_t *vram_main, *vram_buffer;

    void draw_line_horz(int x0, int x1, int y, color_t color);
    void draw_line_vert(int x, int y0, int y1, color_t color);
    void draw_rect(int x, int y, int width, int height, int32_t border, int32_t fill);

#endif
