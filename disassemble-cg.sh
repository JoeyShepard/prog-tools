#!/bin/bash

echo Writing disassembly.lst...
sh-elf-objdump -D -S build-cg/prog-tools > disassembly.lst
