/***
    https://leetcode.com/problems/validate-stack-sequences

    Validate Stack Sequences

    Given two integer arrays pushed and popped each with distinct values,
    return true if this could have been the result of a sequence
    of push and pop operations on an initially empty stack, or false otherwise.

    Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
    Output: true
    Explanation: We might do the following sequence:
    push(1), push(2), push(3), push(4),
    pop() -> 4,
    push(5),
    pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

    Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
    Output: false
    Explanation: 1 cannot be popped before 2.

    Constraints:

    1 <= pushed.length <= 1000
    0 <= pushed[i] <= 1000
    All the elements of pushed are unique.
    popped.length == pushed.length
    popped is a permutation of pushed.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue Mar 15 22:28:25 PDT 2022
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



bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize) {
  int i = 0, j = 0, k = 0;
  int * arr = (int*) malloc (pushedSize * sizeof(int));
  while (k >= 0 && k < pushedSize && j < poppedSize) {
    if (k>0 && arr[k-1] == popped[j]) {
      k--; j++;
    } else {
      if (i < pushedSize) {
	if (pushed[i] == popped[j]) {
	  i++; j++;
	} else {
	  arr[k++] = pushed[i++];
	}
      } else {
	free (arr);
	return false;
      }
    }
  }
  free (arr);
  return true;
}

bool validateStackSequences2(int* pushed, int pushedSize, int* popped, int poppedSize) {
  int pushed_index = 0;
  int popped_index = 0;
  int stack[pushedSize];
  int top_of_stack = 0;

  while(pushed_index < pushedSize/* && popped_index < poppedSize*/) {
    stack[top_of_stack++] = pushed[pushed_index++]; // push
    while(top_of_stack > 0 && stack[top_of_stack - 1] == popped[popped_index]) {
      popped_index++;
      top_of_stack--; // pop
    }
  }
  return (top_of_stack == 0);
}

void test() {
  bool ret;
  int pushed[] = {1, 2, 3, 4, 5};
  int pushedSize = 5;
  int popped[] = {4, 5, 3, 2, 1};
  int poppedSize = 5;

  ret =  validateStackSequences(pushed, pushedSize, popped, poppedSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=111 :Output = 1
**/
