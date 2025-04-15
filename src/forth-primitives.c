#include <string.h>

#include "compatibility.h"
#include "forth-primitives.h"

//Globals
const struct ForthPrimitive forth_primitives[]=
{
    {"!",1,&forth_prim_store},
    {"C!",2,&forth_prim_c_store},
    {"H!",2,&forth_prim_w_store},
    {"'",1,&forth_prim_tick},
    {"(",1,&forth_prim_paren},
    {"*",1,&forth_prim_star},
    {"*/",2,&forth_prim_star_slash},
    {"*/MOD",5,&forth_prim_star_slash_mod},
    {"+",1,&forth_prim_plus},
    {"+LOOP",5,&forth_prim_plus_loop},
    {",",1,&forth_prim_comma},
    {"C,",2,&forth_prim_c_comma},
    {"H,",2,&forth_prim_w_comma},
    {"-",1,&forth_prim_minus},
    {".",1,&forth_prim_dot},
    {".\"",2,&forth_prim_dot_quote},
    {"/",1,&forth_prim_slash},
    {"/MOD",4,&forth_prim_slash_mod},
    {":",1,&forth_prim_colon},
    {";",1,&forth_prim_semicolon},
    {"<",1,&forth_prim_less_than},
    {"=",1,&forth_prim_equals},
    {">",1,&forth_prim_greater_than},
    {">NUMBER",7,&forth_prim_to_number},
    {"?DUP",4,&forth_prim_question_dupe},
    {"@",1,&forth_prim_fetch},
    {"C@",2,&forth_prim_c_fetch},
    {"H@",2,&forth_prim_w_fetch},
    {"QUIT",4,&forth_prim_quit},
    {"ABS",3,&forth_prim_abs},
    {"ACCEPT",6,&forth_prim_accept},
    {"ALIGN",5,&forth_prim_align},
    {"ALIGNED",7,&forth_prim_aligned},
    {"ALLOT",5,&forth_prim_allot},
    {"AND",3,&forth_prim_and},
    {"BASE",4,&forth_prim_base},
    {"BEGIN",5,&forth_prim_begin},
    {"BL",2,&forth_prim_b_l},
    {"CELLS",5,&forth_prim_cells},
    {"CHAR",4,&forth_prim_char},
    {"CONSTANT",8,&forth_prim_constant},
    {"CR",2,&forth_prim_c_r},
    {"DECIMAL",7,&forth_prim_decimal},
    {"DEPTH",5,&forth_prim_depth},
    {"DO",2,&forth_prim_do},
    {"DROP",4,&forth_prim_drop},
    {"DUP",3,&forth_prim_dupe},
    {"ELSE",4,&forth_prim_else},
    {"EMIT",4,&forth_prim_emit},
    {"EVALUATE",8,&forth_prim_evaluate},
    {"EXIT",4,&forth_prim_exit},
    {"FILL",4,&forth_prim_fill},
    {"FIND",4,&forth_prim_find},
    {"HERE",4,&forth_prim_here},
    {"I",1,&forth_prim_i},
    {"IF",2,&forth_prim_if},
    {"IMMEDIATE",9,&forth_prim_immediate},
    {"INVERT",6,&forth_prim_invert},
    {"J",1,&forth_prim_j},
    {"KEY",3,&forth_prim_key},
    {"LEAVE",5,&forth_prim_leave},
    {"LITERAL",7,&forth_prim_literal},
    {"LOOP",4,&forth_prim_loop},
    {"LSHIFT",6,&forth_prim_l_shift},
    {"MAX",3,&forth_prim_max},
    {"MIN",3,&forth_prim_min},
    {"MOD",3,&forth_prim_mod},
    {"MOVE",4,&forth_prim_move},
    {"NEGATE",6,&forth_prim_negate},
    {"OR",2,&forth_prim_or},
    {"OVER",4,&forth_prim_over},
    {"REPEAT",6,&forth_prim_repeat},
    {"ROT",3,&forth_prim_rote},
    {"-ROT",4,&forth_prim_minus_rote},
    {"RSHIFT",6,&forth_prim_r_shift},
    {"S\"",2,&forth_prim_s_quote},
    {"SPACE",5,&forth_prim_space},
    {"SPACES",6,&forth_prim_spaces},
    {"STATE",5,&forth_prim_state},
    {"SWAP",4,&forth_prim_swap},
    {"THEN",4,&forth_prim_then},
    {"TYPE",4,&forth_prim_type},
    {"UNTIL",5,&forth_prim_until},
    {"VARIABLE",8,&forth_prim_variable},
    {"VAR",3,&forth_prim_var},
    {"WHILE",5,&forth_prim_while},
    {"XOR",3,&forth_prim_x_or},
    {"[",1,&forth_prim_left_bracket},
    {"]",1,&forth_prim_right_bracket},
    {"[']",3,&forth_prim_bracket_tick},
    {"[CHAR]",6,&forth_prim_bracket_char},
    {".R",2,&forth_prim_dot_r},
    {"<>",2,&forth_prim_not_equals},
    {"AGAIN",5,&forth_prim_again},
    {"CASE",4,&forth_prim_case},
    {"FALSE",5,&forth_prim_false},
    {"HEX",3,&forth_prim_hex},
    {"NIP",3,&forth_prim_nip},
    {"PICK",4,&forth_prim_pick},
    {"ROLL",4,&forth_prim_roll},
    {"S\"",3,&forth_prim_s_backslash_quote},
    {"TRUE",4,&forth_prim_true},
    {"TUCK",4,&forth_prim_tuck},
    {"UNUSED",6,&forth_prim_unused},
    {"WITHIN",6,&forth_prim_within},
    {"\\",1,&forth_prim_backslash},
    {".S",2,&forth_prim_dot_s},
    {"?",1,&forth_prim_question},
    {"DUMP",4,&forth_prim_dump},
    {"SEE",3,&forth_prim_see},
    {"WORDS",5,&forth_prim_words},
    {"STATE",5,&forth_prim_state},
    {"BYE",3,&forth_prim_bye},
    {"COMPARE",7,&forth_prim_compare},
};

//Can't determine length of array primitives in other files, so calculate here
const int forth_primitives_len=(int)(ARRAY_SIZE(forth_primitives));

//Functions
void forth_prim_store(struct ForthEngine *engine)
{
}

void forth_prim_c_store(struct ForthEngine *engine)
{
}

void forth_prim_w_store(struct ForthEngine *engine)
{
}

void forth_prim_tick(struct ForthEngine *engine)
{
}

void forth_prim_paren(struct ForthEngine *engine)
{
}

void forth_prim_star(struct ForthEngine *engine)
{
}

void forth_prim_star_slash(struct ForthEngine *engine)
{
}

void forth_prim_star_slash_mod(struct ForthEngine *engine)
{
}

void forth_prim_plus(struct ForthEngine *engine)
{
}

void forth_prim_plus_loop(struct ForthEngine *engine)
{
}

void forth_prim_comma(struct ForthEngine *engine)
{
}

void forth_prim_c_comma(struct ForthEngine *engine)
{
}

void forth_prim_w_comma(struct ForthEngine *engine)
{
}

void forth_prim_minus(struct ForthEngine *engine)
{
}

void forth_prim_dot(struct ForthEngine *engine)
{
}

void forth_prim_dot_quote(struct ForthEngine *engine)
{
}

void forth_prim_slash(struct ForthEngine *engine)
{
}

void forth_prim_slash_mod(struct ForthEngine *engine)
{
}

void forth_prim_colon(struct ForthEngine *engine)
{
}

void forth_prim_semicolon(struct ForthEngine *engine)
{
}

void forth_prim_less_than(struct ForthEngine *engine)
{
}

void forth_prim_equals(struct ForthEngine *engine)
{
}

void forth_prim_greater_than(struct ForthEngine *engine)
{
}

void forth_prim_to_number(struct ForthEngine *engine)
{
}

void forth_prim_question_dupe(struct ForthEngine *engine)
{
}

void forth_prim_fetch(struct ForthEngine *engine)
{
}

void forth_prim_c_fetch(struct ForthEngine *engine)
{
}

void forth_prim_w_fetch(struct ForthEngine *engine)
{
}

void forth_prim_quit(struct ForthEngine *engine)
{
}

void forth_prim_abs(struct ForthEngine *engine)
{
}

void forth_prim_accept(struct ForthEngine *engine)
{
}

void forth_prim_align(struct ForthEngine *engine)
{
}

void forth_prim_aligned(struct ForthEngine *engine)
{
}

void forth_prim_allot(struct ForthEngine *engine)
{
}

void forth_prim_and(struct ForthEngine *engine)
{
}

void forth_prim_base(struct ForthEngine *engine)
{
}

void forth_prim_begin(struct ForthEngine *engine)
{
}

void forth_prim_b_l(struct ForthEngine *engine)
{
}

void forth_prim_cells(struct ForthEngine *engine)
{
}

void forth_prim_char(struct ForthEngine *engine)
{
}

void forth_prim_constant(struct ForthEngine *engine)
{
}

void forth_prim_c_r(struct ForthEngine *engine)
{
}

void forth_prim_decimal(struct ForthEngine *engine)
{
}

void forth_prim_depth(struct ForthEngine *engine)
{
}

void forth_prim_do(struct ForthEngine *engine)
{
}

void forth_prim_drop(struct ForthEngine *engine)
{
}

void forth_prim_dupe(struct ForthEngine *engine)
{
}

void forth_prim_else(struct ForthEngine *engine)
{
}

void forth_prim_emit(struct ForthEngine *engine)
{
}

void forth_prim_evaluate(struct ForthEngine *engine)
{
}

void forth_prim_exit(struct ForthEngine *engine)
{
}

void forth_prim_fill(struct ForthEngine *engine)
{
}

void forth_prim_find(struct ForthEngine *engine)
{
}

void forth_prim_here(struct ForthEngine *engine)
{
}

void forth_prim_i(struct ForthEngine *engine)
{
}

void forth_prim_if(struct ForthEngine *engine)
{
}

void forth_prim_immediate(struct ForthEngine *engine)
{
}

void forth_prim_invert(struct ForthEngine *engine)
{
}

void forth_prim_j(struct ForthEngine *engine)
{
}

void forth_prim_key(struct ForthEngine *engine)
{
}

void forth_prim_leave(struct ForthEngine *engine)
{
}

void forth_prim_literal(struct ForthEngine *engine)
{
}

void forth_prim_loop(struct ForthEngine *engine)
{
}

void forth_prim_l_shift(struct ForthEngine *engine)
{
}

void forth_prim_max(struct ForthEngine *engine)
{
}

void forth_prim_min(struct ForthEngine *engine)
{
}

void forth_prim_mod(struct ForthEngine *engine)
{
}

void forth_prim_move(struct ForthEngine *engine)
{
}

void forth_prim_negate(struct ForthEngine *engine)
{
}

void forth_prim_or(struct ForthEngine *engine)
{
}

void forth_prim_over(struct ForthEngine *engine)
{
}

void forth_prim_repeat(struct ForthEngine *engine)
{
}

void forth_prim_rote(struct ForthEngine *engine)
{
}

void forth_prim_minus_rote(struct ForthEngine *engine)
{
}

void forth_prim_r_shift(struct ForthEngine *engine)
{
}

void forth_prim_s_quote(struct ForthEngine *engine)
{
}

void forth_prim_space(struct ForthEngine *engine)
{
}

void forth_prim_spaces(struct ForthEngine *engine)
{
}

void forth_prim_state(struct ForthEngine *engine)
{
}

void forth_prim_swap(struct ForthEngine *engine)
{
}

void forth_prim_then(struct ForthEngine *engine)
{
}

void forth_prim_type(struct ForthEngine *engine)
{
}

void forth_prim_until(struct ForthEngine *engine)
{
}

void forth_prim_variable(struct ForthEngine *engine)
{
}

void forth_prim_var(struct ForthEngine *engine)
{
}

void forth_prim_while(struct ForthEngine *engine)
{
}

void forth_prim_x_or(struct ForthEngine *engine)
{
}

void forth_prim_left_bracket(struct ForthEngine *engine)
{
}

void forth_prim_right_bracket(struct ForthEngine *engine)
{
}

void forth_prim_bracket_tick(struct ForthEngine *engine)
{
}

void forth_prim_bracket_char(struct ForthEngine *engine)
{
}

void forth_prim_dot_r(struct ForthEngine *engine)
{
}

void forth_prim_not_equals(struct ForthEngine *engine)
{
}

void forth_prim_again(struct ForthEngine *engine)
{
}

void forth_prim_case(struct ForthEngine *engine)
{
}

void forth_prim_false(struct ForthEngine *engine)
{
}

void forth_prim_hex(struct ForthEngine *engine)
{
}

void forth_prim_nip(struct ForthEngine *engine)
{
}

void forth_prim_pick(struct ForthEngine *engine)
{
}

void forth_prim_roll(struct ForthEngine *engine)
{
}

void forth_prim_s_backslash_quote(struct ForthEngine *engine)
{
}

void forth_prim_true(struct ForthEngine *engine)
{
}

void forth_prim_tuck(struct ForthEngine *engine)
{
}

void forth_prim_unused(struct ForthEngine *engine)
{
}

void forth_prim_within(struct ForthEngine *engine)
{
}

void forth_prim_backslash(struct ForthEngine *engine)
{
}

void forth_prim_dot_s(struct ForthEngine *engine)
{
}

void forth_prim_question(struct ForthEngine *engine)
{
}

void forth_prim_dump(struct ForthEngine *engine)
{
}

void forth_prim_see(struct ForthEngine *engine)
{
}

void forth_prim_words(struct ForthEngine *engine)
{
}

void forth_prim_bye(struct ForthEngine *engine)
{
}

void forth_prim_compare(struct ForthEngine *engine)
{
}

