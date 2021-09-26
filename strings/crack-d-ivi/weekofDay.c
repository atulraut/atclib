/***
    Day of the week are represented as three-letter strings
    as "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun".
    Write a function that, given a string S represending
    the day of the week and an integer K(between 0 & 500, inclusive)
    returns the day of the week that is K days later.

    For ex. given, S="Wed" & K=3, returns "Fri"
    given S="Sat", K=23, returns "Mon"

    Date: 25 Sept 2021
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

#include <stdio.h>
char* solution(char *S, int K) {
  // write your code in C99 (gcc 6.2.0)
  char* final[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
  int remainder = 0;
  int index = 0;

  while (strcmp(S,final[index]) != 0)
    ++index;

  //debug ("index = %d \n", index);
  remainder = (K+index)%7;
  debug ("remain = %d index=%d", remainder, index);

  return final[remainder];
}

int main() {
  char* ret = 0;

  ret =solution("Tue", 7);
  debug("7 Sat -> %s \n\n", ret);
  ret =solution("Wed", 2);
  printf("2, Wed --> %s \n\n", ret);
  ret =solution("Sat", 23);
  debug("23, Sat --> %s \n\n", ret);
  ret =solution("Mon", 4);
  printf("2 Wed -> %s \n\n", ret);

  return 0;
}

/**
   [solution] L=32 :remain = 1 index=1
   [main] L=40 :7 Sat -> Tue

   [solution] L=32 :remain = 4 index=2
   2, Wed --> Fri

   [solution] L=32 :remain = 0 index=5
   [main] L=44 :23, Sat --> Mon

   [solution] L=32 :remain = 4 index=0
   2 Wed -> Fri
**/
