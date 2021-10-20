/***
    https://leetcode.com/problems/largest-rectangle-in-histogram/
    Hard: Largest Rectangle in Histogram

    Given an array of integers heights representing the
    histogram's bar height where the width of each bar
    is 1, return the area of the largest rectangle in the histogram.

    Input: heights = [2,1,5,6,2,3]
    Output: 10
    Explanation: The above is a histogram where width of each bar is 1.
    The largest rectangle is shown in the red area, which has an area = 10 units.

    Input: heights = [2,4]
    Output: 4

    Constraints:

    1 <= heights.length <= 105
    0 <= heights[i] <= 104

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings *.c -lm

    Date: 18 Oct 2021
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


#define max(a, b) a>b?a:b
// C program for array implementation of stack
// A structure to represent a stack
struct Stack
{
  int top;
  unsigned capacity;
  int* array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
  struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (int*) malloc(stack->capacity * sizeof(int));
  return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{   return stack->top == stack->capacity - 1; }

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{   return stack->top == -1;  }

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
  if (isFull(stack))
    return;
  stack->array[++stack->top] = item;
  //printf("%d pushed to stack\n", item);
}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
  if (isEmpty(stack))
    return INT_MIN;
  return stack->array[stack->top--];
}

// Function to return the last item from stack
int back(struct Stack* stack)
{
  if (isEmpty(stack))
    return INT_MIN;
  return stack->array[stack->top];
}

int largestRectangleArea(int* heights, int heightsSize) {
  // 在heights数组后增加一个高度为0的bar
  heightsSize += 1;
  //realloc(heights, sizeof(int)*heightsSize);
  //heights[heightsSize-1] = 0;
  int* tempArray = (int*)malloc(sizeof(int)*heightsSize);
  for(int j=0; j<heightsSize-1; j++)
    tempArray[j] = heights[j];
  tempArray[heightsSize-1] = 0;
  struct Stack* stack = createStack(heightsSize);
  int sum = 0;
  int i = 0;
  while(i < heightsSize) {
    if(isEmpty(stack) || tempArray[i] > tempArray[back(stack)]) {
      push(stack, i);
      i++;
    } else {
      int t = back(stack);
      //printf("%d\n", t);
      pop(stack);
      // stack为空的情况
      int temp = tempArray[t]*(isEmpty(stack)?i:i-back(stack)-1);
      sum = max(sum, temp);
    }
  }
  free(tempArray);
  return sum;
}

int main (int argc, char **argv) {
  int ret = 0;
  int heights[] = {2,1,5,6,2,3};
  int heightsSize = sizeof(heights)/sizeof(heights[0]);

  ret =  largestRectangleArea(heights, heightsSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=131 :Output = 10
**/
