#include "console.h"
#include "structs.h"

struct ConsoleInfo *forth_engine_console;
  
void forth_print(const char *text)
{
    console_text_default(text,forth_engine_console);
}
