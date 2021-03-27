/***
    923. 3Sum With Multiplicity
    https://leetcode.com/problems/3sum-with-multiplicity/solution/

    Given an integer array arr, and an integer target, return the
    number of tuples i, j, k such that i < j < k and arr[i] + arr[j] + arr[k] == target.

    As the answer can be very large, return it modulo 109 + 7.

    Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
    Output: 20
    Explanation:
    Enumerating by the values (arr[i], arr[j], arr[k]):
    (1, 2, 5) occurs 8 times;
    (1, 3, 4) occurs 8 times;
    (2, 2, 4) occurs 2 times;
    (2, 3, 3) occurs 2 times.

    Input: arr = [1,1,2,2,2,2], target = 5
    Output: 12
    Explanation:
    arr[i] = 1, arr[j] = arr[k] = 2 occurs 12 times:
    We choose one 1 from [1,1] in 2 ways,
    and two 2s from [2,2,2,2] in 6 ways.

    Constraints:
    3 <= arr.length <= 3000
    0 <= arr[i] <= 100
    0 <= target <= 300

    Date : 27 March 2021
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

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

int partition(int *a, int start, int end) {
  int pivot = a[end];
  int partitionIndex = start; // set partition index as start initially
  for (int i=start; i<end; i++) {
    if (a[i] <= pivot) {
      swap(&a[i], &a[partitionIndex]);
      partitionIndex++;
    }
  }
  swap(&a[partitionIndex], &a[end]); // swap pivot with element as partition index
  return partitionIndex;
}

void quick_sort(int *a, int start, int end) {
  if(start < end) {
    int partitionIndex = partition(a, start, end);
    quick_sort(a, start, partitionIndex-1);
    quick_sort(a, partitionIndex+1, end);
  }
}

/***
    Binomial Coefficient :
    https://mathworld.wolfram.com/BinomialCoefficient.html
*/
int threeSumMulti(int* arr, int arrSize, int target) {
  //int threeSumMulti(int[] A, int target) {
  int MOD=1e9+7;
  long ans = 0;
	
  quick_sort(arr, 0, arrSize-1);

  for (int i = 0; i < arrSize; ++i) {
    // We'll try to find the number of i < j < k
    // with arr[j] + arr[k] == T, where T = target - A[i].

    // The below is a "two sum with multiplicity".
    int T = target - arr[i];
    int j = i+1, k = arrSize - 1;

    while (j < k) {
      // These steps proceed as in a typical two-sum.
      if (arr[j] + arr[k] < T)
	j++;
      else if (arr[j] + arr[k] > T)
	k--;
      else if (arr[j] != arr[k]) {  // We have A[j] + A[k] == T.
	// Let's count "left": the number of A[j] == A[j+1] == A[j+2] == ...
	// And similarly for "right".
	int left = 1, right = 1;
	while (j+1 < k && arr[j] == arr[j+1]) {
	  left++;
	  j++;
	}
	while (k-1 > j && arr[k] == arr[k-1]) {
	  right++;
	  k--;
	}

	ans += left * right;
	ans %= MOD;
	j++;
	k--;
      } else {
	// M = k - j + 1
	// We contributed M * (M-1) / 2 pairs.
	ans += (k-j+1) * (k-j) / 2;
	ans %= MOD;
	break;
      }
    }
  }

  return (int) ans;
}

int threeSumMulti2(int* arr, int arrSize, int target){
  const int KMaxN = 100;
  const int KMod = 1e9+7;

  long* table = (long*)calloc(KMaxN+1,sizeof(long));
  long ans = 0;

  for(int i=0; i < arrSize; i++)
    table[arr[i]]++;
  
  for(int i=0; i<= target; i++) {
    for(int j=i; j<=target; j++) {
      int k = target - i - j;
      if(k<0 || k>=KMaxN+1 || k<j)
	continue;
      if(table[i]==0 || table[j]==0 || table[k]==0)
	continue;
      if(i==j && j==k)
	ans += (table[i]-2)*(table[j]-1)*(table[k])/6;
      else if(i==j && j!=k)
	ans += ((table[i]-1)*(table[j])/2)*(table[k]);
      else if (i!=j && j==k)
	ans += (table[i])*((table[j]-1)*(table[k])/2);
      else
	ans += table[i]*table[j]*table[k];
    }
  }
  return ans % KMod;
}

int main () {
  int arr[] = {1,1,2,2,3,3,4,4,5,5};
int target = 8;
int arrSize = sizeof(arr)/sizeof(arr[0]);

int output = threeSumMulti2(arr, arrSize, target);
debug ("output = %d ", output);

return 0;
}

/**
   For Algo : Check Daigram.
 **/
/**
  => ./a.out
  [main] L=136 :output = 20
 **/
