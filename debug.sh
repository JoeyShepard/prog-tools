#!/bin/bash
make
ret=$?
if [ $ret -eq 0 ]; then
    gdbserver localhost:2345 sdl2/cg50-sdl2 &
    gdb -x gdb-options.txt
fi
