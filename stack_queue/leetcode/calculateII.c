/***
    https://leetcode.com/problems/basic-calculator-ii/
    Basic Calculator II

    Given a string s which represents an expression, evaluate this
    expression and return its value.

    The integer division should truncate toward zero.

    You may assume that the given expression is always valid.
    All intermediate results will be in the range of [-231, 231 - 1].
    Note: You are not allowed to use any built-in function which
    evaluates strings as mathematical expressions, such as eval().

    Input: s = "3+2*2"
    Output: 7

    Input: s = " 3/2 "
    Output: 1

    Input: s = " 3+5 / 2 "
    Output: 5
    Constraints:

    1 <= s.length <= 3 * 105
    s consists of integers and operators ('+', '-', '*', '/') separated
    by some number of spaces.
    s represents a valid expression.
    All the integers in the expression are non-negative
    integers in the range [0, 231 - 1].
    The answer is guaranteed to fit in a 32-bit integer.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address calculateII.c -lm

    Date: 12/24/2021
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
#define MAX_STACK 300000

typedef struct stack_t_ {
  int top;
  int data[MAX_STACK];
} stack_t;

bool stack_pop(stack_t *stack, int *data) {
  if (stack->top == -1)
    return false;
  *data = stack->data[stack->top--];
  return true;
}

bool stack_push(stack_t *stack, int data) {
  if ((stack->top+1) == MAX_STACK)
    return false;

  stack->data[++stack->top] = data;
  return true;
}

char *get_num(char *s, int *num) {
  int data = 0;
  while (*s) {                                        // string may end with NULL
    if ((*s >= '0') && (*s <= '9')) {               // process digits
      data = (data * 10) + (*s - '0');            // shift data in place
    } else if (*s != ' ') {                         // skip leading ' ' in s before digits
      break;                                      // done if we see anything else
    }
    ++s;                                            // consume and advance s
  }
  *num = data;                                        // update return data
  return s;                                           // return next string position to be processed
}

int calculate(char * s) {
  int data, tmp;
  stack_t stack={.top = -1};

  s = get_num(s, &data);                              // get first operand and stash it away
  stack_push(&stack, data);

  while(*s) {                                         // for the rest of the string
    char op = *s++;                                 // extract the op and second operand
    s = get_num(s, &data);
    switch(op) {
    case '+':   stack_push(&stack, data);       // stash it away if we can't complete operation yet
      break;
    case '-':   stack_push(&stack, -1 * data);  // stash -data because this operand is to be subtracted
      break;
    case '*':   stack_pop(&stack, &tmp);        // pop the last operand
      tmp *= data;                    // perform the * operation
      stack_push(&stack, tmp);        // stash it back in case next op is also * or /
      break;
    case '/':   stack_pop(&stack, &tmp);        // pop the last operand
      tmp /= data;                    // complete the / operation
      stack_push(&stack, tmp);        // stash it back in case next op is also * or /
      break;
    }
  }

  data = 0;                                           // we can now finally add the stack and get our answer
  while(stack_pop(&stack, &tmp)) {
    data += tmp;
  }
  return data;
}

// +, -, *, /, (, push
// ) or end of string then keep calaulate until ( or end of stack
// digit or () result check stack top, if * or / then operate, + or - then push

bool isDigit(char c) {
  if(c-'0'>=0 && c-'0'<=9) {
    return true;
  }
  return false;
}


// 3 + 3 * 3 +
int calculate1(char * s) {
  int prev = 0;
  char preOp = '+';
  int num = 0;
  int len = strlen(s);
  int sum = 0;
  for(int i=0;i<=len;i++) {
    if(i==len || (!isDigit(s[i]) && s[i]!= ' ')) {
      //printf("i=%d,%c\n",i,s[i]);
      switch(preOp) {
	// printf("prev = %d\n",prev);
	// printf("num = %d\n",num);
      case '+':
	sum += prev;
	prev = num;
	break;
      case '-':
	sum += prev;
	prev = -num;
	break;
      case '*':
	prev *= num;
	break;
      case '/':
	prev /= num;
	break;
      }

      if(i!=len)
	preOp = s[i];
      num = 0;
    } else if(s[i] == ' ') {

    } else {
      num  = num*10 + (s[i]-'0');
    }
  }
  return prev + sum;
}

struct node {
  long int val;
  struct node* next;
};

struct Stack {
  struct node* top;
};
typedef struct node* node;
typedef struct Stack* Stack;

Stack New() {
  Stack result = malloc(sizeof(struct Stack));
  result->top = NULL;
  return result;
}

//Requires : stack != NULL for all Stack functions
bool isEmpty(Stack stack) {
  return stack->top == NULL;
}

void push(Stack stack, long int data) {
  node Last = stack->top;
  node New = malloc(sizeof(struct node));
  New->val = data;
  New->next = Last;
  stack->top = New;
}

long int pop(Stack stack) {
  node last = stack->top;
  stack->top = last->next;
  long int result = last->val;
  free(last);
  return result;
}

char* cleanup(char *s, size_t length, size_t *result) {
  char *workspace = calloc(sizeof(char), length+1);
  size_t j = 0;
  for (size_t i = 0; i < length; i++) {
    if (s[i] != ' ') {
      workspace[j] = s[i];
      j++;
    }
  }
  *result = j;
  return workspace;
}

int calculate2(char *s) {
  if (s == NULL || *s == '\0') {
    return 0;
  }
  size_t length = 0;
  size_t len = strlen(s);
  s = cleanup(s, strlen(s), &length);

  //Stack stack = New();
  Stack stack = malloc(sizeof(struct Stack) * len);
  stack->top = NULL;
  char *cursor = s;

  //here we need to handle the situation where the formula begins with a sign, and read in the first number
  if (s[0] == '-') {
    cursor++;
    push(stack, -strtol(cursor,&cursor, 0));
  }
  else{
    if (s[0] == '+') {      cursor++;
    }
    push(stack, strtol(cursor,&cursor, 0));
  }

  //From here on whenever we enter the loop the string should begin with a sign, otherwise the formula is not well-formed
  while (cursor != &s[length]) {
    if (*cursor == '-') {
      cursor++;
      push(stack, -strtol(cursor, &cursor, 0));
    }
    else if (*cursor == '+') {
      cursor++;
      push(stack, strtol(cursor,&cursor, 0));
    }
    else if (*cursor == '*') {
      cursor++;
      push(stack, pop(stack) * strtol(cursor, &cursor, 0));
    }
    else {
      cursor++;
      push(stack, pop(stack) / strtol(cursor, &cursor, 0));
    }
  }

  //Here we should have eliminated all times and divides
  long int result = 0;
  while (!isEmpty(stack)) {
    result += pop(stack);
  }
  return (int)result;
}

int main (int argc, char **argv) {
  int ret = 0;
  char s[] = "3+2*2";
  ret = calculate2(s);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=293 :Output = 7
**/
