#ifndef __GUARD_PROG_TOOLS_FORTH_ACTIONS
    #define __GUARD_PROG_TOOLS_FORTH_ACTIONS

    #include <stdint.h>

    #include "forth-engine.h"

    int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,const char **error_word,
                        uint32_t prior_word_len,struct ForthDefinitionsInfo *definitions,struct ForthWordIDsInfo **word_IDs,
                        struct ForthControlElement **control_stack,uint8_t *heap_ptr);
    int action_semicolon(struct ForthEngine *engine,struct ForthDefinitionsInfo *definitions,
                            struct ForthWordIDsInfo **word_IDs,struct ForthControlElement **control_stack,
                            uint8_t *heap_ptr);
    int32_t action_char_common(const char *source,uint32_t *start);
    void action_paren(const char *source,uint32_t *start);
    void action_words(struct ForthEngine *engine,struct ForthWordIDsInfo *word_IDs);
    int action_tick_common(const char *source,uint32_t *start,const char **error_word,uint32_t prior_word_len,
                            struct ForthWordIDsInfo *word_IDs,uint32_t *index);


#endif
