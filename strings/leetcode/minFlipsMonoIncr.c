/***
    Medium: Flip String to Monotone Increasing

    A binary string is monotone increasing if it consists of some
    number of 0's (possibly none), followed by some number of 1's
    (also possibly none).

    You are given a binary string s. You can flip s[i] changing it
    from 0 to 1 or from 1 to 0.

    Return the minimum number of flips to make s monotone increasing.

    Input: s = "00110"
    Output: 1
    Explanation: We flip the last digit to get 00111.

    Input: s = "010110"
    Output: 2
    Explanation: We flip to get 011111, or alternatively 000111.

    Input: s = "00011000"
    Output: 2
    Explanation: We flip to get 00000000.

    https://leetcode.com/problems/flip-string-to-monotone-increasing/

    Date: 10 August 2021
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

int minFlipsMonoIncr(char * s) {
int len = strlen(s);

    /* Solution I */

    /*
    // numZero[i] is number of 0's after index i
    // numOne[i] is number of 1's before index i
    int * numZero = malloc(sizeof(int) * len);
    int * numOne = malloc(sizeof(int) * len);

    numZero[len-1] = 0;
    for(int i = len-2; i >= 0; i--){
        if(s[i+1] == '0')
            numZero[i] = numZero[i+1] + 1;
        else
            numZero[i] = numZero[i+1];
    }

    numOne[0] = 0;
    for(int i = 1; i < len; i++){
        if(s[i-1] == '1')
            numOne[i] = numOne[i-1] + 1;
        else
            numOne[i] = numOne[i-1];
    }

    // for each i, find minimum numOne[i] + numZero[i]
    int min = INT_MAX;
    for(int i = 0; i < len; i++){
        if(numOne[i] + numZero[i] < min)
            min = numOne[i] + numZero[i];
    }

    return min;
    */

    /* Solution II: somehow works */
    int one = 0;
    int flip = 0;

    for(int i = 0; i < len; i++) {
        if(s[i] == '1')
            one++;
        else
            flip++;
        flip = flip < one ? flip : one;
    }

    return flip;
}

int main () {
  int ret = 0;
  char str[] = "00011000";
  ret = minFlipsMonoIncr(str);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=100 :Output = 2
**/
