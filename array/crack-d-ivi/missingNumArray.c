/***
    Given an array of size n-1 and given that there are numbers from
    1 to n with one missing, the missing number is to be found.

    Input:
    The first line of input contains an integer T denoting the number of test cases.
    The first line of each test case is N.
    The second line of each test case contains N-1 input C[i],numbers in array.

    Output:
    Print the missing number in array.

    Constraints:
    1 ≤ T ≤ 200
    1 ≤ N ≤ 1000
    1 ≤ C[i] ≤ 1000

    Input
    2
    5
    1 2 3 5
    10
    1 2 3 4 5 6 7 8 10
    Output
    4
    9
*/
/**
  Algorithm:
  1. Get the sum of numbers
  total = n*(n+1)/2
  2  Subtract all the numbers from sum and
  you will get the missing number.
  Issue - Time Complexity: O(n)
  There can be overflow if n is large. In order to avoid Integer Overflow,
  we can pick one number from known numbers and subtract one number from given
  numbers. This way we wont have Integer Overflow ever. Thanks to Sahil
  Rally for suggesting this improvement.
**/
#include <stdio.h>
#include <stdarg.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/* getMissingNo takes array and size of array as arguments*/
int getMissingNo (int a[], int n) {
  int i, total;
  total  = (n+1)*(n+2)/2;
  printf("[%s] total = %d L=%d \n",__func__, total, __LINE__);
  for ( i = 0; i< n; i++) {
    printf ("[%s] total = %d, a[%d] = %d   L=%d ", __func__, total, i, a[i], __LINE__);
    total -= a[i];
    printf("[%s] total = %d L=%d \n", __func__, total, __LINE__);
  }
  return total;
}
/*
  METHOD 2(Use XOR)
  1) XOR all the array elements, let the result of XOR be X1.
  2) XOR all numbers from 1 to n, let XOR be X2.
  3) XOR of X1 and X2 gives the missing number.
*/
/* getMissingNo takes array and size of array as arguments*/
int getMissingNoXOR(int a[], int n) {
  int i;
  int x1 = a[0]; /* For xor of all the elements in array */
  int x2 = 1; /* For xor of all the elements from 1 to n+1 */

  for (i = 1; i< n; i++)
    x1 = x1^a[i];

  for ( i = 2; i <= n+1; i++)
    x2 = x2^i;

  return (x1^x2);
}

/***
    LeetCode : https://leetcode.com/problems/missing-number/
    Note : It need 1 element in array 0.
 */
int missingNumber(int* nums, int numsSize){
  int missing = numsSize;
   for (int i = 0; i < numsSize; i++) {
            missing ^= i ^ nums[i];
        }
        return missing;
}

/*program to test above function */
int main() {
  int a[] = {1,2,4,5,6};
  int a1[] = {1,2,4,5,0};
  int miss = getMissingNo(a,5);
  debug ("Output --> [%d] \n", miss);
  miss = getMissingNoXOR(a, 5);
  debug ("Output = %d \n", miss);

  miss = missingNumber(a1, 5);
  debug ("Output = %d \n", miss);

}

/**
=> ./a.out
[getMissingNo] total = 15 L=44
[getMissingNo] total = 15, a[0] = 1   L=46 [getMissingNo] total = 14 L=48
[getMissingNo] total = 14, a[1] = 2   L=46 [getMissingNo] total = 12 L=48
[getMissingNo] total = 12, a[2] = 4   L=46 [getMissingNo] total = 8 L=48
[getMissingNo] total = 8, a[3] = 5   L=46 [getMissingNo] total = 3 L=48
[getMissingNo] total = 3, a[4] = 6   L=46 [getMissingNo] total = -3 L=48

 [main] Output --> [-3]

 [main] Output = 3
 **/
