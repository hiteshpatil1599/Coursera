#include<iostream>
#include<stdio.h>
using namespace std;

#define intSize long int

intSize getMin(intSize* Rank, intSize N)
{
  intSize MaxCount= 0;
  intSize count;
  intSize index= 0;

  count= 1;
  while(index< N)
    {
      count=1 ;
      do
	{
	  index++;
	  MaxCount+= count;
	  count++ ;
	}while(index< N && Rank[index]<Rank[index+1]);
	    }
      return MaxCount;
    }
  typedef struct
  {
    intSize numOfEmployes;
    intSize* rankOfEmployes;
  }Comp;
  
  int main()
  {
    intSize testCases;
    cin>> testCases;
    Comp* comp= new Comp[testCases];
    for(intSize i= 0; i< testCases; i++)
      {
	cin>> comp[i].numOfEmployes;
	comp[i].rankOfEmployes = new intSize[comp[i].numOfEmployes];
	for(intSize j= 0; j< comp[i].numOfEmployes; j++)
	  cin >> comp[i].rankOfEmployes[j];
      }
    for(intSize i= 0; i< testCases; i++)
      printf("%ld\n",getMin(comp[i].rankOfEmployes, comp[i].numOfEmployes));
  }
