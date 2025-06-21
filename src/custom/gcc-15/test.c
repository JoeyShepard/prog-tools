/*
struct ForthEngine
{
    void (**address)(struct ForthEngine *engine);
    int sp;
};

void foo(struct ForthEngine *engine)
{
    __attribute__((musttail)) return (*engine->address)(engine);
}
*/

#include <stdint.h>
int32_t asm_test()
{
    return 43;
}

