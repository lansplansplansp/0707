#include<stdio.h>

//四种写法表示函数传数组
//void disp_array(int array[])
//void disp_array(int* array)
//void disp_array(int *array)
void disp_array(int array[5])
{
    printf("array:%d\n",sizeof(array));
    printf("%p\n",array);
    int i;
    int *p = array;
    for(i=0;i<5;i++)
        printf("array[%d] = %d\n",i,p[i]);
}
int main()
{
    int array[5] = {1,2,3,4,5};
    printf("array:%d\n",sizeof(array));
    printf("%p\n",array);
    disp_array(array);
    return 0;
}
#endif
