#include <stdio.h>

int f();    //C function
int g();    //Hand-written asm function
int h();    //C function converted to asm before compiling

int main()
{
    printf("%d\n",f() + g()+ h());
}
