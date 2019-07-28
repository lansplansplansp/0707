#include<stdio.h>
#include<string.h>
#include "queue.h"

int main()
{
    FILE *fp1 = fopen("mingwen.txt","r");
    FILE *fp2 = fopen("miyao.txt","r");
    FILE *fp3 = fopen("miwen.txt","w");

    if(fp1 == NULL)
    {
        printf("mingwen.txt not exist\n");
        return 1;
    }
    if(fp2 == NULL)
    {
        printf("miyao.txt not exist\n");
        return 1;
    }
    if(fp3 == NULL)
    {
        printf("miwen.txt not exist\n");
        return 1;
    }

    queue_t *qhead = NULL;
    qhead = queue_init();
    char ch = '1';
    int ret;
    while(ch)
    {
        ret = fscanf(fp2,"%c",&ch);
        if(ret == EOF)
            break;
        if(ch=='\n')
        {
            ch = '\0';
            break;
        }
        enqueue(qhead,ch);
    }
    display(qhead);
    char mingwen[1024];
    char miwen[1024];
    int k,i=0;
    while(fgets(mingwen,1024,fp1)!=NULL)
    {
        i = 0;
        while(mingwen[i]!='\0')
        {
            if(mingwen[i] == '\n')
                break;
            ch = dequeue(qhead);
            if(ch>='0' && ch<='9')
                k = ch-'0';
            if(ch>='a' && ch<='z')
                k = ch-'a';
            if(ch>='A' && ch<='Z')
                k = ch-'A';
            miwen[i] = mingwen[i] + k;
            printf("%c\t%d+%c(%d)=\n",ch,k,mingwen[i],mingwen[i]);
            printf("%c(%d)\n",miwen[i],miwen[i]);
            i++;
            enqueue(qhead,ch);
        }
        fputs(miwen,fp3);
    }

    return 0;
}
