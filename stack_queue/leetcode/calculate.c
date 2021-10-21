/***
    Hard: Basic Calculator

    Given a string s representing a valid expression,
    implement a basic calculator to evaluate it, and
    return the result of the evaluation.

    Note: You are not allowed to use any built-in function
    which evaluates strings as mathematical expressions,
    such as eval().

    Input: s = "1 + 1"
    Output: 2

    Input: s = " 2-1 + 2 "
    Output: 3

    Input: s = "(1+(4+5+2)-3)+(6+8)"
    Output: 23

    Constraints:
    1 <= s.length <= 3 * 105
    s consists of digits, '+', '-', '(', ')', and ' '.
    s represents a valid expression.
    '+' is not used as a unary operation.
    '-' could be used as a unary operation but it has to be
    inside parentheses.
    There will be no two consecutive operators in the input.
    Every number and running calculation will fit in a signed
    32-bit integer.

    https://leetcode.com/problems/basic-calculator/
    gcc -o main calculate.c -lm

    Date: 9/11/2021
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

/* Array based fixed sized stack */
struct stack {
  int top;
  int stakSize;
  int *buf;
};

struct stack *m_init(void  *_ptr, int sz) {
  struct stack *s = (struct stack *)_ptr;
  if(NULL == s) {
    printf ("memset needs valid pointer \n");
    exit(1);
  }
  memset((void *)s, 0, sizeof(struct stack));
  s->top = -1;
  s->stakSize = sz;
  s->buf = (int *)malloc(sz * sizeof(int));
  if(NULL == s->buf)
    return NULL;
  else
    return s;
}

int push(void *_ptr, int val) {
  struct stack* s = (struct stack *)_ptr;

  //debug ("top=%d stakSize=%d val=%d", s->top, s->stakSize, val);

  if (s->top == s->stakSize)
    return -1;
  s->top = s->top+1;
  s->buf[s->top] = val;
  debug ("top=%d val=%d", s->top, val);
  return 0;
}

int pop (void *_ptr) {
  int val;
  struct stack *s = (struct stack *)_ptr;

  if (s->top < 0)
    return -1;
  val = s->buf[s->top];
  s->top = s->top-1;
  debug ("Poped =%d top=%d",val, s->top);
  return val;
}

int topElement(void *_ptr) {
  struct stack *s = (struct stack *)_ptr;
  if (s->top < 0)
    return -1;
  debug("Top%d", s->buf[s->top]);
  return s->buf[s->top];
}

int isEmpty(void *_ptr) {
  struct stack *s = (struct stack *)_ptr;
  if(s->top < 0) {
    debug ("Empty S - top=%d", s->top);
    return -1;
  } else {
    debug ("Not - top=%d", s->top);
    return 1;
  }
}


int evaluateExpr_(char* str) {
  int operand = 0;
  int n = 0;
  for (int i = strlen(str) - 1; i >= 0; i--) {
    char ch = str[i];

    if (isdigit(ch)) {
      // Forming the operand - in reverse order.
      operand = (int) pow(10, n) * (int) (ch - '0') + operand;
      n += 1;

    }
    debug ("ch = %c n=%d operand=%dgh", ch, n, operand);
  }
  return n;
}

int evaluateExpr(struct stack* thisStack) {
  int res = 0;

  if (!isEmpty(thisStack)) {
    res = pop(thisStack);
  }

  // Evaluate the expression till we get corresponding ')'
  while (!isEmpty(thisStack) && !(topElement(thisStack) == ')')) {
    char sign = pop(thisStack);
    if (sign == '+') {
      res += pop(thisStack);
    } else {
      res -= pop(thisStack);
    }
  }
  debug("res = %d", res);
  return res;
}

int calculate(char* s) {
  int operand = 0;
  int n = 0;
  struct stack *dstack = NULL;
  struct stack estack;
  int sz = strlen(s);

  dstack = m_init(&estack, sz);

  for (int i=sz-1; i >= 0; --i) {
    char ch = s[i];
    if (isdigit(ch)) {
      // Forming the operand - in reverse order.
      operand = (int) pow(10, n) * (int) (ch - '0') + operand;
      n += 1;
    } else if (ch != ' ') {
      if (n != 0) {
	// Save the operand on the stack
	// As we encounter some non-digit.
	push(dstack, operand);
	n = 0;
	operand = 0;
      }
      if (ch == '(') {
	int res = evaluateExpr(dstack);
	pop(dstack);
	// Append the evaluated result to the stack.
	// This result could be of a sub-expression within the parenthesis.
	push(dstack, res);
      } else {
	// For other non-digits just push onto the stack.
	push(dstack, ch);
      }
    }
  }
  //Push the last operand to stack, if any.
  if (n != 0) {
    push(dstack, operand);
  }

  // Evaluate any left overs in the stack.
  return evaluateExpr(dstack);
}

int main (int argc, char **argv) {
  int ret = 0;
  char s[] = "(1+1)";
  //  char s[] = "(1+(4+5+2)-3)+(6+8)";

  //ret = test_main ();
  ret = calculate(s);

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
