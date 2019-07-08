#include "src.h"

int myadd(int x,int y)
{
    return x+y;
}
int mydel(int x,int y)
{
    return x-y;
}
int mymul(int x,int y)
{
    return x*y;
}
int mydiv(int x,int y)
{
    if(y!=0)
        return x/y;
    else
        return 0;
}
int myres(int x,int y)
{
    return x%y;
}
Operator caltype(char op)
{
    if(op == '+')
        return ADD;
    else if(op == '-')
        return DEL;
    else if(op == '*')
        return MUL;
    else if(op == '/')
        return DIV;
    else if(op == '%')
        return RES;
    else
        return None;
}
