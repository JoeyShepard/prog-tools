#ifndef __GUARD_PROG_TOOLS_CONSOLE
    #define __GUARD_PROG_TOOLS_CONSOLE

    #include <stdint.h>

    #include "structs.h"
    #include "compatibility.h"

    //Dimensions (may change - see manager.h):
    //- Whole:  388x204 - 64 chars, 4 pixels x 22 rows, 6 pixels (or 20 rows, 4 pixels)
    //- Vsplit: 388x100 - 64 chars, 4 pixels x 11 rows, 1 pixel  (or 10 rows, 0 pixels)
    //- Hsplit: 192x204 - 31 chars, 6 pixels x 22 rows, 6 pixels (or 20 rows, 4 pixels)

    //Console
    #define CONS_WHOLE_WIDTH    64
    #define CONS_WHOLE_HEIGHT   22
    #define CONS_WHOLE_X        1
    //#define CONS_WHOLE_Y        2 //Equal space above and below console - top text doesn't line up with vertical split
    #define CONS_WHOLE_Y        0   //Top text lines up with vertical split - space above and below console not equal

    #define CONS_HALF_WIDTH     31
    #define CONS_HALF_HEIGHT    11
    #define CONS_HALF_X         2
    #define CONS_HALF_Y         0
    
    #define CONS_ROW_HEIGHT     9

    #define CONS_BUFFER_SIZE    (CONS_WHOLE_WIDTH*CONS_WHOLE_HEIGHT+CONS_WHOLE_HEIGHT)

    //structures
    //==========
    struct ConsoleChar
    {
        char character;
        color_t fg;
        color_t bg;
    };

    struct ConsoleInput
    {
        struct ConsoleChar *text;   //Zero-terminated string
        int len;                    //Cached length to speed up processing
        int start;
        int cursor;
    };

    struct ConsoleInfo
    {
        //Console output
        struct ConsoleChar text[CONS_BUFFER_SIZE];
        int text_len;
        uint32_t overflow_count;
        int buffer_index;
        color_t text_col_fg;
        color_t text_col_bg;
        int x;
        int y;
        int width;
        int height;

        //Input line
        struct ConsoleInput input;
        struct ConsoleInput input_copy;
        bool reset_input;
        int modifier;
        bool input_copied;
        int input_text_max;
        color_t input_col_fg;
        color_t input_col_bg;

        //History
        struct ConsoleInput *history;
        struct ConsoleChar *history_texts;
        int history_index;
        int history_count;
        int history_read_count;
        int history_array_size;

        //Offset in memory from beginning of struct where pointers above point to.
        //Used to reset pointers when address of struct shifts since offset
        //will always be the same if struct and memory pointers point to are stored
        //in the same struct together.
        ptrdiff_t offset_input_text;
        ptrdiff_t offset_input_copy_text;
        ptrdiff_t offset_history;
        ptrdiff_t offset_history_texts;
    };

    //Functions
    //=========
    void init_console(struct ConsoleInfo *console,color_t text_col_fg,color_t text_col_bg,struct ConsoleChar *input_text,struct ConsoleChar *input_copy_text,int input_text_max,color_t input_fg,color_t input_bg,struct ConsoleInput *history,struct ConsoleChar *history_texts,int history_array_size);
    void reset_console_pointers(struct ConsoleInfo *console);
    void init_history(struct ConsoleInfo *console);
    void init_position(struct ConsoleInfo *console,struct Point pos,int split_state);
    void console_char(char character, color_t fg, color_t bg, struct ConsoleInfo *console);
    void console_text(const char *text, color_t fg, color_t bg, struct ConsoleInfo *console);
    void console_text_default(const char *text, struct ConsoleInfo *console);
    void add_input_text(const char *text,color_t fg,color_t bg,bool add_to_start,struct ConsoleInfo *console);
    void add_input_char(char character,color_t fg,color_t bg,bool add_to_start,struct ConsoleInfo *console);
    void draw_input_line(struct ConsoleInfo *console,struct Point pos,int console_width,int input_height);
    void draw_console(struct ConsoleInfo *console);
    void reset_console(struct ConsoleInfo *console);
    void add_history(struct ConsoleInfo *console);
    void history_key(struct ConsoleInfo *console,int key);
    void copy_console_text(struct ConsoleInput *input,char *input_buffer,int input_size,int offset);
    int console_strlen(struct ConsoleChar *text);
    void input_deep_copy(struct ConsoleInput *dest,struct ConsoleInput *source,int elements);

#endif
