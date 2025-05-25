#ifndef __GUARD_PROG_TOOLS_FORTH_ACTIONS
    #define __GUARD_PROG_TOOLS_FORTH_ACTIONS

    #include <stdint.h>

    #include "forth-engine.h"
    #include "forth-process.h"

    int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    int action_semicolon(struct ForthEngine *engine,struct ForthCompileInfo *compile);
    int32_t action_char_common(const char *source,uint32_t *start,int32_t *index,struct ForthCompileInfo *compile);
    void action_paren(const char *source,uint32_t *start);
    void action_words(struct ForthEngine *engine,struct ForthWordHeaderInfo *word_headers);
    int action_tick_common(const char *source,uint32_t *start,uint32_t *index,struct ForthCompileInfo *compile);


#endif
