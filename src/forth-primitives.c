#include <string.h>

#include "compatibility.h"
#include "forth-primitives.h"

const struct ForthPrimitive forth_primitives[]=
{
    //Macro PRIMITIVE fills in both name and length
    PRIMITIVE("dup"),
    PRIMITIVE("swap"),
    PRIMITIVE("over"),
    PRIMITIVE("drop"),
    PRIMITIVE("rot"),
    PRIMITIVE("-rot")
};

//Can't determine length of array primitives in other files, so calculate here
const int forth_primitives_len=(int)(ARRAY_SIZE(forth_primitives));
