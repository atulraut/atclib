/*
  Program : Min Stack
  Design a stack that supports push, pop, top, and retrieving
  the minimum element in constant time.
  push(x) -- Push element x onto stack.
  pop() -- Removes the element on top of the stack.
  top() -- Get the top element.
  getMin() -- Retrieve the minimum element in the stack.
  Example 1:
  Input
  ["MinStack","push","push","push","getMin","pop","top","getMin"]
  [[],[-2],[0],[-3],[],[],[],[]]
  Output
  [null,null,null,null,-3,null,0,-2]
  Explanation
  MinStack minStack = new MinStack();
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  minStack.getMin(); // return -3
  minStack.pop();
  minStack.top();    // return 0
  minStack.getMin(); // return -2
  Constraints:
  Methods pop, top and getMin operations will always be called
  on non-empty stacks.

  Date : 05/27/2020
  https://www.youtube.com/watch?v=8UegNFCUQks
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

stack *m_init(void  *_ptr, int sz) {
  stack *s = (stack *)_ptr;
  if(NULL == s) {
	printf ("memset needs valid pointer \n");
	exit(1);
  }
  memset((void *)s, 0, sizeof(stack));
  s->top = -1;
  s->min = -1;
  s->stabuf = (int *)malloc(sz * sizeof(int));
  s->minbuf = (int *)malloc(sz * sizeof(int));
  if(NULL == s->stabuf || NULL == s->minbuf )
    return NULL;
  else
    return s;
}

int push(void *_ptr, int val) {
  stack *s = (stack *)_ptr;
  if (s->top == STACK_SZ-1) {
    debug ("Stack is FULL, Remove Some element.");
    return -1;
  }

  s->top++;
  s->stabuf[s->top] = val;

  if(s->min >= 0) {
    if(s->minbuf[s->min] > val) {
      s->min += 1;
      s->minbuf[s->min] = val;
    } else {
      s->minbuf[s->min+1] = s->minbuf[s->min];
      s->min += 1;;
    }
  } else {
    s->min += 1;
    s->minbuf[s->min] = val;
  }

  printf ("[%s] val=%d top=%d min=%d L=%d \n", __func__, val, s->top, s->min, __LINE__);
  return 0;
}

int pop (void *_ptr) {
  int val;
  stack *s = (stack *)_ptr;
  if (s->top < 0)
    return -1;

  val = s->stabuf[s->top];
  s->top = s->top-1;
  s->min = s->min-1;;
  printf ("\n[pop] top=%d min=%d \n", s->top, s->min);

  return val;
}

int topElement(void *_ptr) {
  stack *s = (stack *)_ptr;
  if (s->top < 0)
    return -1;
  return s->stabuf[s->top];
}

int getMin(void *_ptr) {
  stack *s = (stack *)_ptr;
  if (s->top < 0)
    return -1;
  return s->stabuf[s->min];
}


int isEmpty(void *_ptr) {
  stack *s = (stack *)_ptr;
  if(s->top < 0) {
    printf ("[%s] Empty S - top=%d", __func__, s->top);
    return -1;
  } else {
    printf ("[%s] Not - top=%d", __func__, s->top);
    return 1;
  }
}

int m_DisplayMin(void *_ptr) {
  stack *s = (stack *)_ptr;
  if(s->top < 0) {
    printf ("[%s] Empty S - top=%d" ,__func__ ,s->top);
    return -1;
  } else {
    printf ("[%s] top=%d min_stack=%d  L=%d \n",__func__, \
	    s->stabuf[s->top], s->minbuf[s->min], __LINE__);
    return 1;
  }
}

int m_Display(void *_ptr) {
  stack *s = (stack *)_ptr;
  if(s->top < 0) {
    printf ("[%s] Empty S - top=%d" ,__func__ ,s->top);
    return -1;
  } else {
    int temp = s->top;
    for (int j=0; j<=temp; ++j)
      printf ("[%s] top[%d]=%d L=%d \n",__func__, j,	\
	    s->stabuf[j], __LINE__);
    return 1;
  }
}

int quit(void *_ptr) {
  printf ("Good Bye! \n");
  exit(0);
}
