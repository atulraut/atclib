/***
	https://leetcode.com/problems/ones-and-zeroes/submissions/
	474. Ones and Zeroes

	You are given an array of binary strings strs and two integers
	m and n.
	Return the size of the largest subset of strs such that there
	are at most m 0's and n 1's in the subset.
	A set x is a subset of a set y if all elements of x are also elements of y.

	Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
	Output: 4
	Explanation: The largest subset with at most 5 0's and 3 1's is
	{"10", "0001", "1", "0"}, so the answer is 4.
	Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
	{"111001"} is an invalid subset because it contains 4 1's, greater
	than the maximum of 3.

	Input: strs = ["10","0","1"], m = 1, n = 1
	Output: 2
	Explanation: The largest subset is {"0", "1"}, so the answer is 2.

	Constraints:
	1 <= strs.length <= 600
	1 <= strs[i].length <= 100
	strs[i] consists only of digits '0' and '1'.
	1 <= m, n <= 100

	Date : 4/3/21
	San Dieg0, CA
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

int* countFunc(char* s) {
  int* ret=(int*)calloc(2,sizeof(int));

  for(int i=0; i<strlen(s); i++)
    ret[s[i]-'0']++;

  return ret;
}

int max(int a,int b) {
  return a>b?a:b;
}

int findMaxForm(char** strs, int strsSize, int m, int n) {
  int** dp = (int**)malloc((m+1) * sizeof(int*));

  for(int i=0; i<m+1; i++)
    dp[i]=(int*)calloc(n+1,sizeof(int));

  dp[0][0]=0;

  for(int k=0; k<strsSize; k++) {
    int* temp=countFunc(strs[k]);
    for(int i=m; i>=temp[0]; --i) {
      for(int j=n; j>=temp[1]; --j) {
	dp[i][j] = max(dp[i][j], dp[i-temp[0]][j-temp[1]]+1);
      }
    }
    free(temp);
  }
  return dp[m][n];
}


int main () {
  char *strs[] = {"10","0001","111001","1","0"};
  int strsSize = sizeof(strs) / sizeof(strs[0]);

  int m = 5, n = 3;

  int result = findMaxForm(strs, strsSize, m, n);

  debug ("Result = %d \n",result);
  return 0;
}

/**
   => ./a.out
   [main] L=88 :Result = 4
**/

/***
    Approach #5 Dynamic Programming [Accepted]

    Algorithm

    This problem can be solved by using 2-D Dynamic Programming.
    We can make use of a dpdpdp array, such that an entry dp[i][j] denotes the
    maximum number of strings that can be included in the subset given
    only i 0's and j 1's are available.

    Now, let's look at the process by which we'll fill the dp array. We
    traverse the given list of strings one by one. Suppose, at some point,
    we pick up any string sks_ksk​ consisting of x zeroes and y ones.
    Now, choosing to put this string in any of the subset possible by
    using the previous strings traversed so far will impact the element
    denoted by dp[i][j] for i and j satisfying x ≤ i ≤ m, y ≤ j ≤ n.
    This is because for entries dp[i][j] with i<xi < xi<x or j<yj < yj<y,
    there won't be sufficient number of 1's and 0's available to accomodate
    the current string in any subset.

    Thus, for every string encountered, we need to appropriately update the dp
    entries within the correct range.

    Further, while updating the dpdpdp values, if we consider choosing the
    current string to be a part of the subset, the updated result will depend
    on whether it is profitable to include the current string in any subset or not.
    If included in the subset, the dp[i][j] entry needs to be updated as
    dp[i][j]=1+dp[i−zeroes(current_string)][j−ones(current_string)]
    where the factor of +1 takes into account the number of elements in the
    current subset being increased due to a new entry.

    But, it could be possible that the current string could be so long that
    it could be profitable not to include it in any of the subsets. Thus,
    the correct equation for dpdpdp updation becomes:

    dp[i][j]=max(1+dp[i−zeroescurrent_string][j−onescurrent_string], dp[i][j])

    Thus, after the complete list of strings has been traversed, dp[m][n]
    gives the required size of the largest subset.x
*/
