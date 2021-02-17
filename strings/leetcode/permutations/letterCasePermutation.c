/***
    Letter Case Permutation
    https://leetcode.com/problems/letter-case-permutation/

    Given a string S, we can transform every letter individually to be lowercase
    or uppercase to create another string.

    Return a list of all possible strings we could create. You can return
    the output in any order.
    Example 1:
    Input: S = "a1b2"
    Output: ["a1b2","a1B2","A1b2","A1B2"]

    Example 2:
    Input: S = "3z4"
    Output: ["3z4","3Z4"]

    Example 3:
    Input: S = "12345"
    Output: ["12345"]

    Example 4:
    Input: S = "0"
    Output: ["0"]

    Constraints:
    S will be a string with length between 1 and 12.
    S will consist only of letters or digits.

    Date : 16 Feb 2021
    San Diego, CA
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../../at_lib.h"

/**
   Approch 2 : 12ms
**/
char** letterCasePermutation2(char* S, int* returnSize) {
  int len=strlen(S);

  char **a;

  if (len==0) {
    *returnSize=1;
    a=(char**)malloc(sizeof(char*));
    a[0]=S;
    return a;
  }

  int k=0, i;

  for (i=0; i<len; i++)
    if (isalpha(S[i]))
      k++;
  int j = 0, upperb = 1<<k;
  debug ("k = %d upperb = %d", k, upperb);
  a=(char **)malloc(upperb * sizeof(char *));

  for (i=0; i<upperb; i++) {
    a[j] = (char *)malloc(len+1);
    a[j][len] = 0;

    int i1 = i;
    for (int m=len-1; m>=0; m--)
      if (isalpha(S[m])) {
	a[j][m] = (i1 & 1) ? toupper(S[m]) : tolower(S[m]);
	i1 >>= 1;
	debug ("i1=%d (i1 & 1)=%d", i1, (i1 & 1));
      } else
	  a[j][m] = S[m];
    j++;
  }

  *returnSize=j;
  return a;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void dfs(char* S, char* tS, int index, char** ans, int* returnSize) {
  if(S[index] == '\0') {
      tS[index] = '\0';
      ans[*returnSize] = malloc(index + 1);
      memcpy(ans[*returnSize], tS, index + 1);
      ++*returnSize;

      return;
    }

  if(isalpha(S[index])) {
      tS[index] = tolower(S[index]);
      dfs(S, tS, index + 1, ans, returnSize);

      tS[index] = toupper(S[index]);
      dfs(S, tS, index + 1, ans, returnSize);
    } else {
      tS[index] = S[index];
      dfs(S, tS, index + 1, ans, returnSize);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCasePermutation(char* S, int* returnSize) {
  if (NULL == S)
    return NULL;

  int len = strlen(S);

  int** ans = calloc(10000, sizeof(char*));
  *returnSize = 0;

  char* tS = malloc(strlen(S) + 1);
  memcpy(tS, S, len + 1);

  dfs(S, tS, 0, ans, returnSize);

  free(tS);

  return ans;

}

int main () {
  char str1[] = "3z4";
  char str[] = "a1b2";
  int returnSize = 0;

  char **ptr = letterCasePermutation2(str, &returnSize);

  for (int i=0; i<returnSize; i++)
    debug (" Combination[%d] = %s ",i, ptr[i]);

  return 0;
}

/**
   => ./a.out
   [main] L=133 : Combination[0] = 3z4
   [main] L=133 : Combination[1] = 3Z4

   => ./a.out
   [main] L=134 : Combination[0] = a1b2
   [main] L=134 : Combination[1] = a1B2
   [main] L=134 : Combination[2] = A1b2
   [main] L=134 : Combination[3] = A1B2
**/
