/***
    Height Checker
    A school is trying to take an annual photo of all the students.
    The students are asked to stand in a single file line in non-decreasing
    order by height. Let this ordering be represented by the integer array
    expected where expected[i] is the expected height of the ith student in line.

    You are given an integer array heights representing the current order
    that the students are standing in. Each heights[i] is the height of the
    ith student in line (0-indexed).

    Return the number of indices where heights[i] != expected[i].

    Input: heights = [1,1,4,2,1,3]
    Output: 3
    Explanation:
    heights:  [1,1,4,2,1,3]
    expected: [1,1,1,2,3,4]
    Indices 2, 4, and 5 do not match.

    Input: heights = [5,1,2,3,4]
    Output: 5
    Explanation:
    heights:  [5,1,2,3,4]
    expected: [1,2,3,4,5]
    All indices do not match.

    Input: heights = [1,2,3,4,5]
    Output: 0
    Explanation:
    heights:  [1,2,3,4,5]
    expected: [1,2,3,4,5]
    All indices match.

    Date: 29 August 2021
    Fair Oaks, CA.
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

int heightChecker(int* heights, int heightsSize) {
  int n=0;
  int nums[heightsSize];
  int count=0;

  /* Copy heights array to nums array. */
  for(int i=0; i<heightsSize; i++)
    nums[n++]=heights[i];

  /* Sort heights Array */
  for(int i=0; i<heightsSize-1; i++) {
    for(int j=0; j<heightsSize-1-i; j++) {
      if(heights[j] > heights[j+1]) {
	int temp=heights[j];
	heights[j]=heights[j+1];
	heights[j+1]=temp;
      }
    }
  }

  /* Print sorted array */
  for(int i=0; i<heightsSize-1; i++)
    debug("Sorted Array arr[%d]=%d", i, heights[i]);

  /* Check heights array with nums array */
  int i=0,j=0;
  while(i<heightsSize && j<n) {
    if(heights[i] != nums[j])
      count+=1;

    i++, j++;
  }
  return count;
}

int main (int argc, char **argv) {
  int ret = 0;

  int heights[] = {1, 1, 4, 2, 1, 3};
  int heightsSize = sizeof(heights)/sizeof(heights[0]);
  ret = heightChecker(heights, heightsSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   [heightChecker] L=74 :Sorted Array arr[0]=1
   [heightChecker] L=74 :Sorted Array arr[1]=1
   [heightChecker] L=74 :Sorted Array arr[2]=1
   [heightChecker] L=74 :Sorted Array arr[3]=2
   [heightChecker] L=74 :Sorted Array arr[4]=3
   [main] L=93 :Output = 3
**/
