#include<stdio.h>

size_t maxSeq(int* array, size_t n)
{
  size_t i, j, count, maxCount=0;
  i=0;
  while(i<n)
    {
      j= i+1;
      count= 1;
      while(j< n && array[j]>array[i])
	{
	  j++;
	  i++;
	  count++;
	}
      if(count> maxCount)
	{
	  maxCount =count;
	}
      i++;
    }
  return maxCount;
}
