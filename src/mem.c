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
    //HEAP_NEXT: Linked list - distance to next tab/split pair
    heap_ptr=write_heap_u32(HEAP_DATA_SIZE,heap_ptr);
    //HEAP_TAB
    heap_ptr=write_heap_u8(tab,heap_ptr);
    //HEAP_SPLIT
    heap_ptr=write_heap_u8(split,heap_ptr);
    //Alignment
    heap_ptr+=2;
    //HEAP_OBJECTS: Linked list - distance to next object or 0 for end of list
    heap_ptr=write_heap_u32(0,heap_ptr);

    return heap_ptr;
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

    //Debug
    /*
    debug_heap(0);
    select_heap(2,1);
    debug_heap(0);
    */

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
        if ((heap_ptr[HEAP_TAB]==tab)&&(heap_ptr[HEAP_SPLIT]==split))
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

    uint32_t *xram_ptr=(uint32_t *)xram;
    uint32_t copy_count;
    while (obj_end!=heap_end)
    {
        //Copy chunk of next object to buffer
        if ((heap_end-obj_end)<XRAM_SIZE/sizeof(uint32_t)) copy_count=heap_end-obj_end;
        else copy_count=XRAM_SIZE/sizeof(uint32_t);

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

    //Add space for address of next link
    size+=sizeof(uint32_t);

    *(uint32_t *)heap_ptr+=size;
    heap_ptr+=HEAP_OBJECTS;
    while(*(uint32_t *)heap_ptr)
        heap_ptr+=*(uint32_t *)heap_ptr;
    *(uint32_t *)heap_ptr=size;
    *(uint32_t *)(heap_ptr+size)=0;
    return heap_ptr+sizeof(uint32_t);
}

