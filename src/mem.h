#ifndef __GUARD_PROG_TOOLS_MEM
    #define __GUARD_PROG_TOOLS_MEM

    #define HEAP_NEXT           0       //4 bytes
    #define HEAP_TAB            4       //1 byte
    #define HEAP_SPLIT          5       //1 byte
    //Alignment                 6-7     //2 bytes
    #define HEAP_OBJECTS        8       //4 bytes

    //Size of empty heap data at initialization
    #define HEAP_DATA_SIZE      12

    uint8_t *write_heap_i32(int32_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_i16(int16_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_i8(int8_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_u32(uint32_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_u16(uint16_t val,uint8_t *heap_ptr);
    uint8_t *write_heap_u8(uint8_t val,uint8_t *heap_ptr);
    uint8_t *new_split_mem(uint8_t tab, uint8_t split, uint8_t *heap_ptr);
    void init_heap();
    void select_heap(int tab, int split);
    uint32_t heap_left();
    uint32_t heap_used();
    uint8_t *get_split_heap();
    uint8_t *add_object(size_t size,uint8_t *heap_ptr);
    uint8_t *object_address(int ID, uint8_t *heap_ptr);

#endif
