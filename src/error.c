#include "compatibility.h"
#include "error.h"
#include "text.h"

#ifdef CG50
    //Calculator version
    void error_exit(int error)
    {
        struct point pos={0,0};

        switch (error)
        {
            case ERROR_NONE:
                return;
            case ERROR_FONT_NOT_FOUND:
                draw_text("Error: font not found!", pos, COL_BLACK, COL_WHITE, false, FONT_5x8); 
                break;
            case ERROR_MENU_TEXT_TOO_LONG:
                draw_text("Error: menu text too long!", pos, COL_BLACK, COL_WHITE, false, FONT_5x8); 
                break;
            case ERROR_UNALIGNED_WRITE:
                draw_text("Error: unaligned write to heap!", pos, COL_BLACK, COL_WHITE, false, FONT_5x8);
                break;
            case ERROR_BAD_HEAP_ID:
                draw_text("Error: bad heap ID!", pos, COL_BLACK, COL_WHITE, false, FONT_5x8);
                break;
        }

        //No way to exit on calculator so hang here
        while(1);
    }

#else
    //PC version
    #include <stdio.h>
    void error_exit(int error)
    {
        switch (error)
        {
            case ERROR_NONE:
                return;
                break;
            case ERROR_FONT_NOT_FOUND:
                printf("Error - font not found!\n");
                break;
            case ERROR_MENU_TEXT_TOO_LONG:
                printf("Error: menu text too long!\n");
                break;
            case ERROR_UNALIGNED_WRITE:
                printf("Error: unaligned write to heap!\n");
                break;
            case ERROR_BAD_HEAP_ID:
                printf("Error: bad heap ID!\n");
                break;
        }
        exit(1);
    }

#endif
