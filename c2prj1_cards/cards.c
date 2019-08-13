#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);  
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  char *c;
  switch(r){
  case  STRAIGHT_FLUSH: c = "Five cards of the same suit that are also sequentially ordered"; break;
  case  FOUR_OF_A_KIND: c = "Four cards of the same value"; break;
  case  FULL_HOUSE: c = "Three cards of one value and a pair of another value"; break;
  case  FLUSH: c = "Five cards of the same suit"; break;
  case  STRAIGHT: c = "Five cards such that the cards are sequentially ordered"; break;
  case  THREE_OF_A_KIND: c = "Three cards of the same value"; break;
  case  TWO_PAIR: c = "Two times two cards of the same value"; break;
  case  PAIR: c = "Two cards of the same value"; break;
  case  NOTHING: c = ""; break;    
  }
  return c;
}

/* Returns the character that textually represents the value of the passed-in card */
char value_letter(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);

  char letter;
  if (c.value >= 2 && c.value <= 9){
    letter = c.value + '0';
  } else {
      switch(c.value){
        case 10: letter = 'O'; break;
        case 11: letter = 'J'; break;
        case 12: letter = 'Q'; break;
        case 13: letter = 'K'; break;
        case 14: letter = 'A'; break;
      }
  }
  return letter;
}

/* Returns the letter that textually represents the suit of the card passed in */
char suit_letter(card_t c) {
  assert(c.suit >= 0 && c.suit <= 3);
  
  char letter;
  switch(c.suit) {
    case 0: letter = 's'; break;
    case 1: letter = 'h'; break;
    case 2: letter = 'd'; break;
    case 3: letter = 'c'; break;
    case 4: letter = '\0'; break;      
  }
  return letter;
}

/* Prints out the textual representation of the card (Value first then suit) */
void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

/* Returns a card_t whose value and suit correspond to the letters passed in */
card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if (value_let >= '2' && value_let <= '9') {
    temp.value = value_let - '0';
  } else {
    switch(value_let) {
      case 'O': temp.value = 0; break;
      case 'J': temp.value = 11; break;
      case 'Q': temp.value = 12; break;
      case 'K': temp.value = 13; break;
      case 'A': temp.value = 14; break;
      default: temp.value = '\0';
    }
  }

  switch(suit_let) {
    case 's': temp.suit = SPADES; break;
    case 'h': temp.suit = HEARTS; break;
    case 'd': temp.suit = DIAMONDS; break;
    case 'c': temp.suit = CLUBS; break;
  }
  
  //assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  int division_value = c/13;
  switch (division_value) {
    case 3: temp.suit = SPADES; break;
    case 2: temp.suit = HEARTS; break;
    case 1: temp.suit = DIAMONDS; break;
    case 0: temp.suit = CLUBS; break;      
  }
  temp.value = c%13 + 2;
  assert_card_valid(temp);
  return temp;
}
