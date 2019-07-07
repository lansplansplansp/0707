#include<stdio.h>
#include<string.h>//strtok_r();

int mysplit(char *pstr,char av[][20])
{
    // char *strtok_r(char *str, const char *delim, char **saveptr);
    char *pos = NULL;
    char *res;
    int i=0;
    res = strtok_r(pstr,",",&pos);//返回指针；
    //av[i++] = res;
    strcpy(av[i++],res);//<==>av[i++]=res 但是不能这样写；
    while((res = strtok_r(NULL,",",&pos))!=NULL)
        //av[i++] = res;
         strcpy(av[i++],res);
    return i;
}
int main()
{
    char str[100];
    gets(str);
    char arr[10][20];
    int ac;
    ac = mysplit(str,arr);
    int j;
    for(j=0;j<ac;j++)
    printf("av[%d]=%s\n",j,arr[j]);
    int max=0;
    int maxindex;
    for(j=0;j<ac;j++)
    {
        if(strlen(arr[j])>max)
        {
            max = strlen(arr[j]);
            maxindex = j;
        }
    }
    printf("the max string is %s\n",arr[maxindex]);
    return 0;
}
