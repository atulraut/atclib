/***
    https://leetcode.com/problems/check-whether-two-strings-are-almost-equivalent/
    2068. Check Whether Two Strings are Almost Equivalent

    Two strings word1 and word2 are considered almost equivalent if
    the differences between the frequencies of each letter from
    'a' to 'z' between word1 and word2 is at most 3.

    Given two strings word1 and word2, each of length n, return
    true if word1 and word2 are almost equivalent, or false otherwise.

    The frequency of a letter x is the number of times it
    occurs in the string.

    Input: word1 = "aaaa", word2 = "bccb"
    Output: false
    Explanation: There are 4 'a's in "aaaa" but 0 'a's in "bccb".
    The difference is 4, which is more than the allowed 3.

    Input: word1 = "abcdeef", word2 = "abaaacc"
    Output: true
    Explanation: The differences between the frequencies of each letter
    in word1 and word2 are at most 3:
    - 'a' appears 1 time in word1 and 4 times in word2. The difference is 3.
    - 'b' appears 1 time in word1 and 1 time in word2. The difference is 0.
    - 'c' appears 1 time in word1 and 2 times in word2. The difference is 1.
    - 'd' appears 1 time in word1 and 0 times in word2. The difference is 1.
    - 'e' appears 2 times in word1 and 0 times in word2. The difference is 2.
    - 'f' appears 1 time in word1 and 0 times in word2. The difference is 1.

    Input: word1 = "cccddabba", word2 = "babababab"
    Output: true
    Explanation: The differences between the frequencies of
    each letter in word1 and word2 are at most 3:
    - 'a' appears 2 times in word1 and 4 times in word2. The difference is 2.
    - 'b' appears 2 times in word1 and 5 times in word2. The difference is 3.
    - 'c' appears 3 times in word1 and 0 times in word2. The difference is 3.
    - 'd' appears 2 times in word1 and 0 times in word2. The difference is 2.

    Constraints:
    n == word1.length == word2.length
    1 <= n <= 100
    word1 and word2 consist only of lowercase English letters.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address checkAlmostEquivalent.c -lm

    Date: Jan, 3, 2022
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

bool checkAlmostEquivalent(char* word1, char* word2) {
  bool ret = true;
  int diff = 0;
  int table1[26] = {0,};
  int table2[26] = {0,};

  for (int i = 0; word1[i] != '\0'; i++)
    table1[word1[i] - 'a']++;

  for (int i = 0; word2[i] != '\0'; i++)
    table2[word2[i] - 'a']++;

  for (int i = 0; i < 26; i++) {
    diff = abs(table1[i] - table2[i]);
    debug("c=%c: diff=%d", (i + 'a'), diff);
    //ret = true;
    if (diff > 3)  {
      ret = false;
      break;
    }
  }
  return ret;
}

bool checkAlmostEquivalent_(char* word1, char* word2) {
  int cnt[26] = {};
  char c;
  for (int i=0; word1[i] != '\0'; ++i)  {
    c =  word1[i];
    cnt[c - 'a']++;
  }
  for (int i=0; word2[i] != '\0'; ++i) {
    c =  word2[i];
    cnt[c - 'a']--;
  }
  for (int i = 0; i < 26; ++i) {
    if (abs(cnt[i]) > 3)
      return false;
  }
  return true;
}

bool checkAlmostEquivalent__(char* word1, char* word2) {
  int i = 0;
  int isPresent1[256] = {0};
  int isPresent2[256] = {0};
  int flag = 0;

  if (strlen(word1) != strlen(word2))
    return false;

  for (i=0; word1[i] != '\0'; i++) {
    isPresent1[word1[i]]++;
    debug("i=%d, word1[%d], isPresent[%d]", i, word1[i], isPresent1[word1[i]]);
  }

  for (i=0; word2[i] != '\0'; i++) {
    isPresent2[word2[i]]++;
    debug("i=%d, word2[%d], isPresent[%d]", i, word2[i], isPresent2[word2[i]]);
  }

  for (i=0; word2[i] != '\0'; i++) {
    if (word1[i] == word2[i]) {
      flag = 1;
      debug ("w1=%d w2=%d", isPresent1[word1[i]],  isPresent2[word2[i]]);
      debug ("Diff = %d", (isPresent1[word1[i]] - isPresent2[word2[i]]));
      if ((isPresent1[word1[i]] - isPresent2[word2[i]]) > 3) {
	debug ("Opps, returning!");
	return false;
      }
    }
    //      debug("i=%d, b[%d], isPresent[%d]", i, b[i], isPresent2[b[i]]);
  }
  if (!flag)
    return false;
  return true;
}

int main (int argc, char **argv) {
  int ret = 0;
  char word11[] = "aaaa";
  char word22[] = "bccb";
  char word111[] = "abcdeef";
  char word222[] = "abaaacc";
  char word1[] = "cqvvnqjncrp";
  char word2[] = "hjtlyzvcbhj";
  ret = checkAlmostEquivalent(word1, word2);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [checkAlmostEquivalent] L=50 :c=a: diff=0
   [checkAlmostEquivalent] L=50 :c=b: diff=1
   [checkAlmostEquivalent] L=50 :c=c: diff=1
   [checkAlmostEquivalent] L=50 :c=d: diff=0
   [checkAlmostEquivalent] L=50 :c=e: diff=0
   [checkAlmostEquivalent] L=50 :c=f: diff=0
   [checkAlmostEquivalent] L=50 :c=g: diff=0
   [checkAlmostEquivalent] L=50 :c=h: diff=2
   [checkAlmostEquivalent] L=50 :c=i: diff=0
   [checkAlmostEquivalent] L=50 :c=j: diff=1
   [checkAlmostEquivalent] L=50 :c=k: diff=0
   [checkAlmostEquivalent] L=50 :c=l: diff=1
   [checkAlmostEquivalent] L=50 :c=m: diff=0
   [checkAlmostEquivalent] L=50 :c=n: diff=2
   [checkAlmostEquivalent] L=50 :c=o: diff=0
   [checkAlmostEquivalent] L=50 :c=p: diff=1
   [checkAlmostEquivalent] L=50 :c=q: diff=2
   [checkAlmostEquivalent] L=50 :c=r: diff=1
   [checkAlmostEquivalent] L=50 :c=s: diff=0
   [checkAlmostEquivalent] L=50 :c=t: diff=1
   [checkAlmostEquivalent] L=50 :c=u: diff=0
   [checkAlmostEquivalent] L=50 :c=v: diff=1
   [checkAlmostEquivalent] L=50 :c=w: diff=0
   [checkAlmostEquivalent] L=50 :c=x: diff=0
   [checkAlmostEquivalent] L=50 :c=y: diff=1
   [checkAlmostEquivalent] L=50 :c=z: diff=1
   [main] L=123 :Output = 1
**/
