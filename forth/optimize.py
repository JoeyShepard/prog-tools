#!/usr/bin/env python3

#Generate combined Forth primitives

#Selected primitives to optimize
#- Keep memory access but ignore dictionary access (ALLOT, C, etc)

#If wrapping, figure out slots and assign address only once

prim_mem=[
    "!",
    "C!",
    "W!",
    "@",
    "C@",
    "W@",
    "ALIGNED",
    "CELLS",
    "WALIGNED",
    "CXT",
    "WXT"
    ]

prim_math=[
    "*",
    "*/",
    "*/MOD",
    "+",
    "-",
    "/",
    "/MOD",
    "<",
    "=",
    ">",
    "ABS",
    "AND",
    "INVERT",
    "LSHIFT",
    "MAX",
    "MIN",
    "MOD",
    "NEGATE",
    "OR",
    "RSHIFT",
    "U<",
    "U>",
    "XOR",
    "<>",
    "WITHIN",
    ]

prim_stack=[
    "DROP",
    "2DROP",
    "DUP",
    "2DUP",
    "OVER",
    "2OVER",
    "ROT",
    "-ROT",
    "SWAP",
    "2SWAP",
    "NIP",
    "TUCK",
    ]

prim_other=[
    "I",
    "J",
    "FALSE",
    "TRUE",
    ]

#Small set for testing
prim_test=[
    "DUP",
    "DROP",
    "SWAP",
    "ROT",
    "+",
    "-"
    "STORE0",
    "LOAD0",
    "1",
    "0"
    ]

prim_all=prim_mem+prim_math+prim_stack+prim_other

#Numbers
#Locals
    #Fetch
    #Store


