#!/usr/bin/env python3

#TODO
#Tests to HTML
#Python console on page


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
    #TODO: more organized tests
    #TODO: descriptions of tests
    "x 3 + 4 x + 5 6 * 7 x + + + +",
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

class ObjClass:
    def __init__(self,item_type,a1=None,a2=None,a3=None,a4=None,a5=None):
        self.type=item_type
        if self.type=="none":
            pass
        elif self.type=="initial":
            self.id=a1
        elif self.type=="const":
            self.value=a1
        elif self.type=="local_fetch":
            self.id=a1
            self.gen=locals_gen[self.id]
            self.name="xyz"[self.id]
        elif self.type=="ssa":
            self.id=a1
            self.op=a2
            self.x=a3
            self.y=a4
            self.optimization=a5
        else:
            print(f"ObjClass.__init__: unknown item type '{item_type}'")
            print("Exiting...")
            exit(1)

        self.opt_list=[]

    def types(self):
        if self.type=="ssa":
            return [self.x.type,self.y.type]
        else:
            return [None,None]

    def format(self):
        if self.type=="initial":
            return f"initial[{self.id}]"
        elif self.type=="const":
            return f"#{self.value}"
        elif self.type=="local_fetch":
            return f"{self.name}"
        elif self.type=="ssa":
            arg_text=[]
            for arg in [self.x,self.y]:
                if self.type==None:
                    pass
                else:
                    if arg.type=="ssa":
                        arg_text.append(f"SSA[{arg.id}]")
                    elif arg.type!="none":
                        arg_text.append(arg.format())
            
            ret_val=f"SSA[{self.id}]"
            if len(arg_text)==1:
                #Single argument like INVERT
                ret_val+=f" ({self.op} {arg_text[0]})"
            else:
                #Two arguments
                ret_val+=f" ({arg_text[1]} {self.op} {arg_text[0]})"
            if self.optimization!=None:
                ret_val+=f" from {self.optimization}"
            return ret_val
        else:
            print(f"ObjClass.format: unknown item type '{self.type}'")
            print("Exiting...")
            exit(1)

    def equal(self,other):
        if self.type!=other.type:
            return False
        elif self.type=="initial":
            return self.id==other.id
        elif self.type=="const":
            return self.value==other.value
        elif self.type=="local_feth":
            return self.id==other.id and self.gen==other.gen
        elif self.type=="ssa":
            return self.id==other.id

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

def init_test():
    #Fill stack with beginning values
    global stack
    stack=[]
    for i in range(STACK_DEPTH):
        stack.append(ObjClass("initial",i))

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

def print_stack(f,stack):
    started=False
    items=[]
    for i,item in enumerate(stack):
        if item.type=="initial" and item.id==i:
            if started==True:
                items.append(item)
        else:
            items.append(item)

    if len(items)==0:
        f.write("- Empty\n")
    else:
        counter=len(items)-1
        for item in items:
            f.write(f"- [{counter}]: {item.format()}\n")
            counter-=1
    f.write("\n")

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
    stack.append(ssa_add("and",stack.pop(),stack.pop()))

def const_and(x,y):
    return y & x

def forth_or(stack):
    stack.append(ssa_add("or",stack.pop(),stack.pop()))

def const_or(x,y):
    return y | x

def forth_xor(stack):
    stack.append(ssa_add("xor",stack.pop(),stack.pop()))

def const_xor(x,y):
    return y ^ x
    
def add(stack):
    stack.append(ssa_add("+",stack.pop(),stack.pop()))

def const_add(x,y):
    return y + x

def sub(stack):
    stack.append(ssa_add("-",stack.pop(),stack.pop()))

def const_sub(x,y):
    return y - x

def mult(stack):
    stack.append(ssa_add("*",stack.pop(),stack.pop()))

def const_mult(x,y):
    return y * x

def div(stack):
    stack.append(ssa_add("/",stack.pop(),stack.pop()))

def const_div(x,y):
    if x==0:
        x=1
    return int(y / x)

def fetch_x(stack):
    index=0
    stack.append(ObjClass("local_fetch",index))

def fetch_y(stack):
    index=1
    stack.append(ObjClass("local_fetch",index))

def fetch_z(stack):
    index=2
    stack.append(ObjClass("local_fetch",index))

def print_ssa(f,ssa):
    if len(ssa)==0:
        f.write("- None\n")
    else:
        ssa_ids=list(ssa.keys())
        ssa_ids.sort()
        for s in ssa_ids:
            f.write(f"- {ssa[s].format()}\n")
    f.write("\n")

def ssa_add(op,x,y,optimization=None):
    global ssa
    global ssa_counter
    new_ssa=ObjClass("ssa",ssa_counter,op,x,y,optimization)
    ssa[ssa_counter]=new_ssa
    ssa_counter+=1
    return new_ssa

def ssa_replace(ssa,index,replacement):
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        xy=[]
        for arg in [item.x,item.y]:
            if arg.type=="ssa":
                if arg.id==index:
                    arg=replacement 
            xy.append(arg)
        if xy!=[item.x,item.y]:
            ssa[i]=ObjClass("ssa",i,item.op,xy[0],xy[1])

def ssa_fold_constants(ssa):
    opt_name="fold_constants"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            item.opt_list.append(opt_name)
            if item.types()==["const","const"]:
                op,const_op=words[item.op]
                if const_op!=None:
                    #Replace all references with new constant
                    ssa_replace(ssa,i,ObjClass("const",const_op(item.x.value,item.y.value)))

                    #Found at least one fold
                    triggered=True

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
    opt_name="normalize"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            item.opt_list.append(opt_name)
            if item.op in ["*","+","-","and","or","xor"]:
                #Commutative - switch order if necessary
                arg_weights=[]
                arg_types=item.types()
                for arg in [item.x,item.y]:
                    if arg.type in weights:
                        arg_weights.append(weights[arg.type])
                    else:
                        arg_weights.append(weights["other"])

                if item.op=="-":
                    #Subtraction only commutative if subtracting constant
                    #TODO: also local? list should be in one place
                    if item.x.type=="const" and item.y.type in ["initial","ssa"]:
                        ssa_replace(ssa,i,ssa_add("+",ObjClass("const",-item.x.value),item.y,opt_name))
                        triggered=True
                else:
                    #All others ok to commute if neccesary
                    if arg_weights[0]>arg_weights[1]:
                        ssa_replace(ssa,i,ssa_add(item.op,item.y,item.x,opt_name))
                        triggered=True
    return triggered

#START HERE
    #Need second ssa_replace that creates new SSA for each occurance - NO!
    #Better than orphan? do need single value for ABS and INVERT unless remove
    #ie #30 in test 1 should not replace but instead create new SSA every time ssa[2] referenced
        #actually, not sure bc could do this for all of them but then count explodes

def ssa_identities(ssa):
    opt_name="identities"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            item.opt_list.append(opt_name)
            if item.op in ["+","-"]:
                if item.x.type=="const" and item.x.value==0:
                    ssa_replace(ssa,i,item.y)
                    triggered=True
            elif item.op=="*":
                if item.x.type=="const" and item.x.value==0:
                    ssa_replace(ssa,i,item.x)
                    triggered=True
                elif item.x.type=="const" and item.x.value==1:
                    ssa_replace(ssa,i,item.y)
                    triggered=True
            elif item.op in ["and","or"]:
                if item.x.equal(item.y):
                    ssa_replace(ssa,i,item.x)
                    triggered=True
                else:
                    if item.op=="and":
                        if item.x.type=="const" and item.x.value==0:
                            ssa_replace(ssa,i,item.x)
                            triggered=True
                        elif item.x.type=="const" and item.x.value==-1:
                            ssa_replace(ssa,i,item.y)
                            triggered=True
                    elif item.op=="or":
                        if item.x.type=="const" and item.x.value==0:
                            ssa_replace(ssa,i,item.y)
                            triggered=True
                        elif item.x.type=="const" and item.x.value==-1:
                            ssa_replace(ssa,i,item.x)
                            triggered=True
            elif item.op=="xor":
                if item.x.equal(item.y):
                    ssa_replace(ssa,i,ObjClass("const",0))
                    triggered=True
                elif item.x.type=="const" and item.x.value==0:
                    ssa_replace(ssa,i,item.y)
                    triggered=True
                #TODO: SSA with no y!
                #elif item.x.type=="const" and item.x.value==-1:
                #    ssa_replace(ssa,i,ssa_add("invert",item.y))
                #    triggered=True
    return triggered

def ssa_commutative(ssa):
    opt_name="commutative"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            item.opt_list.append(opt_name)
            if item.op in "*+":
                if item.types()==["const","ssa"]:
                    if item.op==item.y.op:
                        if item.y.x.type=="const":
                            #TODO: should be one list for all functions
                            if item.y.y.type in ["initial","local_fetch","ssa"]:
                                _,func_opt=words[item.op]
                                new_value=ObjClass("const",func_opt(item.x.value,item.y.x.value))
                                ssa_replace(ssa,i,ssa_add(item.op,new_value,item.y.y,opt_name))
                                triggered=True
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
        #commutative for local and initial
        #common_code
        #- see global/local value elimination
        #prune_orphans or just prune everything
        #masking
        #review primitives

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
                stack.append(ObjClass("const",int(word)))
            else:
                if word.lower() in words:
                    func,_=words[word.lower()]
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

            #Stack before optimizing
            f.write("Stack before optimizing:\n")
            print_stack(f,stack)
            
            #Output SSA before optimizing
            f.write("SSA before optimizing:\n")
            print_ssa(f,ssa)

            #Optimize SSA
            ssa_optimize_all(ssa)

            #Stack after optimizing
            f.write("Stack after optimizing:\n")
            print_stack(f,stack)

            #Output SSA after optimizing
            f.write("SSA after optimizing:\n")
            print_ssa(f,ssa)

            #TODO: variable writes
            #Find values on stack to be written
            values={}
            for i,item in enumerate(stack):
                if item.type=="initial" and item.id==i:
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
                f.write(f"- load {source.format()}\n");
                    
                for dest in dests:
                    f.write(f"- store stack[{dest}]\n")

            #Adjust stack for output
            if len(stack)!=STACK_DEPTH:
                f.write(f"- SP+={str(len(stack)-STACK_DEPTH)}\n")

            #Done - ie not aborted above
            f.write("- Done\n\n");

        test_num+=1
        f.write("\n")
