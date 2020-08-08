#include<stdio.h>
#include<stdlib.h>
#include"power.c"

//unsigned power(unsigned, unsigned);

int main()
{
  if(power(0,0)!=1){/*printf("power1\n")*/;return EXIT_FAILURE;}//3
  if(power(1,0)!=1){/*printf("power2\n")*/;return EXIT_FAILURE;}//2
  if(power(1,1)!=1){/*printf("power3\n")*/;return EXIT_FAILURE;}//6,7,9
  if(power(2,1)!=2){/*printf("power4\n")*/;return EXIT_FAILURE;}//1
  if(power(5,2)!=25){/*printf("power5\n")*/;return EXIT_FAILURE;}//8,5,10
  if(power(-1,1)!=-1){/*printf("power6\n")*/;return EXIT_FAILURE;}//
  return EXIT_SUCCESS;
}
