/***
    https://leetcode.com/problems/maximum-frequency-stack
    Maximum Frequency Stack

    Design a stack-like data structure to push elements to
    the stack and pop the most frequent element from the stack.

    Implement the FreqStack class:

    FreqStack() constructs an empty frequency stack.
    void push(int val) pushes an integer val onto the top
    of the stack.
    int pop() removes and returns the most frequent
    element in the stack.
    If there is a tie for the most frequent element,
    the element closest to the stack's top is removed and returned.

    Input
    ["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop", "pop", "pop"]
    [[], [5], [7], [5], [7], [4], [5], [], [], [], []]
    Output
    [null, null, null, null, null, null, null, 5, 7, 5, 4]

    Explanation
    FreqStack freqStack = new FreqStack();
    freqStack.push(5); // The stack is [5]
    freqStack.push(7); // The stack is [5,7]
    freqStack.push(5); // The stack is [5,7,5]
    freqStack.push(7); // The stack is [5,7,5,7]
    freqStack.push(4); // The stack is [5,7,5,7,4]
    freqStack.push(5); // The stack is [5,7,5,7,4,5]
    freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,5,7,4].
    freqStack.pop();   // return 7, as 5 and 7 is the most frequent, but 7 is closest to the top. The stack becomes [5,7,5,4].
    freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,4].
    freqStack.pop();   // return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top. The stack becomes [5,7].

    Constraints:

    0 <= val <= 109
    At most 2 * 104 calls will be made to push and pop.
    It is guaranteed that there will be at least one element in the stack before calling pop.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Mar 19 11:58:18 PDT 2022
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

/*
  Context : Below is a barebone and low-level implementation for
  this given problem involving mmap(). It does not use any kind
  of built-in Data Structures such as maps, max-heap, etc. It uses
  custom data organization in achieving O(1) Push/Pop operations
  for the most-frequent-stack logic. Instead of using the usual malloc,
  calloc, and the like to allocate memory, below code uses mmap() system
  call(which of course would be called by malloc and the like for
  large allocations) directly since the former ones failed in doing
  the needed memory allocation for unknown reasons. Before arriving
  at the below simple solution, I had spent significant time and
  effort on other approaches similar to my LFU implementation, but
  due to insufficient memory, I had to redesign the whole thing and
  come up with below simple one, which I feel is totally worth my
  time and effort. Cheers.

  NOTE: There is absolutely no memory-(re)allocation in the Push/Pop
  functions. All allocations are done in one-shot using a single
  mmap() call. Of course, the backing memory regions would be made
  available on-demand as page-faults occur and new pages for those
  are allocated which I think is true even for malloc, etc and also
  the Push/Pop operations for built-in data structures in other languages.

  Below are part of sys/mman.h, but for some reason(platform macro disabled?), these
  don't look like accessible even if that's included. So, defining these myself here
  based on their original values.
*/

#define PROT_READ           0x1
#define PROT_WRITE          0x2
#define MAP_ANONYMOUS       0x20
#define MAP_PRIVATE         0x02
#define MAP_FAILED          ((void *)-1)
extern void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

#define ALL_SZ              10000
#define ONEG                (1024 * 1024 * 1024ULL)

struct this {
  uint16_t out[ALL_SZ];
  uint16_t mbuf[ONEG];
  uint16_t mxf;
  int fmup[ALL_SZ][ALL_SZ];
} FreqStack;

struct FreqStack* freqStackCreate() {
  /*
    Though usual malloc, calloc, would internally call
    mmap() for large allocations such as this, for
    some reason, it didn't or failed in doing so. So, I am
    directly using mmap() myself for doing the needed
    anonymous memory allocation.
  */
  return mmap(NULL, sizeof(struct FreqStack), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void freqStackPush(struct FreqStack* obj, int x) {
  struct FreqStack *f = obj;
  int fq = ++f->mbuf[x];
  f->fmup[fq][++f->out[fq]] = x;
  f->mxf < f->mbuf[x] ? f->mxf = f->mbuf[x] : 0;
}

int freqStackPop(struct FreqStack* obj) {
  struct FreqStack *f = obj;
  int val = f->fmup[f->mxf][f->out[f->mxf]--];
  f->mbuf[val]--;
  !f->out[f->mxf] ? f->mxf-- : 0;
  return val;
}

void freqStackFree(struct FreqStack* obj) {
  munmap(obj);
}

void test() {
  int ret = 0;
  struct FreqStack* obj = freqStackCreate();
  freqStackPush(obj, 5); // The stack is [5]
  freqStackPush(obj, 7); // The stack is [5,7]
  freqStackPush(obj, 5); // The stack is [5,7,5]
  freqStackPush(obj, 7); // The stack is [5,7,5,7]
  freqStackPush(obj, 4); // The stack is [5,7,5,7,4]
  freqStackPush(obj, 5); // The stack is [5,7,5,7,4,5]
  ret = freqStackPop(obj);   // return 5, as 5 is the most frequent. The stack becomes [5,7,5,7,4].
  debug("Output = %d", ret);
  ret = freqStackPop(obj);   // return 7, as 5 and 7 is the most frequent, but 7 is closest to the top. The stack becomes [5,7,5,4].
  debug("Output = %d", ret);
  ret = freqStackPop(obj);   // return 5, as 5 is the most frequent. The stack becomes [5,7,4].
  debug("Output = %d", ret);
  ret = freqStackPop(obj);   // return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top. The stack becomes [5,7].
  debug("Output = %d", ret);
  freqStackFree(obj);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
