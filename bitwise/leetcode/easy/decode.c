/***
    LeedCode : https://leetcode.com/problems/decode-xored-array/
    There is a hidden integer array arr that consists of n non-negative integers.

    It was encoded into another integer array encoded of length n - 1,
    such that encoded[i] = arr[i] XOR arr[i + 1]. For example, if arr = [1,0,2,1], then encoded = [1,2,3].

    You are given the encoded array. You are also given an integer first,
    that is the first element of arr, i.e. arr[0].
    Return the original array arr. It can be proved that the answer exists
    and is unique.

    Example 1:
    Input: encoded = [1,2,3], first = 1
    Output: [1,0,2,1]
    Explanation: If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0 XOR 2, 2 XOR 1] = [1,2,3]

    Example 2:
    Input: encoded = [6,2,7,3], first = 4
    Output: [4,2,0,7,4]

    Constraints:
    2 <= n <= 104
    encoded.length == n - 1
    0 <= encoded[i] <= 105
    0 <= first <= 105
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* decode(int* encoded, int encodedSize, int first, int* returnSize) {
  *returnSize = encodedSize + 1;
  int index = 0, i;
  int *final = (int *)malloc(*returnSize * sizeof(int));
  if(NULL == final)
    return NULL;

  final[index++] = first;
  for (i=0; i<encodedSize; i++)
    final[index++] = encoded[i] ^ final[index-1];

  return final;
}

int main () {
  int encoded[] = {1, 2, 3};
  int encodedSize = sizeof(encoded) / sizeof(encoded[0]);
  int first = 1;
  int returnSize;
  int*ret = decode(encoded, encodedSize, first, &returnSize);

  for (int i=0; i<returnSize; i++)
    debug ("ret[%d] = %d", i, ret[i]);

  free(ret);
  ret = NULL;
  return 0;
}

/**
   gcc decode.c -o main -Wall -Werror -g -fsanitize=address
   => ./main
   [main] L=74 :ret[0] = 1
   [main] L=74 :ret[1] = 0
   [main] L=74 :ret[2] = 3
   [main] L=74 :ret[3] = 2
**/
