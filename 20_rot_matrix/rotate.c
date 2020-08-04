//#include<stdio.h>
//#include<stdlib.h>

void rotate(char matrix[10][10])
{
  int temp[10][10];
  int col;
  for(int i= 0;i< 10;i++)
    {
      col= 9-i;
      for(int j=0;j< 10;j++)
	{
	  temp[j][col]= matrix[i][j];
	}
    }
  for(int i= 0;i< 10;i++)
    {
      for(int j=0;j< 10;j++)
	{
	  matrix[i][j]= temp[i][j];
	}
    }

}
