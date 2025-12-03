#ifndef __GUARD_PROG_TOOLS_FORTH_ENGINE
    #define __GUARD_PROG_TOOLS_FORTH_ENGINE

    #include <stdint.h>

    //Subset of ForthEngine for testing
    struct ForthEngine
    {
        //Data stack
        uintptr_t stack_base;   //Store base as uintptr_t to do wrapping calculation on pointer
        int32_t *stack;         //Points to currently free stack element
        uint32_t stack_count;   //Count of elements allocated for stack

        //Locals stack
        int32_t *locals_base;
        int32_t *locals_stack;
        uint32_t locals_count;

        //Execution
        void (**address)(struct ForthEngine *engine);
    };

    struct ForthWordHeader
    {
        void (**address)(struct ForthEngine *engine);   //Target address within definitions memory
        uint32_t offset;                                //Offset into definitions of target address
        uint32_t definition_size;
        uint32_t name_offset;
        uint32_t name_len;
        char *name;
        uint16_t ID;                        //ID assigned to each user-defined word
        uint16_t locals_count;              //Count of local variables used
        uint8_t type;                       //User-defined word, variable, constant, etc
        bool last;                          //Whether this header is empty header marking end of list
        bool done;                          //Whether word is done being processed. Used to rewind if error in word.
    };

#endif
