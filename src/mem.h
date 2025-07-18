#ifndef __GUARD_PROG_TOOLS_MEM
    #define __GUARD_PROG_TOOLS_MEM

    #include <stdalign.h>
    #include <stddef.h>

    struct HeapInfo
    {
        uint32_t size;
        uint8_t tab;
        uint8_t split;
        //Flexible Array Member
        alignas(uint32_t) uint8_t objects[];
    };

    struct ObjectInfo
    {
        uint32_t size;
        //Flexible Array Member
        uint8_t data[];
    };

    uint8_t *write_heap_i32(int32_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_i16(int16_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_i8(int8_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_u32(uint32_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_u16(uint16_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_u8(uint8_t val,uint8_t *heap_ptr);
    uint8_t *new_split_mem(uint8_t tab,uint8_t split,uint8_t *heap_ptr);
    void init_heap();
    void select_heap(int tab,int split);
    uint32_t heap_left();
    uint32_t heap_used();
    uint8_t *get_split_heap();
    uint8_t *add_object(size_t size,uint8_t *heap_ptr);
    struct ObjectInfo *object_address(int ID, uint8_t *heap_ptr);
    int expand_object(size_t size,int ID,uint8_t *heap_ptr);
    int reduce_object(size_t size,int ID,uint8_t *heap_ptr);
    int resize_object(size_t new_size,int ID,uint8_t *heap_ptr);
    size_t object_data_size(struct ObjectInfo *object);

#endif
