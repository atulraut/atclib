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

/* stack */
struct stack_t {
  int top;
  int *space;
};

struct stack_t * stack_init(int slen) {
  struct stack_t * ret = malloc(sizeof(struct stack_t));
  ret->space = (int *)malloc(sizeof(int) * slen);
  ret->top = -1;
  return ret;
}

void stack_free(struct stack_t *stack) {
  free(stack->space);
  free(stack);
}

void stack_push(struct stack_t *stack, int val) {
  stack->top++;
  stack->space[stack->top] = val;
}

void stack_pop(struct stack_t *stack, int *val) {
  *val = stack->space[stack->top];
  stack->top--;
}

int stack_is_null(struct stack_t *stack) {
  return stack->top == -1;
}

void skip_space(char **s) {
  int ret = 0;

  while (**s == ' ') {
    (*s)++;
  }
}

/*
 * ret = nubmer
 * *offset = skip number;
 */
int get_number(char **s) {
  int ret = 0;

  while (**s >= '0' && **s <= '9') {
    ret = ret * 10 + (**s - '0');
    (*s)++;
  }

  return ret;
}

/*
 * ret -1: fail, 0: successful
 */
int get_next_element(char **s, int *val, int *is_number) {
  skip_space(s);

  if (**s == '\0')
    return -1;

  if (**s >= '0' && **s <= '9') {
    *val = get_number(s);
    *is_number = 1;
  } else {
    *val = **s;
    (*s)++;
    *is_number = 0;
  }

  return 0;
}

int __calculate(int val1, int val2, int last_add) {
  if (last_add) {
    val1 += val2;
  } else {
    val1 -= val2;
  }
  return val1;
}

int calculate(char* s) {
  int slen = strlen(s);
  struct stack_t *ret_stack = stack_init(slen);
  int val1, ret = 0, tmp_ret;
  int is_number;
  int last_add = 1;
  int unary_check = 1;

  while (get_next_element(&s, &val1, &is_number) == 0) {
    if (is_number) {
      ret = __calculate(ret, val1, last_add);
      unary_check = 0;
    } else {
      if (val1 == '-') {
	if (unary_check) {
	  last_add = !last_add;
	} else {
	  last_add = 0;
	  unary_check = 1;
	}
      } else if (val1 == '+') {
	last_add = 1;
	unary_check = 1;
      } else if (val1 == '(') {
	stack_push(ret_stack, ret);
	stack_push(ret_stack, last_add);
	ret = 0;
	last_add = 1;
      } else if (val1 == ')') {
	stack_pop(ret_stack, &last_add);
	stack_pop(ret_stack, &tmp_ret);
	ret = __calculate(tmp_ret, ret, last_add);
      }

    }
  }

  stack_free(ret_stack);

  return ret;
}

int main (int argc, char **argv) {
  int ret = 0;
  //char s[] = "(1+1)";
  /* Below one wont work as this code wont support multiplication */
  //char s[] = "(1+((2+3)*(4*5)))";
  char s[] = "(1+(4+5+2)-3)+(6+8)";

  //ret = test_main ();
  ret = calculate(s);

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
