/***
    https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
    https://walkccc.me/LeetCode/problems/1547/
    1547. Minimum Cost to Cut a Stick

    Given a wooden stick of length n units. The stick is labelled from 0 to n
    For example, a stick of length 6 is labelled as follows:

    Given an integer array cuts where cuts[i] denotes a position you should
    perform a cut at.

    You should perform the cuts in order, you can change the order of the
    cuts as you wish.

    The cost of one cut is the length of the stick to be cut, the total
    cost is the sum of costs of all cuts. When you cut a stick, it will
    be split into two smaller sticks (i.e. the sum of their lengths is the
    length of the stick before the cut). Please refer to the first example
    for a better explanation.

    Return the minimum total cost of the cuts.

    Date : 4/8/2021 April
    San Diego, CA

    Status : Need Fix - Pending
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

/***
    EXTENDED-BOTTOM-UP-CUT-ROD .(p, n)
    1 let r[0..n] and s[0..n] be new arrays
    2 r[0] = 0
    3 for j = 1 to n
    4	q = -Inifinity(Symbol)
    5	for i = 1 to j
    6		if q < p[i] + r[j-i]
    7			q = p[i]+r[j-i]
    8			s[j] = i
    9	r[j] = q
    10 return r and s

    PRINT-CUT-ROD-SOLUTION .(p,n)
    1 (r,s) = EXTENDED-BOTTOM-UP-CUT-ROD (p,n)
    2 while n > 0
    3	print s[n]
    4 	n = n - s[n]
*/
int minCostWood(int* cuts, int n) {
  int r[n];
  int s[n];
  int q;

  r[0] = 0;
  for (int j=1; j<n; j++) {
    q = 0;
    for(int i=1; i<j; i++) {
      if (q < cuts[i] + r[j-i]) {
	q = cuts[i] + r[j-1];
	s[j] = i;
      }
    }
    r[j] = q;
  }

  for (int i=0; i<n; i++)
    debug("r=%d s=%d", r[i], s[i]);
}

int minCost1(int n, int* cuts, int cutsSize){

}

#define min(x, y) (((x) < (y)) ? (x) : (y))

void insertionSort(int list[], int n) {
  // sort list[0] to list[n-1] in ascedning order
  for(int h=1; h<n; h++) {
    int key = list[h];		/* I */
    int j=h-1; /* start comparing with previous item */
    while(j>=0 && key < list[j]) { /*Copy Elememnt from Unsorted(list[j]) to Sorted Array (list[j+1])*/
      list[j+1] = list[j];	/* II */
      --j;
    }
    list[j+1] = key; /* III - key will create hole, copy that at last*/
  }//end for
}//end insertionSort

//https://www.programmersought.com/article/63347326413/

int minCost(int* cuts, int n) {
  int size = sizeof(cuts) / sizeof(cuts[0]);
  int *newCuts = (int *)malloc(sizeof(char) * size + 2);

  newCuts[0] = 0;

  for(int i=0; i<size; i++)
    newCuts[i+1] = cuts[i];

  newCuts[size + 1] = n;

  insertionSort(newCuts, size+1);

  //  int[][] dp = new int[newCuts.length][newCuts.length];
  int **dp = (int **)malloc(sizeof(char) * size);

  //Enumerate the interval, len represents the length of the interval
  for(int len=2; len<size+1; len++){
    //The left end of the enumeration interval
    for(int i=0;i+len<size+1; i++){
      //j is the right end of the interval
      int j = i + len;
      dp[i][j] = INT_MAX;
      //The dividing point of the enumeration interval
      for(int k=i+1 ;k<j; k++){
	dp[i][j] = min(dp[i][j],dp[i][k]+dp[k][j]+newCuts[j]-newCuts[i]);
      }
    }
  }
  return dp[0][size-1];
}
int main() {
  int cuts[] = {1,3,4,5};
  int n = 7;

  int ret = minCost(cuts, n);
  debug ("ret = %d", ret);
  return 0;
}

