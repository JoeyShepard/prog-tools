#include <stdint.h>

#include "util.h"

uint32_t align4(uint32_t value)
{
    return value+((4-value%4)%4);
}
