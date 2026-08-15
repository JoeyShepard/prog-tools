#!/usr/bin/env python3
from color import *
import subprocess
from sys import argv

#Padding for printing
FILE_WIDTH=40
TESTS_WIDTH=10

args=argv[1:]
if len(args)==0:
    print("No tests specified")
    exit(0)

total_tests=0
total_fails=0
for arg in args:
    (code,output)=subprocess.getstatusoutput(arg)
    if code==127:
        #Program not found
        printc(f"Error: program '{arg}' not found\n")
        exit(-1)
    else:
        print(arg.ljust(FILE_WIDTH),end="")
        lines=output.splitlines()
        test_count=lines[-2].split()[0]
        total_tests+=int(test_count)
        print(f"{test_count} tests".ljust(TESTS_WIDTH),end="")
        if code==0:
            #All tests passed
            printc("PASS\n","green")
        else:
            #Some tests failed
            fail_count=lines[-2].split()[2]
            total_fails+=int(fail_count)
            printc("FAIL\n","red")
            for line in lines[0:len(lines)-4]:
                if "FAIL" in line:
                    printc(f"   {line}\n","red")
if total_fails==0:
    printc(f"All tests passed ({total_tests} tests in {len(args)} files)\n","green")
else:
    printc(f"Failed {total_fails} of {total_tests} tests in {len(args)} files\n","red")
