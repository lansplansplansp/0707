#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char str[6][20] = {"beijing", "shanghai", "hangzhou", "nanjing", "yiwu", "shaoxing"};
    int len = 6;
    //先定义指针数组--				每个元素都是指针，一个6个
    char **sa = (char **)malloc(sizeof(char *) * len);
    //其次给每个指针分配空间，并赋值
    int i;
    for(i=0; i<len; i++)
    {
        sa[i] = (char *)malloc(strlen(str[i])+1); // 先开辟空间
        strcpy(sa[i], str[i]);	//再拷贝数值
    }
    //测试结果
    for(i=0; i<len; i++)
    {
        printf("%s , %s\n", sa[i], str[i]);
    }
    //先释放元素指针指向的空间
    for(i=0; i<len; i++)
    {
        free(sa[i]);
    }
    //再释放指针数组
    free(sa);
    return 0;
}
