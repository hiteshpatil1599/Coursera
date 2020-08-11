#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
  clock_t start, end;
  double total;
  start= clock();
  for(int n= 0; n< 52; n++)
    { 
      srand(clock());
      printf("%d ",(int)random()%52);
    }
  end= clock();
  total= (end-start)/(float)CLOCKS_PER_SEC;
  printf("\nTime in sex :%f\n",total);
}
