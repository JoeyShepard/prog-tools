//Useful C macros - not specific to one project


#ifndef __GUARD_USEFUL_C_MACROS
    #define __GUARD_USEFUL_C_MACROS

    //Calculate count of elements in array since sizeof(array) returns size in bytes not elements
    #define ARRAY_LEN(x) ((int)(sizeof(x)/sizeof(x[0])))

    //Mark function argument as unused to silence warnings from -Wunused-parameter
    #define UNUSED(x) __attribute__((unused)) x

    //Get size of struct member
    #define fldsiz(name, member) (sizeof(((struct name *)0)->member))
    
#endif

