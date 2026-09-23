#!/usr/bin/env python3

from color import *

OFFSET_SIZE=0
OFFSET_ID=1
OFFSET_LOCKED=2
OFFSET_FREE=3
OFFSET_DATA=4

mem=[]
mem_id=0
objects={}

def add_object(size,locked,free):
    global mem,mem_id
    addition=[mem_id]*(size)
    addition[OFFSET_SIZE]=size
    addition[OFFSET_ID]=mem_id
    addition[OFFSET_LOCKED]=locked
    addition[OFFSET_FREE]=free
    mem+=addition
    objects[mem_id]={}
    objects[mem_id]["size"]=size
    objects[mem_id]["locked"]=locked
    objects[mem_id]["free"]=free
    ret_id=mem_id
    mem_id+=1
    return ret_id

def add_locked(size):
    return add_object(size,1,0)

def add_unlocked(size):
    return add_object(size,0,0)

def add_free(size):
    return add_object(size,0,1)

def verify():
    index=0
    while index<len(mem):
        size=mem[index+OFFSET_SIZE]
        obj_id=mem[index+OFFSET_ID]
        locked=mem[index+OFFSET_LOCKED]
        free=mem[index+OFFSET_FREE]

        print(f"{obj_id}: {size} bytes, ",end="")
        if free==1:
            print("free")
        else:
            if locked==1:
                print("locked")
            else:
                print("unlocked")

        if objects[obj_id]["size"]!=size:
            print(f"Expected size {objects[obj_id]['size']} but found size {size}")
            return
        if objects[obj_id]["locked"]!=locked:
            print(f"Expected locked {objects[obj_id]['locked']} but found locked {locked}")
            return
        if objects[obj_id]["free"]!=free:
            print(f"Expected free {objects[obj_id]['free']} but found free {free}")
            return

        for i in range(index+OFFSET_DATA,index+size):
            if mem[i]!=obj_id:
                print(f"- Expected {obj_id} but found {mem[i]}")
                print(f"- {mem[index:index+size]}")
                return

        index+=size

def reset_mem():
    global mem
    mem=[]

#Shift memory down and reallocated memory up
def test1():
    reset_mem()
    reallocated=add_unlocked(20)
    add_locked(10)
    add_unlocked(20)
    add_free(10)
    add_locked(10)
    add_unlocked(30)
    add_free(10)
    verify()
    #TODO: reallocate

test_list=[
    test1
    ]

for f in test_list:
    f()
    print()

