#include<stdio.h>
#include<stdlib.h>
//#include"maxSeq.c"
size_t maxSeq(int*, size_t);

int main()
{
  int array1[] = {23, 23};
  int array2[] = {};
  int array3[] = {-1, 0, 1, 6, 8};
  int array4[] = {1, 2, 2, 5, 6, 98};
  int array5[] = {1, 2, 4, 4, 6 ,10};
  if(maxSeq(array1,2)!= 1){printf("array1\n"); return EXIT_FAILURE;}
  //11
  //1
  if(maxSeq(array2,0)!= 0){printf("array2\n"); return EXIT_FAILURE;}
  if(maxSeq(array3,5)!= 5){printf("array3\n"); return EXIT_FAILURE;}
  //10
  //2
  if(maxSeq(array4,6)!= 4){printf("array4\n"); return EXIT_FAILURE;}
  if(maxSeq(array5,6)!= 3){printf("array5\n");return EXIT_FAILURE;}
  //3
  return EXIT_SUCCESS;
}
