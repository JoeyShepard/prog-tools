#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>

#define ARRAY_LEN(x) ((int)(sizeof(x)/sizeof(x[0])))


typedef int (*func_t)();
func_t *run;
char *buffer;

int f1() {return 12;}
int f2() {return 34;}
int exec()
{
    printf("exec - jumps to machine code\n");
    run++;
    func_t target=(func_t)run;
    printf("jumping to machine code at %p\n",target);
    return target(); 
}
int done() {exit(0);return 0;}


int main()
{
    buffer=mmap(NULL,1000,PROT_EXEC|PROT_WRITE|PROT_READ,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    printf("buffer memory starts at %p\n",buffer);

    int offset=0;

    //Write address of f1 to memory
    func_t temp=f1;
    memcpy(buffer+offset,&temp,sizeof(func_t));
    offset+=sizeof(func_t);

    //Write address of f2 to memory
    temp=f2;
    memcpy(buffer+offset,&temp,sizeof(func_t));
    offset+=sizeof(func_t);

    //Write address of exec to memory
    temp=exec;
    memcpy(buffer+offset,&temp,sizeof(func_t));
    offset+=sizeof(func_t);

    //Write machine to memory instead of pointer
    char code[]={   0x00, 0x0b, 0xe0, 0x38
                    };
    memcpy(buffer+offset,code,sizeof(code));
    offset+=sizeof(code);

    //Write address of done to memory
    temp=done;
    memcpy(buffer+offset,&temp,sizeof(func_t));
    offset+=sizeof(func_t);

    //Check results
    printf("Results:\n");
    for (int i=0;i<offset;i++)
    {
        if (i%8==0)
        {
            if (i!=0) printf("\n");
            printf("%p: ",buffer+i);
        }
        printf("%02X ",(unsigned char)buffer[i]);
    }
    printf("\n");

    //Loop through pointers in memory and call them
    run=(func_t *)buffer;
    while(1)
    {
        printf("executing %p stored at %p in buffer\n",*run,run);
        int result=(*run)();
        printf("%d\n",result);
        run++;
    }

    return 0;
}

