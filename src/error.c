#include <stddef.h>

#include "compatibility.h"
#include "error.h"          
#include "getkey.h"
#include "graphics.h"
#include "structs.h"
#include "text.h"

void error_reset(struct ErrorType *e)
{
    e->code=ERROR_NONE;
    e->messages=NULL;
    for (int i=0;i<ERROR_UNWIND_COUNT;i++)
    {
        e->line[i].line_number=0;
        e->line[i].function=NULL;
        e->line[i].file_name=NULL;
    }
}

void error_set_line(struct ErrorType *e,uint32_t line,const char *function,const char *file_name)
{
    //Look for empty slot to store line information
    for (int i=0;i<ERROR_UNWIND_COUNT;i++)
    {
        if ((e->line[i].line_number==0)&&
            (e->line[i].function==NULL)&&
            (e->line[i].file_name==NULL))
        {
            //Slot found - store line information
            e->line[i].line_number=line;
            e->line[i].function=function;
            e->line[i].file_name=file_name;
            return;
        }
    }

    //No slot found - error object is full
    return;
}

#ifdef CG50
    //Calculator version
    void error_exit(int error)
    {
        struct Point pos={0,0};

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
        dupdate();

        //No way to exit on calculator so hang here
        while(1);
    }

    void error_debug(struct ErrorType *e)
    {
        //TODO
    }

#else
    //PC version
    #include <stdio.h>
    #include <stdlib.h>

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

    void error_debug(struct ErrorType *e)
    {
        printf("Error %d",e->code);
        if (e->messages!=NULL)
        {
            printf("%s",e->messages[e->code]);
        }
        printf("\n");
        
        for (int i=0;i<ERROR_UNWIND_COUNT;i++)
        {
            if ((e->line[i].function!=NULL)&&(e->line[i].file_name!=NULL))
            {
                printf("  from line %d of %s() in %s\n",e->line[i].line_number,e->line[i].function,e->line[i].file_name);
            }
        }
    }
#endif

void error_screen(int error,struct Point pos,int width,int height)
{
    const int font=FONT_5x8;
    const char *error_msg;
    switch (error)
    {
        case ERROR_OUT_OF_MEMORY:
            error_msg="Error: out of heap memory!";
            break;
        default:
            error_msg="Unknown error";
    }

    draw_rect(pos.x,pos.y,width,height,ERROR_COL_BG,ERROR_COL_BG);
    for (int i=0;i<2;i++)
    {
        const char *print_text;
        if (i==0) print_text=error_msg;
        else print_text="Press EXE to exit";

        struct Point new_pos=pos;
        new_pos.x+=width/2-text_width(print_text,font)/2;
        new_pos.y+=height/2;

        if (i==0) new_pos.y-=ERROR_SPACING_Y;
        else new_pos.y+=ERROR_SPACING_Y-font_height(font);

        draw_text(print_text,new_pos,ERROR_COL_FG,-1,false,font);
    }
    dupdate();
    
    int key;
    do
    {
        key=getkey_wrapper(true);
    } while(key!=VKEY_EXE);
}
