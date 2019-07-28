#include<stdio.h>

int main()
{
    FILE *fp = NULL;
    fp = fopen("1fscanf_scanf.c","r");
    if(NULL == fp)
    {
        printf("file not exist\n");
        return 1;
    }
    char ch;
    int ret;
    while(1){
        printf("before:%ld  ",ftell(fp));
        ret = fscanf(fp,"%c",&ch);
        printf("afer:%ld  ",ftell(fp));
        if(ret == EOF)
            break;
        rewind(fp);
        fprintf(stdout,"%c\n",ch);
    }
    fclose(fp);
    return 0;
}
