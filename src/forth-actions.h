#ifndef __GUARD_PROG_TOOLS_FORTH_ACTIONS
    #define __GUARD_PROG_TOOLS_FORTH_ACTIONS

    #include <stdint.h>

    #include "forth-engine.h"
    #include "forth-process.h"

    int action_char_common(const char *source,uint32_t *start,int32_t *index,struct ForthCompileInfo *compile);
    int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    int action_constant(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    int action_create(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    void action_paren(const char *source,uint32_t *start);
    void action_primitives(struct ForthEngine *engine,bool *first_word,int *line_characters,bool redraw);
    void action_secondaries(struct ForthEngine *engine,bool *first_word,int *line_characters,bool defined,bool redraw,
                            struct ForthCompileInfo *compile);
    int action_semicolon(struct ForthEngine *engine,struct ForthCompileInfo *compile);
    int action_tick_common(const char *source,uint32_t *start,uint32_t *index,struct ForthCompileInfo *compile);
    int action_variable(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    void action_words(struct ForthEngine *engine,struct ForthCompileInfo *compile);

#endif
