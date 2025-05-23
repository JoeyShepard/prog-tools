#!/usr/bin/env tmux-script

session prog-tools

window vim src/main.c
rename main

window
rename run

window vim src/compatibility.h
rename sdl2
vsplit vim src/compatibility.c

window vim src/getkey.h
rename keys
vsplit vim src/getkey.c

window vim src/structs.h
rename structs

window vim src/text.h
rename text
vsplit vim src/text.c

window vim src/mem.h
rename mem
vsplit vim src/mem.c

window vim src/forth-engine.h
rename engine
vsplit vim src/forth-engine.c

window vim src/forth-primitives.h
rename prim
vsplit vim src/forth-primitives.c

window vim src/forth.h
rename forth
vsplit vim src/forth.c



