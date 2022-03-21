/***
    https://leetcode.com/problems/partition-labels

    Partition Labels

    You are given a string s. We want to partition the string into
    as many parts as possible so that each letter appears in at most one part.

    Note that the partition is done so that after concatenating all
    the parts in order, the resultant string should be s.

    Return a list of integers representing the size of these parts.

    Input: s = "ababcbacadefegdehijhklij"
    Output: [9,7,8]
    Explanation:
    The partition is "ababcbaca", "defegde", "hijhklij".
    This is a partition so that each letter appears in at most one part.
    A partition like "ababcbacadefegde", "hijhklij" is incorrect,
    because it splits s into less parts.

    Input: s = "eccbbbbdec"
    Output: [10]

    Constraints:

    1 <= s.length <= 500
    s consists of lowercase English letters.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Mar 21 09:02:28 PDT 2022
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

/***
    Approach 1: Greedy
    Intuition

    Let's try to repeatedly choose the smallest left-justified partition.
    Consider the first label, say it's 'a'. The first partition must
    include it, and also the last occurrence of 'a'. However, between
    those two occurrences of 'a', there could be other labels that make
    the minimum size of this partition bigger. For example, in "abccaddbeffe",
    the minimum first partition is "abccaddb". This gives us the idea for
    the algorithm: For each letter encountered, process the last occurrence
    of that letter, extending the current partition [anchor, j] appropriately.

    Algorithm
    We need an array last[char] -> index of S where char occurs last. Then,
    let anchor and j be the start and end of the current partition. If we
    are at a label that occurs last at some index after j, we'll extend the
    partition j = last[c]. If we are at the end of the partition (i == j)
    then we'll append a partition size to our answer, and set the start
    of our new partition to i+1.
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* partitionLabels(char* s, int* returnSize) {
  int last[26] = {0};
  *returnSize = 0;
  int *result = malloc(sizeof(int)*26);

  for (int i=0; s[i] != 0; i++)
    last[s[i]-'a'] = i;

  int end = 0, prev=0;

  for (int i=0; s[i] != 0;i++) {
    end = end > last[s[i]-'a'] ? end : last[s[i]-'a'];
    if (end == i) {
      result[(*returnSize)++] = end+1-prev;
      prev = end + 1;
    }
  }
  return result;
}

void test() {
  int* ret;
  char str[] = "ababcbacadefegdehijhklij";
  int returnSize;

  ret = partitionLabels(str, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=114 :Output = 9
   [test] L=114 :Output = 7
   [test] L=114 :Output = 8
**/
