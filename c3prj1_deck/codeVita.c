#inlcude <bits/stdc++. h>
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
	}while(index< N && Rank[index]<Rank[index+1);
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
    Comp comp[testCases];
    cin >> testCases;
    for(intSize i= 0; i< testCases; i++)
      {
	cin >> comp[i]->numOfEmplyes;
	comp[i]->rankOfEmployes = new intSize[comp[i]->numOfEmployes];
	for(intSize h= 0; j< comp[i]->numOfEmplyes; j++)
	  cin >> comp[i]->rankOfEmployes[j];
      }
    for(intSize i= 0; i< testCases; i++)
      printf("%d\n",getMin(comp[i]->rankOfEmployes, comp[i]->numOfEmployes));
  }
