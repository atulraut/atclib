/***
    https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/

    Minimum Remove to Make Valid Parentheses

    Given a string s of '(' , ')' and lowercase English characters.

    Your task is to remove the minimum number of parentheses
    ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

    Formally, a parentheses string is valid if and only if:

    It is the empty string, contains only lowercase characters, or
    It can be written as AB (A concatenated with B), where
    A and B are valid strings, or
    It can be written as (A), where A is a valid string.

    Input: s = "lee(t(c)o)de)"
    Output: "lee(t(c)o)de"
    Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

    Input: s = "a)b(c)d"
    Output: "ab(c)d"

    Input: s = "))(("
    Output: ""
    Explanation: An empty string is also valid.

    Constraints:
    1 <= s.length <= 105
    s[i] is either'(' , ')', or lowercase English letter

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Mar 14 22:17:37 PDT 2022
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

#define STACK_SIZE_MAX 100000

char* minRemoveToMakeValid(char* s) {

  /*
    What remains in the stack after iteration will be the index of the parentheses to be removed
  */
  int stack[STACK_SIZE_MAX];
  int stackSize = 0;

  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] == '(') {
      // printf("Pt 1: s[%d] = %c, stackSize = %d\n", i, s[i], stackSize);
      stack[stackSize++] = i;
    } else if (s[i] == ')') {
      if (stackSize == 0 || s[stack[stackSize-1]] != '(') {
	// printf("Pt 2: s[%d] = %c, stackSize = %d\n", i, s[i], stackSize);
	stack[stackSize++] = i;
      } else // stackSize != 0 && stack[stackSize-1] == '('
	{
	  // printf("Pt 3: s[%d] = %c, stackSize = %d\n", i, s[i], stackSize);
	  stackSize--;
	}
    }
  }

  char* ans = malloc(sizeof(char) * (strlen(s) - stackSize + 1));
  for (int i = 0; i < stackSize; i++) {
    // printf("s[%d] = %c\n", stack[i], s[stack[i]]);
    s[stack[i]] = '-';
  }

  int j = 0; // write pointer
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] != '-')
      ans[j++] = s[i];
  }
  ans[j] = '\0';

  return ans;
}

void test() {
  char* ret;
  char s[] = "a)b(c)d";
  ret = minRemoveToMakeValid(s);
  debug("Output = %s", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=111 :Output = ab(c)d
**/
