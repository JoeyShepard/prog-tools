#!/bin/bash

echo Writing disassembly.lst...

#If Docker image for cross-musl is installed
#sh4eb-linux-musl objdump -D -S build-cg/prog-tools > disassembly.lst

#If Docker image for fxsdk is installed
docker run -it --rm -v $(pwd):/code -w /code -u $(id -u):$(id -g) fxsdk sh-elf-objdump -D -S build-cg/prog-tools > disassembly.lst

