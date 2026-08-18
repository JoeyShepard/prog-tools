#include <stddef.h>
#include <stdint.h>
#include <string.h>

//TODO: remove
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "gc.h"

//Global variables private to file
static struct GC_Internals gc;

//Static functions
//================
static uint32_t gc_round_up(uint32_t number,uint32_t alignment)
{
    return number+(alignment-number%alignment)%alignment;
}

static void gc_update_id_table(struct GC_Header *old_header,struct GC_Header *new_header,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    if (old_header==gc.id_table_header)
    {
        gc.id_table_header=new_header;
        gc.id_table=(struct GC_Header **)new_header->data;
        gc.id_table[GC_TABLE_ID]=new_header;
    }
}

//Rearrange objects near reallocated object to prepare for expansion where reallocated
    //object is first followed by free space then unlocked objects
static void gc_rearrange_realloc(uint32_t id,struct GC_Header *range_begin,uint32_t free_size,uint32_t unlocked_size,struct ErrorType *e)
{
    //Free space in range is enough - rearrange unlocked objects
    struct GC_Header *end_header=(struct GC_Header *)(((uintptr_t)range_begin)+free_size+unlocked_size);
    bool changed;
    do
    {
        //Rearrange objects until no changes left
        changed=false;
        bool obj_found=false;
        struct GC_Header *search_header=range_begin;

        printf("rearrange - restart\n");

        while(search_header!=end_header)
        {
            //No changes to make if at last header in range since can't swap
            struct GC_Header *next_header=gc_next_header(search_header,e);
            if (e->code!=ERROR_NONE) return;
            
            printf("before\n");
            printf("rearrange - free %d, size %d, lock_count %d, id %d\n",search_header->free,search_header->size,search_header->lock_count,search_header->id);
            printf("rearrange - free %d, size %d, lock_count %d, id %d\n",next_header->free,next_header->size,next_header->lock_count,next_header->id);

            if (next_header!=end_header)
            {
                if (search_header->free==true)
                {
                    //First object is free
                    if (next_header->free==true)
                    {
                        //Both objects free - combine
                        search_header->size+=next_header->size;
                        changed=true;
                    }
                    else
                    {
                        //Second object is unlocked
                        if (obj_found==false)
                        {
                            //Below reallocated object - push free object up
                            if (next_header->id==id)
                            {
                                //Mark reallocated object as found
                                obj_found=true;
                            }
                            gc_swap_next(search_header,e);
                            if (e->code!=ERROR_NONE) return;
                            changed=true;
                        }
                        else
                        {
                            //Above reallocated object - no change
                        }
                    }
                }
                else
                {
                    //First object is unlocked
                    if (next_header->free==true)
                    {
                        //Second object is free
                        if (obj_found==false)
                        {
                            //Below reallocated object - no change
                            if (search_header->id==id)
                            {
                                //Mark reallocated object as found
                                obj_found=true;
                            }
                        }
                        else
                        {
                            //Above reallocated object - move free object down
                            gc_swap_next(search_header,e);
                            if (e->code!=ERROR_NONE) return;
                            changed=true;
                        }
                    }
                    else
                    {
                        //Second object is unlocked
                        if (next_header->id==id)
                        {
                            gc_swap_next(search_header,e);
                            if (e->code!=ERROR_NONE) return;
                            changed=true;
                            obj_found=true;
                        }
                        else if (search_header->id==id)
                        {
                            //Mark reallocated object as found
                            obj_found=true;
                        }
                    }
                }
            }

            printf("after\n");
            printf("rearrange - free %d, size %d, lock_count %d, id %d\n",search_header->free,search_header->size,search_header->lock_count,search_header->id);
            next_header=gc_next_header(search_header,e);
            if (e->code!=ERROR_NONE) return;
            printf("rearrange - free %d, size %d, lock_count %d, id %d\n",next_header->free,next_header->size,next_header->lock_count,next_header->id);
            /*
            char *b=NULL;
            int n=0;
            getline(&b,&n,stdin);
            */

            //Advance to next header
            search_header=gc_next_header(search_header,e);
            if (e->code!=ERROR_NONE) return;
        }
    } while(changed==true);
}

//Functions
//=========
uint32_t gc_obj_size(uint32_t size)
{
    return gc_round_up(size+sizeof(struct GC_Header),GC_OBJ_ALIGN);
}

struct GC_Header *gc_find_free(uint32_t size,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return NULL;

    struct GC_Header *header=(struct GC_Header *)gc.heap_base;
    while(header->end==false)
    {
        if ((header->free==true)&&(header->size>=size))
        {
            //Free slot found - done searching
            return header;
        }

        //Advance to next header
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return NULL;
    }

    //Finished searching without finding match
    return NULL;
}

//Functions
//=========

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

//TODO: add check that id corresponds to address
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

    //Make sure object is not misaligned
        //Would only happen if heap is corrupt
    if (header->size%GC_OBJ_ALIGN!=0)
    {
        e->code=GC_ERROR_OBJ_ALIGNMENT;
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

//TODO: check if multiple of GC_OBJ_SIZE
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
    header->size=gc_round_up(sizeof(struct GC_Header)+sizeof(struct GC_Header *)*GC_TABLE_ELEMENTS,GC_OBJ_ALIGN);
    header->end=false;
    header->free=false;     
    header->pid=GC_ROOT_PID;
    header->lock_count=0;
    ((struct GC_Header **)header->data)[GC_TABLE_ID]=header;  //First object in table is table itself
    header->id=0;
    for (int i=1;i<GC_TABLE_ELEMENTS;i++)
    {
        //Set all GC IDs in table to NULL showing not used
        ((struct GC_Header **)header->data)[i]=NULL;
    }
    gc.table_elements=GC_TABLE_ELEMENTS;
    gc.ids_left=GC_TABLE_ELEMENTS-1;    //Less one for ID table in slot 0
    gc.id_table_header=header;
    gc.id_table=(struct GC_Header **)header->data;

    //Free memory ready for allocation
    uint32_t bytes_left=gc.heap_size-header->size;
    header=gc_next_header(header,e);
    header->size=bytes_left-GC_OBJ_ALIGN;   //Account for end marker below
    header->end=false;
    header->free=true;
    //Don't need pid or lock_count if memory is free

    //Empty object to mark end of heap
    header=(struct GC_Header *)((uintptr_t)gc.heap_base+gc.heap_size-GC_OBJ_ALIGN);
    header->size=GC_OBJ_ALIGN;
    header->end=true;
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

    //Account for header and round up to alignment
    size=gc_obj_size(size);

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
    const int try_count=3;
    for (int i=0;i<try_count;i++)
    {
        //Search heap for free memory slot
        struct GC_Header *header=gc_find_free(size,e);
        if (e->code!=ERROR_NONE) return 0;
        if (header!=NULL)
        {
            //Memory slot found - claim
            header->end=false;
            header->free=false;
            header->pid=gc.current_pid;
            header->lock_count=0;
            uint32_t old_size=header->size;
            header->size=size;
            
            //Assign ID in table
            gc.id_table[assigned_id]=header;
            header->id=assigned_id;

            //Create new free block if memory left over
            if (old_size>size)
            {
                struct GC_Header *new_header=gc_next_header(header,e);
                if (e->code!=ERROR_NONE) return 0;
                new_header->size=old_size-size;
                new_header->end=false;
                new_header->free=true;
            }

            //Done
            gc.ids_left--;
            return assigned_id;
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

void gc_realloc(uint32_t id,uint32_t requested_size,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Object size cannot be 0
    if (requested_size==0)
    {
        e->code=GC_ERROR_OBJ_SIZE;
        return;
    }

    //Object cannot be locked
    struct GC_Header *original_header=gc_get_header(id,e);
    if (e->code!=ERROR_NONE) return;
    if (original_header->lock_count!=0)
    {
        e->code=GC_ERROR_REALLOC_LOCKED;
        return;
    }

    //Account for header and round up to alignment
    uint32_t obj_size=gc_obj_size(requested_size);

    //Shrink or expand based on size difference
    if (original_header->size==obj_size)
    {
        //No change in size - nothing to do
        return;
    }
    else if (original_header->size>obj_size)
    {
        //Requested size is smaller than original object - shrink
        uint32_t old_size=original_header->size;
        original_header->size=obj_size;
        struct GC_Header *new_header=gc_next_header(original_header,e);
        if (e->code!=ERROR_NONE) return;
        new_header->size=old_size-obj_size;
        new_header->end=false;
        new_header->free=true;
    }
    else
    {
        //Requested size is larger than original object - expand

        //First, try to allocate new object and copy
        {
            uint32_t new_id=gc_alloc(requested_size,e);
            if (e->code==GC_ERROR_NONE)
            {
                //Allocation succeeded
                struct GC_Header *dest_header=gc_get_header(new_id,e);
                if (e->code!=ERROR_NONE) return;
                gc.id_table[new_id]=NULL;
                original_header=gc_get_header(id,e);
                if (e->code!=ERROR_NONE) return;
                memcpy(dest_header,original_header,original_header->size);
                dest_header->size=obj_size;
                gc_update_id_table(original_header,dest_header,e);
                if (e->code!=ERROR_NONE) return;
                gc.id_table[dest_header->id]=dest_header;
                original_header->free=true;

                //Done
                return;
            }
            else if (e->code==GC_ERROR_OUT_OF_MEM)
            {
                //Allocation failed - try alternate strategy below
                error_reset(e);
            }
            else
            {
                //Other error than out of memory - exit
                return;
            }
        }

        //Second, try to shift neighboring blocks in the same range to make room
        {
            original_header=gc_get_header(id,e);
            uint32_t unlocked_size=0;
            uint32_t free_size=0;
            bool obj_found=false;
            struct GC_Header *search_header=(struct GC_Header *)gc.heap_base;
            struct GC_Header *range_begin=NULL;
            while(search_header->end==false)
            {
                
                printf("header: free %d, size %d, lock %d, id %d. free_size %d, unlocked_size %d\n",
                    search_header->free,search_header->size,
                    search_header->lock_count,search_header->id,free_size,unlocked_size);

                if (search_header->free==true)
                {
                    //Found free object - add to total
                    free_size+=search_header->size;

                    //Record beginning of range if first object
                    if (range_begin==NULL) range_begin=search_header;
                }
                else if (search_header->free==false)
                {
                    if (search_header->lock_count==0)
                    {
                        //Found unlocked object - add to total
                        unlocked_size+=search_header->size;

                        //Record beginning of range if first object
                        if (range_begin==NULL) range_begin=search_header;
                        
                        //Found range containing reallocated object
                        if (search_header==original_header) obj_found=true;
                    }
                    else
                    {
                        //Found locked object - check if done searching
                        if (obj_found==true)
                        {
                            //Found range containing reallocated object - done searching 
                            break;
                        }
                        else
                        {
                            //Range does not contain reallocated object - discard
                            free_size=0;
                            unlocked_size=0;
                            range_begin=NULL;
                        }
                    }
                }

               //Advance to next object
               search_header=gc_next_header(search_header,e);
                if (e->code!=ERROR_NONE) return;
            }

            //If enough free space exists in the range, use it to expand the object
            uint32_t additional_space=obj_size-original_header->size;
            if (additional_space<=free_size)
            {
                printf("start rearranging\n");

                //Rearrange blocks so that reallocated object is first followed by free space
                    //followed by unlocked objects
                gc_rearrange_realloc(id,range_begin,free_size,unlocked_size,e);
                if (e->code!=ERROR_NONE) return;

                printf("done rearranging\n");

                gc_debug(e);
                if (e->code!=ERROR_NONE) return;
                printf("\n");

                //Expand reallocated object
                original_header=gc_get_header(id,e);
                struct GC_Header *free_header=gc_next_header(original_header,e);
                if (e->code!=ERROR_NONE) return;
                uint32_t new_free_size=original_header->size+free_header->size-obj_size;
                original_header->size=obj_size;
                if (new_free_size>0)
                {
                    //Create new free object for any excess space
                    free_header=gc_next_header(original_header,e);
                    free_header->free=true;
                    free_header->end=false;
                    free_header->size=new_free_size;
                }

                //Done
                return;
            }
        }

        //Third, subset sum
    }
}

void gc_free(uint32_t id,struct ErrorType *e)
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

void *gc_lock(uint32_t id,struct ErrorType *e)
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

void gc_unlock(uint32_t id,struct ErrorType *e)
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
        if (header->end==true) return size;

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
        if (header->end==true) return size;

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
        if (header->end==true) return size;

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
        if (header->end==true) return total_size;

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
        if (header->end==true) return count;

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
        if (header->end==true) return;

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
                if (combine_header->end==true) break;

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

                    //Mark next object as free
                    struct GC_Header *free_header=gc_next_header(header,e);
                    if (e->code!=ERROR_NONE) return;
                    free_header->size=free_size;
                    free_header->free=true;
                    free_header->end=false;
                    found=true;
                }
                else
                {
                    //Empty object marking end of heap is locked, so no need
                        //to check for it explicitly
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
                    if (fill_header->end==true) break;

                    //Can object fill empty space?
                    if (fill_header->free==false)
                    {
                        if (fill_header->lock_count==0)
                        {
                            if (header->size>=fill_header->size)
                            {
                                //Object found - move into free space
                                uint32_t old_size=header->size;
                                gc.id_table[fill_header->id]=header;
                                memmove(header,fill_header,fill_header->size);

                                //Mark moved object as free
                                fill_header->free=true;

                                //Create new free object for any excess space
                                if (old_size>header->size)
                                {
                                    struct GC_Header *new_header=gc_next_header(header,e);
                                    if (e->code!=ERROR_NONE) return;
                                    new_header->size=old_size-header->size;
                                    new_header->end=false;
                                    new_header->free=true;
                                }

                                //Update pointer to ID table if it changed
                                gc_update_id_table(fill_header,header,e);
                                if (e->code!=ERROR_NONE) return;

                                //Combine newly freed memory with next block if free
                                struct GC_Header *next_header=gc_next_header(fill_header,e);
                                if (e->code!=ERROR_NONE) return;
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

uint32_t gc_get_header_size(uint32_t id,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return 0;

    struct GC_Header *header=gc_get_header(id,e);
    if (e->code!=ERROR_NONE) return 0;
    
    return header->size;
}

uint32_t gc_get_data_size(uint32_t id,struct ErrorType *e)
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

        if (header->end==true)
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
        if (header->end==true) return;
        
        //Object information
        printf("%X: size: %d, free: %d",header,header->size,header->free);
        if (header->free==false)
            printf(", ID: %d, pid %d, locked %d",header->id,header->pid,header->lock_count);
        printf("\n");

        //Error if address in ID table incorrect
        if (header->free==false)
        {
            if (gc.id_table[header->id]!=header)
            {
                printf("ERROR: expected %X in id_table[%d] but found %X\n",header,header->id,gc.id_table[header->id]);
                e->code=GC_ERROR_BAD_HEADER_ID;
                return;
            }
        }

        //Advance to next object
        header=gc_next_header(header,e);
        if (e->code!=ERROR_NONE) return;
    }
}

void gc_swap_next(struct GC_Header *header,struct ErrorType *e)
{
    //Exit early if prior function set error
    if (e->code!=ERROR_NONE) return;

    //Neither object can be end object
    struct GC_Header *obj1=header;
    if (obj1->end==true)
    {
        e->code=GC_ERROR_SWAP_END;
        return;
    }
    struct GC_Header *obj2=gc_next_header(header,e);
    if (e->code!=ERROR_NONE) return;
    if (obj2->end==true)
    {
        e->code=GC_ERROR_SWAP_END;
        return;
    }

    //Neither object can be locked
    if (((obj1->free==false)&&(obj1->lock_count>0))||
        ((obj2->free==false)&&(obj2->lock_count>0)))
    {
        e->code=GC_ERROR_SWAP_LOCKED;
        return;
    }

    //Triple reverse algorithm
    uint32_t obj1_size=obj1->size;
    uint32_t obj2_size=obj2->size;
    bool obj1_free=obj1->free;
    bool obj2_free=obj2->free;
    uint32_t obj1_id=obj1->id;
    uint32_t obj2_id=obj2->id;
    
    //Access bytes of objects as uint32_t for speed
    union CopyAccess
    {
        struct GC_Header *header;
        uint32_t *u32;
    } copy_begin,copy_end;

    //Reverse first object
    copy_begin.header=obj1;
    copy_end.header=(struct GC_Header *)(((uintptr_t)obj1)+obj1_size-sizeof(uint32_t));

    printf("swap 1st obj %X, size %d, end %X\n",obj1,obj1_size,copy_end.header);

    if (obj1->free==true)
    {
        printf("swap 1st obj - free object header only\n"); 
        int debug_counter=0;

        //Free object - only reverse header
        while(((uintptr_t)copy_begin.header-(uintptr_t)obj1)<sizeof(struct GC_Header))
        {
            printf("- %d, %X (%X)\n",debug_counter,copy_begin.u32,*copy_begin.u32);
            debug_counter++;

            *copy_end.u32=*copy_begin.u32;
            copy_end.u32--;
            copy_begin.u32++;
        }
    }
    else
    {
        printf("swap 1st obj - reverse whole object\n"); 
        printf("- swapping ");

        //Reverse whole object
        while (copy_end.u32>copy_begin.u32)
        {
            printf("%X (%X) <> %X (%X), \n",*copy_begin.u32,copy_begin.u32,*copy_end.u32,copy_end.u32);

            uint32_t temp=*copy_end.u32;
            *copy_end.u32=*copy_begin.u32;
            *copy_begin.u32=temp;
            copy_end.u32--;
            copy_begin.u32++;
        }

        printf("\n");
    }

    //Reverse second object
    copy_begin.header=obj2;
    copy_end.header=(struct GC_Header *)(((uintptr_t)obj2)+obj2_size-sizeof(uint32_t));

    printf("swap 2nd obj %X, size %d, end %X\n",obj2,obj2_size,copy_end.header);

    if (obj2->free==true)
    {
        printf("swap 2nd obj - free object header only\n"); 
        int debug_counter=0;
        printf("- end %d\n",copy_begin.header->end);

        //Free object - only reverse header
        while(((uintptr_t)copy_begin.header-(uintptr_t)obj2)<sizeof(struct GC_Header))
        {
            printf("- %d, %X (%X)\n",debug_counter,copy_begin.u32,*copy_begin.u32);
            debug_counter++;

            *copy_end.u32=*copy_begin.u32;
            copy_end.u32--;
            copy_begin.u32++;
        }
    }
    else
    {
        printf("swap 2nd obj - reverse whole object\n"); 
        printf("- swapping ");

        //Reverse whole object
        while (copy_end.u32>copy_begin.u32)
        {
            printf("%X (%X) <> %X (%X), \n",*copy_begin.u32,copy_begin.u32,*copy_end.u32,copy_end.u32);

            uint32_t temp=*copy_end.u32;
            *copy_end.u32=*copy_begin.u32;
            *copy_begin.u32=temp;
            copy_end.u32--;
            copy_begin.u32++;
        }

        printf("\n");
    }


    //Reverse combined object
    //TODO: Optimization if one or both objects is free
    copy_begin.header=obj1;
    copy_end.header=(struct GC_Header *)(((uintptr_t)obj1)+obj1_size+obj2_size-sizeof(uint32_t));

    printf("swap combined obj %X, size %d, end %X\n",obj1,obj1_size+obj2_size,copy_end.header);
    printf("- swapping ");
    
    while (copy_end.u32>copy_begin.u32)
    {
        printf("%X (%X) <> %X (%X), \n",*copy_begin.u32,copy_begin.u32,*copy_end.u32,copy_end.u32);

        uint32_t temp=*copy_end.u32;
        *copy_end.u32=*copy_begin.u32;
        *copy_begin.u32=temp;
        copy_end.u32--;
        copy_begin.u32++;
    }

    printf("\n");
    
    printf("Done swapping\n");

    //Assign IDs
    struct GC_Header *new_obj1=gc_next_header(obj1,e);
    struct GC_Header *new_obj2=obj1;
    printf("1\n");
    if (e->code!=ERROR_NONE) return;
    gc_update_id_table(obj1,new_obj1,e);
    printf("2\n");
    gc_update_id_table(obj2,new_obj2,e);
    printf("3\n");
    if (e->code!=ERROR_NONE) return;

    if (obj1_free==false) gc.id_table[obj1_id]=new_obj1;
    if (obj2_free==false) gc.id_table[obj2_id]=new_obj2;
    
    printf("4\n");

    printf("Done assigning IDs\n");

    gc_debug(e);
}


