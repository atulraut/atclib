/***
    848. Shifting Letters
    You are given a string s of lowercase English letters and
    an integer array shifts of the same length.
    Call the shift() of a letter, the next letter in the
    alphabet, (wrapping around so that 'z' becomes 'a').
    For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.
    Now for each shifts[i] = x, we want to shift the first
    i + 1 letters of s, x times.
    Return the final string after all such shifts to s are applied.

    Input: s = "abc", shifts = [3,5,9]
    Output: "rpl"
    Explanation: We start with "abc".
    After shifting the first 1 letters of s by 3, we have "dbc".
    After shifting the first 2 letters of s by 5, we have "igc".
    After shifting the first 3 letters of s by 9, we have "rpl", the answer.

    Input: s = "aaa", shifts = [1,2,3]
    Output: "gfd"

    Constraints:
    1 <= s.length <= 105
    s consists of lowercase English letters.
    shifts.length == s.length
    0 <= shifts[i] <= 109

    https://leetcode.com/problems/shifting-letters/
    Date: 9/9/2021
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

char* shiftingLetters_1(char* s, int* shifts, int shiftsSize) {
  long long x;
  int i;

  x = -('a' % 26);
  debug ("x = %lld 'a' % 26= %d", x, ('a' % 26));
  for (i = shiftsSize - 1; i >= 0; --i)
    s[i] = (s[i] + (x += shifts[i])) % 26 + 'a';

  return s;
}

char* shiftingLetters_AR(char* s, int* shifts, int shiftsSize) {
  int j = 0;
  int k = 0;
  //shiftsSize -= 1;

  for (int i=shiftsSize; i>=1; --i) {
    debug("s[%d]=%c", i, s[i]);
    j = shiftsSize - i;
    debug("<<<<<< j = %d >>>>>>>>>>", j);
    for (k=0; k<=j; ++k) {  // j will loop number of times we want to shift e.g. 1,2,3
      debug ("k = %d s[j]=%c shifts[j]=%d", k, s[k], shifts[k]);
      s[k] = s[k] + shifts[j];
      debug("<<<<** s[%d] = %c **>>>>", j, s[j]);
    }
  }
  return s;
}

char * shiftingLetters(char* s, int* shifts, int shiftsSize){
  int shiftAmt = 0;

  //go through and adjust letters by the right amount.
  for(int i = shiftsSize - 1; i >= 0; i--){
    shiftAmt = (shiftAmt + shifts[i]) % 26;
    debug ("shiftAmt=%d", shiftAmt);
    if(s[i] + shiftAmt > 122)
      s[i] -= 26;

    s[i] += shiftAmt;
  }

  return s;
}

int main (int argc, char **argv) {
  int ret = 0;
  char s[] = "bad";
  char s2[] = "abc";
  char s1[] = "aaa";
  int shifts2[] = {3,5,9};
  int shifts1[] = {1,2,3};
  int shifts[] = {10,20,30};
  int shiftsSize = sizeof(shifts)/sizeof(shifts[0]);

  debug("Output = %s", shiftingLetters(s, shifts, shiftsSize));

  return 0;
}

/**

 **/
