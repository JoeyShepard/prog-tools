#!/bin/bash
rm -f test
gcc -Wa,-aghlns=main.lst -O2 -g main.c -o test
gcc -S -O3 main.c
./test
