/***
    https://leetcode.com/problems/find-all-anagrams-in-a-string/
    Find All Anagrams in a String

    Given two strings s and p, return an array of all the start
    indices of p's anagrams in s. You may return the answer in
    any order.

    An Anagram is a word or phrase formed by rearranging the
    letters of a different word or phrase, typically using all the
    original letters exactly once.

    Input: s = "cbaebabacd", p = "abc"
    Output: [0,6]
    Explanation:
    The substring with start index = 0 is "cba", which is an anagram of "abc".
    The substring with start index = 6 is "bac", which is an anagram of "abc".

    Input: s = "abab", p = "ab"
    Output: [0,1,2]
    Explanation:
    The substring with start index = 0 is "ab", which is an anagram of "ab".
    The substring with start index = 1 is "ba", which is an anagram of "ab".
    The substring with start index = 2 is "ab", which is an anagram of "ab".

    Constraints:
    1 <= s.length, p.length <= 3 * 104
    s and p consist of lowercase English letters.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address findAnagrams.c -lm

    Date: Feb 1, 2022
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/**
   Remove Condition @L46 to get below Error  : && s[j] != '\0'
   ==1680==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffe04b7047b at pc 0x000000400c89 bp 0x7ffe04b70240 sp 0x7ffe04b70230

 **/
int is_anagram(char* s, int si, char* p) {
  int len = strlen(p);
  debug ("len = %d si = %d", len ,si);
  //assert(len >= si);
  int isAna[26] = {0};

  for (int i=0, j=si; i<len && s[j] != '\0'; ++i, ++j) {
    debug ("--> %d", (s[j] - 'a'));
    isAna[s[j] - 'a']++;
  }

  for (int i=0; i<len; ++i)
    if(!isAna[p[i] - 'a'])
      return false;
  return true;
}

int* findAnagrams(char* s, char* p, int* returnSize){
  int j = 0, cnt = 0;
  int slen = strlen(s);
  int* ret_array = (int *)malloc(sizeof(int) * slen);
  memset(ret_array, 0, slen);
  debug ("s len = %d", slen);
  for (j=0; j<slen; ++j) {
    int ret = is_anagram(s, j, p);
    debug("j=%d Result = %d", j, ret);
    if(ret) {
      ret_array[cnt++] = j;
      *returnSize = cnt;
    }
  }
  return ret_array;
}

void test() {
  int *ret;
  char s2[] = "cbaebabacd";
  char p2[] = "abc";
  char s1[] = "abab";
  char p1[] = "ab";
  char s[] = "aa";
  char p[] = "bb";
  int returnSize;
  ret = findAnagrams(s, p, &returnSize);
  debug("returnSz = %d", returnSize);
  for(int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  free(ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./main
   [findAnagrams] L=62 :s len = 4
   [is_anagram] L=42 :len = 2 si = 0
   [is_anagram] L=47 :--> 0
   [is_anagram] L=47 :--> 1
   [findAnagrams] L=65 :j=0 Result = 1
   [is_anagram] L=42 :len = 2 si = 1
   [is_anagram] L=47 :--> 1
   [is_anagram] L=47 :--> 0
   [findAnagrams] L=65 :j=1 Result = 1
   [is_anagram] L=42 :len = 2 si = 2
   [is_anagram] L=47 :--> 0
   [is_anagram] L=47 :--> 1
   [findAnagrams] L=65 :j=2 Result = 1
   [is_anagram] L=42 :len = 2 si = 3
   [is_anagram] L=47 :--> 1
   [findAnagrams] L=65 :j=3 Result = 0
   [test] L=83 :returnSz = 3
   [test] L=85 :Output = 0
   [test] L=85 :Output = 1
   [test] L=85 :Output = 2
**/
