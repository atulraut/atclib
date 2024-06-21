/***

    https://leetcode.com/problems/student-attendance-record-i/
    551. Student Attendance Record I

    You are given a string s representing an attendance record for a student
    where each character signifies whether the student was absent, late, or
    present on that day. The record only contains the following three characters:

    'A': Absent.
    'L': Late.
    'P': Present.
    The student is eligible for an attendance award if they meet both of the
    following criteria:

    The student was absent ('A') for strictly fewer than 2 days total.
    The student was never late ('L') for 3 or more consecutive days.
    Return true if the student is eligible for an attendance award, or false otherwise.

    Input: s = "PPALLP"
    Output: true
    Explanation: The student has fewer than 2 absences and was never late 3
    or more consecutive days.

    Input: s = "PPALLL"
    Output: false
    Explanation: The student was late 3 consecutive days in the last 3 days,
    so is not eligible for the award.

    Constraints:

    1 <= s.length <= 1000
    s[i] is either 'A', 'L', or 'P'.
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun 26 May 2024 11:12:24 AM PDT
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

bool checkRecord(char* s) {

  int A = 0, L = 0;
  while(*s != '\0') {
    if(*s == 'A') {
      L = 0; A++;
      if(A > 1) { return false;}
    } else if(*s == 'L') {
      L++;
      if(L > 2) { return false; }
    } else {
      L = 0;
    }

    s++;
  }

  return true;
}

void test() {
  int ret = 0;
  ret = checkRecord("PPALLP");
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[77] [test] :| Output = 1
**/
