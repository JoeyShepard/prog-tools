#ifndef __GUARD_PROG_TOOLS_FORTH_MEM
    #define __GUARD_PROG_TOOLS_FORTH_MEM

    #include "forth.h"

    typedef union GenericUnion
    {
        forth_prim_t prim;
        int32_t i32;
        int16_t i16;
        int8_t i8;
        uint32_t u32;
        uint16_t u16;
        uint8_t u8;
    } generic_t;

    int expand_generic(size_t size,size_t mem_size,int ID,uint32_t *bytes_left,struct ForthCompileInfo *compile);
    int write_generic(generic_t value,size_t size,unsigned char *data,uint32_t *index,size_t mem_size,
                        int ID,uint32_t *bytes_left,struct ForthCompileInfo *compile);

#endif
