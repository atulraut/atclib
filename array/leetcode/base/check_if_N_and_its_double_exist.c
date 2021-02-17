/***
    LeetCode : Check If N and Its Double Exist
    https://leetcode.com/explore/featured/card/fun-with-arrays/527/searching-for-items-in-an-array/3250/

    Given an array arr of integers, check if there exists two
    integers N and M such that N is the double of M ( i.e. N = 2 * M).

    More formally check if there exists two indices i and j such that :

    i != j
    0 <= i, j < arr.length
    arr[i] == 2 * arr[j]


    Example 1:
    Input: arr = [10,2,5,3]
    Output: true
    Explanation: N = 10 is the double of M = 5,that is, 10 = 2 * 5.

    Example 2:
    Input: arr = [7,1,14,11]
    Output: true
    Explanation: N = 14 is the double of M = 7,that is, 14 = 2 * 7.

    Example 3:
    Input: arr = [3,1,7,11]
    Output: false
    Explanation: In this case does not exist N and M, such that N = 2 * M.

    Constraints:
    2 <= arr.length <= 500
    -10^3 <= arr[i] <= 10^3
*/

#include <stdio.h>
#include "../../../at_lib.h"
/***
    4ms
*/
bool checkIfExist(int* arr, int arrSize){
  int i, j;
  for (i=0; i<arrSize-1; i++)
    for (j=i+1; j<arrSize; j++)
      if ((arr[i] == 2*arr[j]) || (arr[j] == 2*arr[i]))
	return true;
  return false;
}

/***
    0ms
    Algo :
    On each step of the loop check if we have seen the
    element 2 * arr[i] so far or arr[i] / 2 was seen if arr[i] % 2 == 0.
*/
bool checkIfExist2(int* arr, int arrSize){
  int       ahash[4001];
  int       count;

  memset( ahash, 0, ( 4001 * sizeof( int ) ) );

  for ( count = 0; count < arrSize; count++ ){
    if ( ( ( (arr[count] % 2) == 0 ) &&
	   ( ahash[(arr[count]/2) + 2000 ] ) ) ||
	 ( ahash[(2 * arr[count]) + 2000 ] ) ) {
      return true;
    }

    ahash[arr[count] + 2000] = 1;
  }

  return false;
}

int main() {
  int arr[] = {7, 1, 14, 11};

  if(checkIfExist(arr, 4))
    debug ("Found = %d", checkIfExist(arr, 4));
  else
    debug ("NOT Found = %d", checkIfExist(arr, 4));
  return 0;
}

/***
    => ./a.out
    [main] L=77 :Found = 1

*/
