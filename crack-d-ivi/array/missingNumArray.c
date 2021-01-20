/******************************************************************************
Given an array of size n-1 and given that there are numbers from 1 to n with one missing, the missing number is to be found.
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
Example:
Input
2
5
1 2 3 5
10
1 2 3 4 5 6 7 8 10
Output
4
9
*******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
/*Algorithm:
1. Get the sum of numbers 
       total = n*(n+1)/2
2  Subtract all the numbers from sum and
   you will get the missing number.
   Issue - Time Complexity: O(n)
There can be overflow if n is large. In order to avoid Integer Overflow, we can pick one number from known numbers and subtract one number from given numbers. This way we wont have Integer Overflow ever. Thanks to Sahil Rally for suggesting this improvement.
*/
/* getMissingNo takes array and size of array as arguments*/
int getMissingNo (int a[], int n) {
    int i, total;
    total  = (n+1)*(n+2)/2;  
    printf("total 0 --> [%d] \n", total);
    for ( i = 0; i< n; i++) {
        printf ("total =%d, a[%d]=%d  ", total, i, a[i]);
        total -= a[i];
        printf("total 1 --> [%d] \n", total);
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
 
/*program to test above function */
int main() {
    int a[] = {1,2,4,5,6};
    int miss = getMissingNo(a,5);
    printf("\n\n Output --> [%d] \n", miss);
    miss = getMissingNoXOR(a, 5);
    printf("\n Output = %d \n", miss);
    getchar();
}
