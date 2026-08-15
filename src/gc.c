#include <stddef.h>
#include <stdint.h>
#include <string.h>

//TODO: remove
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "gc.h"

//TODO: switch from adding extra bytes to objects to aligning to 16 or so


//Global variables private to file
static struct GC_Internals gc;

//Get header from ID
struct GC_Header *gc_get_header(uint32_t id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return NULL;

    //Make sure ID is in range
    if (id>=gc.table_elements)
    {
        e->code=GC_ERROR_ID_RANGE;
        return NULL;
    }

    //Make sure ID is not in use
    if (gc.id_table[id]==NULL)
    {
        //ID is not assigned
        e->code=GC_ERROR_ID_UNASSIGNED;
        return NULL;
    }

    return gc.id_table[id];
}

//Advance to next header
struct GC_Header *gc_next_header(struct GC_Header *header,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return NULL;

    //Make sure header size is not 0 which would stall traversing list
        //Would only happen if heap is corrupt
    if (header->size==0)
    {
        e->code=GC_ERROR_EMPTY_HEADER;
        return NULL;
    }

    //Make sure next header is at higher address
        //Would only happen if heap is corrupt
    struct GC_Header *new_header=(struct GC_Header *)(((uintptr_t)header)+header->size);
    if (new_header<=header)
    {
        e->code=GC_ERROR_HEADER_SIZE;
        return NULL;
    }

    //Make sure new header address is not beyond end of heap
        //Would only happen if heap is corrupt
    if (((uintptr_t)new_header)>((uintptr_t)gc.heap_base+gc.heap_size-sizeof(struct GC_Header)))
    {
        e->code=GC_ERROR_HEADER_OVERFLOW;
        return NULL;
    }

    return new_header;
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
    header->lock_count=0;
    ((struct GC_Header **)header->data)[GC_TABLE_ID]=header;  //First object in table is table itself
    for (int i=1;i<GC_TABLE_ELEMENTS;i++)
    {
        //Set all GC IDs in table to NULL showing not used
        ((struct GC_Header **)header->data)[i]=NULL;
    }
    gc.table_elements=GC_TABLE_ELEMENTS;
    gc.ids_left=GC_TABLE_ELEMENTS;
    gc.id_table_header=header;
    gc.id_table=(struct GC_Header **)header->data;

    //Free memory ready for allocation
    uint32_t bytes_left=gc.heap_size-header->size;
    header=gc_next_header(header,e);
    header->size=bytes_left-sizeof(struct GC_Header);   //Account for end marker below
    header->free=true;
    //Don't need pid or lock_count if memory is free

    //Empty object to mark end of heap
    header=(struct GC_Header *)((uintptr_t)gc.heap_base+gc.heap_size-sizeof(struct GC_Header));
    header->size=sizeof(struct GC_Header);  //Header only marks end of heap
    header->free=false;
    header->pid=GC_ROOT_PID;
    header->lock_count=1;

    //Assume root access to objects until set otherwise
    gc.current_pid=GC_ROOT_PID;
}

void gc_set_pid(uint8_t pid,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;
    
    gc.current_pid=pid;
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

    //Expand ID table if necessary
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

    //Try to find free memory slot then compact and try again if necessary
    for (int i=0;i<3;i++)
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
                header->id=assigned_id;

                //Split block if possible
                if (header->size>=size+sizeof(struct GC_Header)+GC_MIN_SIZE)
                {
                    //Split block into two
                    uint32_t old_size=header->size;
                    header->size=size;
                    struct GC_Header *new_header=gc_next_header(header,e);
                    if (e->code!=ERROR_NONE) return 0;
                    new_header->size=old_size-size;
                    new_header->free=true;
                }
                else
                {
                    //Cannot split - new block would not be big enough for header and min data size
                    //Leave size as is even if slightly larger than requested
                }

                //Done
                gc.ids_left--;
                return assigned_id;
            }

            //Advance to next header
            header=gc_next_header(header,e);
            if (e->code!=ERROR_NONE) return 0;
        }

        //Search finished without finding free memory slot
        if (i==0)
        {
            //Try 1 - compact heap quickly and try allocating again
            gc_compact_fast(e);
            if (e->code!=ERROR_NONE) return 0;
        }
        else if (i==1)
        {
            //Try 2 - compact heap completely and try allocating again
            gc_compact_full(e);
            if (e->code!=ERROR_NONE) return 0;
        }
        else
        {
            //Try 3 - heap fully compacted and no free memory slot - out of memory
            e->code=GC_ERROR_OUT_OF_MEM;
            return 0;
        }
    }
}

void gc_realloc(int id,uint32_t size,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Object size cannot be 0
    if (size==0)
    {
        e->code=GC_ERROR_OBJ_SIZE;
        return;
    }

    //TODO: check if locked

    //Round up object size to alignment
    size+=(GC_ALIGN-size%GC_ALIGN)%GC_ALIGN;

    //Add size of header to requested size
    size+=sizeof(struct GC_Header);

    //Shrink or expand based on size difference
    struct GC_Header *original_header=gc_get_header(id,e);
    if (e->code!=ERROR_NONE) return;
    if (original_header->size==size)
    {
        //No change in size - nothing to do
        return;
    }
    else if (original_header->size>size)
    {
        //Requested size is smaller than original object - shrink
        uint32_t original_size=original_header->size;
        uint32_t free_size=original_size-size;
        
        //Create free object in extra space if possible
        if (free_size>=sizeof(struct GC_Header)+GC_MIN_SIZE)
        {
            //Create free object
            struct GC_Header *free_header=gc_next_header(original_header,e);
            if (e->code!=ERROR_NONE) return;
            original_header->size=size;
            free_header->size=free_size;
            free_header->free=true;
        }
        else
        {
            //Cannot split - new block would not be big enough for header and min data size
            //Leave size as is even if slightly larger than requested
        }
    }
    else
    {
        //Requested size is larger than original object - expand
    }

    /*
    //Try to find free memory slot then compact and try again if necessary
    for (int i=0;i<3;i++)
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
                header->id=assigned_id;

                //Split block if possible
                if (header->size>=size+sizeof(struct GC_Header)+GC_MIN_SIZE)
                {
                    //Split block into two
                    uint32_t old_size=header->size;
                    header->size=size;
                    header=gc_next_header(header,e);
                    header->size=old_size-size;
                    header->free=true;
                }
                else
                {
                    //Cannot split - new block would not be big enough for header and min data size
                    //Leave size as is even if slightly larger than requested
                }

                //Done
                gc.ids_left--;
                return assigned_id;
            }

            //Advance to next header
            header=gc_next_header(header,e);
            if (e->code!=ERROR_NONE) return;
        }

        //Search finished without finding free memory slot
        if (i==0)
        {
            //Try 1 - compact heap quickly and try allocating again
            gc_compact_fast(e);
            if (e->code!=ERROR_NONE) return;
        }
        else if (i==1)
        {
            //Try 2 - compact heap completely and try allocating again
            gc_compact_full(e);
            if (e->code!=ERROR_NONE) return;
        }
        else
        {
            //Try 3 - heap fully compacted and no free memory slot - out of memory
            e->code=GC_ERROR_OUT_OF_MEM;
            return 0;
        }
    }
    */
}

void gc_free(int id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Check memory before freeing, including ID range
        //Also errors if memory here is free catching double free
    struct GC_Header *header=gc_get_header(id,e);
    if (e->code!=ERROR_NONE) return;

    //Make sure memory does not belong to another program
    if (gc.current_pid!=GC_ROOT_PID)
    {
        //PID is not root
        if (header->pid!=gc.current_pid)
        {
            //PID of object does not belong to current process
            e->code=GC_ERROR_WRONG_PID;
            return;
        }
    }
    else
    {
        //PID is root - ok to modify memory of any other process
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
    gc.id_table[id]=NULL;
    gc.ids_left++;
}

void *gc_lock(int id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return NULL;

    //Check memory before locking including ID range
    struct GC_Header *header=gc_get_header(id,e);
    if (e->code!=ERROR_NONE) return NULL;

    //Make sure memory does not belong to another program
    if (gc.current_pid!=GC_ROOT_PID)
    {
        //PID is not root
        if (header->pid!=gc.current_pid)
        {
            //PID of object does not belong to current process
            e->code=GC_ERROR_WRONG_PID;
            return NULL;
        }
    }
    else
    {
        //PID is root - ok to modify memory of any other process
    }

    //Don't exceed max number of locks
    if (header->lock_count==GC_MAX_LOCKS)
    {
        //Exceeded max lock count
        e->code=GC_ERROR_LOCK_COUNT;
        return NULL;
    }

    //Increase lock count
    header->lock_count++;

    //Return pointer to data portion of object, not header
    return header->data;
}

void gc_unlock(int id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Check memory before freeing including ID range
    struct GC_Header *header=gc_get_header(id,e);
    if (e->code!=ERROR_NONE) return;

    //Make sure memory does not belong to another program
    if (gc.current_pid!=GC_ROOT_PID)
    {
        //PID is not root
        if (header->pid!=gc.current_pid)
        {
            //PID of object does not belong to current process
            e->code=GC_ERROR_WRONG_PID;
            return;
        }
    }
    else
    {
        //PID is root - ok to modify memory of any other process
    }

    //Don't unlock if already unlocked
    if (header->lock_count==0)
    {
        //Already unlocked
        e->code=GC_ERROR_UNLOCK;
        return;
    }

    //Decrease lock count
    header->lock_count--;
}

uint32_t gc_free_bytes(struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    //First object in heap
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;

    //Loop through all objects
    uint32_t size=0;
    while(1)
    {
        //End of heap found?
        if (header->size==sizeof(struct GC_Header)) return size;

        //Add up size of all free objects
        if (header->free==true)
            size+=header->size;

        //Next header
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return 0;
    }
}

uint32_t gc_allocated_bytes(bool pid_only,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    //First object in heap
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;

    //Loop through all objects
    uint32_t size=0;
    while(1)
    {
        //End of heap found?
        if (header->size==sizeof(struct GC_Header)) return size;

        //Add up size of all allocated objects belonging to PID or all PIDs
            //Skip table of object IDs used internally for housekeeping
        if (header!=gc.id_table_header)
        {
            if (header->free==false)
            {
                if ((pid_only==false)||(gc.current_pid==header->pid))
                {
                    size+=header->size;
                }
            }
        }

        //Next header
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return 0;
    }
}

uint32_t gc_locked_bytes(bool pid_only,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    //First object in heap
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;

    //Loop through all objects
    uint32_t size=0;
    while(1)
    {
        //End of heap found?
        if (header->size==sizeof(struct GC_Header)) return size;

        //Add up size of all locked objects belonging to PID or all PIDs
            //Skip table of object IDs used internally for housekeeping
        if (header!=gc.id_table_header)
        {
            if (header->free==false)
            {
                if ((pid_only==false)||(gc.current_pid==header->pid))
                {
                    if (header->lock_count>0)
                    {
                        size+=header->size;
                    }
                }
            }
        }

        //Next header
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return 0;
    }
}

//Size of all free bytes exluding last free object
    //Only makes sense immediately after gc_compact
uint32_t gc_lost_bytes(struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    //First object in heap
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;

    //Loop through all objects
    uint32_t size=0;
    uint32_t total_size=0;
    while(1)
    {
        //End of heap found?
        if (header->size==sizeof(struct GC_Header)) return total_size;

        //Add up size of all free objects
        if (header->free==true)
        {
            size+=header->size;
        }
        else 
        {
            total_size+=size;
            size=0;
        }

        //Next header
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return 0;
    }
}

uint32_t gc_obj_count(bool pid_only,bool locked,bool unlocked,bool free,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    //First object in heap
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;

    //Loop through all objects
    uint32_t count=0;
    while(1)
    {
        //End of heap found?
        if (header->size==sizeof(struct GC_Header)) return count;

        //Count objects
        if (header!=gc.id_table_header)
        {
            if (header->free==true)
            {
                if (free==true) count++;
            }
            else
            {
                if ((pid_only==false)||(gc.current_pid==header->pid))
                {
                    if (locked)
                    {
                        if (header->lock_count>0) count++;
                    }
                    if (unlocked)
                    {
                        if (header->lock_count==0) count++;
                    }
                }
            }
        }

        //Next header
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return 0;
    }
}

void gc_compact_fast(struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //First object in heap
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;

    //Loop through all objects on heap
    while(1)
    {
        //End of heap found?
        if (header->size==sizeof(struct GC_Header)) return;

        //Free space found - combine with contiguous free space then fill
        if (header->free==true)
        {
            //Search for neighboring free space
            while(1)
            {
                //Advance to next object
                struct GC_Header *combine_header=gc_next_header(header,e);
                if (e->code!=ERROR_NONE) return;

                //End of heap found?
                if (combine_header->size==sizeof(struct GC_Header)) break;

                if (combine_header->free==true)
                {
                    //Next object is free space - combine with current
                    header->size+=combine_header->size;
                }
                else
                {
                    //Next object is not free - done searching
                    break;
                }
            }

            //Move neighboring block down to fill hole if unlocked
            bool found=false;
            struct GC_Header *fill_header=gc_next_header(header,e);
            if (e->code!=ERROR_NONE) return;
            if (fill_header->free==false)
            {
                if (fill_header->lock_count==0)
                {
                    //Neighboring block unlocked - move down
                    uint32_t free_size=header->size;
                    gc.id_table[fill_header->id]=header;
                    memmove(header,fill_header,fill_header->size);
                    fill_header=gc_next_header(header,e);
                    if (e->code!=ERROR_NONE) return;
                    fill_header->size=free_size;
                    fill_header->free=true;
                    found=true;
                }
            }

            //Search for unlocked memory to fill empty space with
            if (found==false)
            {
                fill_header=header;
                while(1)
                {
                    //Advance to next object
                    fill_header=gc_next_header(fill_header,e);
                    if (e->code!=ERROR_NONE) return;

                    //End of heap found?
                    if (fill_header->size==sizeof(struct GC_Header)) break;

                    //Can object fill empty space?
                    if (fill_header->free==false)
                    {
                        if (fill_header->lock_count==0)
                        {
                            if (header->size>=fill_header->size)
                            {
                                //Object found - move into free space
                                uint32_t old_size=header->size;
                                if (header->size>=fill_header->size+sizeof(struct GC_Header)+GC_MIN_SIZE)
                                {
                                    //Excess room - create free object at end after copying
                                    header->size=fill_header->size;
                                    struct GC_Header *free_header=gc_next_header(header,e);
                                    if (e->code!=ERROR_NONE) return;
                                    free_header->size=old_size-header->size;
                                    free_header->free=true;
                                    gc.id_table[fill_header->id]=header;
                                    memcpy(header,fill_header,fill_header->size);
                                    fill_header->free=true;
                                }
                                else
                                {
                                    //Not enough room after object is copied - add excess to
                                        //object copied even if not needed
                                    gc.id_table[fill_header->id]=header;
                                    memcpy(header,fill_header,fill_header->size);
                                    header->size=old_size;
                                    fill_header->free=true;
                                }

                                //Update pointer to ID table if it changed
                                if (fill_header==gc.id_table_header)
                                {
                                    gc.id_table_header=header;
                                    gc.id_table=(struct GC_Header **)header->data;
                                }

                                //Combine newly freed memory with next block if free
                                struct GC_Header *next_header=gc_next_header(fill_header,e);
                                if (next_header->free==true)
                                    fill_header->size+=next_header->size;

                                //Stop searching
                                break;
                            }
                        }
                    }
                }
            }
        }

        //Next header
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return;
    }
}

void gc_compact_full(struct ErrorType *e)
{
    //TODO
}

uint32_t gc_get_header_size(int id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    struct GC_Header *header=gc_get_header(id,e);
    if (e->code!=ERROR_NONE) return 0;
    
    return header->size;
}

uint32_t gc_get_data_size(int id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    struct GC_Header *header=gc_get_header(id,e);
    if (e->code!=ERROR_NONE) return 0;
    
    return header->size-sizeof(struct GC_Header);
}

void gc_check(struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //First object in heap
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;

    //Loop through all objects
    uint32_t size=0;
    while(1)
    {
        //Track combined size of all objects
        size+=header->size;

        if (header->size==sizeof(struct GC_Header))
        {
            //End of heap found
            if (size!=gc.heap_size)
            {
                //Total size of objects does not equal total heap
                e->code=GC_ERROR_HEAP_SIZE;
            }

            //No errors found - done
            return;
        }

        //Rely on heap corruption tests in gc_next_header 
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return;
    }
}

void gc_debug(struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //First object in heap
    struct GC_Header *header=(struct GC_Header *)gc.heap_base;

    //Loop through all objects
    uint32_t size=0;
    while(1)
    {
        if (header->size==sizeof(struct GC_Header)) return;

        printf("%X: size: %d, free: %d",header,header->size,header->free);
        if (header->free==false)
            printf(", ID: %d, pid %d, locked %d",header->id,header->pid,header->lock_count);
        printf("\n");

        header=gc_next_header(header,e);
    }
}
