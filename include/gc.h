//Garbage collection routines
#pragma once

#include <stdbool.h>

#include "error.h"

#define GC_TABLE_ELEMENTS   128     //Elements in table of memory IDs

struct GC_Header
{
    uint32_t size;                  //Including header
    uint8_t pid;
    bool free;
    uint8_t lock_count;
    //Flexible array member
    alignas(uint32_t) char data[];
};

void gc_init(void *new_heap_base,uint32_t new_heap_size,struct ErrorType *e);
int gc_alloc(uint32_t size,struct ErrorType *e);
void gc_realloc(int id,uint32_t size,struct ErrorType *e);
void gc_free(int id,struct ErrorType *e);
void *gc_lock(int id,struct ErrorType *e);
void gc_unlock(int id,struct ErrorType *e);
uint32_t gc_free_bytes(struct ErrorType *e);
uint32_t gc_locked_bytes(struct ErrorType *e);
uint32_t gc_overhead_bytes(struct ErrorType *e);
void gc_compact(struct ErrorType *e);
void gc_check(struct ErrorType *e);
