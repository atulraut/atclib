/***
    https://leetcode.com/problems/min-stack/
    Min Stack

    Design a stack that supports push, pop, top, and retrieving
    the minimum element in constant time.

    Implement the MinStack class:

    MinStack() initializes the stack object.
    void push(int val) pushes the element val onto the stack.
    void pop() removes the element on the top of the stack.
    int top() gets the top element of the stack.
    int getMin() retrieves the minimum element in the stack.

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

    -231 <= val <= 231 - 1
    Methods pop, top and getMin operations will always be called on non-empty stacks.
    At most 3 * 104 calls will be made to push, pop, top, and getMin.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 24 Oct 2021
    Fair Oaks, CA.
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
  ({ typeof (a) _a = (a);			\
    typeof (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ typeof (a) _a = (a);			\
    typeof (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

#include<stdio.h>
#include<stdlib.h>

typedef struct min_stack {
  int data;
  struct min_stack *next;
  int min_num;
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
  MinStack *stack =(MinStack*)malloc(sizeof(MinStack));

  if(stack == NULL) {
    return NULL;
  }

  stack->next = NULL;
  stack->min_num = INT_MAX;

  return stack;
}

void minStackPush(MinStack* obj, int x) {
  MinStack *p = NULL;

  p = (MinStack*)malloc(sizeof(MinStack));
  if(p == NULL) {
    return;
  }

  p->data = x;
  if(x < obj->min_num) {
    p->min_num = x;
    obj->min_num = x;
  } else {
    p->min_num = obj->min_num;
  }
  p->next = obj->next;
  obj->next = p;
}

void minStackPop(MinStack* obj) {
  // Delete the minimum value, update the global minimum (obj->min_num)
  if(obj->next->next && obj->next->data == obj->min_num){
    obj->min_num = obj->next->next->min_num;
  }
  obj->next = obj->next->next;
  // After deleting the last node, reset obj->min_num set
  if(!obj->next){
    obj->min_num = INT_MAX;
  }
}

int minStackTop(MinStack* obj) {
  return obj->next->data;
}

int minStackGetMin(MinStack* obj) {
  return obj->next->min_num;
}

void minStackFree(MinStack* obj) {
  if(!obj->next) {
    return;
  }
  while(obj->next){
    MinStack *p = obj->next;
    obj->next = obj->next->next;
    free(p);
  }
  free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
 */

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
