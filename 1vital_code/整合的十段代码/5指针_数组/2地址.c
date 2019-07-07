#include<stdio.h>
#include<string.h>

int main()
{
#if 0
    char str1[] = "abc";
    char str2[] = "abc";

    const char str3[] = "abc";
    const char str4[] = "abc";

    const char *str5 = "abc";
    const char *str6 = "abc";

    char *str7 = "abc";
    char *str8 = "abc";

    printf("%d\n", ( str1 == str2 ));//0
    printf("%d\n", ( str3 == str4 ));//0
    printf("%d\n", ( str5 == str6 ));//1
    printf("%d\n", ( str7 == str8 ));//1
#endif

    char str1[6]={'h','e','l','l','o','\0'};
    char str2[]="hello";
    char *p="hello";

    str1[0]='H';
    str1[4]='0';
    str1[5]='x';//warming//²»»á¾¯¸æ°¡
    str2[0]='L';
    //p[0]='H';//bus erorr:10

//    printf("please input a string p;\n");
//    scanf("%s",p);//bus erorr:10
//    printf("please input a string str1;\n");
//    scanf("%s",str1);
    printf("str1:%s\n",str1);
    printf("str2:%s\n",str2);
    printf("sizeof(str1)=%lu\n",sizeof(str1));
    printf("sizeof(str2)=%lu\n",sizeof(str2));
    printf("sizeof(p)=%lu\n",sizeof(p));
    printf("strlen(p)=%lu\n",strlen(p));
    printf("strlen(str1)=%lu\n",strlen(str1));
    return 0;
}
