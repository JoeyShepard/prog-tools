//Garbage collection routines
#pragma once

#include <stdbool.h>

#include "error.h"

#define GC_ALIGN            4           //Alignment requirement on SH4
#define GC_OBJ_ALIGN        16          //Must be large enough for header and GC_MIN_SIZE
#define GC_TABLE_ELEMENTS   128         //Elements in table of memory IDs
#define GC_ROOT_PID         0           //Root can access memory belonging to any PID
#define GC_TABLE_ID         0           //First table entry is pointer to table
#define GC_MAX_LOCKS        UINT8_MAX   //Max times same object can be locked

enum GC_ERRORS
{
    GC_ERROR_NONE=ERROR_NONE,   //0
    GC_ERROR_OBJ_SIZE,          //1
    GC_ERROR_OUT_OF_MEM,        //2
    GC_ERROR_ID_RANGE,          //3
    GC_ERROR_FREE_LOCKED,       //4
    GC_ERROR_WRONG_PID,         //5
    GC_ERROR_LOCK_COUNT,        //6
    GC_ERROR_UNLOCK,            //7
    GC_ERROR_ID_UNASSIGNED,     //8
    GC_ERROR_EMPTY_HEADER,      //9
    GC_ERROR_HEADER_SIZE,       //10
    GC_ERROR_HEADER_OVERFLOW,   //11
    GC_ERROR_HEAP_SIZE,         //12
    GC_ERROR_OBJ_ALIGNMENT,     //13
    GC_ERROR_REALLOC_LOCKED,    //14
    GC_ERROR_SWAP_END,          //15
    GC_ERROR_SWAP_LOCKED,       //16
};

struct GC_Header
{
    uint32_t size;                  //Including header
    uint32_t id;                    //ID assigned in ID table
    bool end;                       //Whether empty object marking end of heap
    bool free;                      //Whether free to be assigned
    uint8_t pid;                    //PID from requesting process
    uint8_t lock_count; 
    //Flexible array member
    alignas(GC_ALIGN) char data[];
};

struct GC_Internals
{
    void *heap_base;
    uint32_t heap_size;
    uint32_t table_elements;
    uint32_t ids_left;
    struct GC_Header *id_table_header;
    struct GC_Header **id_table;
    uint8_t current_pid;
};

//Round number up for heap object size calculation
uint32_t gc_obj_size(uint32_t size);

//Get pointer to header of heap object from its ID
struct GC_Header *gc_get_header(uint32_t id,struct ErrorType *e);

//Get pointer to next header in linked list of heap objects
struct GC_Header *gc_next_header(struct GC_Header *header,struct ErrorType *e);

//Initialize garbage collector
void gc_init(void *new_heap_base,uint32_t new_heap_size,struct ErrorType *e);

//Set PID belonging to process using the garbage collector
    //PID 0 is the root PID and can access and modify all other objects' PIDs
    //PIDs other than 0 can only access their own objects
void gc_set_pid(uint8_t pid,struct ErrorType *e);

//Allocate a heap object returning its ID
uint32_t gc_alloc(uint32_t size,struct ErrorType *e);

//Reallocate heap object and change its size
void gc_realloc(uint32_t id,uint32_t size,struct ErrorType *e);

//Free heap object which must be unlocked first
void gc_free(uint32_t id,struct ErrorType *e);

//Lock heap object and return temporary pointer to its data section
    //Objects can be locked multiple times and must be unlocked the
    //same number of times before they can be compacted or freed
void *gc_lock(uint32_t id,struct ErrorType *e);

//Unlock heap object. Objects can be locked multiple times and must
    //be unlocked the same number of times before they can be
    //compacted ot freed.
void gc_unlock(uint32_t id,struct ErrorType *e);

//Get total number of free bytes on heap including header bytes
uint32_t gc_free_bytes(struct ErrorType *e);

//Get total number of allocated bytes on heap including header bytes
    //Does not include the two objects used internally for housekeeping
    //pid_only - whether to calculate bytes for current PID or all PIDs
uint32_t gc_allocated_bytes(bool pid_only,struct ErrorType *e);

//Get total number of locked bytes on heap including header bytes
    //Does not include the two objects used internally for housekeeping
    //pid_only - whether to calculate bytes for current PID or all PIDs
uint32_t gc_locked_bytes(bool pid_only,struct ErrorType *e);

//Get total number of free bytes on heap including header bytes and 
    //excluding last free object on heap. These are fragmented bytes 
    //that were not recovered while compacting. Only makes sense 
    //immediately after compacting.
uint32_t gc_lost_bytes(struct ErrorType *e);

//Get count of heap objects
    //Does not include the two objects used internally for housekeeping
    //pid_only - whether to calculate bytes for current PID or all PIDs
    //locked - whether to count locked objects
    //unlocked - whether to count unlocked objects
    //free - whether to count free objects though contiguous free objects
        //are not combined until compacting
uint32_t gc_obj_count(bool pid_only,bool locked,bool unlocked,bool free,struct ErrorType *e);

//Compact memory combining free blocks and moving them to end of heap
    //Searches for first unlocked memory to fit into each free slot
    //Relatively fast but may leave more fragmentation
void gc_compact_fast(struct ErrorType *e);

//Compact memory combining free blocks and moving them to end of heap
    //Searches all heap objects for best fit to fill each free slot
    //Relatively slow but less fragmentation
void gc_compact_full(struct ErrorType *e);

//Get size of object as stored in header which may be slightly larger
    //than the size requested
uint32_t gc_get_header_size(uint32_t id,struct ErrorType *e);

//Get size of object as stored in header which may be slightly larger
    //than the size requested less size of header
uint32_t gc_get_data_size(uint32_t id,struct ErrorType *e);

//TODO: describe
void gc_check(struct ErrorType *e);

//TODO: remove
void gc_debug(struct ErrorType *e);
