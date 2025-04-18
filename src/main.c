#include <stdbool.h>
#include <stdint.h>
#include "compatibility.h"
#include "getkey.h"
#include "graphics.h"
#include "manager.h"
#include "mem.h"
#include "text.h"

//TODO
//====
/*
remove headers
getkey.c arrays for key_printable not used
- deleted key_printable since compiler complained about not being used
draw_char can draw out of bounds!
TODOs in all files
rearrange struct orders for speed
error_exit in mem? maybe better to recover
copy of forth struct needs to be stored in XRAM
*/


//Constants
//=========
#define TICK_MS         40  //ie 25 FPS
#define SCALE_FACTOR    3

//Functions
//=========

//int main(int argc, char *argv[])  //PC only
int main(void)                      //cg50 and PC
{
    //Setup - SDL2 on PC and timer on calculator
    setup(SCALE_FACTOR,TICK_MS);

    //Initialize heap memory
    init_heap();

    //VRAM pointer for double buffering
    dgetvram(&vram_main,&vram_buffer);

    //Jump into window manager
    window_manager();

    return 0;    
}

