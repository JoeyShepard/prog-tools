#!/bin/bash
./compile.sh

qemu-sh4eb-static -g 2345 test
