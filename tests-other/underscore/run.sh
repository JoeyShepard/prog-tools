#!/bin/bash

docker run -it --rm -v $(pwd):/code -w /code -u $(id -u):$(id -g) fxsdk sh-elf-gcc -O2 -S -fno-leading-underscore foo.c
