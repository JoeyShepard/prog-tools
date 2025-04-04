#!/usr/bin/env python3

import sys
import os

DIR_NAME="ls-test/"

if len(sys.argv)!=3:
    print("Expected - exactly two arguments")
    exit(1)

for i in range(1,3):
    if not sys.argv[i].isnumeric():
        print(f"Expected number but found {argv[i]}")
        exit(1)

os.system(f"rm {DIR_NAME}/*")

name_len=int(sys.argv[1])
count=int(sys.argv[2])

char=ord('a')
for i in range(count):
    f=open(DIR_NAME+chr(char)*name_len,"w")
    f.close()
    char+=1
    if char>ord('z'):
        char=ord('a')


os.system(f"ls {DIR_NAME}")
