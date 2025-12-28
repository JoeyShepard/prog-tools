//TODO: remove
#include <stdio.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "error.h"
#include "forth-mem.h"
#include "forth-process.h"
#include "logging.h"
#include "mem.h"

int expand_generic(size_t size,size_t mem_size,int ID,uint32_t *bytes_left,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_EXPAND_GENERIC,"expand_generic");

    if (*bytes_left<size)
    {
        //Logging
        log_text("expanding\n");

        //Not enough memory left - expand memory
        int result=expand_object(mem_size,ID,compile->heap_ptr);
        if (result!=ERROR_NONE)
        {
            //Error while allocating memory
            if (result==ERROR_OUT_OF_MEMORY)
                return FORTH_ERROR_OUT_OF_MEMORY;
            else
            {
                //Logging
                log_pop();

                //Some other type of allocation error like alignment
                return FORTH_ERROR_MEMORY_OTHER;
            }
        }

        //Update count of bytes left
        *bytes_left=*bytes_left+mem_size;

        //Update pointers since shifted by expand_object above
        update_compile_pointers(compile);
    }
    else
    {
        log_text("not expanding\n");
    }

    //Logging
    log_pop();

    return FORTH_ERROR_NONE;
}

int write_generic(generic_t value,size_t size,unsigned char *data,uint32_t *index,size_t mem_size,
                    int ID,uint32_t *bytes_left,struct ForthCompileInfo *compile)
{
    //Logging
    log_push(LOGGING_FORTH_WRITE_GENERIC,"write_generic");

    //Expand memory if necessary
    int result=expand_generic(size,mem_size,ID,bytes_left,compile);
    if (result!=FORTH_ERROR_NONE) return result;

    //Logging
    log_text("destination: %p\n",data+*index);
    
    //Write value to data - memcpy to avoid casting object pointer to function pointer
    memcpy(data+*index,&value,size);

    //Update counts 
    *index=*index+size;
    *bytes_left=*bytes_left-size;

    //Logging
    log_pop();
    
    return FORTH_ERROR_NONE;
}

