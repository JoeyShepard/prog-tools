int foo_tail(int x,int (*func)(int))
{
    if (x>1000000) return x;
    else __attribute__((musttail)) return func(x+1);
}
