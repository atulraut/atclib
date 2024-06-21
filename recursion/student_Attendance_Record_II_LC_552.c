/***

    https://leetcode.com/problems/student-attendance-record-ii/
    552. Student Attendance Record II
    Hard
    An attendance record for a student can be represented as a string
    where each character signifies whether the student was absent, late,
    or present on that day. The record only contains the following
    three characters:

    'A': Absent.
    'L': Late.
    'P': Present.
    Any student is eligible for an attendance award if they meet
    both of the following criteria:

    The student was absent ('A') for strictly fewer than 2 days total.
    The student was never late ('L') for 3 or more consecutive days.
    Given an integer n, return the number of possible attendance records
    of length n that make a student eligible for an attendance award.
    The answer may be very large, so return it modulo 109 + 7.

    Input: n = 2
    Output: 8
    Explanation: There are 8 records with length 2 that are eligible for an award:
    "PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
    Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).

    Input: n = 1
    Output: 3

    Input: n = 10101
    Output: 183236316

    Constraints:
    1 <= n <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun 26 May 2024 11:17:49 AM PDT
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

#define MOD 1000000007

int check_all_records(int cur_ind, int count_a, int count_l, int n, int temp[n][2][3]) {
  // Base Case
  if (cur_ind == n)
    return 1;

  if (temp[cur_ind][count_a][count_l] != -1)
    return temp[cur_ind][count_a][count_l];

  // Recursion case
  int with_a_next = 0;
  if (count_a == 0) {
    with_a_next = check_all_records(cur_ind + 1, count_a + 1, 0, n, temp);
  }

  int with_l_next = 0;

  if (count_l < 2)
    with_l_next = check_all_records(cur_ind + 1, count_a, count_l + 1, n, temp);

  int with_p_next = check_all_records(cur_ind + 1, count_a, 0, n, temp);

  int total = ((with_a_next + with_l_next) % MOD + with_p_next) % MOD;
  temp[cur_ind][count_a][count_l] = total;

  return total;
}

int checkRecord(int n) {
  int temp[n][2][3];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 3; k++) {
	temp[i][j][k] = -1;
      }
    }
  }
  return check_all_records(0, 0, 0, n, temp);
}

void test() {
  int ret = 0;
  int n = 2;
  ret = checkRecord(n);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[103] [test] :| Output = 8
**/

/**
   Notes :
   Approach 1: Recursion with memoization
   Intuition :
   so first thing that come up in my mind is just recursion and this
   approach is quite simple.

   We will start from the empty string and each time we will choose
   which character to add.
   We don't want to pass the string into the function because all
   we interested in is just how many consecutive "L" we have so far
   and how many "A" already in the string.
   We want to call recursion with this rules
    - If we reached the end of the string we want to return result
      (this string is eligable because of steps I describe below)
    - On every recursion we will call recursion with every of three
      characters but only if this string will be eligable after we
      add this new character (So, if there's already 1 "A" we can't
      add another of if there's already 2 consecutive "L" we can't add another)
   - We will find the sum of all callings and return it
   This is sufficient to write code for this approach but
   there's some interesting things I want to mention:
    - Recursion without memoization will give TLE because we
      recalculate many states wich we've seen already. As was
      said every state is defined only by 3 parameters: cur_ind, count_a, count_l
   - I have no idea why but temp[cur_ind][count_a][count_l] is
     much faster than temp[cur_ind][count_l][count_a].
   - If you don't take the mod on this step: total:
     int = (with_a_next + with_l_next + with_p_next) % MOD you will get MLE error.

   Coding :
   Let's code this up and move to the next approach

   Define variables temp for memoization and MOD=10**9 + 7.
   Define recursive function with this rules:
    - If we've reached the end of the string then return 1 (we've found new eligable string)
    - If another case check whether we've already seen this state. If True then
      just return it and if False calculate with recursion every possible state
      from this, sum them up, write in memoization and return result
    From every total we want to get modulo by MOD and only then memo result.

    Complexity :
     - Time complexity: O(n), due to memoization we will have only 2 * 3 * n
       unique states which is O(n)
     - Space complexity: O(n) we use O(n) for recursion stack and O(2 * 3 * n)
       for memoization so O(7n) in total or just O(n)
*/
