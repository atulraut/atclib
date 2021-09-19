/***
    Given a string num that contains only digits and an
    integer target, return all possibilities to add the
    binary operators '+', '-', or '*' between the digits
    of num so that the resultant expression evaluates to
    the target value.

    Input: num = "123", target = 6
    Output: ["1*2*3","1+2+3"]

    Input: num = "232", target = 8
    Output: ["2*3+2","2+3*2"]

    Input: num = "105", target = 5
    Output: ["1*0+5","10-5"]

    Input: num = "00", target = 0
    Output: ["0*0","0+0","0-0"]

    Input: num = "3456237490", target = 9191
    Output: []

    Constraints:
    1 <= num.length <= 10
    num consists of only digits.
    -231 <= target <= 231 - 1

    https://leetcode.com/problems/expression-add-operators/

    Date:18 Sept 2021
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

#define DBG(x)
#define pr(...) DBG(printf(__VA_ARGS__))

char **ret;
int cret;

void addPossibility(char* s) {
  ret[cret++] = strdup(s);
}

/*
 *    * we put the op here and choose 1..strlen(s) digits
 *    |
 * 2+2?21234
 * | | |
 * | | ^s
 * | ^ last_val
 * ^val
 *
 * sizeof(res) guarantees enough space for result
 */
void rec(char* s, int target, int val, int last_val, char* res) {
  debug("s %10s val %3d last_val %3d res %21s ", s,val,last_val,res);
  if (!*s) {
    if (target == (val+last_val))
      addPossibility(res);
    return;
  }

  int len = strlen(s), rlen = strlen(res);
  int curn = 0;
  for (int i = 0; i < len; i++) {
    curn = curn*10 + s[i] - '0';

    strncpy(res+rlen+1, s, i+1);
    res[rlen+i+2] = 0;

    // +
    res[rlen] = '+';
    rec(s+i+1, target, val+last_val, curn, res);
    // -
    res[rlen] = '-';
    rec(s+i+1, target, val+last_val, 0-curn, res);
    // *
    if (curn == 0 || (INT_MAX/curn > last_val || (INT_MAX/curn == last_val && INT_MAX%curn == 0))) {
      res[rlen] = '*';
      rec(s+i+1, target, val, last_val*curn, res);
    }
    if (!i && s[i] == '0')
      break;
  }
  // back to 0
  res[rlen] = 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** addOperators(char* num, int target, int* returnSize) {
  char res[21] = {0}, *s = num;
  int i, curn = 0;
  cret = 0;
  ret = (char **)malloc(sizeof(char *)*20000);//~3^9

  for (i = 0; i < strlen(num); i++) {
    if (INT_MAX/10 > curn || (INT_MAX/10 == curn && s[i] <= (INT_MAX%10+'0')) )
      curn = curn*10 + (s[i] - '0');
    else
      break;
    res[i] = s[i];
    res[i+1] = 0;

    rec(s+i+1, target, 0, curn, res);
    if (!i && s[0] == '0')
      break;
  }
  *returnSize = cret;
  return ret;
}

int main (int argc, char **argv) {
  char** ret = 0;
  char num[] = "123";
  int target = 6;
  int returnSize;

  ret = addOperators(num, target, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %s", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=110 :Output = 1+2+3
   [main] L=110 :Output = 1*2*3
**/
