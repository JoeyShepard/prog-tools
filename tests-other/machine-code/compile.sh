#!/bin/bash
rm -f test

sh4eb-linux-musl-gcc -O2 -g -static main.c -o test
