/***
    Easy: 1427. Perform String Shifts
    https://leetcode.com/problems/perform-string-shifts/

    You are given a string s containing lowercase English letters,
    and a matrix shift, where shift[i] = [directioni, amounti]:

    directioni can be 0 (for left shift) or 1 (for right shift).
    amounti is the amount by which string s is to be shifted.
    A left shift by 1 means remove the first character of s and
    append it to the end.
    Similarly, a right shift by 1 means remove the last character
    of s and add it to the beginning.

    Return the final string after all operations.

    Input: s = "abc", shift = [[0,1],[1,2]]
    Output: "cab"
    Explanation:
    [0,1] means shift to left by 1. "abc" -> "bca"
    [1,2] means shift to right by 2. "bca" -> "cab"

    Input: s = "abcdefg", shift = [[1,1],[1,1],[0,2],[1,3]]
    Output: "efgabcd"
    Explanation:
    [1,1] means shift to right by 1. "abcdefg" -> "gabcdef"
    [1,1] means shift to right by 1. "gabcdef" -> "fgabcde"
    [0,2] means shift to left by 2. "fgabcde" -> "abcdefg"
    [1,3] means shift to right by 3. "abcdefg" -> "efgabcd"

    Constraints:
    1 <= s.length <= 100
    s only contains lower case English letters.
    1 <= shift.length <= 100
    shift[i].length == 2
    directioni is either 0 or 1.
    0 <= amounti <= 100

    April 26 2021
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

char* stringShift(char* s, int shift[][2], int shiftSize, int* shiftColSize) {
  int index;
  int loop;
  int shiftDirection;
  int shiftSteps;
  int time;
  int summaryActions;
  char temp;

  summaryActions = 0;

  // Add up the left shifts and right shifts
  for (index=0; index < shiftSize; index++) {

    shiftDirection = **(shift+index);
    shiftSteps = *(*(shift+index)+1);

    debug("shiftDirection=%d shiftSteps=%d", shiftDirection, shiftSteps);

    if (shiftDirection == 0) {
      summaryActions -= shiftSteps;
    } else if (shiftDirection == 1 ) {
      summaryActions += shiftSteps;
    }
  }

  debug("summaryActions=%d", summaryActions);
  summaryActions %= abs(strlen(s));
  debug("summaryActions=%d", summaryActions);

  // Determine which shift (if any) to perform.
  if (summaryActions < 0) {
    for (time = 0; (time < abs(summaryActions)); time++) {
      temp = *(s);
      for (loop = 0; loop < strlen(s); loop++) {
	*(s+loop) = *(s+loop+1);
      }
      *(s+loop-1) = temp;
    }
  } else if (summaryActions > 0) {
    for (time=0; time < summaryActions; time++) {
      temp = *(s+strlen(s)-1);
      for (loop = (strlen(s)-1); loop > 0; loop--) {
	*(s+loop) = *(s+loop-1);
      }
      *(s) = temp;
    }
  }
  return s;
}

int main() {
  char s[] = "abc";
  int shift[2][2] = {
    {0,1},
    {1,2},
  };

  int shiftSize = 2;
  int shiftColSize;

  char*ret = stringShift(s, shift, shiftSize, &shiftColSize);
  debug("Output = %s", ret);

  return 0;
}
