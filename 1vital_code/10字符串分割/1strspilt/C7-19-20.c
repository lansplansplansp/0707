#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char ** mysplit(char *pstr, int *pac);
int main()
{
    char str[100];
    gets(str);
    char **arr;
    int ac=0;
    arr	= mysplit(str, ac);
    int j;
    for(j=0; j<ac; j++)
        printf("av[%d]=%s\n", j, arr[j]);
    //先释放元素指针指向的空间
    int i;
    for(i=0; i<ac; i++)
    {
        free(arr[i]);
    }
    //再释放指针数组
    free(arr);
    return 0;
}
char ** mysplit(char *pstr, int *pac)
{
    // char *strtok_r(char *str, const char *delim, char **saveptr);
    char **arr=NULL;
    char *pos=NULL;
    char *res;
    res = strtok_r(pstr, ",", &pos);
    arr = (char **)realloc(arr, (*pac +1) * sizeof(char *));
    arr[*pac] = strdup(res);
    (*pac)++;

    while( (res = strtok_r(NULL,",", &pos )) != NULL)
    {
        arr = (char **)realloc(arr, (*pac +1) * sizeof(char *));
        arr[*pac] = strdup(res);
        (*pac)++;
    }
    return arr;
}
