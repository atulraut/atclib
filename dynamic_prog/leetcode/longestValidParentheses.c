
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

struct stack {
  int *array;
  int top;
  int len;
};

void spush(struct stack *root, int i) {
  if (root->top == root->len-1) {
    debug("Stack is Full!");
    return -1;
  }
  root->top++;
  root->array[root->top] = i;
  debug("data = %d top=%d", i, root->top);
}

int spop(struct stack *root, int i) {
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
  struct stack estack = {NULL, -1, len};
  int *dp;

  /* Allocate the stack */
  estack.array = malloc(sizeof(int) * (len * 2));
  if (!estack.array)
    return 0;

  /* Allocate the memoization array */
  dp = &estack.array[len];
  debug ("dp addres = %p", dp);
  debug ("stack addr= %p", estack.array);
  debug ("stack addr= %p", estack.array+len);

  /* Loop through the string */
  i = 0;
  while (i < len) {
    /* Initialize the memoization array */
    dp[i] = -1;

    /* If it's an open parentheses, then stack push */
    if (s[i] == '(')
      spush(&estack, i);

    /* Else if (s[i] == ')'), then it's closing parentheses,
       evaluate the expression */
    else if ((offset = spop(&estack, i)) != -1) {
      debug("offset = %d", offset);
      /* If the valid open parentheses for this expression was
	 preceded by another valid set, then pick the open parentheses
	 offset of that set.

	 Basically, now the dp array for the cases like
	 "(  ) (  )  ( )  ( )  (  (  (  )  )  )" would look like below:
	 |-1|0|-1|0|-1|0|-1|0|-1|-1|-1|10| 9| 0  <-- dp array
	 | 0|1| 2|3| 4|5| 6|7| 8| 9|10|11|12|13

	 This way in a single pass we can figure out the longest
	 valid sequence.
	 ".
      */
      dp[i] = ((offset - 1 >= 0) && (dp[offset - 1] != -1)) ?
	dp[offset - 1] : offset;

      /* Update the length */
      longest = (longest < i - dp[i] + 1) ? i - dp[i] + 1 : longest;
      debug("dp[%d] = %d longest=%d", i, dp[i], longest);
    }
    ++i;
  }

  /* Free the stack */
  free(estack.array);
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
	maxlen = fmax(maxlen, i-array[index-1]);
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
  char *exp3 = ")()())";
  char *exp ="(((())))";
  int result = longestValidParentheses(exp);

  debug ("Result = %d ", result);
  return 0;
}
