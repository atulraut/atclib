/***
    Maximum Length of a Concatenated String with
    Unique Characters

    Given an array of strings arr. String s is a
    concatenation of a sub-sequence of arr which
    have unique characters.

    Return the maximum possible length of s.

    Input: arr = ["un","iq","ue"]
    Output: 4
    Explanation: All possible concatenations are
    "","un","iq","ue","uniq" and "ique".
    Maximum length is 4.

    Input: arr = ["cha","r","act","ers"]
    Output: 6
    Explanation: Possible solutions are "chaers" and "acters".

    Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
    Output: 26

    Constraints:

    1 <= arr.length <= 16
    1 <= arr[i].length <= 26
    arr[i] contains only lower case English letters.

    https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
    Date: 22 Sept 2021
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

void backtrack(int *bits, int n, int pos, int t, int *len) {
    int l = 0, prev, i;
    prev = t;
    while (prev) {
        l++;
        prev &= prev - 1;
    }
    if (l > *len)
        *len = l;
    for (i = pos; i < n; i++) {
        if ((t & bits[i]) != 0)
            continue;
        backtrack(bits, n, i+1, t | bits[i], len);
    }
}

int maxLength(char** arr, int arrSize) {
    int *bits, i, j, len = 0;
    bits = calloc(arrSize, sizeof(*bits));
    for (i = 0; i < arrSize; i++) {
        for (j = 0; j < strlen(arr[i]); j++) {
            if ((bits[i] & 1 << (arr[i][j] - 'a')) != 0) {
                bits[i] = 0;
                break;
            }
            bits[i] |= 1 << (arr[i][j] - 'a');
        }
    }
    backtrack(bits, arrSize, 0, 0, &len);
    return len;
}

int main (int argc, char **argv) {
  int ret = 0;

  char* arr[] = {"cha","r","act","ers"};
  int arrSize = 4;
  ret = maxLength(arr, arrSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=86 :Output = 6
**/
