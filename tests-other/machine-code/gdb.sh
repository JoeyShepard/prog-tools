#!/bin/bash
./compile.sh

gdb-multiarch --quiet -x gdb-options.txt test
