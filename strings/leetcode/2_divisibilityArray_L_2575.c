/***
    https://leetcode.com/problems/find-the-divisibility-array-of-a-string/

    2575. Find the Divisibility Array of a String - Medium

    You are given a 0-indexed string word of length n consisting
    of digits, and a positive integer m.

    The divisibility array div of word is an integer array of length n such that:

    div[i] = 1 if the numeric value of word[0,...,i] is divisible by m, or
    div[i] = 0 otherwise.
    Return the divisibility array of word.

    Input: word = "998244353", m = 3
    Output: [1,1,0,0,0,1,1,0,0]
    Explanation: There are only 4 prefixes that are divisible
    by 3: "9", "99", "998244", and "9982443".

    Input: word = "1010", m = 10
    Output: [0,1,0,1]
    Explanation: There are only 2 prefixes that are divisible by 10: "10", and "1010".

    Constraints:
    1 <= n <= 105
    word.length == n
    word consists of digits from 0 to 9
    1 <= m <= 109

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri 09 Aug 2024 04:22:42 PM PDT
    Folsom, CA.
    Amazon
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* divisibilityArray(char * word, int m, int* returnSize) {
  const int size = strlen(word);
  int *div = malloc(size * sizeof *div);
  long long sum = 0;
  for (int i = 0; i < size; ++i) {
    sum = (sum * 10 + word[i] - '0') % m;

    div[i] = (!sum) ? 1 : 0;
  }
  *returnSize = size;
  return div;
}

void test() {
  int m = 3;
  char word[] = "998244353";
  int returnSize;

  int*ret = divisibilityArray(word, m, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[74] [test] :| Output = 1
   L=[74] [test] :| Output = 1
   L=[74] [test] :| Output = 0
   L=[74] [test] :| Output = 0
   L=[74] [test] :| Output = 0
   L=[74] [test] :| Output = 1
   L=[74] [test] :| Output = 1
   L=[74] [test] :| Output = 0
   L=[74] [test] :| Output = 0
**/
