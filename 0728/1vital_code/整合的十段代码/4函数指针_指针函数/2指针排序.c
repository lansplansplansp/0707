#include<stdio.h>

void input(void);
void print(void);
void sort(void);

int g_array[10];

int main()
{
    input();
    print();
    sort();
    print();

   return 0;
}
void input(void)
{	
    int i;

    for(i=0;i<10;i++){
        g_array[i]=rand()%100;
    }
}
void print(void)
{
   int *p=g_array;
   int i=0;
   while(i++<10){
        printf("%4d,",*(p+i));
   }
   printf("\n");
}
void sort(void)
{
    int *p=g_array;
    int i,j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){

        }
        if(*(p+i)<g_array[i+1]){
            *(p+i)=g_array[i+1];
        }
    }
}

