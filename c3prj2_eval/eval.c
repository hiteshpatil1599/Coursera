#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*
int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t* const* c1= vp1;
  const card_t* const* c2= vp2;

  if(c1[0][0].value > c2[0][0].value)
    return -1;
  if(c1[0][0].value < c2[0][0].value)
    return 1;
  if(c1[0][0].suit > c2[0][0].suit)
    return -1;
  if(c1[0][0].suit < c2[0][0].suit)
    return 1;
  
  return 0;
}
*/


int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t* const *cp1=vp1;
  const card_t* const *cp2=vp2;
  if((*cp1)->value>(*cp2)->value)
    return -1;
  else if((*cp1)->value<(*cp2)->value)
    return 1;
  else
    {
      if((*cp1)->suit<(*cp2)->suit)
	return 1;
      else  if((*cp1)->suit>(*cp2)->suit)
	return -1;
      else
	return 0;
    }
}


/*
suit_t flush_suit(deck_t * hand) {
  int s=0, h=0, d=0, c=0;
  
  for(int i=0; i<hand->n_cards; i++)
    {
      if((*(hand->cards+i))->suit == 0)
	s++;
      else if((*(hand->cards+i))->suit == 1)
	h++;
      else if((*(hand->cards+i))->suit == 2)
	d++;
      else if((*(hand->cards+i))->suit == 3)
	c++;
    }
  if(s>=5)
    return SPADES;
  if(h>=5)
    return HEARTS;
  if(d>=5)
    return DIAMONDS;
  if(c>=5)
    return CLUBS;
  return NUM_SUITS;
}
*/
suit_t flush_suit(deck_t * hand) {
  int arr[4]={0};
  for(int i=0;i<hand->n_cards;i++)
    {
      if(hand->cards[i]->suit<NUM_SUITS)
	arr[hand->cards[i]->suit]++;
    }
  for(int i=0;i<4;i++)
    if(arr[i]>=5)
      return i;
  return NUM_SUITS;
}



/*
unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned max= arr[0];
  for(size_t i=1; i<n; i++)
    if(arr[i]>max)
      max=arr[i];
  return max;
}
*/

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned max=0;
  for(int i=0;i<n;i++)
    if(arr[i]>max)
      max=arr[i];
  return max;
}


/*
size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  
  for(size_t i=0; i<n; i++)
    if(match_counts[i]==n_of_akind)
      return i;
  return 0;
}
*/

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for(int i=0;i<n;i++)
    if(match_counts[i]==n_of_akind)
      return i;
  fprintf(stderr,"\nCould not find the index");
  exit(EXIT_FAILURE);
}



/*
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  
  card_t** cards = hand->cards;
  size_t num_cards = hand->n_cards;

  for(size_t i=0; i<num_cards; i++)
    {
      if(match_counts[i]>1&&cards[i][0].value != cards[match_idx][0].value)
	return i;
    }
  return -1;
}
*/



ssize_t  find_secondary_pair(deck_t * hand,unsigned * match_counts,size_t match_idx) {
  for(int i=0;i<hand->n_cards;i++)
    {
      if(match_counts[i]>1&&(hand->cards[i]->value!=hand->cards[match_idx]->value))
	return i;
    }
  return -1;
}



/*
int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  card_t** cards= hand->cards;
  if(fs==NUM_SUITS)
    {
      int value= cards[index][0].value;
      
      for(int i=index; i<hand->n_cards; i++)
	if(cards[i][0].value==value)
	  value--;
      if(value<=(cards[index][0].value-5))
	return 1;

      if(cards[index][0].value==14)
	{
	  value= 5;
	  for(int i=index+1;i<hand->n_cards;i++)
	    if(cards[i][0].value==value)
	      value--;
	  if(value==1)
	    return -1;
	}
      return 0;
    }
  else
    {
      int value= cards[index][0].value;
      if(cards[index][0].suit!=fs)
	return 0;

      for(int i=index; i<hand->n_cards; i++)
	if(cards[i][0].value==value && cards[i][0].suit==fs)
	  value--;
      if(value<=(cards[index][0].value-5))
	return 1;
         
      if(cards[index][0].value==14)
	{
	  value= 5;
	  for(int i= index+1; i<hand->n_cards; i++)
	    if(cards[i][0].value==value && cards[i][0].suit==fs)
	      value--;
	  if(value==1)
 	    return -1;
	}
      return 0;
    }
}
*/

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if(fs==NUM_SUITS)
    {
      int count=0;
      for(int i=index;i<hand->n_cards-1;i++)
	{
	  int diff=hand->cards[i]->value-hand->cards[i+1]->value;
	  if(diff>1)
	    break;
	  if(count==4)
	    break;
	  if(diff==1)
	    count++;
	}
      if(count==4)
	return 1;

      if(hand->cards[index]->value==VALUE_ACE)       //func for ace low straight
	{
	  count=0;
	  for(int i=index+1;i<hand->n_cards-1;i++)
	    {
	      if(hand->cards[index]->value-hand->cards[index+1]->value>1&&hand->cards[index+1]->value!=5)
		break;
	      if(hand->cards[i]->value==5)
		count=1;
	      int diff=hand->cards[i]->value-hand->cards[i+1]->value;
	      if(diff==1&&count)
		count++;
	      if(diff>1&&!count)
		break;
	    }
	  if(count==4)
	    return -1;
	}
      return 0;
    }
  else
    {
      int count=0;
      int count_suit[5]={0};
      for(int i=index;i<hand->n_cards;i++)
	count_suit[hand->cards[i]->suit]++;
      suit_t suspect=NUM_SUITS;
      for(int i=0;i<5;i++)
	if(count_suit[i]>=5)
	  {
	    suspect=i;
	    break;
	  }
      if(suspect!=NUM_SUITS)
	{
	  int temp_value=-1;
	  if(hand->cards[index]->suit!=suspect)
	    return 0;
	  for(int i=index;i<hand->n_cards;i++)
	    {
	      int diff=temp_value-hand->cards[i]->value;
	      int diff_suit=suspect-hand->cards[i]->suit;
	      if(diff>1)
		break;
	      if(count==4)
		break;
	      if(diff==1&&!diff_suit)
		count++;
	      if(hand->cards[i]->suit==suspect)
		temp_value=hand->cards[i]->value;
	    }
	  if(count==4)
	    return 1;
	}
      if(hand->cards[index]->value==VALUE_ACE)       //func for ace low straight flush
	{
	  count=0;
	  int temp_value=-1;
	  for(int i=index;i<hand->n_cards;i++)
	    {
	      if(hand->cards[i]->value==5&&hand->cards[i]->suit==hand->cards[index]->suit)
		count=1;
	      int diff=temp_value-hand->cards[i]->value;
	      int diff_suit=suspect-hand->cards[i]->suit;
	      if(diff==1&&!diff_suit&&count)
		count++;
	      //    if(diff>1)
	      //        break;
	      if(hand->cards[i]->suit==suspect&&hand->cards[i]->value<=5)
		temp_value=hand->cards[i]->value;
	    }
	  if(count==4)
	    return -1;
	}
      return 0;
    }
}



/*
hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  
  hand_eval_t ans;
  size_t i=0, j=0;
  int flag[7]= {0};
  ans.ranking= what;

  for(i=0; i<n; i++)
    {
      ans.cards[i]= hand->cards[idx];
      flag[idx]= 1;
      idx++;
    }
  while(i<5 && j< hand->n_cards)
    {
      if(flag[j] == 0)
	{
	  ans.cards[i]= hand->cards[j];
	  i++;
	  j++;
	}
      else
	{
	  j++;
	}
    }
  return ans;
}
*/

hand_eval_t build_hand_from_match(deck_t * hand,unsigned n,hand_ranking_t what, size_t idx) {

  hand_eval_t ans;
  ans.ranking=what;
  for(int i=idx,j=0;i<n+idx;i++,j++)
    ans.cards[j]=hand->cards[i];
  card_t *rem_cards[7];
  int j=0;
  for(int i=0;i<idx;i++)
    rem_cards[j++]=hand->cards[i];
  for(int i=n+idx;i<hand->n_cards;i++)
    rem_cards[j++]=hand->cards[i];
  for(int i=n,j=0;i<5;i++)
    ans.cards[i]=rem_cards[j++];
  return ans;
}


/*
int compare_hands(deck_t * hand1, deck_t * hand2) {

  hand_eval_t c1, c2;
  int flag;
  for(size_t i=1; i<hand1->n_cards-1; i++)
    {
      for(size_t j=0; j<hand1->n_cards-i; j++)
	{
	  if((hand1->cards[j][0].value < hand1->cards[j+1][0].value) ||
	     (hand1->cards[j][0].value == hand1->cards[j+1][0].value
	      && hand1->cards[j][0].suit < hand1->cards[j+1][0].suit))
	    {
	      card_t* temp= hand1->cards[j];
	      hand1->cards[j]= hand1->cards[j+1];
	      hand1->cards[j+1]= temp;
	    }
	}
    }
  for(size_t i=1; i<hand2->n_cards-1; i++)
    {
      for(size_t j=0; j<hand2->n_cards-i; j++)
	{
	  if((hand2->cards[j][0].value < hand2->cards[j+1][0].value) ||
	     (hand2->cards[j][0].value == hand2->cards[j+1][0].value
	      && hand2->cards[j][0].suit < hand2->cards[j+1][0].suit))
	    {
	      card_t* temp= hand2->cards[j];
	      hand2->cards[j]= hand2->cards[j+1];
	      hand2->cards[j+1]= temp;
	    }
	}
    }

  c1= evaluate_hand(hand1);
  c2= evaluate_hand(hand2);

  if(c1.ranking > c2.ranking) return -1;
  if(c1.ranking < c2.ranking) return 1;

  if(c1.ranking == c2.ranking)
    {
      if(c1.ranking == NOTHING)
	{
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  //if all cards have same value.Then check them wrt suit. s>h>d>c.
	  for(int i=0; i<5; i++)
	    if((flag= card_ptr_comp(c1.cards, c2.cards)))
	      return flag;
	  return 0;
	}
      if(c1.ranking == PAIR)
	{
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  //if all cards are same. Then tie.
	  //for(int i=0; i<5; i++)
	  //if((flag= card_ptr_comp(c1.cards, c2.cards)))
	  //return flag;
	  return 0;
	}

      if(c1.ranking == TWO_PAIR)
	{
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  //if all cards are same. Then tie.
	  //for(int i=0; i<5; i++)
	  //if((flag= card_ptr_comp(c1.cards, c2.cards)))
	  //return flag;
	  return 0;
	}

      if(c1.ranking == THREE_OF_A_KIND)
	{
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  //if all cards are same. Then tie.
	  //for(int i=0; i<5; i++)
	  //if((flag= card_ptr_comp(c1.cards, c2.cards)))
	  //return flag;
	  return 0;
	}
      if(c1.ranking == FLUSH)
	{
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  //if all cards are same. Then tie.
	  //for(int i=0; i<5; i++)
	  //if((flag= card_ptr_comp(c1.cards, c2.cards)))
	  //return flag;
	  return 0;
	}
      
      if(c1.ranking == FULL_HOUSE)
	{
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  //if all cards are same. Then tie.
	  //for(int i=0; i<5; i++)
	  //if((flag= card_ptr_comp(c1.cards, c2.cards)))
	  //return flag;
	  return 0;
	}

      if(c1.ranking == FOUR_OF_A_KIND)
	{
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  //if all cards are same. Then tie.
	  //for(int i=0; i<5; i++)
	  //if((flag= card_ptr_comp(c1.cards, c2.cards)))
	  //return flag;
	  return 0;
	}

      if(c1.ranking == STRAIGHT_FLUSH)
	{
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  
	  //for(int i=0; i<5; i++)
	  //if((flag= card_ptr_comp(c1.cards, c2.cards)))
	  //return flag;
	  return 0;
	}

      
      if(c1.ranking==STRAIGHT)
	{
	  if(c1.cards[1][0].value==11 && c1.cards[1][0].suit==HEARTS)
	    return 0;
	  for(int i=0; i<5; i++)
	    if((flag= c1.cards[i][0].value-c2.cards[i][0].value))
	      return flag;
	  return 0; 
	}
      
      for(int i=0,flag=0; i<5; i++)
	if((flag= card_ptr_comp(c1.cards, c2.cards)))
	  return flag;
      return 0; 
    }
  return c1.ranking - c2.ranking;
}
*/

int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards,hand1->n_cards,sizeof(card_t*),card_ptr_comp);
  qsort(hand2->cards,hand2->n_cards,sizeof(card_t*),card_ptr_comp);
  hand_eval_t ans1,ans2;
  ans1=evaluate_hand(hand1);
  ans2=evaluate_hand(hand2);
  if(ans1.ranking!=ans2.ranking)
    {
      int diff=ans1.ranking-ans2.ranking;
      if(diff<0)
	return 1;
      if(diff>0)
	return -1;
      return 0;
    }
  else
    {
      if(ans1.ranking==STRAIGHT_FLUSH||ans1.ranking==STRAIGHT)
	{
	  int diff= ans1.cards[0]->value-ans2.cards[0]->value;
	  if(diff>0)
	    return 1;
	  if(diff<0)
	    return -1;
	  return 0;
	}
      if(ans1.ranking==FOUR_OF_A_KIND||ans1.ranking==FULL_HOUSE)
	{
	  int diff=ans1.cards[0]->value-ans2.cards[0]->value;
	  if(diff>0)
	    return 1;
	  else if(diff<0)
	    return -1;
	  else
	    {
	      diff=ans1.cards[4]->value-ans2.cards[4]->value;
	      if(diff>0)
		return 1;
	      else if(diff<0)
		return -1;
	      else return 0;
	    }
	}
      if(ans1.ranking==FLUSH)
	{
	  for(int i=0;i<5;i++)
	    {
	      int diff=ans1.cards[i]->value-ans2.cards[i]->value;
	      if(diff>0)
		return 1;
	      if(diff<0)
		return -1;
	    }
	  return 0;
	}
      if(ans1.ranking==THREE_OF_A_KIND||ans1.ranking==TWO_PAIR||ans1.ranking==PAIR||ans1.ranking==NOTHING)
	{
	  int index;
	  if(ans1.ranking==THREE_OF_A_KIND)
	    index=3;
	  else if(ans1.ranking==TWO_PAIR||ans1.ranking==PAIR)
	    index=2;
	  else index=1;
	  int diff=ans1.cards[0]->value-ans2.cards[0]->value;
	  if(diff>0)
	    return 1;
	  else if(diff<0)
	    return -1;
	  else
	    {
	      for(int i=index;i<5;i++)
		{
		  int diff=ans1.cards[i]->value-ans2.cards[i]->value;
		  if(diff>0)
		    return 1;
		  if(diff<0)
		    return -1;
		}
	      return 0;
	    }
	}
    }
  return 0;
}




//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
