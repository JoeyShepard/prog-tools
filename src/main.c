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
draw_char can draw out of bounds!
TODOs in all files
rearrange struct orders for speed
error_exit in mem? maybe better to recover
copy of forth struct needs to be stored in XRAM
shift+enter for new line in Forth
forth variables are IDs 0-255 so faster (not locals)
- words and create are 256 and up
in Forth console, cursor in last column is one pixel too wide
default forth data size should be smaller
sign extend for c@ and w@
key modifier in cursor?
command suggestion in status area
recheck syntax highlighter for : since colors primatives as secondary name
stagger key legend to take up less room
console - only copy to history if different from last
buffer stack_base in primitives? need to check disassembly
double check all engine->print references check not NULL
ON should break ACCEPT and KEY
compare signs of comments in standard to primitives
- actually, can mostly disregard if maskign
EXE in forth prompt causes redraw when line empty
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

