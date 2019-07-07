#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
    int nums;
    char names[20];
    char sex;
    int age;
}stu_t;
int main()
{
    FILE *fp = NULL;

    fp = fopen("data.c","wb+");
    if(NULL == fp)
    {
        printf("file not exist\n");
        return 1;
    }
#if 1
    int arr[10] = {12,23,4,65,76,456,754,9,56,987};
    fwrite(arr,sizeof(int),10,fp);
    fseek(fp,-1*sizeof(int)*5,SEEK_CUR);
    int x;
    fread(&x,sizeof(int),1,fp);	 //&x:*buffer(缓冲器),sizeof(int):size(每个数据的字节数),1:count(多少个数据项)
    printf("x = %d\n",x);
    fseek(fp,0,SEEK_END);           //光标移动至文档最后一位
#endif
#if 1
    stu_t stus[3] = {{1001,"abc",'F',22},
                     {1002,"xyz",'M',23},
                     {1003,"ABC",'M',44}
                    };
    fwrite(stus,sizeof(stu_t),3,fp);
    fseek(fp,-1*sizeof(stu_t)*2,SEEK_CUR);      //光标由后向前移动sizeof(stu_t)*2字节
    stu_t *p = (stu_t *)malloc(sizeof(stu_t));
    fread(p,sizeof(stu_t),1,fp);
    printf("mun:%d name:%ssex:%cage:%d\n",p->nums,p->names,p->sex,p->age);
    fseek(fp,0,SEEK_END);
#endif
    fseek(fp,-1*(sizeof(stu_t)*3),SEEK_CUR);
    int j;
    fseek(fp,-1*sizeof(int)*5,SEEK_CUR);
    fread(&j,sizeof(int),1,fp);
    printf("j:%d\n",j);

    fclose(fp);
    return 0;
}
