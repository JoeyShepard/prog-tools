#!/bin/bash

echo Compiling for cg50...
fxsdk build-cg
ret=$?
if [ $ret -ne 0 ]; then
    exit 1
fi

