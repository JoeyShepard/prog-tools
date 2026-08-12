//Garbage collection routines
#pragma once

#include <stdbool.h>

#include "error.h"

#define GC_ALIGN            4       //Alignment requirement on SH4
#define GC_TABLE_ELEMENTS   128     //Elements in table of memory IDs
#define GC_ROOT_PID         0       //Root can access memory belonging to any PID

enum GC_ERRORS
{
    GC_ERROR_NONE=ERROR_NONE,
    GC_ERROR_OBJ_SIZE,
    GC_ERROR_OUT_OF_MEM,
    GC_ERROR_ID_RANGE,
    GC_ERROR_DOUBLE_FREE,
    GC_ERROR_FREE_LOCKED,
    GC_ERROR_WRONG_PID,
    GC_ERROR_LOCK_COUNT,
    GE_ERROR_UNLOCK,
};

struct GC_Header
{
    uint32_t size;                  //Including header
    bool free;
    uint8_t pid;
    uint8_t lock_count;
    //Flexible array member
    alignas(uint32_t) char data[];
};

struct GC_Internals
{
    void *heap_base;
    uint32_t heap_size;
    uint32_t table_elements;
    uint32_t ids_left;
    struct GC_Header **id_table;
    uint8_t current_pid;

};

struct GC_Header *gc_next_header(struct GC_Header *header);
void gc_init(void *new_heap_base,uint32_t new_heap_size,struct ErrorType *e);
void gc_set_pid(uint8_t pid,struct ErrorType *e);
uint32_t gc_alloc(uint32_t size,struct ErrorType *e);
void gc_realloc(int id,uint32_t size,struct ErrorType *e);
void gc_free(int id,struct ErrorType *e);
void *gc_lock(int id,struct ErrorType *e);
void gc_unlock(int id,struct ErrorType *e);
struct GC_Header *gc_header(uint32_t id,struct ErrorType *e);
uint32_t gc_free_bytes(struct ErrorType *e);
uint32_t gc_locked_bytes(struct ErrorType *e);
uint32_t gc_overhead_bytes(struct ErrorType *e);
void gc_compact(struct ErrorType *e);
