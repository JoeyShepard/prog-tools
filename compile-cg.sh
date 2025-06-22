#!/bin/bash

#First, compile C files relying on __attribute__((musttail)) to .s with gcc 15 running
#in container then pass to fxsdk. Not sure how to pass obj file to fxsdk.
rm -f src/custom/generated/*
cd src/custom/
docker run -it --rm -v ./gcc-15:/gcc-15 -v ./generated:/generated -w /generated -u $(id -u):$(id -g) sh-gcc:15.1.0 \
    bash -c "sh-elf-gcc -O3 -S -ffreestanding /gcc-15/*.c"
ret=$?
if [ $ret -ne 0 ]; then
    exit 1
fi
cd ../../

#Next, start fxsdk to compile C files and .s files generated above
fxsdk build-cg -- -s
ret=$?
if [ $ret -ne 0 ]; then
    exit 1
fi

