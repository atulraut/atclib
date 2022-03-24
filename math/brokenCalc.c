/***
    https://leetcode.com/problems/broken-calculator/

    Broken Calculator

    There is a broken calculator that has the integer startValue
    on its display initially. In one operation, you can:

    multiply the number on display by 2, or
    subtract 1 from the number on display.
    Given two integers startValue and target, return the minimum
    number of operations needed to display target on the calculator.

    Input: startValue = 2, target = 3
    Output: 2
    Explanation: Use double operation and then decrement operation {2 -> 4 -> 3}.

    Input: startValue = 5, target = 8
    Output: 2
    Explanation: Use decrement and then double {5 -> 4 -> 8}.


    Input: startValue = 3, target = 10
    Output: 3
    Explanation: Use double, decrement and double {3 -> 6 -> 5 -> 10}.

    Constraints:
    1 <= x, y <= 109

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue Mar 22 21:39:43 PDT 2022
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

/***
    Approach 1: Work Backwards
    Intuition

    Instead of multiplying by 2 or subtracting 1 from startValue,
    we could divide by 2 (when target is even) or add 1 to target.

    The motivation for this is that it turns out we always
    greedily divide by 2:

    If say target is even, then if we perform 2 additions and
    one division, we could instead perform one division and one
    addition for less operations [(target + 2) / 2 vs target / 2 + 1].

    If say target is odd, then if we perform 3 additions and one
    division, we could instead perform 1 addition, 1 division,
    and 1 addition for less operations [(target + 3) / 2 vs (target + 1) / 2 + 1].

    Algorithm

    While target is larger than startValue, add 1 if it is odd,
    else divide by 2. After, we need to do startValue - target
    additions to reach startValue.
*/

int brokenCalc(int startValue, int target) {
  int ans = 0;
  while (target > startValue) {
    ans++;
    if (target % 2 == 1)
      target++;
    else
      target /= 2;
  }
  return ans + startValue - target;
}

void test() {
  int ret = 0;
  int startValue = 3, target = 10;

  ret = brokenCalc(startValue, target);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
