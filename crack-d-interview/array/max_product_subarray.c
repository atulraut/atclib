/*
Find the contiguous subarray within an array (containing at least one number) 
which has the largest product.
For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

int maxProduct_plus(int A[], int n) {
  int ans=A[0],i,j,sum=0;
  for(i=0;i<n;i++){
    sum+=A[i];
    ans=max(sum,ans);
    sum=max(sum,0);
    printf ("-> ans = %d sum = %d\n", ans, sum);
  }
  return ans;
}

/* Returns the product of max product subarray. 
   Assumes that the given array always has a subarray
   with product more than 1 */
int maxSubarrayProduct_multiplication(int arr[], int n)
{
  // max positive product ending at the current position
  int max_ending_here = 1;

  // min negative product ending at the current position
  int min_ending_here = 1;

  // Initialize overall max product
  int max_so_far = 1;

  /* Traverse through the array. Following values are
       maintained after the i'th iteration:
       max_ending_here is always 1 or some positive product
                       ending with arr[i]
       min_ending_here is always 1 or some negative product 
       ending with arr[i] */
  for (int i = 0; i < n; i++)
    {
      /* If this element is positive, update max_ending_here. 
           Update min_ending_here only if min_ending_here is 
           negative */
      if (arr[i] > 0)
	{
	  max_ending_here = max_ending_here*arr[i];
	  min_ending_here = min (min_ending_here * arr[i], 1);
	}

      /* If this element is 0, then the maximum product 
           cannot end here, make both max_ending_here and 
           min_ending_here 0
           Assumption: Output is alway greater than or equal 
	   to 1. */
      else if (arr[i] == 0)
	{
	  max_ending_here = 1;
	  min_ending_here = 1;
	}

      /* If element is negative. This is tricky
           max_ending_here can either be 1 or positive. 
           min_ending_here can either be 1 or negative.
           next min_ending_here will always be prev. 
           max_ending_here * arr[i] next max_ending_here
           will be 1 if prev min_ending_here is 1, otherwise 
           next max_ending_here will be prev min_ending_here *
           arr[i] */
      else
	{
	  int temp = max_ending_here;
	  max_ending_here = max (min_ending_here * arr[i], 1);
	  min_ending_here = temp * arr[i];
	}

      // update max_so_far, if needed
      if (max_so_far <  max_ending_here)
	max_so_far  =  max_ending_here;
    }

  return max_so_far;
}

int main () {
  //  int ar[] = {2, 3, 8, -2, 4, 8};
  int ar[] = {2,3,-2,4};
  int sz = sizeof(ar)/sizeof (ar[0]);
  printf ("sz -> %d \n", sz);
  int ret = 0;  
  //  ret = maxProduct_plus(ar, sz);
  ret = maxSubarrayProduct_multiplication(ar, sz);
  printf ("-> %d \n", ret);
}
