/***
    LeetCode : Find the Difference
    https://leetcode.com/problems/find-the-difference/
    https://leetcode.com/explore/featured/card/september-leetcoding-challenge/557/week-4-september-22nd-september-28th/3471/
    Given two strings s and t which consist of only lowercase letters.

    String t is generated by random shuffling string s and then add one more letter at a random position.
    Find the letter that was added in t.
    Example:
    Input:
    s = "abcd"
    t = "abcde"
    Output:
    e
    Explanation:
    'e' is the letter that was added.
    Logic : https://www.youtube.com/watch?v=sRwElQ_TOr8
    Use XOR 1 ^ 1 = 0 & 0 ^ 0 = 0 & rest all are 1, so easy to cancel same element.
*/

#include "../../at_lib.h"

/* Optimal Solution */
char findTheDifference(char * s, char * t) {
  char ans = 0;
    register int i;
    for (i = 0; s[i] != '\0'; i++) {
        ans ^= s[i];
        ans ^= t[i];
    }

    ans ^= t[i];

    return ans;

}

/* Brute force */
char findTheDifference2 (char * s, char * t) {
  int i, flag = 0;
  char isPresent[256] = {0};

  int slen = strlen (s);
  int tlen = strlen (t);
  for (i=0; i<slen; i++)
    ++isPresent[s[i]];

  for (i=0; i<tlen; i++) {
    if (isPresent[t[i]])  {
      printf (" --> %c \n", t[i]);
    } else
      flag = i;
  }
  printf ("flag = %d \n", flag);
  return t[flag];
}


int main () {
  char *s = "abcd";
  char *t = "abcde";
  printf ("[%s] output = %c \n", __func__, findTheDifference(s, t));
  debug(" Enter ");
}

/***
    [main] output = e
    [string/find_diff.c] [main()] L=63 : Enter
*/
