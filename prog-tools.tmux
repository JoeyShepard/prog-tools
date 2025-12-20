#!/usr/bin/env tmux-script

session prog-tools

window vim src/main.c
rename main

window sdl2-server/build/sdl2-server
rename run
vsplit

window vim include/compatibility.h
rename sdl2
vsplit vim src/compatibility.c

window vim include/getkey.h
rename keys
vsplit vim src/getkey.c

window vim include/structs.h
rename structs

window vim include/text.h
rename text
vsplit vim src/text.c

window vim include/mem.h
rename mem
vsplit vim src/mem.c

window vim include/forth-engine.h
rename engine
vsplit vim src/forth-engine.c

window vim include/forth-primitives.h
rename prim
vsplit vim src/forth-primitives.c

window vim include/forth.h
rename forth
vsplit vim src/forth.c



