#include<stdio.h>
#include<stdlib.h>

struct _ret_info
{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct ret_info retire_info;

void printDet(int year, int month, double balance){
   printf("Age %3d month %2d you have $%.2lf\n",year, month, balance) ;
}

void retirement (int startAge, double initial,
		 retire_info working, retire_info retired) {
  int temp = 0;
  while(temp < working.months){
    int rem = (startAge+temp)%12 ;
    int year = (startAge+temp-rem)/12 ;
    printDet(year, rem, initial) ;
    initial += (initial*working.rate_of_return) + working.contribution ;
    temp++ ;
  }
  startAge += temp ;
  temp = 0 ;
  while(temp < retired.months){
    int rem = (startAge+temp)%12 ;
    int year = (startAge+temp-rem)/12 ;
    printDet(year, rem, initial) ;
    initial += (initial*retired.rate_of_return) + retired.contribution ;
    temp++ ;
  }  
}

int main (void){
  double initial = 21345 ;
  int startAge = 327 ;
  retire_info retired;
  retire_info working;
  working.months = 489 ;
  working.contribution = 1000 ;
  working.rate_of_return = 0.045/12 ;
  retired.months = 384 ;
  retired.contribution = -4000 ;
  retired.rate_of_return = 0.01/12 ;
  retirement (startAge, initial, working, retired);
  return 0;
}
