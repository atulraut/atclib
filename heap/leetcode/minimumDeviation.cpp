/***
    https://leetcode.com/problems/minimize-deviation-in-array/
    Hard:Minimize Deviation in Array

    You are given an array nums of n positive integers.

    You can perform two types of operations on any element of
    the array any number of times:

    If the element is even, divide it by 2.
    For example, if the array is [1,2,3,4], then you can do
    this operation on the last element, and the array will be [1,2,3,2].

    If the element is odd, multiply it by 2.
    For example, if the array is [1,2,3,4], then you can do
    this operation on the first element, and the array will be [2,2,3,4].

    The deviation of the array is the maximum difference
    between any two elements in the array.

    Return the minimum deviation the array can have after
    performing some number of operations.

    Input: nums = [1,2,3,4]
    Output: 1
    Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2],
    then the deviation will be 3 - 2 = 1.

    Input: nums = [4,1,5,20,3]
    Output: 3
    Explanation: You can transform the array after two operations
    to [4,2,5,5,3], then the deviation will be 5 - 2 = 3.

    Input: nums = [2,10,8]
    Output: 3

    Constraints:
    n == nums.length
    2 <= n <= 105
    1 <= nums[i] <= 109
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Feb 19 13:16:27 PST 2022
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
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

/*----------------------------------- Micro --------------------------------------*/
//#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

class Solution {
public:
  int minimumDeviation(vector<int>& nums) {
    set<int> range;

    for(int i = 0; i < nums.size(); i++)
      if(nums[i]%2) range.insert(nums[i]<<1);
      else  range.insert(nums[i]);

    int ans = *range.rbegin() - *range.begin();

    while(*range.rbegin() % 2 == 0){
      range.insert(*range.rbegin()>>1);
      range.erase(*range.rbegin());
      ans = min(ans, *range.rbegin() - *range.begin());
    }

    return ans;
  }
};

void test() {
  int ret = 0;
  Solution obj;
  int arr[] = {1,2,3,4};
  // Create an empty vector
  vector<int> vect;
  vect.push_back(1);
  vect.push_back(2);
  vect.push_back(3);
  vect.push_back(3);

  for (int x : vect)
    cout << x << " ";

  ret = obj.minimumDeviation (vect);
  printf("Output = %d\n\n", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   Input  = 1 2 3 3
   Output = 1
**/
