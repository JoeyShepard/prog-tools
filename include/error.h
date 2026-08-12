#pragma once

#include <stdint.h>

#include "structs.h"

#define ERROR_COL_BG    COL_RED
#define ERROR_COL_FG    COL_WHITE

#define ERROR_SPACING_Y 12

enum ErrorNumber
{
    //error_exit - fatal, stop executing
    ERROR_NONE,
    ERROR_FONT_NOT_FOUND,
    ERROR_MENU_TEXT_TOO_LONG,
    ERROR_UNALIGNED_WRITE,
    ERROR_BAD_HEAP_ID,
    ERROR_BAD_OBJECT_ADDRESS,

    //error_screen - not fatal, show screen then return to menu
    ERROR_OUT_OF_MEMORY
};

struct ErrorType
{
    uint32_t code;              //Set as needed by programs
    uint32_t subcode;           //Optional. Set as needed by programs.
    const char **messages;      //Optional error message list
};

void error_reset(struct ErrorType *e);
void error_exit(int error);
void error_screen(int error,struct Point pos,int width,int height);

