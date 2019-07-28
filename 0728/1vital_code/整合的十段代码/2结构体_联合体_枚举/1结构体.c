#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NUMBER 5
struct vote
{
    char *name;
    int count;
};
typedef struct vote vote_t;
typedef struct vote *pvote;
void init_info(vote_t votes[],int len)
{
    int i;
    char name[32];
    for(i=0;i<len;i++)
    {
        scanf("%s",name);
        votes[i].name = (char *)malloc(strlen(name+1));
        strcpy(votes[i].name, name);
    }
}
void toupiao(vote_t votes[],int len)
{
    char name[32];
    int i;
    while(1)
    {
        scanf("%s",name);
        if(strcmp("exit",name) == 0)
                break;
        for(i=0;i<len;i++)
        {
            if(strcmp(name,votes[i].name)==0)
            {
                votes[i].count += 1;
                break;
            }
        }
    }
}
void show_info(pvote ss, int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        printf("%s -> %d\n",ss->name,ss->count);
        ss++;
    }
}
void destory_info(pvote ss ,int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        free(ss->name);
        ss++;
    }
}
int main()
{
    vote_t votes[NUMBER];
    memset(votes,0,sizeof(vote_t)*NUMBER);
    init_info(votes,NUMBER);
    toupiao(votes,NUMBER);
    show_info(votes,NUMBER);
    destory_info(votes,NUMBER);
    return 0;
}
