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

window vim src/graphics.h
rename gfx
vsplit vim src/graphics.c

window vim src/text.h
rename txt
vsplit vim src/text.c

window vim src/mem.h
rename mem
vsplit vim src/mem.c

window vim src/manager.h
rename win
vsplit vim src/manager.c

window vim src/command.h
rename cmd
vsplit vim src/command.c

window vim src/console.h
rename dummy
vsplit vim src/console.c



