/***
    https://leetcode.com/problems/find-all-anagrams-in-a-string/
    438. Find All Anagrams in a String
    Medium

    Given two strings s and p, return an array of all the
    start indices of p's anagrams in s. You may return the
    answer in any order.

    An Anagram is a word or phrase formed by rearranging the
    letters of a different word or phrase, typically using all
    the original letters exactly once.

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

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 7 Jan 2021
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
  int hash[26] = {0};
  int cnt_hash[26] = {0};
  int i, j, k, s_len, p_len, idx = 0, tmp_i, tmp_idx;
  int *ret_array;
  bool not_match, over_cnt;
  char ascii_val;

  s_len = strlen(s);
  p_len = strlen(p);

  if (s_len == 0 || p_len == 0)
    return NULL;

  ret_array = malloc(sizeof(int) * s_len);

  for (i = 0; i < p_len; i++)
    hash[p[i] - 'a']++;

  /* loop through the whole string with a sliding window */
  for (i = 0; i < s_len; i++) {
    cnt_hash[s[i] -'a']++;

    if (i >= p_len)
      cnt_hash[s[i - p_len] - 'a']--;

    debug("i=%d char=%c cnt=%d\n", i, s[i], cnt_hash[s[i]-'a']);
    for (j = 0; j < 26; j++) {
      if (cnt_hash[j] != hash[j])
	break;
    }
    if (j == 26) {
      debug("***** match i=%d\n", i);
      ret_array[idx++] = i - p_len + 1;
    }
  }
  *returnSize = idx;
  return ret_array;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int isEquals(int sHash[],int pHash[]){
  for(int i=0;i<26;i++){
    if(sHash[i] != pHash[i]) {
      return 0;
    }
  }
  return 1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams_(char* s, char* p, int* returnSize) {
  int *ret = (int*)malloc(sizeof(int)*100000);
  *returnSize = 0;
  int sLen = strlen(s);
  int pLen = strlen(p);

  if(sLen < pLen)
    return NULL;

  int pHash[26] = {0};
  int sHash[26] = {0};

  for(int i=0; i<sLen; i++) {
    sHash[s[i]-'a']++;
  }

  for(int i=0; i<pLen; i++) {
    if(sHash[p[i]-'a'] == 0) {
      *returnSize = 0;
      return NULL;
    }
    pHash[p[i]-'a']++;
  }
  memset(sHash, 0, 26*sizeof(int));

  for(int i=0; i<pLen; i++) {
    sHash[s[i]-'a']++;
  }

  if(isEquals(sHash, pHash)) {
    ret[(*returnSize)++] = 0;
  }

  for(int i=1; i<sLen-pLen+1; i++) {
    sHash[s[i-1]-'a']--;
    sHash[s[i+pLen-1]-'a']++;
    if(isEquals(sHash,pHash)) {
      ret[(*returnSize)++]=i;
    }
  }
  return ret;
}

int main (int argc, char **argv) {
  int* ret;
  char s[] = "abab";
  char p[] = "ab";
  int returnSize;

  ret = findAnagrams(s, p, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [findAnagrams] L=92 :i=0 char=a cnt=1

   [findAnagrams] L=92 :i=1 char=b cnt=1

   [findAnagrams] L=98 :***** match i=1

   [findAnagrams] L=92 :i=2 char=a cnt=1

   [findAnagrams] L=98 :***** match i=2

   [findAnagrams] L=92 :i=3 char=b cnt=1

   [findAnagrams] L=98 :***** match i=3

   [main] L=171 :Output = 0
   [main] L=171 :Output = 1
   [main] L=171 :Output = 2
**/
