#include <stddef.h>
#include <stdint.h>

//TODO: remove
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "gc.h"

//Constants
#define GC_TABLE_ELEMENTS   128     //Initial size of table
#define GC_TABLE_ID         0       //First table entry is pointer to table

//Global variables private to file
static struct GC_Internals gc;

//Advance to next header
struct GC_Header *gc_next_header(struct GC_Header *header)
{
    return (struct GC_Header *)(((uintptr_t)header)+header->size);
}

//Initialize garbage collector
void gc_init(void *new_heap_base,uint32_t new_heap_size,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Record heap characteristics for later
    gc.heap_base=new_heap_base;
    gc.heap_size=new_heap_size;

    //First object is for table of GC IDs
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;
    header->size=sizeof(struct GC_Header)+sizeof(struct GC_Header *)*GC_TABLE_ELEMENTS;
    header->free=false;     
    header->pid=GC_ROOT_PID;
    header->lock_count=1;   //Locked and should never be unlocked
    ((struct GC_Header **)header->data)[GC_TABLE_ID]=header;  //First object in table is table itself
    for (int i=1;i<GC_TABLE_ELEMENTS;i++)
    {
        //Set all GC IDs in table to NULL showing not used
        ((struct GC_Header **)header->data)[i]=NULL;
    }
    gc.table_elements=GC_TABLE_ELEMENTS;
    gc.ids_left=GC_TABLE_ELEMENTS;
    gc.id_table=(struct GC_Header **)header->data;

    //Free memory ready for allocation
    uint32_t bytes_left=gc.heap_size-header->size;
    header=gc_next_header(header);
    header->size=bytes_left-sizeof(struct GC_Header);   //Account for end marker below
    header->free=true;
    //Don't need pid or lock_count if memory is free

    //Empty object to mark end of heap
    header=(struct GC_Header *)((uintptr_t)gc.heap_base+gc.heap_size-sizeof(struct GC_Header));
    header->size=sizeof(struct GC_Header);  //Header only marks end of heap
    header->free=false;
    header->pid=GC_ROOT_PID;
    header->lock_count=1;

    //Assume root access to until set otherwise
    gc.current_pid=GC_ROOT_PID;
}

uint32_t gc_alloc(uint32_t size,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    //Object size cannot be 0
    if (size==0)
    {
        e->code=GC_ERROR_OBJ_SIZE;
        return 0;
    }

    //Round up object size to alignment
    size+=(GC_ALIGN-size%GC_ALIGN)%GC_ALIGN;

    //Add size of header to requested size
    size+=sizeof(struct GC_Header);

    //Expand ID table it necessary
    if (gc.ids_left==0)
    {
        //ID table full - expand
        //TODO: probably can't use gc_realloc
    }

    //Assign ID
    uint32_t assigned_id=0;
    for (int i=0;i<gc.table_elements;i++)
    {
        if (gc.id_table[i]==NULL)
        {
            //Found new ID to use
            assigned_id=i;
            break;
        }
    }
    gc.ids_left--;

    //Try to find free memory slot then compact and try again if necessary
    for (int i=0;i<2;i++)
    {
        //Search heap for free memory slot
        struct GC_Header *header=(struct GC_Header *)gc.heap_base;
        while(header->size-sizeof(struct GC_Header)!=0)
        {
            if ((header->free==true)&&(header->size>=size))
            {
                //Memory slot found - claim
                header->free=false;
                header->pid=gc.current_pid;
                header->lock_count=0;
                
                //Assign ID in table
                gc.id_table[assigned_id]=header;

                //Split block if possible
                if (header->size>=size+sizeof(struct GC_Header)+GC_ALIGN)
                {
                    //Split block into two
                    uint32_t old_size=header->size;
                    header->size=size;
                    header=gc_next_header(header);
                    header->size=old_size-size;
                    header->free=true;
                }
                else
                {
                    //Cannot split - new block would not be big enough for header and min data size
                    //Leave size as is even if slightly larger than requested
                }

                //Done
                return assigned_id;
            }

            //Advance to next header
            header=gc_next_header(header);
        }

        //Search finished without finding free memory slot
        if (i==0)
        {
            //Compact heap and try again
            gc_compact(e);
        }
        else
        {
            //Second time through - heap was compacted last time so must be out of memory
            e->code=GC_ERROR_OUT_OF_MEM;
            return 0;
        }
    }
}

void gc_realloc(int id,uint32_t size,struct ErrorType *e);

void gc_free(int id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Check memory before freeing including ID range
    struct GC_Header *header=get_header(id,e);
    if (e->code!=ERROR_NONE) return;

    //Make sure memory is not already free
        //Must happen first since PID and lock_count only valid if free is false
    if (header->free==true)
    {
        //Memory is already free
        e->code=GC_ERROR_DOUBLE_FREE;
        return;
    }

    //Make sure memory does not belong to another program
    if (gc.current_pid!=GC_ROOT_PID)
    {
        //PID is not root
        if (header->pid!=gc.current_pid)
        {
            e->code=GC_ERROR_WRONG_PID;
            return;
        }
    }

    //Make sure memory is not locked
    if (header->lock_count>0)
    {
        //Memory is still locked
        e->code=GC_ERROR_FREE_LOCKED;
        return;
    }

    //Free memory
    header->free=true;
}

void *gc_lock(int id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Check memory before freeing including ID range
    struct GC_Header *header=get_header(id,e);
    if (e->code!=ERROR_NONE) return;

    //Make sure memory does not belong to another program
    if (gc.current_pid!=GC_ROOT_PID)
    {
        //PID is not root
        if (header->pid!=gc.current_pid)
        {
            e->code=GC_ERROR_WRONG_PID;
            return;
        }
    }

    //Don't exceed max number of locks
    if (header->lock_count==UINT8_MAX)
    {
        //Exceeded max lock count
        e->code=GC_ERROR_LOCK_COUNT;
        return;
    }

    //Increase lock count
    header->lock_count++;
}

void gc_unlock(int id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Check memory before freeing including ID range
    struct GC_Header *header=get_header(id,e);
    if (e->code!=ERROR_NONE) return;

    //Make sure memory does not belong to another program
    if (gc.current_pid!=GC_ROOT_PID)
    {
        //PID is not root
        if (header->pid!=gc.current_pid)
        {
            e->code=GC_ERROR_WRONG_PID;
            return;
        }
    }

    //Don't unlock if already unlocked
    if (header->lock_count==0)
    {
        //Exceeded max lock count
        e->code=GC_ERROR_UNLOCK;
        return;
    }

    //Increase lock count
    header->lock_count--;
}

struct GC_Header *gc_header(uint32_t id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return NULL;

    //Make sure ID is in range
    if (id>=gc.table_elements)
    {
        e->code=GC_ERROR_ID_RANGE;
        return NULL;
    }

    return gc.id_table[id];
}
uint32_t gc_free_bytes(struct ErrorType *e);
uint32_t gc_locked_bytes(struct ErrorType *e);
uint32_t gc_object_count(struct ErrorType *e);
void gc_compact(struct ErrorType *e)
{
    

}
