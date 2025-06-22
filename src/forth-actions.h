#ifndef __GUARD_PROG_TOOLS_FORTH_ACTIONS
    #define __GUARD_PROG_TOOLS_FORTH_ACTIONS

    #include <stdint.h>

    #include "forth-engine.h"
    #include "forth-process.h"

    int action_again(struct ForthCompileInfo *compile);
    int action_begin(struct ForthCompileInfo *compile);
    int action_char_common(const char *source,uint32_t *start,int32_t *index,struct ForthCompileInfo *compile);
    int action_colon(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    void action_comment(const char *source,uint32_t *start);
    int action_constant(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    int action_create(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    int action_do(struct ForthCompileInfo *compile);
    int action_dot_quote_interpret(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    int action_else(struct ForthCompileInfo *compile);
    int action_execute(struct ForthEngine *engine,int *word_type,struct ForthCompileInfo *compile);
    int action_i(struct ForthCompileInfo *compile);
    int action_if(struct ForthCompileInfo *compile);
    int action_j(struct ForthCompileInfo *compile);
    int action_loop(struct ForthCompileInfo *compile);
    void action_paren(const char *source,uint32_t *start);
    int action_plus_loop(struct ForthCompileInfo *compile);
    void action_primitives(struct ForthEngine *engine,bool *first_word,int *line_characters,bool redraw);
    int action_quote_common(struct ForthEngine *engine,const char *source,uint32_t *start,bool escape,bool definition,
                                struct ForthCompileInfo *compile);
    int action_repeat(struct ForthCompileInfo *compile);
    void action_secondaries(struct ForthEngine *engine,bool *first_word,int *line_characters,bool defined,bool redraw,
                            struct ForthCompileInfo *compile);
    int action_semicolon(struct ForthEngine *engine,struct ForthCompileInfo *compile);
    int action_then(struct ForthCompileInfo *compile);
    int action_tick_common(const char *source,uint32_t *start,uint32_t *index,struct ForthCompileInfo *compile);
    int action_until(struct ForthCompileInfo *compile);
    int action_variable(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);
    int action_while(struct ForthCompileInfo *compile);
    int action_wordsize(struct ForthEngine *engine,const char *source,uint32_t *start,struct ForthCompileInfo *compile);

#endif
