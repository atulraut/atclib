/***
    https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60
    1010. Pairs of Songs With Total Durations Divisible by 60

    You are given a list of songs where the ith song has a duration of
    time[i] seconds.

    Return the number of pairs of songs for which their total duration in
    seconds is divisible by 60. Formally, we want the number of
    indices i, j such that i < j with (time[i] + time[j]) % 60 == 0.

    Input: time = [30,20,150,100,40]
    Output: 3
    Explanation: Three pairs have a total duration divisible by 60:
    (time[0] = 30, time[2] = 150): total duration 180
    (time[1] = 20, time[3] = 100): total duration 120
    (time[1] = 20, time[4] = 40): total duration 60

    Input: time = [60,60,60]
    Output: 3
    Explanation: All three pairs have a total duration of 120, which is divisible by 60.

    Constraints:
    1 <= time.length <= 6 * 104
    1 <= time[i] <= 500

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Jan 1, 2022
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
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

int numPairsDivisibleBy60(int* time, int timeSize) {
  int* map=(int*)calloc(60,sizeof(int));
  for(int i=0;i<timeSize;i++) {
    map[time[i]%60]++;
  }

  int ret=0;
  ret+=(map[0]-1)*map[0]/2;
  ret+=(map[30]-1)*map[30]/2;
  for(int i=1;i<30;i++) {
    ret+=map[i]*map[60-i];
  }
  return ret;
}

int numPairsDivisibleBy60_brute_Force(int* time, int timeSize) {
  int count = 0, n = timeSize;
  for (int i = 0; i < n; i++) {
    // j starts with i+1 so that i is always to the left of j
    // to avoid repetitive counting
    for (int j = i + 1; j < n; j++) {
      if ((time[i] + time[j]) % 60 == 0) {
	count++;
      }
    }
  }
  return count;
}

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {30,20,150,100,40};
  int sz = arrsz(arr);
  ret = numPairsDivisibleBy60(arr, sz);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=93 :Output = 3
**/
