#include "compatibility.h"
#include "forth-primitives.h"
#include "graphics.h"
#include "logging.h"
#include "manager.h"
#include "mem.h"


//TODO - PRIORITY
//===============
/*
- tail call elimination

- more abbreviations
  - << and >> for shift
  - NEG for NEGATE
  - INV for INVERT
- add >= and <=

- EXECUTE
  - disabled EXEC in EXEC bc circular stack but enabled now that stack no longer circular

- insert checks after the fact for stack
  - at the top of each if block etc
  - possible to eliminate for do loop if no branch or secondary inside?
    - could keep track of whether each block or word is clean but then cant redefine

- improve memory system
  - need to add lots of different mem types so better to have list of mem segments
    if they all work the same way. IIRC, all sections currently have custom update :(

- local variables
  - store names after word for debugger and browser

- typedef for function pointers

- need opt on and off for testing

- color code )

- try blue for primitives
  - color by primitive type too?
  - best may be to rotate through colors on button press

- autocomplete
  - use arrow key - don't need special characters in source
  - other use would be to insert TO

- paren comments not working in word definition
  - now can't reproduce
  - got it more than once to include ) as undefined word

- tail call improvements
  - get compiler to generate tail call
  - have stack underflow generate exception

- shift should stay on if held down

- ON should break ACCEPT and KEY

- CASE

- rework word KEY
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

for optimizing structs
- https://dreamcast.wiki/Useful_programming_tips

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
- locals
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
peepholing
- tail call recursion!
- could render asm with fixed address for ie MOVE but no benefit on RISC
- big payoff of peepholing is only doing wrapping calculation once
copy primitive bodies to RAM
no stack wrapping and check every 10 primitives for overflow
- only check so many instructions
- alignment no longer matters - should work!
- otoh, what if OOB then back in? wouldnt catch
  - could OR and AND one address in primitive but need stack to be aligned - wastes 2x stack
- could work but not if NEXT is in each primitive
new idea?
- problem - how to exit from combined primitive on underflow? need constant checks
  - check once at beginning and exit?
- check stack wrapping by bit for under/overflow
  - fast if set executing to result and change type
- need buffer space above stack
  - worse might be loading locals which pops up to 32 values
  - could put stack that doesnt need to be aligned next so dont lose 2x memory
- need buffer space below stack
  - SP points to available memory so full stack would trigger underflow
  - what pushes most values to stack? need that much buffer space
    - s" is 2
linked list for stack
- probably slower than masking but could try
- could also be index for each stack depth but slower than explicit check?
explicit check
- put in word and compare
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
switch case as mentioned online?
- someone said this was fastest on x86 but how? switch in while?
*/


//Constants
//=========
#define TICK_MS         40  //25 FPS

//Functions
//=========

//TODO: remove
#include <stdio.h>
#include <string.h>
#include "getkey.h"
#include "test.h"
#include "text.h"

//Defined in test.S
int test();

int foo()
{
    return 0x12345678;
}

void jit_test()
{
    //Output text
    char buffer[TEXT_INT32_SIZE];
    dclear(COL_BLACK);
    struct Point pos={20,20};
    pos=draw_text("JIT test",pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    dupdate();

    //sh4eb machine code
    char test_code[]={
        //0x00, 0x0B, //rts
        //0xE0, 0x2A, //mov #42,r0

        //0xD0, 0x01, //mov.l @(4,PC),r0
        //0x00, 0x0B, //rts
        //0x00, 0x09, //nop
        //0x00, 0x00, //alignment
        //0x12, 0x34, //const 0x12345678
        //0x56, 0x78

        0x4F, 0x22, //sts.l pr,@-r15
        0xD0, 0x03, //mov.l @(8,PC),r0
        0x40, 0x0B, //jsr @r0
        0x00, 0x09, //nop
        0x4F, 0x26, //lds.l @r15+,pr
        0x00, 0x0B, //rts
        0x00, 0x09, //nop
        0x00, 0x00, //alignment
        ((uintptr_t)foo)>>24,           //&foo
        (((uintptr_t)foo)>>16)&0xff,    //&foo
        (((uintptr_t)foo)>>8)&0xff,     //&foo
        ((uintptr_t)foo)&0xFF,          //&foo

        };
   
    //Copy machine code to memory
    memcpy(heap,test_code,sizeof(test_code));
    
    /*

    //Output bytes just written to heap
    pos.x=20;
    pos.y+=12;
    text_hex32((uintptr_t)heap,buffer);
    pos=draw_text(buffer,pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    pos=draw_text(": ",pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    for (int i=0;i<4;i++)
    {
        text_hex32_padded(*(heap+i),buffer,2);
        pos=draw_text(buffer,pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
        pos=draw_text(" ",pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    }

    //Output bytes from test function which should be the same as bytes just written
    pos.x=20;
    pos.y+=12;
    char *func_ptr=(char *)&test;
    pos=draw_text("test:     ",pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    for (int i=0;i<4;i++)
    {
        text_hex32_padded(*(func_ptr+i),buffer,2);
        pos=draw_text(buffer,pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
        pos=draw_text(" ",pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    }

    */

    //Jump to machine code
    int result=((int (*)())heap)();

    //Output result
    pos.x=20;
    pos.y+=12;
    pos=draw_text("Result: ",pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    text_int32(result,buffer);
    pos=draw_text(buffer,pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    pos=draw_text(" (0x",pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    text_hex32_padded(result,buffer,8);
    pos=draw_text(buffer,pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    pos=draw_text(")",pos,COL_WHITE,COL_TRANS,false,FONT_5x8);
    dupdate();

    //Wait for key
    getkey_wrapper(true);
}

//int main(int argc, char *argv[])  //PC only
int main(void)                      //cg50 and PC
{
    //Initialize logging if on PC
    init_logging("log.txt");

    //TODO: remove
    const int expected_count=148;
    log_none("Primitive count: %d of %d (%d left)\n",forth_primitives_len,expected_count,expected_count-forth_primitives_len);

    //Configure device specific settings - TCP on PC and timer on calculator
    setup(TICK_MS);

    //VRAM pointer for double buffering
    dgetvram(&vram_main,&vram_buffer);

    //TODO: remove
    //jit_test();

    //Initialize heap memory
    init_heap();

    //Jump into window manager
    window_manager();

    return 0;    
}

