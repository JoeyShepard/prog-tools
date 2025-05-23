#include <stdbool.h>

#include "compatibility.h"
#include "debug.h"
#include "manager.h"
#include "mem.h"

#ifdef CG50

    void debug_heap(int level)
    {
        //Silence unused variable warning
        level=level;

        return;
    }

#else

    void debug_heap(int level)
    {
        //TODO: rewrite with struct HeapInfo
        /*
        uint8_t *ptr=heap;
      
        printf("Debugging heap:\n");
        for (int i=0;i<48;i++)
        {
            printf("%p:",ptr+i*4);
            for (int j=0;j<4;j++) printf(" %.2X",ptr[i*4+j]);
            printf("\n");
        }
        printf("\n");

        for (int i=0;i<SPLIT_COUNT*TAB_COUNT;i++)
        {
            printf("Heap object\n");
            uint32_t size=*(uint32_t *)ptr;
            printf("- Size:  %d\n",size);
            printf("- Tab:   %d\n",ptr[HEAP_TAB]);
            printf("- Split: %d\n",ptr[HEAP_SPLIT]);
            uint32_t *tab_ptr=(uint32_t *)(ptr+HEAP_OBJECTS);
            int counter=0;
            while (*tab_ptr)
            {
                if (level==0)
                {
                    counter++;
                }
                else if (level==1)
                {
                    printf("- Tab object. Size: %d \n",*tab_ptr);
                }
                tab_ptr+=(*tab_ptr)/sizeof(uint32_t);
            }
            if (level==0) printf("- Tab objects: %d\n",counter);
            printf("- End\n\n");
            ptr+=size;
        }
        printf("Heap end\n");
        */
    }

    void debug_dump(void *mem,uint32_t count)
    {
        for (uint32_t i=0;i<count;i++)
        {
            if (i%8==0) printf("%p: ",(mem+i));
            printf("%.02X ",*(uint8_t *)(mem+i));
            if (i%8==7) printf("\n");
        }
    }

#endif
