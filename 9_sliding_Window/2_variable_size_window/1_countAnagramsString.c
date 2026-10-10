/***

    https://leetcode.com/problems/count-anagrams/description/

    2514. Count Anagrams

    You are given a string s containing one or more words.
    Every consecutive pair of words is separated by a single space ' '.

    A string t is an anagram of string s if the ith word of t is
    a permutation of the ith word of s.

    For example, "acb dfe" is an anagram of "abc def", but "def cab"
    and "adc bef" are not.
    Return the number of distinct anagrams of s. Since the answer may
    be very large, return it modulo 109 + 7.

    Input: s = "too hot"
    Output: 18
    Explanation: Some of the anagrams of the given string are "too hot",
    "oot hot", "oto toh", "too toh", and "too oht".

    Input: s = "aa"
    Output: 1
    Explanation: There is only one anagram possible for the given string.

    Constraints:
    1 <= s.length <= 105
    s consists of lowercase English letters and spaces ' '.
    There is single space between consecutive words.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct  9 16:16:20 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#define MOD 1000000007LL
#define MAXN 100001

long long fact[MAXN];
long long invFact[MAXN];

// Calculate base^exp % MOD
long long power(long long base, long long exp) {
  long long result = 1;

  while (exp > 0) {
    if (exp & 1)
      result = result * base % MOD;

    base = base * base % MOD;
    exp >>= 1;
  }
  return result;
}

int countAnagrams(char* s) {
  int n = strlen(s);

  // Step 1: Precompute factorials
  fact[0] = 1;

  for (int i = 1; i <= n; i++)
    fact[i] = fact[i-1] * i % MOD;

  // Step 2: Precompute inverse factorials
  invFact[n] = power(fact[n], MOD - 2);

  for (int i = n; i > 0; i--)
    invFact[i-1] = invFact[i] * i % MOD;

  long long answer = 1;
  int i = 0;

  // Step 3: Process each word
  while (i < n) {

    int freq[26] = {0};
    int len = 0;

    // Count characters in current word
    while (i < n && s[i] != ' ') {
      freq[s[i] - 'a']++;
      len++;
      i++;
    }

    // Number of permutations = len!
    long long ways = fact[len];

    // Divide by repeated-character factorials
    for (int j = 0; j < 26; j++) {
      ways = ways * invFact[freq[j]] % MOD;
    }

    // Multiply permutations of all words
    answer = answer * ways % MOD;

    i++; // Skip space
  }

  return (int)answer;
}

void test() {
  char s1[] = "too hot";
  char s2[] = "aa";
  char s3[] = "abc def";
  char s4[] = "aabb";

  debug("%d\n", countAnagrams(s1));
  debug("%d\n", countAnagrams(s2));
  debug("%d\n", countAnagrams(s3));
  debug("%d\n", countAnagrams(s4));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[127][1_findAnagramsString.c]->[test] :| 18
   L=[128][1_findAnagramsString.c]->[test] :| 1
   L=[129][1_findAnagramsString.c]->[test] :| 36
   L=[130][1_findAnagramsString.c]->[test] :| 6
**/
