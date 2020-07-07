#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value>=2);
  assert(c.value<=VALUE_ACE);
  // assert(c.suit>=SPADES);
  assert(c.suit<=CLUBS);

}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r)
    {
    case STRAIGHT_FLUSH:return "STRAIGHT_FLUSH";
    case FOUR_OF_A_KIND:return "FOUR_OF_A_KIND";
    case FULL_HOUSE:return "FULL_HOUSE";
    case FLUSH:return "FLUSH";
    case STRAIGHT:return "STRAIGHT";
    case THREE_OF_A_KIND:return "THREE_OF_A_KIND";
    case TWO_PAIR:return "TWO_PAIR";
    case PAIR:return "PAIR";
    case NOTHING:return "NOTHING";
    }
  return "";
}

char value_letter(card_t c) {
  switch(c.value)
    {
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return '0';
    case 11: return 'J';
    case 12: return 'Q';
    case 13: return 'K';
    case 14: return 'A';
    }
  return 'x';
}


char suit_letter(card_t c) {
  switch(c.suit)
    {
    case SPADES:return 's';
    case HEARTS:return 'h';
    case DIAMONDS:return 'd';
    case CLUBS:return 'c';
    default:return '?';
    }
  return '?';
}

void print_card(card_t c)
{
  switch(c.value)
    {
    case 2:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case 3:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case 4:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case 5:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case 6:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case 7:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case 8:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case 9:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case 10:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case VALUE_ACE:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case VALUE_KING:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case VALUE_QUEEN:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    case VALUE_JACK:
      printf("%c%c",value_letter(c),suit_letter(c));
      break;
    }
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  switch(value_let)
    {
    case 'A':temp.value=14;
    case 'K':temp.value=13;
    case 'Q':temp.value=12;
    case 'J':temp.value=11;
    case '2':temp.value=2;
    case '3':temp.value=3;
    case '4':temp.value=4;
    case '5':temp.value=5;
    case '6':temp.value=6;
    case '7':temp.value=7;
    case '8':temp.value=8;
    case '9':temp.value=9;
    case '0':temp.value=10;
    }
  switch(suit_let)
    {
    case 's':temp.suit=0;
    case 'h':temp.suit=1;
    case 'd':temp.suit=2;
    case 'c':temp.suit=3;
    }
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  int value;
  assert(c<52);
  value = c%13;
  temp.suit = c/13;
  switch(value)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
      temp.value = value+1;
      break;
    case 0:
      temp.value = 14;
      break;
    }
  return temp;
}
