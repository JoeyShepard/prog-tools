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
        alignas(uint32_t) unsigned char objects[];
    };

    struct ObjectInfo
    {
        uint32_t size;
        //Flexible Array Member
        unsigned char data[];
    };

    unsigned char *write_heap_i32(int32_t val,unsigned char *heap_ptr);
    unsigned char *write_heap_i16(int16_t val,unsigned char *heap_ptr);
    unsigned char *write_heap_i8(int8_t val,unsigned char *heap_ptr);
    unsigned char *write_heap_u32(uint32_t val,unsigned char *heap_ptr);
    unsigned char *write_heap_u16(uint16_t val,unsigned char *heap_ptr);
    unsigned char *write_heap_u8(uint8_t val,unsigned char *heap_ptr);
    unsigned char *new_split_mem(uint8_t tab,uint8_t split,unsigned char *heap_ptr);
    void init_heap();
    void select_heap(int tab,int split);
    uint32_t heap_left();
    uint32_t heap_used();
    unsigned char *get_split_heap();
    unsigned char *add_object(size_t size,unsigned char *heap_ptr);
    struct ObjectInfo *object_address(int ID, unsigned char *heap_ptr);
    int expand_object(size_t size,int ID,unsigned char *heap_ptr);
    int reduce_object(size_t size,int ID,unsigned char *heap_ptr);
    int resize_object(size_t new_size,int ID,unsigned char *heap_ptr);
    size_t object_data_size(struct ObjectInfo *object);

#endif
