/***
    https://leetcode.com/problems/palindrome-partitioning/description/
    131. Medium: Palindrome Partitioning
    Given a string s, partition s such that every substring of the partition
    is a palindrome. Return all possible palindrome partitioning of s.

    A palindrome string is a string that reads the same backward as forward.

    Input: s = "aab"
    Output: [["a","a","b"],["aa","b"]]

    Input: s = "a"
    Output: [["a"]]

    Constraints:

    1 <= s.length <= 16
    s contains only lowercase English letters.

    https://leetcode.com/problems/palindrome-partitioning/

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed 14 Aug 2024 10:09:22 PM PDT
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

char** slate;
int slateLen;
char*** ans;
int* ansSize;

// Determine whether a string is a reply text string
bool isPalindrome(char* str, int startIndex, int endIndex) {
  /* Double pointer method: Traverse when the value
     of endIndex (right pointer) is greater than startIndex (left pointer) */
  while(endIndex >= startIndex) {
    // If the left pointer and right pointer point to different elements, return False
    if(str[endIndex--] != str[startIndex++])
      return 0;
  }
  return 1;
}

void backTracking(char* str, int strLen,  int startIndex, int *returnSize) {
  if(startIndex >= strLen) {
    ans[*returnSize] = (char**)malloc(sizeof(char*) * slateLen);
    memcpy(ans[*returnSize], slate, sizeof(char*) * slateLen);
    ansSize[(*returnSize)++] = slateLen;
    return ;
  }

  for(int i = startIndex; i < strLen; i++) {
    // If the substring from subString to i is a palindrome string, put it in slate
    if(isPalindrome(str, startIndex, i)) {
      slate[slateLen] = malloc(sizeof(char)*(i-startIndex+2));
      snprintf(slate[slateLen++],(i-startIndex+2), "%s'\0'" , str+startIndex );
    }
    // If the substring from startIndex to i is not a palindrome string, skip this level
    else {
      continue;
    }
    // Recursively judge the next level
    backTracking(str, strLen, i + 1, returnSize);
    // Backtrace, pop out the last element in slate
    slateLen--;
  }
}

char*** partition(char* s, int* returnSize, int** returnColumnSizes){
  int strLen = strlen(s);
  /* Because the strings in slate are at most strLen (that is, a
     single-character palindrome string), so strLen char* spaces are opened up. */
  slate = (char**)malloc(sizeof(char*) * strLen);
  // Store the array results in slate
  ans = (char***)malloc(sizeof(char**) * 40000);
  // Store the length of each char** array in the ans array
  ansSize = (int*)malloc(sizeof(int) * 40000);
  slateLen = 0;
  *returnSize = 0;
  // Backtracking function
  backTracking(s, strLen, 0, returnSize);

  // Set ansTop to the length of the ans array
  // Set the length of each array in the ans array
  *returnColumnSizes = ansSize;
  return ans;
}

void test() {
  char s[] = "aab";
  int returnSize = 0;
  int* returnColumnSizes;

  char ***ret =  partition(s, &returnSize, &returnColumnSizes);
  for (int i=0; i<returnSize; ++i) {
    for(int j=0; j<*returnColumnSizes; ++j) {
      debug("Output = %s", ret[i][j]);
    }
  }
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/***
    => ./a.out
    L=[112] [test] :| Output = a
    L=[112] [test] :| Output = a
    L=[112] [test] :| Output = b
    L=[112] [test] :| Output = aa
    L=[112] [test] :| Output = b
*/
