#include "compatibility.h"
#include "graphics.h"
#include "logging.h"
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

remove unnecessary headers
TODOs in all files
rearrange struct orders for speed
error_exit in mem? maybe better to recover
- yes, change mem.c to return values not addresses
- or provide error function in forth-compatibility.c
console assumes input less than size of screen
assembler with built-in safety checks?

Forth
=====
only highlight syntax after 1 second? not sure if affects battery life
revisit stack bounds checks instead of masking now that no PICK or ROLL
- check every so many instructions?
in Forth console, cursor in last column is one pixel too wide
key modifier in cursor?
recheck syntax highlighter for : since colors primitives as secondary name
- letter after char
- comments
- color primitives red if compile only etc
- tick on number
- tick on ;, :, quotes etc
- quoting words not working yet
- words with header but no definition should be yellow
- red after const and var like ;
stagger key legend to take up less room
console - only copy to history if different from last
double check all engine->print references check not NULL
ON should break ACCEPT and KEY
compare signs of comments in standard to primitives
- actually, can mostly disregard if masking
EXE in forth prompt causes redraw when line empty
optimize ERASE etc - don't need to mask every cycle
- also, no reason to wrap at end of memory
ctrl+c could overwrite input instead of inserting
individual primitives for local accesses
- how much space would this take?
- even 16 might be good - dont need 256
i and j are function pointers
add test for NULL for headers in primitives that use them
RECURSE? no problem using name if in definition but bad in [ ]
make sure logging really is compiled out! ie comment out then compare binary sizes
- especially for code blocks relying on log_enabled

Forth optimizing
================
compare various methods
most used primitives in IRAM
combined primitives
constant folding
stack and engine in XRAM
peepholing
- tail call recursion!
- could render asm with fixed address for ie MOVE but no benefit on RISC
copy primitive bodies to RAM
no stack wrapping and check every 10 primitives for overflow
assembly? doesnt seem worth it for this
- might be ok since already have C version for x86
- how to combined primitives? either or
tests
- fibonacci
- N queens
- compare to Basic and Python
- https://github.com/ulixxe/forth_coremark
- https://www.eembc.org/coremark/
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
    //Initialize logging if on PC
    init_logging("log.txt");

    //Setup - SDL2 on PC and timer on calculator
    setup(SCALE_FACTOR,TICK_MS);

    //TODO: move to setup?
    //Initialize heap memory
    init_heap();

    //VRAM pointer for double buffering
    dgetvram(&vram_main,&vram_buffer);

    //Jump into window manager
    window_manager();

    return 0;    
}

