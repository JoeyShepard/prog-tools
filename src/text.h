#ifndef __GUARD_PROG_TOOLS_TEXT
    #define __GUARD_PROG_TOOLS_TEXT

    #include <stdbool.h>

    #include "structs.h"

    //Custom characters - same numbering for all fonts
    #define CHAR_RIGHT_ARROW        30  //Right arrow symbol from keypad
    #define CHAR_CUSTOM_CURSOR      31  //solid cursor

    #define CHAR_PRINTABLE_MIN      30  //First printable character
    #define CHAR_PRINTABLE_MAX      126 //Last printable character

    #define TEXT_INT32_SIZE         12  //max 10 digits, 1 for - sign, 1 for terminator
    #define TEXT_HEX32_SIZE         9   //max 8 digits, 1 for terminator
    #define TEXT_INT32_COMMAS_SIZE  15  //max 10 digits, max 3 commas, 1 for - sign, 1 for terminator 
    #define TEXT_INT32_HUMAN_SIZE   6   //max len of: 999, 0.99k, 9.99K, 99.9K, 999K, 9.99M

    #define FONT_HORZ_SPACING       1   //Count of pixels between letters

    enum FontSizes
    {
        FONT_5x8
    };

    uint8_t *font_data(int font);
    int font_width(int font);
    int font_height(int font);
    int text_width(const char *text, int font);
    bool text_printable(char text);
    struct Point draw_char(char text, struct Point pos, int32_t fg, int32_t bg, bool invert, int font);
    struct Point draw_text(const char *text, struct Point pos, int32_t fg, int32_t bg, bool invert, int font);
    struct Point outline_text(const char *text, struct Point pos, int32_t fg, int32_t bg, int32_t border, bool invert, int font);
    void text_int32(int32_t num, char *text);
    void text_hex32(uint32_t num, char *text, int digits);
    void text_int32_commas(int32_t num, char *text);
    void text_int32_human(int32_t num, char *text);
    
#endif
