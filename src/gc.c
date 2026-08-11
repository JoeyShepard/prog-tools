#include <stddef.h>
#include <stdint.h>

#include "error.h"
#include "gc.h"

//Constants
#define GC_TABLE_ELEMENTS   128     //Initial size of table

//Global variables private to file
static void *heap_base;
static uint32_t heap_size;
static struct GC_Header *gc_table;
static uint32_t gc_table_elements;

//Initialize garbage collector
void gc_init(void *new_heap_base,uint32_t new_heap_size,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Record heap characteristics for later
    heap_base=new_heap_base;
    heap_size=new_heap_size;

    //First object is for table of GC IDs
    struct GC_Header *header=(struct GC_Header *)heap_base;
    header->size=sizeof(struct GC_Header)+sizeof(struct GC_Header *)*GC_TABLE_ELEMENTS;
    header->free=false;     
    header->pid=0;          //Belongs to root process
    header->lock_count=1;   //Locked and should never be unlocked
    for (int i=0;i<GC_TABLE_ELEMENTS;i++)
    {
        //Set all GC IDs in table to NULL showing not used
        ((struct GC_Header **)header->data)[i]=NULL;
    }
    gc_table_elements=GC_TABLE_ELEMENTS;
    gc_table=header;

    //Free memory ready for allocation
    uint32_t bytes_left=heap_size-header->size;
    header+=header->size;
    header->size=bytes_left-sizeof(struct GC_Header);   //Account for end marker below
    header->free=true;
    //Don't need pid or lock_count if memory is free

    //Empty object to mark end of heap
    header=(struct GC_Header *)((uintptr_t)heap_base+heap_size-sizeof(struct GC_Header));
    header->size=sizeof(struct GC_Header);  //Header only marks end of heap
    header->free=false;
    header->pid=0;
    header->lock_count=1;
}

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
