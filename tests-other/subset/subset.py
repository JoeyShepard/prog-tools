#!/usr/bin/env python3

from random import randint,seed
from time import perf_counter

DEBUG=False

#List will never contain number >= target
nums=[1,1,2,3,4,5]
#target=6

def brute_force(s,target):
    include=[0]*len(s)
    final=set()
    iterations=2**len(include)
    for i in range(iterations):
        total=0
        combo=[]
        for j,num in enumerate(include):
            if num==1:
                total+=s[j]
                combo+=[s[j]]
        if total==target:
            combo.sort()
            final.add(tuple(combo))
        carry=1
        for j in range(len(include)):
            x=include[j]
            include[j]=(x+carry)&1
            carry=(x+carry)>>1
    return iterations,final

def back_track(s,target):
    class BackTrack():
        def __init__(self):
            self.step=0

    total=0
    stack=[BackTrack() for _ in range(len(s))]
    index=0
    iterations=0
    final=set()
    while index!=-1:
        iterations+=1

        if DEBUG==True:
            print(f"total {total}, index {index}, value {s[index]}, step {stack[index].step}, seq ",end="")
            for i in range(index+1):
                print(f"{stack[i].step} ",end="")
            print()
            input()
        
        #Too much overhead handled by recursion to 
            #use same structure as example

        if stack[index].step==0:
            total+=s[index]
            if total==target:
                x=[]
                for i in range(index):
                    if stack[i].step==1:
                        x+=[s[i]]
                x+=[s[index]]
                final.add(tuple(x))
                if DEBUG==True:
                    print(f"Found {x}")

                total-=s[index]
                index-=1
            elif total>target:
                total-=s[index]
                index-=1
            else:
                stack[index].step+=1
                index+=1
                if index==len(s):
                    index-=1
                    total-=s[index]
                    stack[index].step=2
                else:
                    stack[index].step=0

        elif stack[index].step==1:
            total-=s[index]
            stack[index].step+=1
            index+=1
            if index==len(s):
                index-=1
                stack[index].step=2
            else:
                stack[index].step=0
        elif stack[index].step==2:
            index-=1
                
    return iterations,final


TEST_COUNT=20
TEST_SIZE_MIN=10
TEST_SIZE_MAX=20
TEST_VAL_MIN=1
TEST_VAL_MAX=100
TARGET_MIN=101
TARGET_MAX=1000

def test_both(s,target):
    _,a=brute_force(s,target)
    _,b=back_track(s,target)
    if a==b:
        print(f"MATCH")
    else:
        print(f"Mismatch")
        print(a)
        print(b)
        exit()
    

def timed_test():
    tests=[]
    targets=[]
    for _ in range(TEST_COUNT):
        tests+=[[randint(TEST_VAL_MIN,TEST_VAL_MAX) for _ in range(randint(TEST_SIZE_MIN,TEST_SIZE_MAX))]]
        tests[-1].sort()
        targets+=[randint(TARGET_MIN,TARGET_MAX)]

    start=perf_counter()
    for i,test in enumerate(tests):
        print(f"{len(test)} ", end="")
        target=targets[i]
        brute_force(test,target)
    print(f"Brute force: {perf_counter()-start}")

    start=perf_counter()
    for test in tests:
        print(f"{len(test)} ",end="")
        target=targets[i]
        back_track(test,target)
    print(f"Back track: {perf_counter()-start}")

def compare_test():
    TEST_COUNT=250
    for i in range(TEST_COUNT):
        test=[randint(TEST_VAL_MIN,TEST_VAL_MAX) for _ in range(randint(TEST_SIZE_MIN,TEST_SIZE_MAX))]
        test.sort()
        target=randint(TARGET_MIN,TARGET_MAX)
        _,a=brute_force(test,target)
        _,b=back_track(test,target)
        if a==b:
            print(f"{i} MATCH")
        else:
            print(f"{i} ({len(test)}) Mismatch for {target}")
            print(a)
            print(b)
            exit()

seed(42)

#timed_test()
compare_test()

