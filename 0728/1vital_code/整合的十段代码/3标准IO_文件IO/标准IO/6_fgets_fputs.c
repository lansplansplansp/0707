#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    FILE *fp = NULL;

    fp = fopen("6_fgets_fputs.c","r");
    if(fp == NULL)
    {
        printf("file not exist\n");
        return 1;
    }
    char line[1024];
    char *pline;
#if 1
    while(1){
        pline = fgets(line,1023,fp);
        if(pline == NULL)
            break;
    fputs(line,stdout);
// 		printf("%s",line);
    }
#endif 	
#if 0
    fgets(line,1023,fp);
    printf("%s",line);
    line[strlen(line)-1] = '\0';
    printf("%s",line);
#endif 
    fclose(fp);
    return 0;
}
