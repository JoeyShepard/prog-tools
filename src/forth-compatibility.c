#include "console.h"
#include "structs.h"

struct ConsoleInfo *forth_print_console;
  
void forth_print(const char *text)
{
    console_text_default(text,forth_print_console);
}

void forth_print_color(const char *text,color_t color)
{
    console_text(text,color,forth_print_console->text_col_bg,forth_print_console);
}
