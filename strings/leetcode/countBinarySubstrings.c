/***
    Easy: Count Binary Substrings
    Give a string s, count the number of non-empty (contiguous)
    substrings that have the same number of 0's and 1's, and all
    the 0's and all the 1's in these substrings are grouped
    consecutively.

    Substrings that occur multiple times are counted the number
    of times they occur.

    Input: "00110011"
    Output: 6
    Explanation: There are 6 substrings that have equal number of
    consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".

    Notice that some of these substrings repeat and are counted the
    number of times they occur.

    Also, "00110011" is not a valid substring because all the 0's
    (and 1's) are not grouped together.

    https://leetcode.com/problems/count-binary-substrings/

    Date: 26/04/2021 April
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

#define min(a, b) ((a) < (b) ? (a) : (b))

int countBinarySubstrings(char* s){
  char curChar;
  int preCnt, curCnt, cnt;
  for (curChar = *s++, preCnt = cnt = 0, curCnt = 1; *s; s++, curCnt++) {
    debug("*s=%c curChar=%c cnt=%d preCnt=%d curCnt=%d", *s, curChar, cnt, preCnt, curCnt);
    if (*s != curChar) {
      cnt += min(preCnt, curCnt);
      curChar = *s;
      preCnt = curCnt;
      curCnt = 0;
    }
    debug("*s=%c curChar=%c cnt=%d preCnt=%d curCnt=%d", *s, curChar, cnt, preCnt, curCnt);
  }
  cnt += min(preCnt, curCnt);
  debug("cnt = %d", cnt);
  return cnt;
}

int main () {
  char *s1 = "00110011";
  char *s = "10101";

  int ret =  countBinarySubstrings(s);

  debug ("Output = %d", ret);

  return 0;
}

/***
    => ./a.out
    [countBinarySubstrings] L=47 :*s=0 curChar=1 cnt=0 preCnt=0 curCnt=1
    [countBinarySubstrings] L=54 :*s=0 curChar=0 cnt=0 preCnt=1 curCnt=0
    [countBinarySubstrings] L=47 :*s=1 curChar=0 cnt=0 preCnt=1 curCnt=1
    [countBinarySubstrings] L=54 :*s=1 curChar=1 cnt=1 preCnt=1 curCnt=0
    [countBinarySubstrings] L=47 :*s=0 curChar=1 cnt=1 preCnt=1 curCnt=1
    [countBinarySubstrings] L=54 :*s=0 curChar=0 cnt=2 preCnt=1 curCnt=0
    [countBinarySubstrings] L=47 :*s=1 curChar=0 cnt=2 preCnt=1 curCnt=1
    [countBinarySubstrings] L=54 :*s=1 curChar=1 cnt=3 preCnt=1 curCnt=0
    [countBinarySubstrings] L=57 :cnt = 4
    [main] L=67 :Output = 4
*/
