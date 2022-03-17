/***
    https://leetcode.com/problems/score-of-parentheses/

    Score of Parentheses

    Given a balanced parentheses string s, return the score of the string.

    The score of a balanced parentheses string is based on the following rule:

    "()" has score 1.
    AB has score A + B, where A and B are balanced parentheses strings.
    (A) has score 2 * A, where A is a balanced parentheses string.

    Input: s = "()"
    Output: 1

    Input: s = "(())"
    Output: 2

    Input: s = "()()"
    Output: 2

    Constraints:

    2 <= s.length <= 50
    s consists of only '(' and ')'.
    s is a balanced parentheses string.
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Mar 16 23:55:08 PDT 2022
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

int scoreOfParentheses(char* s) {
  int ans = 0, bal = 0;
  int len = strlen(s);
  for (int i = 0; i < len; ++i) {
    if (s[i] == '(') {
      bal++;
    } else {
      bal--;
      if (s[i-1] == '(') {
	debug ("i = %d ans  %d (1 << bal) = %d", i, ans, (1 << bal));
	ans += 1 << bal;
      }
    }
  }
  return ans;
}


int scoreOfParentheses2(char* s) {
  int len = strlen(s);
  int r=0;
  int top = -1;
  int *arr = (int *)malloc(sizeof(int) * len);
  memset(arr,0,sizeof(arr));
  int i;

  for (i=0; i < len; i++) {
    if (s[i] == '(') {
      top++;
      arr[top] = '(';
    } else if (s[i] == ')') {
      r = top;
      if (arr[r] == '(') {
	arr[r] = 1;
      } else {
	while (arr[r] != '(') {
	  arr[r] = 2 * arr[r];
	  r--;
	}
	arr[r] = 0;
      }
    }
  }
  r=0;
  for (i=0; i <= top; i++) {
    r = r + arr[i];
  }
  return r;
}

void test() {
  char str[] = "()()";
  int ret = 0;

  ret = scoreOfParentheses(str);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [scoreOfParentheses] L=69 :i = 1 ans  0 (1 << bal) = 1
   [scoreOfParentheses] L=69 :i = 3 ans  1 (1 << bal) = 1
   [test] L=115 :Output = 2
**/
