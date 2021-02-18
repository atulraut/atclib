/***
    LeetCode :
    Container With Most Water

    Given n non-negative integers a1, a2, ..., an , where each represents a
    point at coordinate (i, ai). n vertical lines are drawn such that the two
    endpoints of the line i is at (i, ai) and (i, 0). Find two lines, which,
    together with the x-axis forms a container, such that the container
    contains the most water.

    Notice that you may not slant the container.
    https://leetcode.com/problems/container-with-most-water
    Date : 17/02/2021
    San Diego, CA
*/
#include <stdio.h>
#include <stdlib.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
/**
   Start with the maximum width container and go to a shorter width container if
   there is a vertical line longer than the current containers shorter line.
   This way we are compromising on the width but we are looking forward to
   a longer length container.
   Area = length of shorter vertical line * distance between lines
**/
int maxArea(int* height, int heightSize){
  int len = heightSize, low = 0, high = len -1 ;
   int water = 0;
   while (low < high) {
     water = max(water, (high - low) * min(height[low], height[high]));
     if (height[low] < height[high]) {
       low++;
     } else {
       high--;
     }
     debug ("low = %d high=%d water=%d", low, high, water);
   }
   return water;
}

int main () {
  int arr1[] = {1,8,6,2,5,4,8,3,7};
  int arr[] = {4,3,2,1,4};
  int sz = sizeof(arr) / sizeof(arr[0]);
  int ret = maxArea(arr, sz);
  debug ("ret = %d", ret);

  return 0;
}

/**
   Ref : https://leetcode.com/problems/container-with-most-water/discuss/6100/Simple-and-clear-proofexplanation
   Idea / Proof:
   The widest container (using first and last line) is a good candidate,
   because of its width. Its water level is the height of the smaller one of first and last line.
   All other containers are less wide and thus would need a higher water
   level in order to hold more water.
   The smaller one of first and last line doesn't support a higher water level
   and can thus be safely removed from further consideration.

   Implementation: (Python)

   class Solution:
      def maxArea(self, height):
         i, j = 0, len(height) - 1
         water = 0
         while i < j:
               water = max(water, (j - i) * min(height[i], height[j]))
               if height[i] < height[j]:
                  i += 1
               else:
                  j -= 1
     return water

   Further explanation: j = high i = low

   Variables i and j define the container under consideration.
   We initialize them to first and last line, meaning the widest container.
   Variable water will keep track of the highest amount of water we managed so far.
   We compute j - i, the  width of the current container,
   and min(height[i], height[j]), the water level that this container can support.
   Multiply them to get how much water this container can hold, and update water
   accordingly.
   Next remove the smaller one of the two lines from consideration, as justified
   above in "Idea / Proof".
   Continue until there is nothing left to consider, then return the result.
**/

/**
   arr1[] = {4,3,2,1,4};
   => ./a.out
   [maxArea] L=39 :low = 0 high=3 water=16
   [maxArea] L=39 :low = 0 high=2 water=16
   [maxArea] L=39 :low = 0 high=1 water=16
   [maxArea] L=39 :low = 0 high=0 water=16
   [main] L=49 :ret = 16

   arr[] = {1,8,6,2,5,4,8,3,7}
   [maxArea] L=39 :low = 1 high=8 water=8
   [maxArea] L=39 :low = 1 high=7 water=49
   [maxArea] L=39 :low = 1 high=6 water=49
   [maxArea] L=39 :low = 1 high=5 water=49
   [maxArea] L=39 :low = 1 high=4 water=49
   [maxArea] L=39 :low = 1 high=3 water=49
   [maxArea] L=39 :low = 1 high=2 water=49
   [maxArea] L=39 :low = 1 high=1 water=49

   Complexity Analysis :
   Time complexity : O(n)O(n)O(n). Single pass.
   Space complexity : O(1)O(1)O(1). Constant space is used.
**/
