#!/bin/bash

#Copy common files from server one directory up
#gcc runs in container so can't see directories above

cp ../src/common.h src/
cp ../src/common.c src/
