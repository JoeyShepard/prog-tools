#include "forth-engine.h"
#include "forth-jit.h"
#include "logging.h"

int forth_jit(struct ForthEngine *engine)
{
    //compile.word_names=

    //Logging
    log_push(LOGGING_FORTH_JIT,"forth_jit");

    //Logging
    log_pop();

    int FORTH_ERROR_NONE;
}

int forth_jit_free(struct ForthEngine *engine)
{
    //Logging
    log_push(LOGGING_FORTH_JIT_FREE,"forth_jit_free");

    //Logging
    log_pop();

    int FORTH_ERROR_NONE;
}

