#pragma once

#include <stdint.h>

#include "structs.h"

//Constants
#define ERROR_COL_BG        COL_RED
#define ERROR_COL_FG        COL_WHITE
#define ERROR_SPACING_Y     12
#define ERROR_UNWIND_COUNT  10  //Levels of calls to unwind on error

//Macros
#define IF_ERROR_RETURN(return_value) if (e->code!=ERROR_NONE) {error_set_line(e,__LINE__,__FUNCTION__,__FILE_NAME__);return return_value;}
#define IF_ERROR_CLEANUP() if (e->code!=ERROR_NONE) {error_set_line(e,__LINE__,__FUNCTION__,__FILE_NAME__);goto error_exit;}
#define ERROR_SET(new_code) e->code=new_code;error_set_line(e,__LINE__,__FUNCTION__,__FILE_NAME__);

//TODO: separate out error mechanism from specific errors below?
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
    const char **messages;      //Optional error message list indexed by code
    struct
    {
        uint32_t line_number;
        const char *function;
        const char *file_name;
    } line[ERROR_UNWIND_COUNT];
};

void error_reset(struct ErrorType *e);
void error_set_line(struct ErrorType *e,uint32_t line,const char *function,const char *file_name);
void error_exit(int error);
void error_debug(struct ErrorType *e);
void error_screen(int error,struct Point pos,int width,int height);
