/***

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 28 Nov 2021
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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

struct stateType {
  bool visit:1;
  int freq:31;
};

int* frequencySort3(int* nums, int numsSize, int* returnSize) {
  int i, j;
  struct stateType* state = (struct stateType*)malloc(numsSize * sizeof(struct stateType));
  int* ans = (int *)calloc(numsSize, sizeof(int));
  if (NULL == state)
    return ans;

  for (i=0; i<numsSize; ++i) {
    if (state[i].visit == true)
      continue;
    state[i].visit = true;
    state[i].freq = 1;

    for (j=i+1; j<numsSize; ++j) {
      if (nums[i] == nums[j]) {
	state[i].freq = state[i].freq+1;
	state[j].visit = true;
      }
    }
  }

  debug ("[0]-> %d", state[0].freq);
  for (i=1; i<numsSize; ++i) {
    //    if (state[i].freq == 0)
    //  state[i].freq = state[i-1].freq;
    debug ("[%d]-> %d",i, state[i].freq);
  }

  return ans;
}

int main (int argc, char **argv) {
  int* ret;
  int nums[] = {1, 1, 2, 2, 2, 3};
  int numsSize = 6;
  int returnSize;

  ret = frequencySort3(nums, numsSize, &returnSize);
  //  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [frequencySort3] L=62 :[0]-> 2
   [frequencySort3] L=66 :[1]-> 2
   [frequencySort3] L=66 :[2]-> 3
   [frequencySort3] L=66 :[3]-> 3
   [frequencySort3] L=66 :[4]-> 3
   [frequencySort3] L=66 :[5]-> 1
**/
