#!/bin/bash

echo Writing disassembly.lst...

sh4eb-linux-musl objdump -D -S build-cg/prog-tools > disassembly.lst
