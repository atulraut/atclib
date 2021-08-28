/***
    Longest Uncommon Subsequence II

    Given an array of strings strs, return the length of the longest
    uncommon subsequence between them. If the longest uncommon
    subsequence does not exist, return -1.

    An uncommon subsequence between an array of strings is a string
    that is a subsequence of one string but not the others.

    A subsequence of a string s is a string that can be obtained
    after deleting any number of characters from s.

    For example, "abc" is a subsequence of "aebdc" because you can delete
    the underlined characters in "aebdc" to get "abc". Other subsequences
    of "aebdc" include "aebdc", "aeb", and "" (empty string).

    Input: strs = ["aba","cdc","eae"]
    Output: 3

    Input: strs = ["aaa","aaa","aa"]
    Output: -1

    Constraints:
    1 <= strs.length <= 50
    1 <= strs[i].length <= 10
    strs[i] consists of lowercase English letters.

    https://leetcode.com/problems/longest-uncommon-subsequence-ii/
    Date: 27 August 2021
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

#define max1(x, y) (((x) > (y) ? (x) : (y)))

int max(int a,int b) {
  return a>b?a:b;
}

bool isSubsequence(char* a, char* b) {
  int i = 0;
  int k = 0;

  if (strlen(a) < strlen(b))
    return false;

  for(k=0; k<strlen(a); k++) {
    if(i < strlen(b) && b[i] == a[k])
      i++;
  }
  debug ("i = %d", i);

  return i == strlen(b);
}

int findLUSlength(char** str, int strsSize) {
  int res = -1;
  int i, j;

  for (i = 0; i < strsSize; i++) {
    for (j = 0; j < strlen(str[i]); j++) {
      if (j == i)
	continue;
      if (isSubsequence(str[i], str[j]))
	break;
    }
    if (j == strsSize)
      res = max(res, strlen(str[i]));
  }
  return res;
}

int main (int argc, char **argv) {
  int ret = 0;

  char* strs[] = {"aba","cdc","eae"};
  int arrayLen = sizeof(strs)/sizeof(strs[0]);
  debug("array Length = %d", arrayLen);

  ret =  findLUSlength(strs, arrayLen);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [findLUSlength] L=54 :array Length = 1
   [main] L=65 :Output = -1
**/
