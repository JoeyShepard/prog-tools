#!/usr/bin/env tmux-script

session prog-tools

window vim src/main.c
rename main

window
rename run

window vim src/compatibility.h
rename sdl2
vsplit vim src/cg50-sdl2.c

window vim src/getkey.h
rename key
vsplit vim src/getkey.c

window vim src/structs.h
rename structs

window vim src/text.h
rename txt
vsplit vim src/text.c

window vim src/mem.h
rename mem
vsplit vim src/mem.c

window vim src/forth-engine.h
rename cons
vsplit vim src/forth-engine.c

window vim src/forth-primitives.h
rename prim
vsplit vim src/forth-primitives.c

window vim src/forth.h
rename forth
vsplit vim src/forth.c



