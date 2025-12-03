#!/usr/bin/env python3

#import subprocess
#(code,output)=subprocess.getstatusoutput("command")

#from color import *

from random import random

TEST_COUNT=1000000
RANGE=1000

print("Test 1")
for i in range(TEST_COUNT):
    x=int(random()*1000)+1
    y=int(random()*1000)+1
    z=int(random()*1000)+1

    a=x*y/z
    b=x/z*y
    
    if abs(a-b)>a/1000:
        print(f"Failed: {x}, {y}, {z}. {a}!={b}")
        exit()
print("done\n")

print("Test 2")
for i in range(TEST_COUNT):
    x=int(random()*100)+1
    y=int(random()*100)+1
    z=int(random()*100)+1

    a=int(int(x/y)/z)
    b=int(int(x/z)/y)

    if a!=b:
        print(f"Failed: {x}, {y}, {z}. {a}!={b}")
        exit()
print("done\n")

