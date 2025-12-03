#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>

#include "forth-engine.h"
#include "forth-optimize.h"
#include "forth-primitives.h"
#include "macros.h"



struct FuncInfo
{
    const char *word;
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

//Test cases
struct TestInfo
{
    const char *title;
    const char *test;
};

const struct TestInfo tests[]={
    {"foo?","-1 2 3 rOt false"},
    {"bar?","1 2 SWAP DROP"},
    };

//Compile and run test cases
void compile(uint8_t *data,const char *code)
{
    int data_index=0;
    int code_index=0;
    char word[10];
    int word_index=0;
    char c;
    do
    {
        c=code[code_index];
        if ((c==0)||(c==' '))
        {
            if (word_index!=0)
            {
                bool found=false;

                //Word is number?
                char *endptr;
                int32_t result=strtol(word,&endptr,10);
                if (*endptr==0)
                {
                    //Word is number
                    printf("Number: %d\n",result);

                    data[0]=0x12;
                    data[1]=0x34;
                    data[2]=0x56;
                    data[3]=0x78;

                    void (*func)(struct ForthEngine *)=&prim_hidden_push;
                    memcpy(data+data_index,&func,sizeof(&prim_hidden_push));
                    data_index+=sizeof(&prim_hidden_push);
                    printf("%x %p\n",*(uint32_t*)data,func);

                    func(NULL);

                    found=true;
                }
                if (found==false)
                {
                    for (int i=0;i<ARRAY_LEN(functions);i++)
                    {
                        if (strcasecmp(word,functions[i].word)==0)
                        {
                            printf("Word: %s\n",functions[i].word);
                            found=true;
                            break;
                        }
                    }
                }
                if (found==false)
                {
                    for (int i=0;i<ARRAY_LEN(functions);i++)
                    {
                        if (strcasecmp(word,locals[i])==0)
                        {
                            printf("Word: %s\n",locals[i]);
                            found=true;
                            break;
                        }
                    }
                }
                if (found==false)
                {
                    printf("Unknown: %s\n",word);
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
}

void show_thread(uint8_t *data)
{
}

void run_tests()
{
    uint8_t data[4096];
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        printf("Test %d: %s - %s\n",i+1,tests[i].title,tests[i].test);
        compile(data,tests[i].test);
        show_thread(data);
        printf("done\n\n");
    }
}

int main()
{
    run_tests();

    return 0;
}
