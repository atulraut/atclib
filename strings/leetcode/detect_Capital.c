/***
    Problem :Given a word, you need to judge whether the usage of capitals in it is right or not.
    We define the usage of capitals in a word to be right when one of the following cases holds:
    All letters in this word are capitals, like "USA".
    All letters in this word are not capitals, like "leetcode".
    Only the first letter in this word is capital, like "Google".
    Otherwise, we define that this word doesn't use capitals in a right way.
    Example 1:
    Input: "USA"
    Output: True
    Example 2:
    Input: "FlaG"
    Output: False
    LeetCode : https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/549/week-1-august-1st-august-7th/3409/
    Logic : https://www.youtube.com/watch?v=hc6lUrPBmUE
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool detectCapitalUse(char * word) {
  int n = strlen (word);
  /* just check for upper & lower case taken care itself */
  int upper = 0;
  for (int i=0; i<n; i++) {
    if (word[i] >= 'A' && word[i] <= 'Z')
      ++upper;
  }
  /***
      Cond-1: All Upper
      Cond-2: All Lower (if not upper == lower)
      Cond-3: Check only 1 Upper Letter
  */
  if (upper == n || upper == 0 ||
      ((word[0] >= 'A' && word[0] <= 'Z') && upper == 1))
    return true;
  return false;
}

int main() {
  char word_1[] = "USA"; /* Cond-1: All Upper */
  char word_2[] = "usa"; /* Cond-2: All Lower */
  char word_3[] = "Usa"; /* Cond-3: Only one Upper */
  char word_4[] = "USa"; /* False Condition */
  bool ret1 = detectCapitalUse(word_1);
  printf ("I/O = %d \n", ret1);
  bool ret2 = detectCapitalUse(word_2);
  printf ("I/O = %d \n", ret2);
  bool ret3 = detectCapitalUse(word_3);
  printf ("I/O = %d \n", ret3);
  bool ret4 = detectCapitalUse(word_4);
  printf ("I/O = %d \n", ret4);
  return 0;
}

/***
    => ./a.out
    I/O = 1
    I/O = 1
    I/O = 1
    I/O = 0
*/
