#include "compatibility.h"
#include "forth-primitives.h"
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
- fsanitize=undefined
  - make sanitize

remove unnecessary headers
TODOs in all files
rearrange struct orders for speed
error_exit in mem? maybe better to recover
- yes, change mem.c to return values not addresses
- or provide error function in forth-compatibility.c
console assumes input less than size of screen
assembler with built-in safety checks?
- posted on this but now C-like language seems better
C like language
- translates directly to assembly
- variables referring to XRAM
- address registers directly
  - I0, U0 - int, unsigned int
  - B0, ?0 - char, unsigned char
  - W0, ?0 - int16, uint16
- arbitrary calculations with variables and constants
- ideas to reduce masking
  - for loop that takes array name so check bounds at beginning
    - variable name is read/write for array
  - first element is length so always able to check bounds
    - also type? actually, should be declared in argument
  - no pointers, just indexes
    - foo[R0]=...
  - function call passes pointer like python
  - no casting
- dynamic strings
  - how to pass around? ref checking?
- no cpp, pointer shenanigans, UB
review code on github - better to see in second light
gint font is truly 5x7 not 5x8 like mine
- shrink my font? might fit 2-3 more lines on screen

Forth
=====
only highlight syntax after 1 second? not sure if affects battery life
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
- color secondaries if match like primitives
- escape sequences
- numbers out of range
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
dont update screen for emit etc if no print defined
keyboard shortcut to clear stack
- shift DEL?
excessive masking in primitives? data_index should always be valid
- looked briefly and only found C_COMMA. anywhere else?
see assembly for body_dupe. redundant calculation optimized out?

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
- only check so many instructions
- alignment no longer matters - should work!
- otoh, what if OOB then back in? wouldnt catch
  - could OR and AND one address in primitive but need stack to be aligned - wastes 2x stack
assembly? doesnt seem worth it for this
- might be ok since already have C version for x86
- how to do combined primitives? either or
tests
- fibonacci
- N queens
- compare to Basic and Python
- https://github.com/ulixxe/forth_coremark
- https://www.eembc.org/coremark/
only check ->executing on branch
words load next word?
- stops double jump and ->executing=false can just load different address
  - OTOH, not needed if copying primitive body to RAM
- ->executing=false exists very few times in source
try code generation
- doesnt have to be perfect
- compare cycles to combined primitive at runtime to make sure worth it
  - see cycle counting post
  - separate add-on could check all combos and error if not as predicted
switch case as mentioned online?
- someone said this was fastest on x86 but how? switch in while?
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

    //TODO: remove
    const int expected_count=147;
    log_none("Primitive count: %d of %d (%d left)\n",forth_primitives_len,expected_count,expected_count-forth_primitives_len);

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

