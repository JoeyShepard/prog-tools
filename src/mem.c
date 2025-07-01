#include <stdbool.h>
#include <stdint.h>
#include <string.h>

//TODO: need all these headers?
#include "compatibility.h"
#include "debug.h"
#include "error.h"
#include "getkey.h"
#include "logging.h"
#include "manager.h"
#include "macros.h"
#include "mem.h"

//TODO: remove
#include "text.h"

uint8_t *write_heap_i32(int32_t val,uint8_t *heap_ptr)
{
    memcpy(heap_ptr,&val,sizeof(int32_t));
    return heap_ptr+sizeof(int32_t);
}

uint8_t *write_heap_i16(int16_t val,uint8_t *heap_ptr)
{
    memcpy(heap_ptr,&val,sizeof(int16_t));
    return heap_ptr+sizeof(int16_t);
}

uint8_t *write_heap_i8(int8_t val,uint8_t *heap_ptr)
{
    *(int8_t *)heap_ptr=val;
    return heap_ptr+sizeof(int8_t);
}

uint8_t *write_heap_u32(uint32_t val,uint8_t *heap_ptr)
{
    memcpy(heap_ptr,&val,sizeof(uint32_t));
    return heap_ptr+sizeof(uint32_t);
}

uint8_t *write_heap_u16(uint16_t val,uint8_t *heap_ptr)
{
    memcpy(heap_ptr,&val,sizeof(uint16_t));
    return heap_ptr+sizeof(uint16_t);
}

uint8_t *write_heap_u8(uint8_t val,uint8_t *heap_ptr)
{
    *heap_ptr=val;
    return heap_ptr+sizeof(int8_t);
}

uint8_t *new_split_mem(uint8_t tab,uint8_t split,uint8_t *heap_ptr)
{
    struct HeapInfo *heap_info=(struct HeapInfo *)heap_ptr;
    //Size of new memory record being created - struct HeaderInfo with one object with its size member set to zero
    const uint32_t record_size=(int)(sizeof(struct HeapInfo)+sizeof(struct ObjectInfo));
    //size: linked list - distance to next tab/split pair
    heap_info->size=record_size;
    heap_info->tab=tab;
    heap_info->split=split;
    //objects[]: linked list - distance to next object or 0 for end of list
    ((struct ObjectInfo *)(heap_info->objects))->size=0;

    return heap_ptr+record_size;
}

void init_heap()
{
    //Write empty heap data for both splits of all 6 tabs
    uint8_t *heap_ptr=heap;
    for (int i=0;i<TAB_COUNT;i++)
    {
        for (int j=0;j<SPLIT_COUNT;j++)
        heap_ptr=new_split_mem(i,j,heap_ptr);
    }
}

//Move heap for selected tab/split to top so it can access free memory
void select_heap(int tab,int split)
{
    uint8_t *heap_ptr=heap; 
    uint32_t *obj_start;
    uint32_t *obj_end;
    uint32_t obj_size;
    uint32_t *heap_end;

    for (int i=0;i<TAB_COUNT*SPLIT_COUNT;i++)
    {
        struct HeapInfo *heap_info=(struct HeapInfo *)heap_ptr;
        if ((heap_info->tab==tab)&&(heap_info->split==split))
        {
            //Selected heap found - record start and address
            obj_start=(uint32_t *)heap_ptr;
            obj_end=(uint32_t *)(heap_ptr+((struct HeapInfo *)heap_ptr)->size);
            obj_size=obj_end-obj_start;
        }
        heap_ptr+=((struct HeapInfo *)heap_ptr)->size;
    }

    //First word past end of data. Note no ending 0!
    heap_end=(uint32_t *)heap_ptr;

    uint32_t *xram_ptr=(uint32_t *)xram;
    uint32_t copy_count;
    while (obj_end!=heap_end)
    {
        //Copy chunk of next object to buffer
        if ((uintptr_t)(heap_end-obj_end)<XRAM_SIZE/sizeof(uint32_t)) copy_count=heap_end-obj_end;
        else copy_count=XRAM_SIZE/sizeof(uint32_t);

        //TODO: memmove? this doesn't actually need to be fast

        for (uint32_t i=0;i<copy_count;i++)
        {
            xram_ptr[i]=obj_end[i];
        }
        obj_end+=copy_count;

        //Copy selected object up to take place of freed memory
        for (uint32_t i=0;i<obj_size;i++)
        {
            *(obj_end-i-1)=*(obj_end-i-copy_count-1);
        }

        //Copy next object in buffer to replace selected object
        for (uint32_t i=0;i<copy_count;i++)
        {
            obj_start[i]=xram_ptr[i];
        }
        obj_start+=copy_count;
    }
}

uint32_t heap_left()
{
    uint8_t *heap_ptr=get_split_heap();
    //TODO: struct HeapInfo
    heap_ptr+=*(uint32_t *)heap_ptr;
    return (uint32_t)(heap+HEAP_SIZE-heap_ptr);
}

uint32_t heap_used()
{
    return HEAP_SIZE-heap_left();
}

uint8_t *get_split_heap()
{
    uint8_t *heap_ptr=heap;
    for (int i=0;i<TAB_COUNT*SPLIT_COUNT-1;i++)
        heap_ptr+=((struct HeapInfo *)heap_ptr)->size;
    return heap_ptr;
}

//heap_ptr - address of split heap as returned by get_split_heap
uint8_t *add_object(size_t size,uint8_t *heap_ptr)
{
    if (size%ALIGNMENT)
    {
        //Object size must be aligned
        error_exit(ERROR_UNALIGNED_WRITE);
    }

    //Add space for address of next link in list of objects
    size+=fldsiz(ObjectInfo,size);

    //Check if enough memory left
    if (size>heap_left()) return NULL;

    //Add size of object to total size of all objects for that tab/split pair
    ((struct HeapInfo *)heap_ptr)->size+=size;

    //Point past header data to beginning of object list
    heap_ptr=((struct HeapInfo *)heap_ptr)->objects;

    //Skip over each object until end marked by size 0
    while(((struct ObjectInfo *)heap_ptr)->size)
        heap_ptr+=((struct ObjectInfo *)heap_ptr)->size;

    //Change 0 marker for end of object list to size of new object
    ((struct ObjectInfo *)heap_ptr)->size=size;

    //Add 0 marker to mark new end of object list
    ((struct ObjectInfo *)(heap_ptr+size))->size=0;

    //Return address of data field of newly created object
    return ((struct ObjectInfo *)heap_ptr)->data;
}

//Base address function for object functions below
struct ObjectInfo *object_address(int ID, uint8_t *heap_ptr)
{
    //Logging
    log_push(LOGGING_FORTH_OBJECT_ADDRESS,"object_address");
    log_text("heap_ptr: %p\n",heap_ptr);

    //Point past header data to beginning of object list
    heap_ptr=((struct HeapInfo *)heap_ptr)->objects;

    //Logging
    log_text("heap_ptr: %p (skipped Heap header)\n",heap_ptr);
    log_text("Searching for ID %d\n",ID);

    //Skip over each object that comes before
    for (int i=0;i<ID;i++)
    {

        //Size of object to skip
        uint32_t obj_size=((struct ObjectInfo *)heap_ptr)->size;

        //Logging
        log_text("ID %d:",i);
        log_text("Skipping %d bytes to next object\n",obj_size);

        if (obj_size==0)
        {
            //Logging
            log_pop();

            //Reached 0 marker at end unexpectedly so ID is wrong or memory is corrupted
            error_exit(ERROR_BAD_HEAP_ID);
        }

        //Skip object and point to next one
        heap_ptr+=obj_size;
    }

    //Logging
    log_pop();

    //Return base address of object STARTING AT uint32 holding its size
    return (struct ObjectInfo *)heap_ptr;
}

int expand_object(size_t size,int ID,uint8_t *heap_ptr)
{
    //Logging
    log_push(LOGGING_MEM_EXPAND_OBJECT,"expand_object");
    log_text("expanding ID %d by %d bytes\n",ID,size);

    if (size%ALIGNMENT)
    {
        //Object size must be aligned
        return ERROR_UNALIGNED_WRITE;
    }

    if (heap_left()<size)
    {
        //Out of heap memory
        return ERROR_OUT_OF_MEMORY;
    }
    
    struct HeapInfo *heap_info=(struct HeapInfo *)heap_ptr;
    struct ObjectInfo *object_info=object_address(ID,heap_ptr);
    uint8_t *object=(uint8_t *)object_info;
    uint8_t *src=object+object_info->size;
    uint8_t *dest=src+size;
    uint32_t copy_size=heap_info->size-(object-heap_ptr);
    //Memory range overlaps - memmove instead of memcpy
    memmove(dest,src,copy_size);

    //Update linked lists
    heap_info->size+=size;
    object_info->size+=size;
    
    //Logging
    log_pop();

    return ERROR_NONE;
}

int reduce_object(size_t size,int ID,uint8_t *heap_ptr)
{
    if (size%ALIGNMENT)
    {
        //Object size must be aligned
        return ERROR_UNALIGNED_WRITE;
    }

    struct HeapInfo *heap_info=(struct HeapInfo *)heap_ptr;
    struct ObjectInfo *object_info=object_address(ID,heap_ptr);
    uint8_t *object=(uint8_t *)object_info;
    uint8_t *src=object+object_info->size;
    //Memory range overlaps - memmove instead of memcpy
    memmove(src-size,src,size);

    //Update linked lists
    heap_info->size-=size;
    object_info->size-=size;
    
    return ERROR_NONE;
}

//Call expand_object or reduce_object as necessary
int resize_object(size_t new_size,int ID,uint8_t *heap_ptr)
{
    if (new_size%ALIGNMENT)
    {
        //Object size must be aligned
        return ERROR_UNALIGNED_WRITE;
    }

    //Check existing size 
    size_t data_size=object_data_size(object_address(ID,heap_ptr));
    if (data_size==new_size)
    {
        //No change in size - nothing to do
        return ERROR_NONE;
    }
    else if (data_size<new_size)
    {
        return expand_object(new_size-data_size,ID,heap_ptr);
    }
    else if (data_size>new_size)
    {
        return reduce_object(data_size-new_size,ID,heap_ptr);
    }

    //Should not reach here - silence error
    return ERROR_NONE;
}

//Size of object EXCLUDING header - data only
size_t object_data_size(struct ObjectInfo *object)
{
    return object->size-fldsiz(ObjectInfo,size);
}

