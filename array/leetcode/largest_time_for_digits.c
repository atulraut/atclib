/***
    LeetCode : Largest Time for Given Digits
    Given an array arr of 4 digits, find the latest 24-hour time that
    can be made using each digit exactly once.
    24-hour times are formatted as "HH:MM", where HH is between 00 and 23,
    and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the
    latest is 23:59.
    Return the latest 24-hour time in "HH:MM" format.  If no valid time
    can be made, return an empty string.

    Example 1:
    Input: A = [1,2,3,4]
    Output: "23:41"
    Explanation: The valid 24-hour times are "12:34", "12:43", "13:24", "13:42", "14:23",
    "14:32", "21:34", "21:43", "23:14", and "23:41". Of these times, "23:41" is the latest.
    Example 2:
    Input: A = [5,5,5,5]
    Output: ""
    Explanation: There are no valid 24-hour times as "55:55" is not valid.
    Example 3:
    Input: A = [0,0,0,0]
    Output: "00:00"
    Example 4:
    Input: A = [0,0,1,0]
    Output: "10:00"
    Constraints:
    arr.length == 4
    0 <= arr[i] <= 9
    Logic Basics : https://www.youtube.com/watch?v=sn6r0ZV_2y4
    INT_MIN 2147483648
*/

#include "../../at_lib.h"

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int max(int a, int b) {
  return a > b ? a : b;
}

char * largestTimeFromDigits(int* A, int ASize){
  assert(ASize == 4);

  int mx = INT_MIN;

  for (int i = 0; i < 4; ++i) {
    swap(A + 0, A + i);

    for (int j = 1; j < 4; ++j) {
      swap(A + 1, A + j);

      int hr = A[0]*10 + A[1];
      if (hr < 24) {
for (int k = 2; k < 4; ++k) {
  swap(A + 2, A + k);

  int mn = A[2]*10 + A[3];
  if (mn < 60) {
    int val = hr*60 + mn;
    mx = max(mx, val);
    printf ("[%s] mx = %d L=%d \n", __func__, mx, __LINE__);
  }

  swap(A + 2, A + k);
} // K For Loop Ends

      } // hr < 24 If Ends

      swap(A + 1, A + j);

    } // J for Loop Ends
    swap(A + 0, A + i);

  } // I, 1st For Loop Ends

  printf ("[%s] mx = %d L=%d \n", __func__, mx, __LINE__);
  char* ans;
  if (mx != INT_MIN) {
    ans = malloc(6 * sizeof(char));
    sprintf(ans, "%02d:%02d", mx/60, mx%60);
  }
  else {
    ans = malloc(1 * sizeof(char));
    ans[0] = 0;
  }

  return ans;
}


int main () {
  int arr[] = {1, 2, 3, 4};
  //int arr[] = {5, 5, 5, 5};
  int aSize = sizeof(arr) / sizeof(arr[0]);
  char *ret = NULL;
  ret = largestTimeFromDigits(arr, aSize);
  printf ("[%s] output = %s \n", __func__, ret);
  free(ret);
  ret = NULL;
}
