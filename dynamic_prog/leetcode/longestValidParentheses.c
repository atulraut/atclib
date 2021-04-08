/***
    https://leetcode.com/problems/longest-valid-parentheses/
    Hard: 32. Longest Valid Parentheses
    Given a string containing just the characters '(' and ')',
    find the length of the longest valid (well-formed) parentheses substring.

    Input: s = "(()"
    Output: 2
    Explanation: The longest valid parentheses substring is "()".

    Input: s = ")()())"
    Output: 4
    Explanation: The longest valid parentheses substring is "()()".

    Input: s = ""
    Output: 0

    Constraints:
    0 <= s.length <= 3 * 104
    s[i] is '(', or ')'.

    Date : 5/4/21
    San Diego, CA
    Author : Rauji(Atul) Raut
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
#define max(x, y) (((x) > (y)) ? (x) : (y))

struct stack {
  int *array;
  int top;
  int len;
};

int atclib_push(struct stack *root, int i) {
  if (root->top == root->len-1) {
    debug("Stack is Full!");
    return -1;
  }
  root->top++;
  root->array[root->top] = i;
  debug("data = %d top=%d", i, root->top);
}

int atclib_pop(struct stack *root, int i) {
  if (root->top < 0) {
    debug("Stack is Empty!");
    return -1;
  }
  int ret = root->array[root->top];
  root->top = root->top-1;
  debug("ret = %d top=%d arr=%d", ret, root->top, root->array[ret]);
  return ret;
}

int longestValidParentheses(char* s) {
  int i, longest = 0, len = strlen(s), offset;
  struct stack at_stack = {NULL, -1, len};
  int *dp;

  /* Allocate the stack */
  at_stack.array = malloc(sizeof(int) * (len * 2));
  if (!at_stack.array)
    return 0;

  /* Allocate the memoization array */
  dp = &at_stack.array[len];
  debug ("dp addres = %p", dp);
  debug ("stack addr= %p", at_stack.array);
  debug ("stack addr= %p", at_stack.array+len);

  /* Loop through the string */
  i = 0;
  while (i < len) {
    /* Initialize the memoization array */
    dp[i] = -1;

    /* If it's an open parentheses, then stack push */
    if (s[i] == '(')
      atclib_push(&at_stack, i);

    /* Else if (s[i] == ')'), then it's closing parentheses,
       evaluate the expression */
    else if ((offset = atclib_pop(&at_stack, i)) != -1) {
      debug("[ELSE-%d] offset = %d longest = %d",i, offset, longest);
      /* If the valid open parentheses for this expression was
	 preceded by another valid set, then pick the open parentheses
	 offset of that set.

	 Basically, now the dp array for the cases like
	 ")  (  ) (  ) " would look like below:
	 |-1|-1|1|-1|1|  <-- dp array
	 | 0|1| 2|3| 4|

	 This way in a single pass we can figure out the longest
	 valid sequence.
	 ".
      */
      debug("[ELSE-%d] offset-1 = %d dp[offset-1]=%d", i, (offset - 1 >= 0) , (dp[offset-1]) );
      dp[i] = ((offset - 1 >= 0) && (dp[offset - 1] != -1)) ?
	      dp[offset - 1] : offset;

      debug("[ELSE-%d] dp[%d]=%d ", i, i, dp[i] );
      debug("[ELSE-%d] (long<i-dp[i]+1)=%d (longest<i)=%d",i, (longest < i - dp[i] + 1), (longest<i));
      /* Update the length */
      longest = (longest < i - dp[i] + 1) ? i - dp[i] + 1 : longest;
      debug("[ELSE-%d] dp[i] = %d longest=%d", i, dp[i], longest);
    }
    ++i;
  }

  /* Free the stack */
  free(at_stack.array);
  return longest;
}

/**
   Approch 2 by LeetCode :
 **/
int longestValidParentheses2(char * s) {

  int size = 5;
  int *array = (int*)malloc(size*sizeof(int));
  int index = 0;
  array[0] = -1;
  index++;
  int i = 0,maxlen=0;

  if(strlen(s)==0) {
    return 0;
  }

  for(i=0; i<strlen(s); i++) {
    if (s[i] == '(') {
      array[index] = i;
      index++;
    } else {
      index--;
      if (index > 0) {
	maxlen = max(maxlen, i-array[index-1]);
      } else {
	array[index] = i;
	index++;
      }
    }
    if (index > size-1) {
      array = (int*)realloc(array, size*2*sizeof(int));
      size = size*2;
    }
  }
  return maxlen;
}

int main() {
  char *exp1 = "{()}[]";
  char *exp2 = "()(";
  char *exp = ")()())";
  char *exp4 ="(((())))";
  int result = longestValidParentheses(exp);

  debug ("Result = %d ", result);
  return 0;
}

/**
   => ./a.out
   [longestValidParentheses] L=79 :dp addres = 0x2577028
   [longestValidParentheses] L=80 :stack addr= 0x2577010
   [longestValidParentheses] L=81 :stack addr= 0x2577028
   [atclib_pop] L=58 :Stack is Empty!
   [atclib_push] L=53 :data = 1 top=0
   [atclib_pop] L=63 :ret = 1 top=-1 arr=0
   [longestValidParentheses] L=96 :[ELSE-2] offset = 1 longest = 0
   [longestValidParentheses] L=110 :[ELSE-2] offset-1 = 1 dp[offset-1]=-1
   [longestValidParentheses] L=114 :[ELSE-2] dp[2]=1
   [longestValidParentheses] L=115 :[ELSE-2] (long<i-dp[i]+1)=1 (longest<i)=1
   [longestValidParentheses] L=118 :[ELSE-2] dp[i] = 1 longest=2
   [atclib_push] L=53 :data = 3 top=0
   [atclib_pop] L=63 :ret = 3 top=-1 arr=0
   [longestValidParentheses] L=96 :[ELSE-4] offset = 3 longest = 2
   [longestValidParentheses] L=110 :[ELSE-4] offset-1 = 1 dp[offset-1]=1
   [longestValidParentheses] L=114 :[ELSE-4] dp[4]=1
   [longestValidParentheses] L=115 :[ELSE-4] (long<i-dp[i]+1)=1 (longest<i)=1
   [longestValidParentheses] L=118 :[ELSE-4] dp[i] = 1 longest=4
   [atclib_pop] L=58 :Stack is Empty!
   [main] L=172 :Result = 4
**/
