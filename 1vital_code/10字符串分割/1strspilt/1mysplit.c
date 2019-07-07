#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **mysplit(char *str,int *pac);

int main()
{
    char str[100];
    scanf("%s",str);
    char **av;
    int ac;
    av = mysplit(str,&ac);
    int i;
    for(i=0;i<ac;i++)
    {
        printf("av[%d]:%s\n",i,av[i]);
    }
    for(i=0;i<ac;i++)
    {
        free(av[i]);
    }
    free(av);
    return 0;
}

char **mysplit(char *str,int *pac)
{
    char **av = NULL;
    char *pos = NULL;
    char *res = NULL;
    res = strtok_r(str,",",&pos);
    av = (char **)realloc(av,(*pac+1)*sizeof(char *));
    av[*pac] = strdup(res);
    (*pac)++;
    while((res = strtok_r(NULL,",",&pos))!=NULL)
    {
        av = (char **)realloc(av,(*pac+1)*sizeof(char *));
        av[*pac] = strdup(res);
        (*pac)++;
    }
    return av;
}

