#include <strings.h>

#include "forth.h"
#include "forth-check.h"
#include "forth-engine.h"
#include "forth-primitives.h"
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

    void log_primitive(forth_prim_t *func,struct ForthWordHeader *word_headers)
    {
        for (int i=0;i<forth_primitives_len;i++)
        {
            if (*func==forth_primitives[i].body)
            {
                if (strcasecmp(forth_primitives[i].name,"")!=0)
                {
                    log_text("%s (%p)\n",forth_primitives[i].name,*func);
                    return;
                }
            }
        }

        if (*func==prim_hidden_do) log_text("%p: prim_hidden_do\n",*func);
        else if (*func==prim_hidden_done) log_text("%p: prim_hidden_done\n",*func);
        else if (*func==prim_hidden_dot_quote) log_text("%prim_hidden_dot_quote\n",*func);
        else if (*func==prim_hidden_if) log_text("%p: prim_hidden_if\n",*func);
        else if (*func==prim_hidden_jit) log_text("%p: prim_hidden_jit\n",*func);
        else if (*func==prim_hidden_jump) log_text("%p: prim_hidden_jump\n",*func);
        else if (*func==prim_hidden_leave) log_text("%p: prim_hidden_leave\n",*func);
        else if (*func==prim_hidden_loop) log_text("%p: prim_hidden_loop\n",*func);
        else if (*func==prim_hidden_plus_loop) log_text("%p: prim_hidden_plus_loop\n",*func);
        else if (*func==prim_hidden_push) log_text("%p: prim_hidden_push\n",*func);
        else if (*func==prim_hidden_push_check) log_text("%p: prim_hidden_push_check\n",*func);
        else if (*func==prim_hidden_s_quote) log_text("%p: prim_hidden_s_quote\n",*func);
        else if (*func==prim_hidden_secondary)
        {
            log_text("%p: prim_hidden_secondary\n",*func);
            uint32_t index=*(uint32_t *)(func+1);
            log_text("  index: %d\n",index);
            log_text("  name: %s\n",word_headers[index].name);
            log_text("  offset: %d\n",word_headers[index].offset);
            log_text("  address: %p\n",word_headers[index].address);
        }

        //Locals
        else if (*func==prim_locals_copy) log_text("%p: prim_locals_copy\n",*func);
        else if (*func==prim_locals_zero) log_text("%p: prim_locals_zero\n",*func);
        else if (*func==prim_local_fetch0) log_text("%p: prim_local_fetch0\n",*func);
        else if (*func==prim_local_fetch1) log_text("%p: prim_local_fetch1\n",*func);
        else if (*func==prim_local_fetch2) log_text("%p: prim_local_fetch2\n",*func);
        else if (*func==prim_local_fetch3) log_text("%p: prim_local_fetch3\n",*func);
        else if (*func==prim_local_fetch4) log_text("%p: prim_local_fetch4\n",*func);
        else if (*func==prim_local_fetch5) log_text("%p: prim_local_fetch5\n",*func);
        else if (*func==prim_local_fetch6) log_text("%p: prim_local_fetch6\n",*func);
        else if (*func==prim_local_fetch7) log_text("%p: prim_local_fetch7\n",*func);
        else if (*func==prim_local_fetch8) log_text("%p: prim_local_fetch8\n",*func);
        else if (*func==prim_local_fetch9) log_text("%p: prim_local_fetch9\n",*func);
        else if (*func==prim_local_fetch10) log_text("%p: prim_local_fetch10\n",*func);
        else if (*func==prim_local_fetch11) log_text("%p: prim_local_fetch11\n",*func);
        else if (*func==prim_local_fetch12) log_text("%p: prim_local_fetch12\n",*func);
        else if (*func==prim_local_fetch13) log_text("%p: prim_local_fetch13\n",*func);
        else if (*func==prim_local_fetch14) log_text("%p: prim_local_fetch14\n",*func);
        else if (*func==prim_local_fetch15) log_text("%p: prim_local_fetch15\n",*func);
        else if (*func==prim_local_fetch16) log_text("%p: prim_local_fetch16\n",*func);
        else if (*func==prim_local_fetch17) log_text("%p: prim_local_fetch17\n",*func);
        else if (*func==prim_local_fetch18) log_text("%p: prim_local_fetch18\n",*func);
        else if (*func==prim_local_fetch19) log_text("%p: prim_local_fetch19\n",*func);
        else if (*func==prim_local_fetch20) log_text("%p: prim_local_fetch20\n",*func);
        else if (*func==prim_local_fetch21) log_text("%p: prim_local_fetch21\n",*func);
        else if (*func==prim_local_fetch22) log_text("%p: prim_local_fetch22\n",*func);
        else if (*func==prim_local_fetch23) log_text("%p: prim_local_fetch23\n",*func);
        else if (*func==prim_local_fetch24) log_text("%p: prim_local_fetch24\n",*func);
        else if (*func==prim_local_fetch25) log_text("%p: prim_local_fetch25\n",*func);
        else if (*func==prim_local_fetch26) log_text("%p: prim_local_fetch26\n",*func);
        else if (*func==prim_local_fetch27) log_text("%p: prim_local_fetch27\n",*func);
        else if (*func==prim_local_fetch28) log_text("%p: prim_local_fetch28\n",*func);
        else if (*func==prim_local_fetch29) log_text("%p: prim_local_fetch29\n",*func);
        else if (*func==prim_local_fetch30) log_text("%p: prim_local_fetch30\n",*func);
        else if (*func==prim_local_fetch31) log_text("%p: prim_local_fetch31\n",*func);
        else if (*func==prim_local_store0) log_text("%p: prim_local_store0\n",*func);
        else if (*func==prim_local_store1) log_text("%p: prim_local_store1\n",*func);
        else if (*func==prim_local_store2) log_text("%p: prim_local_store2\n",*func);
        else if (*func==prim_local_store3) log_text("%p: prim_local_store3\n",*func);
        else if (*func==prim_local_store4) log_text("%p: prim_local_store4\n",*func);
        else if (*func==prim_local_store5) log_text("%p: prim_local_store5\n",*func);
        else if (*func==prim_local_store6) log_text("%p: prim_local_store6\n",*func);
        else if (*func==prim_local_store7) log_text("%p: prim_local_store7\n",*func);
        else if (*func==prim_local_store8) log_text("%p: prim_local_store8\n",*func);
        else if (*func==prim_local_store9) log_text("%p: prim_local_store9\n",*func);
        else if (*func==prim_local_store10) log_text("%p: prim_local_store10\n",*func);
        else if (*func==prim_local_store11) log_text("%p: prim_local_store11\n",*func);
        else if (*func==prim_local_store12) log_text("%p: prim_local_store12\n",*func);
        else if (*func==prim_local_store13) log_text("%p: prim_local_store13\n",*func);
        else if (*func==prim_local_store14) log_text("%p: prim_local_store14\n",*func);
        else if (*func==prim_local_store15) log_text("%p: prim_local_store15\n",*func);
        else if (*func==prim_local_store16) log_text("%p: prim_local_store16\n",*func);
        else if (*func==prim_local_store17) log_text("%p: prim_local_store17\n",*func);
        else if (*func==prim_local_store18) log_text("%p: prim_local_store18\n",*func);
        else if (*func==prim_local_store19) log_text("%p: prim_local_store19\n",*func);
        else if (*func==prim_local_store20) log_text("%p: prim_local_store20\n",*func);
        else if (*func==prim_local_store21) log_text("%p: prim_local_store21\n",*func);
        else if (*func==prim_local_store22) log_text("%p: prim_local_store22\n",*func);
        else if (*func==prim_local_store23) log_text("%p: prim_local_store23\n",*func);
        else if (*func==prim_local_store24) log_text("%p: prim_local_store24\n",*func);
        else if (*func==prim_local_store25) log_text("%p: prim_local_store25\n",*func);
        else if (*func==prim_local_store26) log_text("%p: prim_local_store26\n",*func);
        else if (*func==prim_local_store27) log_text("%p: prim_local_store27\n",*func);
        else if (*func==prim_local_store28) log_text("%p: prim_local_store28\n",*func);
        else if (*func==prim_local_store29) log_text("%p: prim_local_store29\n",*func);
        else if (*func==prim_local_store30) log_text("%p: prim_local_store30\n",*func);
        else if (*func==prim_local_store31) log_text("%p: prim_local_store31\n",*func);

        //Stack check
        else if (*func==prim_check_0_0) log_text("%p: prim_check_0_0\n",*func);
        else if (*func==prim_check_0_1) log_text("%p: prim_check_0_1\n",*func);
        else if (*func==prim_check_0_2) log_text("%p: prim_check_0_2\n",*func);
        else if (*func==prim_check_0_3) log_text("%p: prim_check_0_3\n",*func);
        else if (*func==prim_check_0_4) log_text("%p: prim_check_0_4\n",*func);
        else if (*func==prim_check_0_5) log_text("%p: prim_check_0_5\n",*func);
        else if (*func==prim_check_0_6) log_text("%p: prim_check_0_6\n",*func);
        else if (*func==prim_check_0_7) log_text("%p: prim_check_0_7\n",*func);
        else if (*func==prim_check_1_0) log_text("%p: prim_check_1_0\n",*func);
        else if (*func==prim_check_1_1) log_text("%p: prim_check_1_1\n",*func);
        else if (*func==prim_check_1_2) log_text("%p: prim_check_1_2\n",*func);
        else if (*func==prim_check_1_3) log_text("%p: prim_check_1_3\n",*func);
        else if (*func==prim_check_1_4) log_text("%p: prim_check_1_4\n",*func);
        else if (*func==prim_check_1_5) log_text("%p: prim_check_1_5\n",*func);
        else if (*func==prim_check_1_6) log_text("%p: prim_check_1_6\n",*func);
        else if (*func==prim_check_1_7) log_text("%p: prim_check_1_7\n",*func);
        else if (*func==prim_check_2_0) log_text("%p: prim_check_2_0\n",*func);
        else if (*func==prim_check_2_1) log_text("%p: prim_check_2_1\n",*func);
        else if (*func==prim_check_2_2) log_text("%p: prim_check_2_2\n",*func);
        else if (*func==prim_check_2_3) log_text("%p: prim_check_2_3\n",*func);
        else if (*func==prim_check_2_4) log_text("%p: prim_check_2_4\n",*func);
        else if (*func==prim_check_2_5) log_text("%p: prim_check_2_5\n",*func);
        else if (*func==prim_check_2_6) log_text("%p: prim_check_2_6\n",*func);
        else if (*func==prim_check_2_7) log_text("%p: prim_check_2_7\n",*func);
        else if (*func==prim_check_3_0) log_text("%p: prim_check_3_0\n",*func);
        else if (*func==prim_check_3_1) log_text("%p: prim_check_3_1\n",*func);
        else if (*func==prim_check_3_2) log_text("%p: prim_check_3_2\n",*func);
        else if (*func==prim_check_3_3) log_text("%p: prim_check_3_3\n",*func);
        else if (*func==prim_check_3_4) log_text("%p: prim_check_3_4\n",*func);
        else if (*func==prim_check_3_5) log_text("%p: prim_check_3_5\n",*func);
        else if (*func==prim_check_3_6) log_text("%p: prim_check_3_6\n",*func);
        else if (*func==prim_check_3_7) log_text("%p: prim_check_3_7\n",*func);
        else if (*func==prim_check_4_0) log_text("%p: prim_check_4_0\n",*func);
        else if (*func==prim_check_4_1) log_text("%p: prim_check_4_1\n",*func);
        else if (*func==prim_check_4_2) log_text("%p: prim_check_4_2\n",*func);
        else if (*func==prim_check_4_3) log_text("%p: prim_check_4_3\n",*func);
        else if (*func==prim_check_4_4) log_text("%p: prim_check_4_4\n",*func);
        else if (*func==prim_check_4_5) log_text("%p: prim_check_4_5\n",*func);
        else if (*func==prim_check_4_6) log_text("%p: prim_check_4_6\n",*func);
        else if (*func==prim_check_4_7) log_text("%p: prim_check_4_7\n",*func);
        else if (*func==prim_check_5_0) log_text("%p: prim_check_5_0\n",*func);
        else if (*func==prim_check_5_1) log_text("%p: prim_check_5_1\n",*func);
        else if (*func==prim_check_5_2) log_text("%p: prim_check_5_2\n",*func);
        else if (*func==prim_check_5_3) log_text("%p: prim_check_5_3\n",*func);
        else if (*func==prim_check_5_4) log_text("%p: prim_check_5_4\n",*func);
        else if (*func==prim_check_5_5) log_text("%p: prim_check_5_5\n",*func);
        else if (*func==prim_check_5_6) log_text("%p: prim_check_5_6\n",*func);
        else if (*func==prim_check_5_7) log_text("%p: prim_check_5_7\n",*func);
        else if (*func==prim_check_6_0) log_text("%p: prim_check_6_0\n",*func);
        else if (*func==prim_check_6_1) log_text("%p: prim_check_6_1\n",*func);
        else if (*func==prim_check_6_2) log_text("%p: prim_check_6_2\n",*func);
        else if (*func==prim_check_6_3) log_text("%p: prim_check_6_3\n",*func);
        else if (*func==prim_check_6_4) log_text("%p: prim_check_6_4\n",*func);
        else if (*func==prim_check_6_5) log_text("%p: prim_check_6_5\n",*func);
        else if (*func==prim_check_6_6) log_text("%p: prim_check_6_6\n",*func);
        else if (*func==prim_check_6_7) log_text("%p: prim_check_6_7\n",*func);
        else if (*func==prim_check_7_0) log_text("%p: prim_check_7_0\n",*func);
        else if (*func==prim_check_7_1) log_text("%p: prim_check_7_1\n",*func);
        else if (*func==prim_check_7_2) log_text("%p: prim_check_7_2\n",*func);
        else if (*func==prim_check_7_3) log_text("%p: prim_check_7_3\n",*func);
        else if (*func==prim_check_7_4) log_text("%p: prim_check_7_4\n",*func);
        else if (*func==prim_check_7_5) log_text("%p: prim_check_7_5\n",*func);
        else if (*func==prim_check_7_6) log_text("%p: prim_check_7_6\n",*func);
        else if (*func==prim_check_7_7) log_text("%p: prim_check_7_7\n",*func);

        //Not found
        else log_text("%p: not found!\n",*func);
    }
    

#endif

