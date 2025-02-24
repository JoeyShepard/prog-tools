#!/bin/bash

echo Switched to make
echo Exiting...
exit 1

echo Compiling for PC...
rm -f sdl2/*
cp src/* sdl2/
cd sdl2/
gcc -O3 *.c -o cg50-sdl2 `sdl2-config --cflags --libs`
ret=$?
if [ $ret -ne 0 ]; then
    exit 1
fi
echo Running...
./cg50-sdl2

