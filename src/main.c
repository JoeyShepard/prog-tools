#include "compatibility.h"
#include "graphics.h"
#include "manager.h"
#include "mem.h"

//TODO
//====
/*
revisit casting rules esp for structs
- seems char * is an exception
  - char * is not the same as uint8_t *
- might be good to post some examples and ask for help
offsetof operator

remove headers
TODOs in all files
rearrange struct orders for speed
error_exit in mem? maybe better to recover
- yes, change mem.c to return values not addresses
console assumes input less than size of screen
fix debug_heap
- changed something then commented out
- may be ok not to fix if dont need again
exit program after start so other pane updates for memory then back?
convert size_t in mem to uint32_t

Forth
=====
copy of forth struct needs to be stored in XRAM
shift+enter for new line in Forth
in Forth console, cursor in last column is one pixel too wide
default forth data size should be smaller
sign extend for c@ and w@
key modifier in cursor?
recheck syntax highlighter for : since colors primitives as secondary name
- letter after char
- comments
- color primitives red if compile only etc
- tick on number
- quoting words not working yet
- words with header but no definition should be yellow
stagger key legend to take up less room
console - only copy to history if different from last
buffer stack_base in primitives? need to check disassembly
double check all engine->print references check not NULL
ON should break ACCEPT and KEY
compare signs of comments in standard to primitives
- actually, can mostly disregard if masking
EXE in forth prompt causes redraw when line empty
optimize ERASE etc - don't need to mask every cycle
- also, no reason to wrap at end of memory
change int32_t back to int in some cases
- changed several to try to be consistent but went too far. int ok sometimes.
ctrl+c could overwrite input instead of inserting
put primitives in alphabetical order for WORDs
PRIMITIVES word since may scroll off screen
also UNDEFINED
individual primitives for local accesses
- how much space would this take?
- even 16 might be good - dont need 256
i and j are function pointers
WORDS - secondaries with header only should be yellow
- add test for NULL for headers in primitives that use them
*/


//Constants
//=========
#define TICK_MS         40  //25 FPS
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

