#include <stdbool.h>
#include <stdio.h>

#include "compatibility.h"
#include "debug.h"
#include "forth-primitives.h"
#include "getkey.h"
#include "macros.h"
#include "manager.h"
#include "mem.h"
#include "text.h"

//Debug functions common to CG50 and PC
void debug_global(const char *msg,void *data,bool count)
{
    static struct Point pos={0,0};
    static int counter=1;
    static int color_index=0;

    bool arg=false;
    char text[TEXT_INT32_SIZE];
    int colors[]={C_RGB(31,24,24),C_RGB(24,31,24),C_RGB(24,24,31),C_RGB(31,31,24),C_RGB(31,24,31),C_RGB(24,31,31)};
    while(*msg)
    {
        bool print=true;
        if (arg==true)
        {
            switch (*msg)
            {
                case 'd':
                    text_int32(*(int32_t *)data,text);
                    break;
                case 'u':
                    text_uint32(*(uint32_t *)data,text);
                    break;
                case 'X':
                    text_hex32(*(uint32_t *)data,text);
                    break;
                case 'p':
                    uintptr_t ptr=(uintptr_t)data;
                    if (sizeof(ptr)>32)
                    {
                        text_hex32(ptr>>32,text);
                        pos=draw_text(text,pos,COL_BLACK,colors[color_index],false,FONT_5x8);
                    }
                    text_hex32(ptr,text);

                    //printf("%lX\n",ptr);

                    break;
                default:
                    print=false;
            }
            
            arg=false;
        }
        else
        {
            if (*msg=='%') 
            {
                arg=true;
                print=false;
            }
            else
            {
                text[0]=*msg;
                text[1]=0;
            }
        }

        if (print==true)
            pos=draw_text(text,pos,COL_BLACK,colors[color_index],false,FONT_5x8);
        
        msg++;
    }

    if (count==true)
    {
        pos=draw_text("(",pos,COL_BLACK,colors[color_index],false,FONT_5x8);
        text_uint32(counter,text);
        pos=draw_text(text,pos,COL_BLACK,colors[color_index],false,FONT_5x8);
        pos=draw_text(")",pos,COL_BLACK,colors[color_index],false,FONT_5x8);
        counter++;
    }
    
    pos.x=color_index*16;
    pos.y+=10;
    if (pos.y>200)
    {
        pos.y=0;
        color_index++;
        color_index=color_index%ARRAY_LEN(colors);
    }
    dupdate();
    getkey_wrapper(true);
}

#ifdef CG50

    void debug_heap(UNUSED(int level))
    {
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
        const int col_count=8;
        char chars[col_count];
        int char_index=0;
        chars[0]=0;

        for (uint32_t i=0;i<count;i++)
        {
            if (i%8==0) printf("%p: ",(mem+i));
            uint8_t value=*(uint8_t *)(mem+i);
            printf("%.02X ",value);
            chars[char_index]=value;
            if ((i%col_count==(col_count-1))||(i==count-1))
            {
                printf(" | ");
                for (int j=0;j<char_index;j++)
                {
                    if ((chars[j]>=32)&&(chars[j]<=126)) printf("%c",chars[j]);
                    else printf(".");
                    if (j!=char_index-1) printf(".");
                }
                printf("\n");
                char_index=0;
            }
            else char_index++;
        }
        printf("prim_hidden_push:      %p\n",&prim_hidden_push);
        printf("prim_hidden_secondary: %p\n",&prim_hidden_secondary);
        printf("prim_hidden_done:      %p\n",&prim_hidden_done);
    }

    void debug_words(struct ForthCompileInfo *compile)
    {
        printf("Debug words\n");
        struct ForthWordHeader *secondary=compile->words->header;
        while (secondary->last==false)
        {
            printf("- target: %p - %s. base: %p\n",secondary->address,secondary->name,secondary);
            secondary++;
        }
    }

    void debug_primitive(void(**func)(struct ForthEngine *),struct ForthCompileInfo *compile)
    {
        printf("debug_primitive (%p): ",*func);
        bool found=false;
        for (int i=0;i<forth_primitives_len;i++)
        {
            if (*func==forth_primitives[i].body)
            {
                printf("%s",forth_primitives[i].name);
                found=true;
                break;
            }
        }

        if (found==false)
        {
            if (*func==prim_hidden_push) printf("prim_hidden_push");
            else if (*func==prim_hidden_secondary)
            {
                printf("prim_hidden_secondary\n");
                uint32_t index=*(uint32_t *)(func+1);
                printf("- index: %d\n",index);
                printf("- %s",compile->words->header[index].name);
            }
            else if (*func==prim_hidden_done) printf("prim_hidden_done");
            else printf("not found!"); 
        }
        
        printf("\n");
    }

#endif
