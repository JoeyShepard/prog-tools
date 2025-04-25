#include "console.h"
#include "structs.h"

struct ConsoleInfo *forth_print_console;
  
void forth_print(const char *text)
{
    console_text_default(text,forth_print_console);
}
