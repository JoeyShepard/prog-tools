#!/usr/bin/env python3

#TODO
#Tests to HTML
#Python console on page

#TODO: DEFINITELY POSSIBLE TO GET INVERT ON ADD AND MINUS ON MULTIPLY
#- need test with all possibilities
#- (a+b)/c+(d+e)/c
#  - a b + c / d e + c / +
#  - S0=a b + , S1=S0 1/c *, S2=d e +, S3=S2 1/c *, S4=S1 S2 +
#    - at least for this, look one level down to simplify

#Constants
STACK_DEPTH=8
LOCALS_COUNT=3
ops_commutative=["+","*","and","or","xor"]

#Globals
stack=[]    #Symbolic stack
error_msg=""
words={}
ssa={}
ssa_counter=0
locals_gen=[]
tests=[
    #3x+2x???

    ("x x x x x x + + + + + 2 / x x + -","Testing ssa_replace: (x+x+x+x+x+x)/2-(x+x) -> 3*x-2*x"),

    ("y x * x / x /","Testing ssa_terms_multiply: y*x/x/x -> y/x"),
    ("y x / y * x *","Testing ssa_terms_multiply: y/x*y*x -> y*y"),

    ("y x * y * x *","Testing ssa_terms_multiply: y*x*y*x -> x*x*y*y"),
    ("y x * y * x /","Testing ssa_terms_multiply: y*x*y/x -> y*y"),
    ("y x * y / x *","Testing ssa_terms_multiply: y*x/y*x -> x*x"),
    ("y x * y / x /","Testing ssa_terms_multiply: y*x/y/x -> 1"),
    ("y x / y * x *","Testing ssa_terms_multiply: y/x*y*x -> y*y"),
    ("y x / y * x /","Testing ssa_terms_multiply: y/x*y/x -> 1/x*1/x*y*y"),
    ("y x / y / x *","Testing ssa_terms_multiply: y/x/y*x -> 1"),
    ("y x / y / x /","Testing ssa_terms_multiply: y/x/y/x -> 1/x*1/x"),

    #Empty list ie *0 or 1-1 or x/y*y or signs
    #- all paths for add and multiply
    #replace - neg and invert

    ("0 1 - 1 / 5 +","Testing ssa_terms_add: (0-1)/1+5 -> 4"),
    ("2 x * x 3 * *","Testing ssa_terms_multiply: (2*x)*(x*3) -> 6*x*x"),
    ("2 x + 3 x + +","Testing ssa_terms_add: (2+x)+(3+x) -> 5+2*x"),
    ("-3 x + x 3 + +","Testing ssa_terms_add: (-3+x)+(x+3) - > 2*x"),

    ("x 2 + y / x 3 + y / +",""),
    ("x x 5 + x 2 * + y - x + /",""),
    ("x x 5 * y / x * -",""),
    ("x x 5 * x / *",""),
    ("2 -3 - x DUP DUP - -",""),
    ("x x x x - DUP DUP - - - -",""),
    ("x 3 + 4 x + 5 6 * 7 x + + + + x -",""),

    #TODO: same as above for mult
    #TODO: mix + and *
    ("DUP",""),
    ("DROP",""),
    ("DUP DROP",""),
    ("OVER OVER DUP",""),
    ("SWAP",""),
    ("DUP SWAP DROP",""),
    ("2 3 SWAP",""),
    ("2 3 NIP",""),
    ("DUP AND DUP OR DUP XOR",""),
    ("x 0 AND x 0 OR x 0 XOR",""),
    ("x -1 AND x -1 OR x -1 XOR",""),
    ("2 - x - - 5 -",""),
    ("x 3 + x 4 + 5 6 * 7 x + + + +",""),
    ("x x",""),
    ("x 2 + x y + 2 +",""),
    ("x 1 - dup 1 +",""),
    ("1 x * x 0 * x 0 +",""),
    ("2 x 1 * + 3 +",""),
    ("x 1 + to_x",""),
    ("x 1 + to_x x",""),
    ]

class SSA_Class:
    def __init__(self,ssa_id,op,ssa_list,optimization=None):
        self.id=ssa_id
        self.op=op
        self.ssa_list=ssa_list
        self.optimization=optimization
        self.opt_list=[]

    def format(self):
        ret_val=f"SSA[{self.id}] ("
        first_arg=True
        for arg in self.ssa_list:
            if first_arg==False:
                ret_val+=f" {self.op} "
            else:
                first_arg=False
            if arg.type=="ssa":
                prefix=""
                if arg.negative==True:
                    prefix+="-"
                if arg.inverted==True:
                    prefix+="1/"
                ret_val+=f"{prefix}SSA[{arg.id}]"
            else:
                ret_val+=f"{arg.format()}"
        ret_val+=")"
        if self.optimization!=None:
            ret_val+=f" from {self.optimization}"
        return ret_val

    def sort(self):
        if self.op in ops_commutative:
            self.ssa_list=sorted(self.ssa_list)

    def opt_log(self,log):
        self.opt_list.append(log)

    def opt_clear(self):
        self.opt_list=[]


class ObjClass:
    def __init__(self,item_type,a1=None):
        self.type=item_type
        if self.type=="initial":
            self.id=a1
        elif self.type=="const":
            self.value=a1
        elif self.type=="local_fetch":
            self.id=a1
            if self.id!=None:
                self.gen=locals_gen[self.id]
                self.name="xyz"[self.id]
        elif self.type=="ssa":
            self.id=a1
        else:
            print(f"ObjClass.__init__: unknown item type '{item_type}'")
            print("Exiting...")
            exit(1)
        self.negative=False
        self.inverted=False

    def get_op(self):
        return ssa[self.id].op

    def get_ssa_list(self):
        return ssa[self.id].ssa_list

    def get_optimization(self):
        return ssa[self.id].optimization

    def get_const(self):
        total=self.value
        if self.inverted:
            if total==0:
                #TODO: divide by zero!
                total=1
            elif total==1:
                total=1
            else:
                #START HERE: not true for multiplication, ie 3*x*1/3
                total=0
        if self.negative:
            total=-total
        return total

    def copy(self):
        new_obj=ObjClass(self.type)
        if self.type=="initial":
            new_obj.id=self.id
        elif self.type=="const":
            new_obj.value=self.value
        elif self.type=="local_fetch":
            new_obj.id=self.id
            new_obj.gen=self.gen
            new_obj.name=self.name
        elif self.type=="ssa":
            new_obj.id=self.id
        new_obj.negative=self.negative
        new_obj.inverted=self.inverted
        return new_obj

    def negate(self):
        if self.type=="const":
            self.value*=-1
        else:
            self.negative=not self.negative

    def invert(self):
        self.inverted=not self.inverted

    def format(self):
        prefix=""
        if self.negative==True:
            prefix+="-"
        if self.inverted==True:
            prefix+="1/"
        if self.type=="initial":
            return f"{prefix}initial[{self.id}]"
        elif self.type=="const":
            return f"#{prefix}{self.value}"
        elif self.type=="local_fetch":
            return f"{prefix}{self.name}"
        elif self.type=="ssa":
            return f"{prefix}{ssa[self.id].format()}"
        else:
            print(f"ObjClass.format: unknown item type '{self.type}'")
            print("Exiting...")
            exit(1)

    #Defining __eq__ without __hash__ makes object unhashable
    #def __eq__(self,other):
    def equal(self,other):
        if self.type!=other.type:
            return False
        elif self.type=="initial":
            return self.id==other.id
        elif self.type=="const":
            return self.value==other.value
        elif self.type=="local_fetch":
            return self.id==other.id and self.gen==other.gen
        elif self.type=="ssa":
            #TODO: look at elements since may be sorted and combined
            return self.id==other.id

    #Less than operation for sorting
    def __lt__(self,other):
        types=["initial","const","local_fetch","ssa"]
        self_rank=types.index(self.type)
        other_rank=types.index(other.type)
        if self_rank==other_rank:
            if self.type=="initial":
                if self.id==other.id:
                    return self.inverted<other.inverted
                return self.id<other.id
            elif self.type=="const":
                return self.get_const()<other.get_const()
            elif self.type=="local_fetch":
                if self.id==other.id:
                    if self.gen==other.gen:
                        return self.inverted<other.inverted
                    return self.gen<other.gen
                return self.id<other.id
            elif self.type=="ssa":
                if self.id==other.id:
                    return self.inverted<other.inverted
                return self.id<other.id
        else:
            return self_rank<other_rank

    def __repr__(self):
        return self.format()

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
    words|={"-":(sub,None)}
    words|={"*":(mult,const_mult)}
    words|={"/":(div,None)}
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

    #Space for three test locals
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
            #TODO:
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
    t=stack.pop()
    stack.append(ssa_add("and",stack.pop(),t))

def const_and(x,y):
    return y & x

def forth_or(stack):
    t=stack.pop()
    stack.append(ssa_add("or",stack.pop(),t))

def const_or(x,y):
    return y | x

def forth_xor(stack):
    t=stack.pop()
    stack.append(ssa_add("xor",stack.pop(),t))

def const_xor(x,y):
    return y ^ x
    
def add(stack):
    t=stack.pop()
    stack.append(ssa_add("+",stack.pop(),t))

def const_add(x,y):
    return y + x

def sub(stack):
    t=stack.pop().copy()
    t.negate()
    stack.append(ssa_add("+",stack.pop(),t))

def mult(stack):
    t=stack.pop()
    stack.append(ssa_add("*",stack.pop(),t))

def const_mult(x,y):
    return y * x

def div(stack):
    t=stack.pop().copy()
    t.invert()
    stack.append(ssa_add("*",stack.pop(),t))

def fetch_x(stack):
    index=0
    stack.append(ObjClass("local_fetch",index))

def fetch_y(stack):
    index=1
    stack.append(ObjClass("local_fetch",index))

def fetch_z(stack):
    index=2
    stack.append(ObjClass("local_fetch",index))

def print_ssa(f):
    global ssa
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
    new_ssa=SSA_Class(ssa_counter,op,[x,y],optimization)
    ssa[ssa_counter]=new_ssa
    new_obj=ObjClass("ssa",ssa_counter)
    ssa_counter+=1
    return new_obj

#Old - for identities
def ssa_replace_old(index,replacement):
    global ssa
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

#TODO: take into account negative and inverted
def ssa_replace(index,replacement):
    #First, process SSA list
    global ssa
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        new_list=[]
        item=ssa[i]
        for arg in item.ssa_list:
            if arg.type=="ssa":
                if arg.id==index:
                    inverted=arg.inverted
                    negative=arg.negative
                    arg=replacement 
                    if inverted:
                        arg.inverted=not arg.inverted
                    if negative:
                        arg.negative=arg.negative

            new_list.append(arg)
        ssa[i].ssa_list=new_list

    #Next, values on stack
    global stack
    for i,item in enumerate(stack):
        if item.type=="ssa":
            if item.id==index:
                inverted=stack[i].inverted
                negative=stack[i].negative
                stack[i]=replacement 
                if inverted:
                    stack[i].inverted=not stack[i].inverted
                if negative:
                    stack[i].negative=stack[i].negative

#Collapse commutative SSAs - ((a+b)+c) -> (a+b+c)
def ssa_commutative():
    global ssa
    opt_name="commutative"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            if item.op in ["+","*"]:
                new_list=[]
                for element in item.ssa_list:
                    new_element=element
                    if element.type=="ssa":
                        if element.get_op()==item.op:
                            for e in element.get_ssa_list():
                                new_element=e.copy()
                                if element.negative:
                                    new_element.negate()
                                if element.inverted:
                                    new_element.invert()
                                new_list.append(new_element)
                            triggered=True
                            item.opt_clear()
                            new_element=None
                    if new_element!=None:
                        new_list.append(new_element)
                item.ssa_list=new_list
            item.opt_log(opt_name)
    return triggered

def ssa_sort():
    global ssa
    opt_name="sort"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            unsorted=False
            compare=item.ssa_list[0]
            for i in item.ssa_list[1:]:
                if i<compare:
                    unsorted=True
                    break
                compare=i
            if unsorted==True:
                item.opt_clear()
                item.sort()
                triggered=True
            item.opt_log(opt_name)
    return triggered

def ssa_terms_add():
    global ssa
    opt_name="terms_add"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            if item.op=="+":
                new_list=[]
                count=0
                total=0
                last_type=None
                last_id=None
                last_gen=None
                last_name=""
                last_inverted=None
                #TODO: add last item to new_list
                for element in item.ssa_list+[None]:
                    if element==None:
                        #Placeholder for end of loop - process last elements
                        new_item=True
                    else:
                        #Process elements
                        new_item=False
                        if element.type==last_type:
                            if element.type=="const":
                                total+=element.get_const()
                                triggered=True
                            elif element.type in ["initial","ssa","local_fetch"]:
                                new_item=True
                                if element.id==last_id and element.inverted==last_inverted:
                                    if element.type!="local_fetch" or (element.type=="local_fetch" and element.gen==last_gen and element.name==last_name):
                                        #Same term as before! Increase count
                                        if element.negative==False:
                                            count+=1
                                        else:
                                            count-=1
                                        new_item=False
                                        triggered=True
                        else:
                            #Different term type
                            new_item=True

                    if new_item==True:
                        #Process pending item
                        if last_type=="const":
                            if total==0:
                                #Constants totalled 0 - nothing to do
                                pass
                            else:
                                new_element=ObjClass(last_type,total)
                                new_list.append(new_element)
                        elif last_type in ["initial","ssa","local_fetch"]:
                            if count==0:
                                #Terms cancelled out 
                                pass
                            else:
                                new_element=ObjClass(last_type,last_id)
                                new_element.inverted=last_inverted
                                if last_type=="local_fetch":
                                    new_element.gen=last_gen
                                    new_element.name=last_name
                                if abs(count)==1:
                                    #Only one term - no coefficient
                                    new_element.negative=count<0
                                    new_list.append(new_element)
                                else:
                                    #Coefficient other than 0 or 1 - create new SSA
                                    new_ssa=ssa_add("*",ObjClass("const",count),new_element,opt_name)
                                    new_list.append(new_ssa)

                        #Keep track of newest item to compare to next item
                        if element==None:
                            #Placeholder value for end of loop - process pending elements only
                            pass
                        else:
                            if element.type=="const":
                                total=element.get_const()
                            elif element.type in ["initial","ssa","local_fetch"]:
                                count=1
                                last_id=element.id
                                last_inverted=element.inverted
                                if element.type=="local_fetch":
                                    last_gen=element.gen
                                    last_name=element.name
                            last_type=element.type

                if len(new_list)==0:
                    #All terms added up to 0
                    item.ssa_list=[ObjClass("const",0)]
                elif len(new_list)==1 and new_list[0].type=="ssa":
                    #SSA list contains one SSA item - replace instead of having list in list
                    ssa_replace(i,new_list[0])
                else:
                    item.ssa_list=new_list
            item.opt_log(opt_name)
    return triggered

def ssa_terms_multiply():
    global ssa
    opt_name="terms_multiply"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            if item.op=="*":
                new_list=[]
                count=0
                total=0
                negative=False
                last_type=None
                last_id=None
                last_gen=None
                last_name=""
                #TODO: add last item to new_list
                for element in item.ssa_list+[None]:
                    if element==None:
                        #Placeholder for end of loop - process last elements
                        new_item=True
                    else:
                        #Process elements
                        new_item=False
                        if element.type==last_type:
                            if element.type=="const":
                                total*=element.get_const()
                                triggered=True
                            elif element.type in ["initial","ssa","local_fetch"]:
                                new_item=True
                                if element.id==last_id:
                                    if element.type!="local_fetch" or (element.type=="local_fetch" and element.gen==last_gen and element.name==last_name):
                                        #Same term as before!
                                        if element.negative==True:
                                            negative=not negative
                                        if element.inverted==False:
                                            count+=1
                                        else:
                                            count-=1
                                        new_item=False
                                        triggered=True
                        else:
                            #Different term type
                            new_item=True

                    if new_item==True:
                        #Process pending item
                        if last_type=="const":
                            if total==0:
                                #Constants totalled 0 - term whole term is 0
                                ssa_replace(i,ObjClass("const",0))
                                break
                            elif abs(total)==1:
                                #Coefficient is 1 or -1 - eliminate
                                if total==-1:
                                    ssa[i].negative=not ssa[i].negative
                            else:
                                new_element=ObjClass(last_type,total)
                                new_list.append(new_element)
                        elif last_type in ["initial","ssa","local_fetch"]:
                            if count==0:
                                #Terms cancelled out 
                                pass
                            else:
                                new_element=ObjClass(last_type,last_id)
                                if count<0:
                                    new_element.inverted=True
                                if last_type=="local_fetch":
                                    new_element.gen=last_gen
                                    new_element.name=last_name

                                for j in range(abs(count)):
                                    new_list.append(new_element.copy())

                        #Keep track of newest item to compare to next item
                        if element==None:
                            #Placeholder value for end of loop - process pending elements only
                            pass
                        else:
                            if element.type=="const":
                                total=element.get_const()
                            elif element.type in ["initial","ssa","local_fetch"]:
                                if element.inverted==False:
                                    count=1
                                else:
                                    count=-1
                                last_id=element.id
                                if element.type=="local_fetch":
                                    last_gen=element.gen
                                    last_name=element.name
                            last_type=element.type
                        
                print(f"multiply: SSA{i} ({item.format()}) - {new_list}")


                if len(new_list)==0:
                    #Terms all cancel - equal to 1
                    ssa_replace(i,ObjClass("const",1))
                    #Also set for orphaned item for debugging
                    item.ssa_list=[ObjClass("const",1)]
                elif len(new_list)==1 and new_list[0].type=="ssa":
                    #SSA list contains one SSA item - replace instead of having list in list
                    ssa_replace(i,new_list[0])
                    #Also set for orphaned item for debugging
                        #Not checking if this also results in one item left since orphaned item not used
                    item.ssa_list=ssa[new_list[0].id].ssa_list
                else:
                    item.ssa_list=new_list

                print(f"- SSA{i} ({ssa[i].format()}, {item.format()})")
            item.opt_log(opt_name)
    return triggered

def ssa_simplify():
    global ssa
    opt_name="simplify"
    triggered=False
    ssa_ids=list(ssa.keys())
    ssa_ids.sort()
    for i in ssa_ids:
        item=ssa[i]
        if opt_name not in item.opt_list:
            if item.op=="+":
                new_list=[]
                count=0
                total=0
                arg=None
                for element in item.ssa_list:
                    add_list=True
                    if arg!=None and arg.type==element.type:
                        if element.type=="const":
                            total+=element.value
                            add_list=False
                        elif element.type in ["initial","ssa"]:
                            if arg.id==element.id:
                                add_list=False
                        elif element.type=="local_fetch":
                            if arg.id==element.id:
                                if arg.gen==element.gen:
                                    add_list=False
                    if add_list==False:
                        if element.negative==True:
                            count-=1
                        else:
                            count+=1
                        triggered=True
                    else:
                        if arg!=None:
                            if arg.type=="const":
                                new_list.append(ObjClass("const",total))
                            else:
                                if count==0:
                                    new_list.append(ObjClass("const",total))
                                else:
                                    #TODO: insert multiply then combine?
                                    temp=arg.copy()
                                    temp.negative=count<0
                                    for i in range(abs(count)):
                                        new_list.append(temp)
                        if element.type=="const":
                            total=element.value
                        else:
                            if element.negative==True:
                                count=-1
                            else:
                                count=1
                    arg=element
                if arg!=None:
                    if arg.type=="const":
                        new_list.append(ObjClass("const",total))
                    else:
                        if count==0:
                            new_list.append(ObjClass("const",total))
                        else:
                            temp=arg.copy()
                            temp.negative=count<0
                            for i in range(abs(count)):
                                new_list.append(temp)
                item.ssa_list=new_list
            item.opt_log(opt_name)
    return triggered

#TODO: assumes 2 args?
def ssa_identities():
    global ssa
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
                    ssa_replace(i,item.y)
                    triggered=True
            elif item.op=="*":
                if item.x.type=="const" and item.x.value==0:
                    ssa_replace(i,item.x)
                    triggered=True
                elif item.x.type=="const" and item.x.value==1:
                    ssa_replace(i,item.y)
                    triggered=True
            elif item.op in ["and","or"]:
                if item.x.equal(item.y):
                    ssa_replace(i,item.x)
                    triggered=True
                else:
                    if item.op=="and":
                        if item.x.type=="const" and item.x.value==0:
                            ssa_replace(i,item.x)
                            triggered=True
                        elif item.x.type=="const" and item.x.value==-1:
                            ssa_replace(i,item.y)
                            triggered=True
                    elif item.op=="or":
                        if item.x.type=="const" and item.x.value==0:
                            ssa_replace(i,item.y)
                            triggered=True
                        elif item.x.type=="const" and item.x.value==-1:
                            ssa_replace(i,item.x)
                            triggered=True
            elif item.op=="xor":
                if item.x.equal(item.y):
                    ssa_replace(i,ObjClass("const",0))
                    triggered=True
                elif item.x.type=="const" and item.x.value==0:
                    ssa_replace(i,item.y)
                    triggered=True
                #TODO: SSA with no y!
                #elif item.x.type=="const" and item.x.value==-1:
                #    ssa_replace(i,ssa_add("invert",item.y))
                #    triggered=True
    return triggered


def ssa_optimize_all():
    global ssa

    #TODO: used
    #Higher level IDs are new statements from optimizing
    global ssa_counter
    ssa_counter=1000

    #Optimize until SSA stabilizes
    triggered=True
    while triggered:
        triggered=False
        triggered|=ssa_commutative()
        triggered|=ssa_sort()
        triggered|=ssa_terms_add()
        triggered|=ssa_terms_multiply()
        #triggered|=ssa_simplify()
        #simplify should be several steps
            #combine similar terms
            #(a+b)*(a+b)
        #handle single values
        #triggered|=ssa_identities(ssa)
        #combine + and -
        #power_reduction
        #common_code
        #- see global/local value elimination
        #masking
        #review primitives

initialize()
with open("results.txt","wt") as f:
    test_num=1
    for test,description in tests:
        test_name=f"Test {test_num}: {test}"
        f.write(f"{test_name}\n")
        f.write(f"{'='*len(test_name)}\n")
        if description!="":
            f.write(f"({description})\n\n")

        print(f"Test {test_num}")


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
            print_ssa(f)

            #Optimize SSA
            ssa_optimize_all()

            #Stack after optimizing
            f.write("Stack after optimizing:\n")
            print_stack(f,stack)

            #Output SSA after optimizing
            f.write("SSA after optimizing:\n")
            print_ssa(f)

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
            f.write("Final output:\n")

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
