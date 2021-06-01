/***
    Medium: Find and Replace Pattern
    Medium

    Given a list of strings words and a string pattern, return a
    list of words[i] that match pattern. You may return the answer
    in any order.

    A word matches the pattern if there exists a permutation of
    letters p so that after replacing every letter x in the
    pattern with p(x), we get the desired word.

    Recall that a permutation of letters is a bijection from
    letters to letters: every letter maps to another letter,
    and no two letters map to the same letter.

    Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
    Output: ["mee","aqq"]
    Explanation: "mee" matches the pattern because there is
    a permutation {a -> m, b -> e, ...}.
    "ccc" does not match the pattern because {a -> c, b -> c, ...}
    is not a permutation, since a and b map to the same letter.

    Input: words = ["a","b","c"], pattern = "a"
    Output: ["a","b","c"]

    Constraints:
    1 <= pattern.length <= 20
    1 <= words.length <= 50
    words[i].length == pattern.length
    pattern and words[i] are lowercase English letters.

    https://leetcode.com/problems/find-and-replace-pattern/

    Date: 27 May 2021.
    San Diego, CA.
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool checkPattern(const char* word, const char* pattern) {
  if (strlen(word) != strlen(pattern)) return false;

  bool used[26];
  int table[26];

  memset(used, 0, sizeof(bool) * 26);   // set every member to false
  memset(table, 0xff, sizeof(int) * 26);  // set every member to -1

  for (int i = 0; word[i] != '\0'; i++) {
    if (table[word[i]-'a'] == -1) {
      if (!used[pattern[i]-'a']) {
	table[word[i]-'a'] = pattern[i] - 'a';
	used[pattern[i]-'a'] = true;
      }
      else {
	return false;
      }
    } else {
      if (table[word[i]-'a'] != pattern[i]-'a') {
	return false;
      }
    }
  }

  return true;
}

char ** findAndReplacePattern(char ** words, int wordsSize, char * pattern, int* returnSize ) {
  *returnSize = 0;
  char** ans = NULL;

  for (int i = 0; i < wordsSize; i++) {
    if (checkPattern(words[i], pattern)) {
      (*returnSize)++;
      ans = realloc(ans, sizeof(char*) * (*returnSize));
      ans[(*returnSize)-1] = words[i];
    }
  }

  return ans;
}

int main () {
  char *words[] =  {"abc","deq","mee","aqq","dkd","ccc"};
  int wordsSize = sizeof(words) / sizeof(words[0]);
  char* pattern  = "abb";
  int returnSize;

  char **ret = findAndReplacePattern(words, wordsSize, pattern, &returnSize);

  for (int i=0; i<returnSize; ++i)
    debug("Output = %s", ret[i]);

  return 0;
}

/**
   => ./a.out
   [main] L=107 :Output = mee
   [main] L=107 :Output = aqq
**/
