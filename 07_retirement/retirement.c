#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

/* Calculates the new balance for a month */
double calculateBalance(double balance, double contribution, double rate_of_return) {
  balance = balance * (1 + rate_of_return/(12 * 100)) + contribution;
  return balance;
}

/* Calculates the balance for each month and prints it out.
   Return the final balance for the whole period */
double calculatePeriod(int currentAge, double currentBalance, int currentMonth, retire_info info){
  double balance = currentBalance;
  int month = currentMonth;
  int age = currentAge;
  for(int i = 0; i < info.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", age/12, month, balance);
    balance = calculateBalance(balance, info.contribution, info.rate_of_return);
    month++;
    if(month == 12) {
      month = 0;
    }
    age++;
  }
  return balance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  // Determine the current month in a year out of the startAge
  int month = startAge % 12;
  double balance = initial;
  
  // Calculate the balance for the working period
  balance = calculatePeriod(startAge, balance, month, working);
  month = (month + working.months) % 12;
  // Calculate the balance for the retired period
  balance = calculatePeriod(startAge + working.months, balance, month, retired);  
}

int main(void){
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 4.5;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 1.0;

  retirement(327, 21345, working, retired);  
  
  return EXIT_SUCCESS;
}
