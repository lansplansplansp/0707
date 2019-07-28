#include<stdio.h>
#include "src.h"

int main()
{
    opfun opf;
    int x,y;
    char op;
    while(1)
    {
        printf("please input your calculation problem:\n");
        scanf("%d%c%d",&x,&op,&y);
        switch(caltype(op))
        {
            case ADD:
                opf = myadd;
                break;
            case DEL:
                opf = mydel;
                break;
            case MUL:
                opf = mymul;
                break;
            case DIV:
                opf = mydiv;
                break;
            case RES:
                opf = myres;
                break;
            default:
                opf = NULL;
                break;
        }
        if(NULL != opf)
            printf("%d\t%c\t%d\t=\t%d\n",x,op,y,opf(x,y));
    }
    return 0;
}
