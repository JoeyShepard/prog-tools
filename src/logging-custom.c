#include "forth.h"
#include "forth-engine.h"
#include "logging.h"
#include "logging-custom.h"

#ifdef CG50
    //Compiling for calculator - header should remove all log functions on calculator

#else
    void log_bytes(void *ptr,int bytes)
    {
        for (int i=0;i<bytes;i++)
        {
            log_text_raw("%.02X ",*(uint8_t *)(ptr+i));
        }
    }

    void log_primitive(void(**func)(struct ForthEngine *),struct ForthWordHeader *word_headers)
    {
        for (int i=0;i<forth_primitives_len;i++)
        {
            if (*func==forth_primitives[i].body)
            {
                log_text("%s (%p)\n",forth_primitives[i].name,*func);
                return;
            }
        }

        if (*func==prim_hidden_done) log_text("prim_hidden_done (%p)\n",*func);
        else if (*func==prim_hidden_do) log_text("prim_hidden_do (%p)\n",*func);
        else if (*func==prim_hidden_dot_quote) log_text("prim_hidden_dot_quote (%p)\n",*func);
        else if (*func==prim_hidden_i) log_text("prim_hidden_i (%p)\n",*func);
        else if (*func==prim_hidden_if) log_text("prim_hidden_if (%p)\n",*func);
        else if (*func==prim_hidden_j) log_text("prim_hidden_j (%p)\n",*func);
        else if (*func==prim_hidden_jump) log_text("prim_hidden_jump (%p)\n",*func);
        else if (*func==prim_hidden_loop) log_text("prim_hidden_loop (%p)\n",*func);
        else if (*func==prim_hidden_push) log_text("prim_hidden_push (%p)\n",*func);
        else if (*func==prim_hidden_s_quote) log_text("prim_hidden_s_quote (%p)\n",*func);
        else if (*func==prim_hidden_secondary)
        {
            log_text("prim_hidden_secondary (%p)\n",*func);
            uint32_t index=*(uint32_t *)(func+1);
            log_text("  index: %d\n",index);
            log_text("  %s\n",word_headers[index].name);
            log_text("  offset: %d\n",word_headers[index].offset);
            log_text("  address: %p\n",word_headers[index].address);
        }
        else log_text("not found!\n");
    }
    

#endif

