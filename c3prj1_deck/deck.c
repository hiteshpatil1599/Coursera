#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include <time.h>
#include "deck.h"

void print_hand(deck_t * hand){

  for(int n=0; n<hand->n_cards; n++)
    {
      print_card(**((hand->cards)+n));
      printf(" ");
    }
}

int deck_contains(deck_t * d, card_t c) {
  int n= 0;
  for(;n< d->n_cards;n++)
    if((**((d->cards)+n)).value == c.value && (**(d->cards+n)).suit == c.suit)
      return 1;
  return 0;
}

void shuffle(deck_t * d){
  int n= 0,newPos;
  card_t *temp;
  int Num= d->n_cards;
  for(;n< Num;n++)
    {
      //srand(clock());
      newPos= random()%Num;
      temp= d->cards[n];
      d->cards[n]= d->cards[newPos];
      d->cards[newPos]= temp;
    }
}

void assert_full_deck(deck_t * d) {
  for(int n= 0; n< d->n_cards; n++)
    {
      assert_card_valid(**(d->cards+n));
      assert(deck_contains(d,card_from_num(n)));
    }
}
