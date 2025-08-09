#!/usr/bin/env python3

#Optimization stages
"""
reorder commutative
power reduction
masking
- ie |= 8 then &= 7
- masking field for SSA type?
equivalent code elimination
- don't reload locals
some ssa goes to stack then never needed again
"""


#Constants
STACK_DEPTH=8
LOCALS_COUNT=3

#Globals
stack=[]    #Symbolic stack
error_msg=""
words={}
ssa={}
ssa_counter=0
locals_gen=[]
tests=[
    "x 3 + x 4 + 5 6 * 7 x + + + +",
    "DUP",
    "DROP",
    "DUP DROP",
    "OVER OVER DUP",
    "SWAP",
    "DUP SWAP DROP",
    "2 3 SWAP",
    "2 3 NIP",
    "DUP AND DUP OR DUP XOR",
    "x 0 AND x 0 OR x 0 XOR",
    "x -1 AND x -1 OR x -1 XOR",
    "2 - x - - 5 -",
    "x 3 + x 4 + 5 6 * 7 x + + + +",
    "x x",
    "x 2 + x y + 2 +",
    "x 1 - dup 1 +",
    "1 x * x 0 * x 0 +",
    "2 x 1 * + 3 +",
    "x 1 + to_x",
    "x 1 + to_x x",
    ]

def initialize():
    #Dictionary of Forth words to functions and optimizing functions
    global words
    words|={"dup":(dup,None)}
    words|={"drop":(drop,None)}
    words|={"swap":(swap,None)}
    words|={"over":(over,None)}
    words|={"nip":(nip,None)}
    words|={"and":(forth_and,const_and)}
    words|={"or":(forth_or,const_or)}
    words|={"xor":(forth_xor,const_xor)}
    words|={"+":(add,const_add)}
    words|={"-":(sub,const_sub)}
    words|={"*":(mult,const_mult)}
    words|={"/":(div,const_div)}
    words|={"x":(fetch_x,None)}
    words|={"y":(fetch_y,None)}
    words|={"z":(fetch_z,None)}
    #TODO: shift, negate, invert, abs, comp, 

def add_ssa(op,x,y):
    global ssa
    global ssa_counter
    new_ssa=(ssa_counter,op,x,y)
    ssa[ssa_counter]=new_ssa
    ret_val=("ssa",ssa_counter)
    ssa_counter+=1
    return ret_val

def format_item(item):
    item_type,item_data=item
    if item_type=="initial":
        return f"initial[{item_data}]"
    elif item_type=="const":
        return f"#{item_data}"
    elif item_type=="local_fetch":
        local_id,local_gen=item_data
        local_name="xyz"[local_id]
        return f"{local_name}[{local_gen}]"
    elif item_type=="ssa":
        ssa_id,ssa_op,ssa_x,ssa_y=ssa[item_data]
        arg_text=[]
        for arg in [ssa_x,ssa_y]:
            if item_type=="none":
                pass
            else:
                arg_type,arg_data=arg
                if arg_type=="ssa":
                    arg_text.append(f"SSA[{arg_data}]")
                elif arg_type!="none":
                    arg_text.append(format_item(arg))
        if len(arg_text)==1:
            if ssa_op=="orphan":
                #Single value where second part was optimized out
                return f"SSA[{ssa_id}] ({arg_text[0]})"
            else:
                #Single argument like INVERT
                return f"SSA[{ssa_id}] ({ssa_op} {arg_text[0]})"
        else:
            #Two arguments
            return f"SSA[{ssa_id}] ({arg_text[1]} {ssa_op} {arg_text[0]})"
    else:
        print(f"format_item: unknown item type '{item_type}'")
        print("Exiting...")
        exit(1)

def init_test():
    #Fill stack with beginning values
    global stack
    stack=[]
    for i in range(STACK_DEPTH):
        stack.append(("initial",i))

    #Clear SSA list from last run
    global ssa
    ssa={}
    global ssa_counter
    ssa_counter=0

    #Space for two test locals
    global locals_gen
    locals_gen=[0]*LOCALS_COUNT

def stack_min(size):
    global error_msg
    global stack
    if len(stack)<size:
        error_msg="Stack too small for operation"
        return True
    else:
        return False

def dup(stack):
    if stack_min(1)==True:
        return
    stack.append(stack[-1])

def drop(stack):
    if stack_min(1)==True:
        return
    stack.pop()

def over(stack):
    if stack_min(2)==True:
        return
    stack.append(stack[-2])

def swap(stack):
    if stack_min(2)==True:
        return
    x=stack.pop()
    y=stack.pop()
    stack.append(x)
    stack.append(y)

def nip(stack):
    if stack_min(2)==True:
        return
    x=stack.pop()
    stack.pop()
    stack.append(x)

def forth_and(stack):
    stack.append(add_ssa("and",stack.pop(),stack.pop()))

def const_and(x,y):
    return y & x

def forth_or(stack):
    stack.append(add_ssa("or",stack.pop(),stack.pop()))

def const_or(x,y):
    return y | x

def forth_xor(stack):
    stack.append(add_ssa("xor",stack.pop(),stack.pop()))

def const_xor(x,y):
    return y ^ x
    
def add(stack):
    stack.append(add_ssa("+",stack.pop(),stack.pop()))

def const_add(x,y):
    return y + x

def sub(stack):
    stack.append(add_ssa("-",stack.pop(),stack.pop()))

def const_sub(x,y):
    return y - x

def mult(stack):
    stack.append(add_ssa("*",stack.pop(),stack.pop()))

def const_mult(x,y):
    return y * x

def div(stack):
    stack.append(add_ssa("/",stack.pop(),stack.pop()))

def const_div(x,y):
    if x==0:
        x=1
    return int(y / x)

def fetch_x(stack):
    index=0
    stack.append(("local_fetch",(index,locals_gen[index])))

def fetch_y(stack):
    index=1
    stack.append(("local_fetch",(index,locals_gen[index])))

def fetch_z(stack):
    index=2
    stack.append(("local_fetch",(index,locals_gen[index])))

def ssa_replace(ssa,index,replacement):
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        ssa_id,ssa_op,ssa_x,ssa_y=ssa[i]
        xy=[]
        for arg in [ssa_x,ssa_y]:
            arg_type,arg_data=arg
            if arg_type=="ssa":
                if arg_data==index:
                    arg=replacement 
            xy.append(arg)
        if xy!=[ssa_x,ssa_y]:
            ssa[i]=(i,ssa_op,xy[0],xy[1])

def ssa_types(ssa_x,ssa_y):
    arg_type,arg_value=ssa_x
    ret_val=[arg_type]
    arg_type,arg_value=ssa_y
    ret_val.append(arg_type)
    return ret_val

def ssa_values(ssa_x,ssa_y):
    arg_type,arg_value=ssa_x
    ret_val=[arg_value]
    arg_type,arg_value=ssa_y
    ret_val.append(arg_value)
    return ret_val

def ssa_fold_constants(ssa):
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        ssa_id,ssa_op,ssa_x,ssa_y=ssa[i]
        pattern=ssa_types(ssa_x,ssa_y)
        values=ssa_values(ssa_x,ssa_y)
        if pattern==["const","const"]:
            op,const_op=words[ssa_op]
            if const_op!=None:
                #Found at least one fold
                triggered=True

                #Keep SSA assignment since may need to push to stack
                new_ssa=("const",const_op(values[0],values[1]))
                ssa[i]=(i,"orphan",new_ssa,("none",0))

                #Replace all references with new constant
                ssa_replace(ssa,i,new_ssa)

    return triggered

#Put assignments in predictatble order if commutative - const, initial, ssa, all else, none
def ssa_normalize(ssa):
    weights={
        "const":0,
        "initial":1,
        "ssa":2,
        "other":3,
        "none":99
        }
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        ssa_id,ssa_op,ssa_x,ssa_y=ssa[i]
        if ssa_op in ["*","+","-","and","or","xor"]:
            #Commutative - switch order if necessary
            arg_weights=[]
            arg_types=ssa_types(ssa_x,ssa_y)
            for arg in [ssa_x,ssa_y]:
                arg_type,arg_data=arg
                if arg_type in weights:
                    arg_weights.append(weights[arg_type])
                else:
                    arg_weights.append(weights["other"])

            if ssa_op=="-":
                #Subtraction only commutative if subtracting constant
                if arg_types[0]=="const" and arg_types[1] in ["initial","ssa"]:
                    ssa_x_type,ssa_x_data=ssa_x
                    new_ssa_x=("const",-ssa_x_data)
                    ssa[i]=(ssa_id,"+",new_ssa_x,ssa_y)
                    triggered=True
            else:
                #All others ok to commute if neccesary
                if arg_weights[0]<arg_weights[1]:
                    ssa[i]=(ssa_id,ssa_op,ssa_y,ssa_x)
                    triggered=True

    return triggered
                    
def ssa_identities(ssa):
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        ssa_id,ssa_op,ssa_x,ssa_y=ssa[i]
        if ssa_op in ["+","-"]:
            if ssa_y==("const",0):
                ssa[i]=(i,"orphan",ssa_x,("none",0))
                ssa_replace(ssa,i,ssa_x)
                triggered=True
        elif ssa_op=="*":
            if ssa_y==("const",0):
                ssa[i]=(i,"orphan",ssa_y,("none",0))
                ssa_replace(ssa,i,ssa_y)
                triggered=True
            elif ssa_y==("const",1):
                ssa[i]=(i,"orphan",ssa_x,("none",0))
                ssa_replace(ssa,i,ssa_x)
                triggered=True
        elif ssa_op in ["and","or"]:
            if ssa_x==ssa_y:
                ssa[i]=(i,"orphan",ssa_x,("none",0))
                ssa_replace(ssa,i,ssa_x)
                triggered=True
            else:
                if ssa_op=="and":
                    if ssa_y==("const",0):
                        ssa[i]=(i,"orphan",ssa_y,("none",0))
                        ssa_replace(ssa,i,ssa_y)
                        triggered=True
                    elif ssa_y==("const",-1):
                        ssa[i]=(i,"orphan",ssa_x,("none",0))
                        ssa_replace(ssa,i,ssa_x)
                        triggered=True
                elif ssa_op=="or":
                    if ssa_y==("const",0):
                        ssa[i]=(i,"orphan",ssa_x,("none",0))
                        ssa_replace(ssa,i,ssa_x)
                        triggered=True
                    elif ssa_y==("const",-1):
                        ssa[i]=(i,"orphan",ssa_y,("none",0))
                        ssa_replace(ssa,i,ssa_y)
                        triggered=True
        elif ssa_op=="xor":
            if ssa_x==ssa_y:
                ssa[i]=(i,"orphan",("const",0),("none",0))
                ssa_replace(ssa,i,("const",0))
                triggered=True
            elif ssa_y==("const",0):
                ssa[i]=(i,"orphan",ssa_x,("none",0))
                ssa_replace(ssa,i,ssa_x)
                triggered=True
            elif ssa_y==("const",-1):
                ssa[i]=(i,"invert",ssa_x,("none",0))
                ssa_replace(ssa,i,ssa_x)
                triggered=True

    return triggered

def ssa_commutative(ssa):
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        ssa_id,ssa_op,ssa_x,ssa_y=ssa[i]
        if ssa_op in "*+":
            pattern=ssa_types(ssa_x,ssa_y)
            if pattern==["ssa","const"]:
                _,i2=ssa_x
                ssa_id2,ssa_op2,ssa_x2,ssa_y2=ssa[i2]
                if ssa_op==ssa_op2:
                    pattern2=ssa_types(ssa_x2,ssa_y2)
                    if pattern2[1]=="const":
                        if pattern2[0] in ["initial","local_fetch","ssa"]:
                            values=ssa_values(ssa_x,ssa_y)
                            values2=ssa_values(ssa_x2,ssa_y2)
                            new_combined=add_ssa(ssa_op,ssa_x2,("const",values[1]+values2[1]))
                            ssa_replace(ssa,i,new_combined)
                            triggered=True
    #Start here - how to stop repeated creation?
    return False
    return triggered

def ssa_optimize_all(ssa):
    #Higher level IDs are new statements from optimizing
    global ssa_counter
    ssa_counter=1000

    #Optimize until SSA stabilizes
    triggered=True
    while triggered:
        triggered=False
        triggered|=ssa_fold_constants(ssa)
        triggered|=ssa_normalize(ssa)
        triggered|=ssa_identities(ssa)
        triggered|=ssa_commutative(ssa)
        #power_reduction
        #common_code
        #prune_orphans or just prune everything

initialize()
with open("results.txt","wt") as f:
    test_num=1
    for test in tests:
        test_name=f"Test {test_num}: {test}"
        f.write(f"{test_name}\n")
        f.write(f"{'='*len(test_name)}\n")

        #New stack and SSA list for testing
        init_test()

        #Create SSA
        abort=False
        for word in test.split():
            if word.isdigit() or (word[0]=='-' and word[1:].isdigit()):
                stack.append(("const",int(word)))
            else:
                if word.lower() in words:
                    func,opt=words[word.lower()]
                    result=func(stack)
                    if result==True:
                        f.write("- Error in primitive: "+error_msg)
                        f.write("- Aborting test\n\n")
                        abort=True
                        break
                else:
                    f.write(f"- Unknown: {word}\n")
                    f.write("- Aborting test\n\n")
                    abort=True
                    break

        #Stop current test if error above
        if abort==False:

            #Output SSA pre-optimization
            f.write("SSA before optimizing:\n")
            if len(ssa)==0:
                f.write("- None\n")
            else:
                ssa_ids=list(ssa.keys())
                ssa_ids.sort()
                for s in ssa_ids:
                    f.write(f"- {format_item(('ssa',s))}\n")
            f.write("\n")

            #Optimize SSA
            ssa_optimize_all(ssa)

            #Output SSA post-optimization
            f.write("SSA after optimizing:\n")
            if len(ssa)==0:
                f.write("- None\n")
            else:
                ssa_ids=list(ssa.keys())
                ssa_ids.sort()
                for s in ssa_ids:
                    f.write(f"- {format_item(('ssa',s))}\n")
            f.write("\n")


            #TODO: variable writes
            #Find values on stack to be written
            values={}
            for i,item in enumerate(stack):
                item_type,item_data=item
                if item_type=="initial" and item_data==i:
                    #Stack item in same place as start - nothing to do
                    pass
                else:
                    #Other value found - record for writing to stack
                    if item not in values:
                        values[item]=[]
                    values[item].append(i)

            #Final output
            f.write("Final output\n")

            #Write values back to stack
            for source,dests in values.items():
                source_type,source_data=source
                f.write(f"- load {format_item(source)}\n");
                    
                for dest in dests:
                    f.write(f"- store stack[{dest}]\n")

            #Adjust stack for output
            if len(stack)!=STACK_DEPTH:
                f.write(f"- SP+={str(len(stack)-STACK_DEPTH)}\n")

            #Done - ie not aborted above
            f.write("- Done\n\n");

        test_num+=1
        f.write("\n")
