#include<stdio.h>
#include "cards.h"

int main(void) {
  card_t firstCard;
  int temp=0;
  for(int i=0;i<4;i++)
    {
      for(int j=2;j<15;j++)
	{
	  firstCard.value = j;
	  firstCard.suit = i;
	  assert_card_valid(firstCard);
	  print_card(firstCard);
	  printf(" ");
	}
      printf("\n");
    }
  while(temp<52)
    {
      firstCard = card_from_num(temp);
      assert_card_valid(firstCard);
      print_card(firstCard);
      if(temp%13)
	printf(" ");
      else
	printf("\n");
      temp++;
    }
  firstCard = card_from_letters('A', 's');
  print_card(firstCard);
  return 0;
}
