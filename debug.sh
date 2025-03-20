#!/bin/bash
make
ret=$?
if [ $ret -eq 0 ]; then
    gdbserver localhost:1000 sdl2/cg50-sdl2 &
    echo Running?
    gdb -x gdb-options.txt
fi
