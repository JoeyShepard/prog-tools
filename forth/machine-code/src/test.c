#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>

#include "forth-engine.h"
#include "forth-locals.h"
#include "forth-optimize.h"
#include "forth-primitives.h"
#include "logging.h"
#include "macros.h"

#define DATA_SIZE 4096
#define OPT_SIZE 4096

//Test cases
struct TestInfo
{
    const char *title;
    const char *test;
};

const struct TestInfo tests[]={
    {"foo?","x 5 + x 2 + *"},
    {"bar?","1 2 SWAP DROP x to Y z"},
    };

struct FuncInfo
{
    const char *name;
    void (*body)(struct ForthEngine *engine);
};

const struct FuncInfo functions[]=
{
    {"!",prim_body_store},
    {"C!",prim_body_c_store},
    {"W!",prim_body_w_store},
    {"*",prim_body_star},
    {"*/",prim_body_star_slash},
    {"*/MOD",prim_body_star_slash_mod},
    {"+",prim_body_plus},
    {"-",prim_body_minus},
    {"/",prim_body_slash},
    {"/MOD",prim_body_slash_mod},
    {"<",prim_body_less_than},
    {"=",prim_body_equals},
    {">",prim_body_greater_than},
    {"@",prim_body_fetch},
    {"C@",prim_body_c_fetch},
    {"W@",prim_body_w_fetch},
    {"ABS",prim_body_abs},
    {"AND",prim_body_and},
    {"BOUNDS",prim_body_bounds},
    {"CELLS",prim_body_cells},
    {"DROP",prim_body_drop},
    {"2DROP",prim_body_two_drop},
    {"DUP",prim_body_dupe},
    {"2DUP",prim_body_two_dupe},
    {"INVERT",prim_body_invert},
    {"LSHIFT",prim_body_l_shift},
    {"MAX",prim_body_max},
    {"MIN",prim_body_min},
    {"MOD",prim_body_mod},
    {"NEGATE",prim_body_negate},
    {"OR",prim_body_or},
    {"OVER",prim_body_over},
    {"2OVER",prim_body_two_over},
    {"ROT",prim_body_rote},
    {"-ROT",prim_body_minus_rote},
    {"RSHIFT",prim_body_r_shift},
    {"SWAP",prim_body_swap},
    {"2SWAP",prim_body_two_swap},
    {"U<",prim_body_u_less_than},
    {"U>",prim_body_u_greater_than},
    {"XOR",prim_body_x_or},
    {"<>",prim_body_not_equals},
    {"FALSE",prim_body_false},
    {"NIP",prim_body_nip},
    {"TRUE",prim_body_true},
    {"TUCK",prim_body_tuck},
    {"CXT",prim_body_cxt},
    {"WXT",prim_body_wxt},
};

const char *locals[]={"X","Y","Z"};


//Compile and run test cases
int compile(uint8_t *data,const char *code)
{
    int data_index=0;
    int code_index=0;
    char word[10];
    int word_index=0;
    char c;
    bool store_local=false;
    do
    {
        c=code[code_index];
        if ((c==0)||(c==' '))
        {
            if (word_index!=0)
            {
                bool found=false;

                //Number?
                char *endptr;
                int32_t result=strtol(word,&endptr,10);
                if (*endptr==0)
                {
                    //Found number
					void (*func)(struct ForthEngine *)=&prim_hidden_push;
                    memcpy(data+data_index,&func,sizeof(&prim_hidden_push));
                    data_index+=sizeof(&prim_hidden_push);
                    memcpy(data+data_index,&result,sizeof(result));
                    data_index+=sizeof(result);

                    //(*((void (**)(struct ForthEngine *))data))(NULL);

                    found=true;
                }
                if (found==false)
                {
                    for (int i=0;i<ARRAY_LEN(functions);i++)
                    {
                        if (strcasecmp(word,functions[i].name)==0)
                        {
                            //Found word
                            memcpy(data+data_index,&functions[i].body,sizeof(&functions[i].body));
                            data_index+=sizeof(&prim_hidden_push);
                            found=true;
                            break;
                        }
                    }
                }
                if (found==false)
                {
                    for (int i=0;i<ARRAY_LEN(locals);i++)
                    {
                        if (strcasecmp(word,locals[i])==0)
                        {
                            //Found local
                            if (store_local==true)
                            {
                                memcpy(data+data_index,&forth_locals_store[i],sizeof(&forth_locals_store[i]));
                                store_local=false;
                            }
                            else
                            {
                                memcpy(data+data_index,&forth_locals_fetch[i],sizeof(&forth_locals_fetch[i]));
                            }
                            data_index+=sizeof(&prim_hidden_push);
                            found=true;
                            break;
                        }
                    }
                }
                if (found==false)
                {
                    if (strcasecmp(word,"TO")==0)
                    {
                        store_local=true;
                        found=true;
                    }
                }
                if (found==false)
                {
                    printf("Unknown: %s\n",word);
                    exit(1);
                }
                word_index=0;
            }
        }
        else
        {
            word[word_index]=c;
            word_index++;
            word[word_index]=0;
        }
        code_index++;
    }
    while (c!=0);

    return data_index;
}

void log_thread(uint8_t *data, int byte_count)
{
    log_text("Code: ");

    int data_index=0;
    while(data_index<byte_count)
    {
        bool found=false;
        void (*func)(struct ForthEngine *)=*(void (**)(struct ForthEngine *))(data+data_index);
        data_index+=sizeof(func);
        if (found==false)
        {
            if (func==&prim_hidden_push)
            {
                int32_t result=*(int32_t *)(data+data_index);
                data_index+=sizeof(result);
                log_text_raw("%d ",result);
                found=true;
            }
        }
        if (found==false)
        {
            for (int i=0;i<ARRAY_LEN(functions);i++)
            {
                if (functions[i].body==func)
                {
                    log_text_raw("%s ",functions[i].name);
                    found=true;
                    break;
                }
            }
        }
        if (found==false)
        {
            for (int i=0;i<ARRAY_LEN(locals);i++)
            {
                if (forth_locals_fetch[i]==func)
                {
                    log_text_raw("%s ",locals[i]);
                    found=true;
                    break;
                }
                if (forth_locals_store[i]==func)
                {
                    log_text_raw("TO %s ",locals[i]);
                    found=true;
                    break;
                }
            }
        }
        if (found==false)
        {
            printf("log_text: UNKNOWN (%p)\n",func);
            exit(0);
        }
    }
    log_text_raw("\n");
}

void run_tests()
{
    log_push(LOGGING_FORTH_OPT_RUN_TESTS,"run_tests");

    uint8_t data[DATA_SIZE];
    uint8_t optimized[OPT_SIZE];
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        printf("Test %d: %s\n",i+1,tests[i].title);

        log_text("Test %d: %s\n",i+1,tests[i].title);
        log_text("Code: %s\n",tests[i].test);
        int byte_count=compile(data,tests[i].test);
        log_thread(data,byte_count);
        forth_optimize(optimized,OPT_SIZE,data,DATA_SIZE);
        log_text("done\n\n");
    }

    log_pop();
}

int main()
{
    init_logging("log.txt");

    run_tests();

    return 0;
}
