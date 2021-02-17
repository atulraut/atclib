/**
 * Palindrome Permutation
 * https://leetcode.com/problems/palindrome-permutation/
 * Given a string, determine if a permutation of the string could
 * form a palindrome.

 * Example 1:

 * Input: "code"
 * Output: false
 * Example 2:
 * Input: "aab"
 * Output: true
 * Example 3:
 * Input: "carerac"
 * Output: true
**/

#include <stdio.h>
#include "../../at_lib.h"

bool canPermutePalindrome(char * s){
  int map[128] = {0};
  int len = strlen(s);

  int count = 0;
  for (int i = 0; i < len; i++) {
    map[s[i]]++;
    debug (" c = %c mapi = %d", s[i], map[s[i]]);
    if (map[s[i]] % 2 == 0) // Even Count
      count--;
    else
      count++;
    debug ("count = %d", count);
  }
  debug ("count = %d (count <=1) = %d ", count, (count <= 1));
  if(count >=2)
    return 0;
  else
    return 1;
  return count <= 1;
}

int main () {
  //char str[] = "code";
  char str[] = "012221";
  debug ("O/P = %d", canPermutePalindrome(str));

  return 0;
}

/**
 * Input = "012221"
 * [canPermutePalindrome] L=28 : c = 0 mapi = 1
 * [canPermutePalindrome] L=33 :count = 1
 * [canPermutePalindrome] L=28 : c = 1 mapi = 1
 * [canPermutePalindrome] L=33 :count = 2
 * [canPermutePalindrome] L=28 : c = 2 mapi = 1
 * [canPermutePalindrome] L=33 :count = 3
 * [canPermutePalindrome] L=28 : c = 2 mapi = 2
 * [canPermutePalindrome] L=33 :count = 2
 * [canPermutePalindrome] L=28 : c = 2 mapi = 3
 * [canPermutePalindrome] L=33 :count = 3
 * [canPermutePalindrome] L=28 : c = 1 mapi = 2
 * [canPermutePalindrome] L=33 :count = 2

 * [canPermutePalindrome] L=34 :count = 2 (count <=1) = 0
 * [main] L=39 :O/P = 0

 * Input = "code"
 * [canPermutePalindrome] L=28 :mapi = 1
 * [canPermutePalindrome] L=28 :mapi = 1
 * [canPermutePalindrome] L=28 :mapi = 1
 * [canPermutePalindrome] L=28 :mapi = 1
 * [canPermutePalindrome] L=33 :coudnt = 4 (count <=1) = 0
 * [main] L=40 :O/P = 0


 Algorithm:

 For this, we traverse over ss and update the number of occurrences of the character
 just encountered in the map. But, whevenever we update any entry in map,
 we also check if its value becomes even or odd. We start of with a count value of 0.
 If the value of the entry just updated in map happens to be odd, we increment
 the value of count to indicate that one more character with odd
 number of occurrences has been found. But, if this entry happens to be EVEN,
 we DECREMENT the value of count to indicate that the number of characters
 with odd number of occurrences has reduced by one.

 But, in this case, we need to traverse till the end of the string to determine the
 final result, unlike the last approaches, where we could stop the traversal over map
 as soon as the count exceeded 1. This is because, even if the number
 of elements with odd number of occurrences may seem very large at the current moment,
 but their occurrences could turn out to be even when we traverse further in the string s.

 At the end, we again check if the value of count is lesser than
 2 to conclude that a palindromic permutation is possible for the string s.
**/
