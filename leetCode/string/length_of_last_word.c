/***
    LeetCode :   Length of Last Word
    https://leetcode.com/explore/featured/card/september-leetcoding-challenge/556/week-3-september-15th-september-21st/3461/
    Given a string s consists of upper/lower-case alphabets and empty space
    characters ' ', return the length of last word (last word means the last
    appearing word if we loop from left to right) in the string.
    If the last word does not exist, return 0.
    Note: A word is defined as a maximal substring consisting of non-space
    characters only.
    Example: Input: "Hello World"
    Output: 5
*/

#include "../at_lib.h"

int lengthOfLastWord(char * s){
  int len = 0;
  int last = 0;

  for (; *s; s++) {
    if (*s==' ') {
      if (len > 0) { /* to fliter end of space*/
         last = len;
      }
      len = 0;
    }
    else
      len++;
  } // for ends

  return len>0 ? len:last;
}

int main() {

  char arr[] = "Hello World";
  printf("[%s]  Word Length Is = %d \n",__func__,  lengthOfLastWord(arr));

  return 0;
}
