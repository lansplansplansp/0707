#ifndef _SRC_H
#define _SRC_H

typedef enum YunSuan
{
    None,
    ADD,
    DEL,
    MUL,
    DIV,
    RES
}Operator;

typedef int (*opfun)(int,int);

Operator caltype(char op);
int myadd(int x,int y);
int mydel(int x,int y);
int mymul(int x,int y);
int mydiv(int x,int y);
int myres(int x,int y);

#endif
