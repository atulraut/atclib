/***
    Hard: You are given a string s and an integer k.
    You can choose one of the first k letters of s
    and append it at the end of the string..

    Return the lexicographically smallest string you
    could have after applying the mentioned step any
    number of moves.

    Input: s = "cba", k = 1
    Output: "acb"
    Explanation:
    In the first move, we move the 1st character 'c'
    to the end, obtaining the string "bac".
    In the second move, we move the 1st character 'b'
    to the end, obtaining the final result "acb".
    Example 2:

    Input: s = "baaca", k = 3
    Output: "aaabc"
    Explanation:
    In the first move, we move the 1st character 'b'
    to the end, obtaining the string "aacab".
    In the second move, we move the 3rd character 'c'
    to the end, obtaining the final result "aaabc".

    Constraints:
    1 <= k <= s.length <= 1000
    s consist of lowercase English letters.

    https://leetcode.com/problems/orderly-queue/

    Date: 7 Sept 2021
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

int cmp(const void *a, const void *b) {
  return *(char *)a - *(char *)b;
}

char* orderlyQueue(char* s, int k) {
  debug("S = %s", s);
  if(k > 1) {
    qsort(s, strlen(s), sizeof(char), cmp);
    debug("S = %s", s);
    return s;
  }

  char* result = (char *)malloc((strlen(s)+1)*sizeof(char));

  for(int i=0; i<strlen(s); i++) {
    for(int j=0; j<strlen(s)-1; j++) {
      char c = s[j];
      s[j] = s[j+1];
      s[j+1] = c;
    }
    debug("S = %s", s);
    if(strcmp(s, result) > 0) { // should be <, but somehow not working.
      debug("AR = %s", s);
      strcpy(result, s);
    } else
      debug("Ig BI");
  }
  debug("result = %s", result);
  return result;
}

int main (int argc, char **argv) {
  char s[] = "cba";
  int k = 1;
  char* ret = orderlyQueue(s, k);

  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [orderlyQueue] L=25 :S = cba
   [orderlyQueue] L=40 :S = bac
   [orderlyQueue] L=42 :AR = bac
   [orderlyQueue] L=40 :S = acb
   [orderlyQueue] L=45 :Ig BI
   [orderlyQueue] L=40 :S = cba
   [orderlyQueue] L=42 :AR = cba
   [orderlyQueue] L=47 :result = cba
   [main] L=56 :Output = cba
**/
