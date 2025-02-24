#ifndef __GUARD_PROG_TOOLS_TEXT
    #define __GUARD_PROG_TOOLS_TEXT

    #include <stdbool.h>
    #include "structs.h"

    //Custom characters - same numbering for all fonts
    #define CUSTOM_CURSOR           31  //solid cursor

    #define CHAR_PRINTABLE_MIN      31  //First printable character
    #define CHAR_PRINTABLE_MAX      126 //Last printable character

    enum FontSizes
    {
        FONT_5x8
    };

    uint8_t *font_data(int font);
    int font_width(int font);
    int font_height(int font);
    int text_width(const char *text, int font);
    bool text_printable(char text);
    struct point draw_char(char text, struct point pos, int32_t fg, int32_t bg, bool invert, int font);
    struct point draw_text(const char *text, struct point pos, int32_t fg, int32_t bg, bool invert, int font);
    struct point outline_text(const char *text, struct point pos, int32_t fg, int32_t bg, int32_t border, bool invert, int font);

#endif
