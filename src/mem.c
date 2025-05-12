#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "compatibility.h"
#include "debug.h"
#include "error.h"
#include "getkey.h"
#include "manager.h"
#include "mem.h"
#include "structs.h"

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

uint8_t *new_split_mem(uint8_t tab, uint8_t split, uint8_t *heap_ptr)
{
    struct HeapInfo *heap_info=(struct HeapInfo *)heap_ptr;
    //Size of new memory record being created (struct size excludes objects[] so uint32_t for size of objects[0])
    const uint32_t record_size=(int)(sizeof(struct HeapInfo)+sizeof(uint32_t));
    //next: linked list - distance to next tab/split pair
    heap_info->next=record_size;
    heap_info->tab=tab;
    heap_info->split=split;
    //objects[]: linked list - distance to next object or 0 for end of list
    heap_info->objects[0]=0;

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
void select_heap(int tab, int split)
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
            obj_end=(uint32_t *)(heap_ptr+*(uint32_t *)heap_ptr);
            obj_size=obj_end-obj_start;
        }
        heap_ptr+=*(uint32_t *)heap_ptr;
    }
    //First word past end of data. Note no ending 0!
    heap_end=(uint32_t *)heap_ptr;

    uint32_t *yram_ptr=(uint32_t *)yram;
    uint32_t copy_count;
    while (obj_end!=heap_end)
    {
        //Copy chunk of next object to buffer
        if ((uintptr_t)(heap_end-obj_end)<YRAM_SIZE/sizeof(uint32_t)) copy_count=heap_end-obj_end;
        else copy_count=YRAM_SIZE/sizeof(uint32_t);

        for (uint32_t i=0;i<copy_count;i++)
        {
            yram_ptr[i]=obj_end[i];
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
            obj_start[i]=yram_ptr[i];
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
        heap_ptr+=*(uint32_t *)heap_ptr;
    return heap_ptr;
}

//heap_ptr - address of split heap as returned by get_split_heap
uint8_t *add_object(size_t size,uint8_t *heap_ptr)
{
    if (size%sizeof(uint32_t))
    {
        //Object size must be aligned
        error_exit(ERROR_UNALIGNED_WRITE);
    }

    //Add space for address of next link in list of objects
    size+=sizeof(uint32_t);

    //Check if enough memory left
    if (size>heap_left()) return NULL;

    //Add size of object to total size of all objects for that tab/split pair
    *(uint32_t *)heap_ptr+=size;

    //Point past header data to beginning of object list
    heap_ptr+=sizeof(struct HeapInfo);

    //Skip over each object until end marked by 0
    while(*(uint32_t *)heap_ptr)
        heap_ptr+=*(uint32_t *)heap_ptr;

    //Change 0 marker for end of object list to size of new object
    *(uint32_t *)heap_ptr=size;

    //Add 0 marker to mark new end of object list
    *(uint32_t *)(heap_ptr+size)=0;

    //Return address of newly added object skipping uint32 holding its size
    return heap_ptr+sizeof(uint32_t);
}

//Base address function for object functions below
static uint8_t *object_base_address(int ID, uint8_t *heap_ptr)
{
    //Point past header data to beginning of object list
    heap_ptr+=sizeof(struct HeapInfo);

    //Skip over each object that comes before
    for (int i=0;i<ID;i++)
    {
        //Size of object to skip
        uint32_t obj_size=*(uint32_t *)heap_ptr;

        if (obj_size==0)
        {
            //Reached 0 marker at end unexpectedly so ID is wrong or memory is corrupted
            error_exit(ERROR_BAD_HEAP_ID);
        }

        //Skip object and point to next one
        heap_ptr+=obj_size;
    }

    //Return base address of object STARTING AT uint32 holding its size
    return heap_ptr;
}

uint8_t *object_address(int ID, uint8_t *heap_ptr)
{
    //Return base address of object SKIPPING uint32 holding its size
    return object_base_address(ID,heap_ptr)+sizeof(uint32_t);
}

size_t object_size(int ID, uint8_t *heap_ptr)
{
    return *(uint32_t *)object_base_address(ID,heap_ptr);
}

int expand_object(size_t size,int ID,uint8_t *heap_ptr)
{
    if (size%sizeof(uint32_t))
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

    //Memory range overlaps - memmove instead of memcpy
    uint8_t *object=object_base_address(ID,heap_ptr);
    uint8_t *src=object+object_size(ID,heap_ptr);
    memmove(src+size,src,size);
    heap_info->next+=size;
    *(uint32_t *)object+=size;
    
    return ERROR_NONE;
}

int reduce_object(size_t size,int ID, uint8_t *heap_ptr)
{
    if (size%sizeof(uint32_t))
    {
        //Object size must be aligned
        return ERROR_UNALIGNED_WRITE;
    }

    struct HeapInfo *heap_info=(struct HeapInfo *)heap_ptr;
    //Memory range overlaps - memmove instead of memcpy
    uint8_t *object=object_base_address(ID,heap_ptr);
    uint8_t *src=object+object_size(ID,heap_ptr);
    memmove(src-size,src,size);
    heap_info->next-=size;
    *(uint32_t *)object-=size;
    
    return ERROR_NONE;
}

