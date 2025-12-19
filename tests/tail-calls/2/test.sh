#!/bin/bash

sh4eb-linux-musl-gcc -O3 -S foo.c
cp foo.s ../../../src/foo.S
