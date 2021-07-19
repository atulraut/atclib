/***
    1047. Remove All Adjacent Duplicates In String
    https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/

    You are given a string s consisting of lowercase English letters.
    A duplicate removal consists of choosing two adjacent and equal letters and removing them.

    We repeatedly make duplicate removals on s until we no longer can.

    Return the final string after all such duplicate removals have been made.
    It can be proven that the answer is unique.

    Example 1:
    Input: s = "abbaca"
    Output: "ca"
    Explanation:
    For example, in "abbaca" we could remove "bb" since the letters are adjacent
    and equal, and this is the only possible move.  The result of this move is
    that the string is "aaca", of which only "aa" is possible, so the final string is "ca".

    Example 2:
    Input: s = "azxxzy"
    Output: "ay"

    Constraints:
    1 <= s.length <= 105
    s consists of lowercase English letters.

    Date: July 19, 2021
    Fair Oaks, CA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)


char * removeDuplicates(char * str) {
  if(str == NULL)
    return NULL;
  int len = strlen(str);
  if(len == 1)
    return str;

  int i =1, j = 0;
  char* top= (char*)malloc(len+1);
  if(top==NULL)
    return NULL;
  memset(top, 0, len+1);

  top[0] = str[0];

  for(int i = 1; i< len; i++) {
    if(j>=0) {
      if(str[i] == top[j]) {
	j--;
      } else {
	j++;
	top[j] = str[i];
      }
    } else {
      top[++j] = str[i];
    }
  }
  top[j+1] = '\0';

  return top;
}

int main () {
  char* ret = 0;
  char str[] = "abbaca";
  ret = removeDuplicates(str);

  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=84 :Output = ca
**/
