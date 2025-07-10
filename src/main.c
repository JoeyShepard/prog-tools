#include "compatibility.h"
#include "forth-primitives.h"
#include "graphics.h"
#include "logging.h"
#include "manager.h"
#include "mem.h"


//TODO - PRIORITY
//===============
/*
- local variables
  - then can benchmark
  - store names after word for debugger and browser

- number words: -1, 0, 1, etc

- move actions to array for primitives?
  - are there actually any prim_compile_ functions that do anything other than return action?

- stack_item_t? no
  - already have FORTH_CELL_SIZE but forgot. replace sizeof(int32_t) elsewhere?

- try blue for primitives
  - color by primitive type too?

- autocomplete
  - use arrow key - don't need special characters in source

- paren comments not working in word definition
  - now can't reproduce
  - got it more than once to include ) as undefined word

- GOT SEG FAULT PRESSING HOME!!!
  - could not reproduce

- tail call improvements
  - get compiler to generate tail call
  - have stack underflow generate exception


- shift should stay on if held down

- ON should break ACCEPT and KEY

- CASE

- rework word key
  - two words rather than word w arg
  - sys_key word
*/


//TODO
//====
/*
revisit casting rules esp for structs
- seems char * is an exception
  - char * is not the same as uint8_t *
  - seems unsigned char though also has special status???
- might be good to post some examples and ask for help
  - yes, file in repo with explanation and links to what may be UB
offsetof operator
- fsanitize=undefined
  - make sanitize
- valgrind

don't show cursor if window doesn't have focus like in tmux
switching tabs should be disabled if full screen instead of redrawing
each character output should NOT update screen
- wait for ticks to go by?
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
- s8, i16 etc variables
  - better s1, s2, s4?
- register keyword with up to 8 or so variables per function
- arbitrary calculations with variables and constants
- ideas to reduce masking
  - for loop that takes array name so check bounds at beginning
    - variable name is read/write for array
    - should also have step as argument
      - step 4 would mean x+2 generated with no mask
    - variable itself can't be modified
  - first element is length so always able to check bounds
    - also type? actually, should be declared in argument
  - small amount of checking to see if need mask
  - seems masking only when pointer modified is most efficient
  - no casting
- see assembly for line typed if more than 1 second
  - limits to optmizing a line at a time but that's fine
  - either show on screen while typing, press key to see, or link split to show
- dynamic strings
  - how to pass around? ref checking?
- no cpp, pointer shenanigans, UB
review code on github - better to see in second light
gint font is truly 5x7 not 5x8 like mine
- shrink my font? might fit 2-3 more lines on screen
combine all errors into one range instead of 3
- there was a reason for doing it this way but can't remember now
- I remember - FORTH should be modular and not tied to rest of program

Forth
=====
XOT as X? keep coming back to it

delete commented out primitives
see assembly for primitives - any space saving slow downs?
shift arrow for home and end
should add .\"
change ->executing to pointer system
- solves problem of still executing after ->executing false if only check every 5th time 
- no longer need to mask!
  - implement PERF and DO first
- actually, not sure in that case how to do check
only highlight syntax after 1 second? not sure if affects battery life
in Forth console, cursor in last column is one pixel too wide
key modifier in cursor?
recheck syntax highlighter for : since colors primitives as secondary name
- letter after char
- comments
- color primitives red if compile only etc
- tick on number
- tick on ;, :, quotes etc
- tick and ['] too
- quoting words not working yet
- words with header but no definition should be yellow
- red after const and var like ;
- color secondaries if match like primitives
- escape sequences
- numbers out of range
- wordsize
- var, const, etc
- at least try blue for primaries
- compile only red if outside of word
  - may need to replace compile only error with one generic function
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
excessive masking in primitives? data_index should always be valid
- looked briefly and only found C_COMMA. anywhere else?
see assembly for body_dupe. redundant calculation optimized out?

Forth optimizing
================
compare various methods
- calculated goto
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
- could work but not if NEXT is in each primitive
linked list for stack
- probably slower than masking but could try
- could also be index for each stack depth but slower than explicit check?
explicit check
- put in word and compare
assembly? doesnt seem worth it for this
- might be ok since already have C version for x86
- how to do combined primitives? either or
tests
- fibonacci
- N queens
- compare to Basic and Python
- https://github.com/ulixxe/forth_coremark
- https://www.eembc.org/coremark/
- bad apple?
only check ->executing on branch
words load next word?
- stops double jump and ->executing=false can just load different address
  - OTOH, not needed if copying primitive body to RAM
- ->executing=false exists very few times in source
- -fno-PIC produces TCO!
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
    const int expected_count=148;
    log_none("Primitive count: %d of %d (%d left)\n",forth_primitives_len,expected_count,expected_count-forth_primitives_len);

    //Configure device specific settings - SDL2 on PC and timer on calculator
    setup(SCALE_FACTOR,TICK_MS);

    //Initialize heap memory
    init_heap();

    //VRAM pointer for double buffering
    dgetvram(&vram_main,&vram_buffer);

    //Jump into window manager
    window_manager();

    return 0;    
}

