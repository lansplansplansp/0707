#include<stdio.h>
#include<time.h>

int main()
{  
   srand(time(NULL));
   int a[10];
   int *p;
   int min=100;
   for(p=&a[0];p<=&a[9];p++){
      *p=rand()%100;
      printf("%4d,",*p);
      if(*p<min){
         min=*p;
      }
   } 
   printf("\n");
   printf("%d\n",min);
   return 0;
}
