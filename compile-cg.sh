#!/bin/bash

#First, compile C files relying on __attribute__((musttail)) to .s with gcc 15 running
#in container then pass to fxsdk. Not sure how to pass obj file to fxsdk.
#rm -f src/custom/generated/*
#cd src/custom/
#docker run -it --rm -v ./gcc-15:/gcc-15 -v ./generated:/generated -w /generated -u $(id -u):$(id -g) sh-gcc:15.1.0 \
#    bash -c "sh-elf-gcc -O3 -S -ffreestanding /gcc-15/*.c"
#ret=$?
#if [ $ret -ne 0 ]; then
#    exit 1
#fi
#cd ../../

#Instead of above, generate assembly from C files to use musttail
    #Will not be necessary when fxsdk moves to gcc 15
FILES=("forth-check" "forth-locals" "forth-primitives")
for file in "${FILES[@]}"; do
    command="sh-elf-gcc -O2 -S -Iinclude -DCG50 -DASM_ONLY -DFXCG50 -o build-asm/$file.s  src/$file.c"
    echo "$command"
    eval "$command"
    ret=$?
    if [ $ret -ne 0 ]; then
        exit 1
    fi
done

#Next, start fxsdk to compile C files and .s files generated above
fxsdk build-cg -- -s
ret=$?
if [ $ret -ne 0 ]; then
    exit 1
fi

