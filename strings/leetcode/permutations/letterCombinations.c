/***
    https://leetcode.com/problems/letter-combinations-of-a-phone-number/submissions/
    Medium : 17. Letter Combinations of a Phone Number
    Given a string containing digits from 2-9 inclusive, return all
    possible letter combinations that the number could represent.
    Return the answer in any order.

    A mapping of digit to letters (just like on the telephone buttons) is
    given below. Note that 1 does not map to any letters.

    Input: digits = "23"
    Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

    Input: digits = ""
    Output: []

    Input: digits = "2"
    Output: ["a","b","c"]

    Constraints:
    0 <= digits.length <= 4
    digits[i] is a digit in the range ['2', '9'].

    Date: 26 March 2021.
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


#define char_to_int(c) ((c) - '0')
#define MAX(a, b) ((a) > (b)? (a) : (b))

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCombinations(char* digits, int* returnSize) {
  /* Mobile Phone Pad has below char per 0-9 key numbers  */
  char *pad[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
  int nextSize;

  if (digits[0] == '\0') {
    *returnSize = 0;
    return NULL;
  }

  char c = digits[0];
  int d = char_to_int(c);

  char **next = letterCombinations(digits + 1, &nextSize);

  int i, j, len_digits = strlen(pad[d]);
  char **res;

  res = malloc(sizeof(char *) * len_digits * MAX(1, nextSize));
  *returnSize = 0;

  for (i = 0; i < len_digits; i++) {
    c = pad[d][i];
    if (nextSize == 0) {
      int len = 1 + 1;
      char *s = malloc(len);
      sprintf(s, "%c", c);
      res[*returnSize] = s;
      (*returnSize)++;
    }
    for (j = 0; j < nextSize; j++) {
      int len = strlen(next[j]) + 1 + 1;
      char *s = malloc(len);
      sprintf(s, "%c%s", c, next[j]);
      res[*returnSize] = s;
      (*returnSize)++;
    }
  }

  return res;
}

int main () {
  char digits[] = "23";
  int returnSize;
  char **ret = letterCombinations(digits, &returnSize);

  for (int i=0; i<returnSize; i++) {
    debug("Combinations : %s", ret[i]);
  }
}

/**
   => ./a.out
   [main] L=91 :Combinations : ad
   [main] L=91 :Combinations : ae
   [main] L=91 :Combinations : af
   [main] L=91 :Combinations : bd
   [main] L=91 :Combinations : be
   [main] L=91 :Combinations : bf
   [main] L=91 :Combinations : cd
   [main] L=91 :Combinations : ce
   [main] L=91 :Combinations : cf
**/
