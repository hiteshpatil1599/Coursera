#include "cards.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_assert_card_valid() {
  card_t new_card;
  new_card.value = VALUE_KING;
  new_card.suit = CLUBS;

  assert_card_valid(new_card);

  new_card.value = 2;
  new_card.suit = SPADES;

  assert_card_valid(new_card);
}

void test_ranking_to_string() {
  assert(strcmp(ranking_to_string(PAIR), "Two cards of the same value") == 0);
  assert(strcmp(ranking_to_string(STRAIGHT), "Five cards such that the cards are sequentially ordered") == 0);
  assert(strcmp(ranking_to_string(NOTHING), "") == 0);
}

void test_value_letter() {
  card_t new_card;
  new_card.value = VALUE_KING;
  new_card.suit = CLUBS;

  assert(value_letter(new_card) == 'K');

  new_card.value = 10;
  assert(value_letter(new_card) == 'O');  

  new_card.value = 5;
  new_card.suit = HEARTS;

  assert(value_letter(new_card) == '5');  
}

void test_suit_letter() {
  card_t new_card;
  new_card.value = VALUE_KING;
  new_card.suit = CLUBS;
  
  assert(suit_letter(new_card) == 'c');

  new_card.suit = SPADES;
  assert(suit_letter(new_card) == 's');
}

void test_print_card() {
  card_t new_card;
  new_card.value = VALUE_JACK;
  new_card.suit = DIAMONDS;

  printf("Printed card should be Jd and is ");
  print_card(new_card);
  printf("\n");

  new_card.value = 8;
  new_card.suit = CLUBS;

  printf("Printed card should be 8c and is ");
  print_card(new_card);
  printf("\n");

  new_card.value = 10;
  new_card.suit = HEARTS;

  printf("Printed card should be Oh and is ");
  print_card(new_card);
  printf("\n");  
}

void test_card_from_letters() {
  card_t new_card = card_from_letters('A', 'c');

  assert(new_card.value == 14);
  assert(new_card.suit == 3);

  new_card = card_from_letters('3', 's');

  assert(new_card.value == 3);
  assert(new_card.suit == 0);

  new_card = card_from_letters('O', 'h');

  assert(new_card.value == 10 );
  assert(new_card.suit == 1);   
}

int main(void) {
  test_ranking_to_string();
  printf("Test 'ranking to string' done\n");
  test_value_letter();
  printf("Test 'value letter' done\n");
  test_suit_letter();
  printf("Test 'suit letter' done\n");
  test_assert_card_valid();
  printf("Test 'assert card valid' done\n");
  test_print_card();
  printf("Test 'print card' done\n");
  test_card_from_letters();
  printf("Test 'card from letters' done\n");  
}

