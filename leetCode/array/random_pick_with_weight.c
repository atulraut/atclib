/***
 * LeetCode : Random Pick with Weight
 * Given an array w of positive integers, where w[i] describes the weight of index
 * i(0-indexed), write a function pickIndex which  * randomly picks an index in proportion
 *  to its weight.
 * For example, given an input list of values w = [2, 8], when we pick up a number out of it,
 * the chance is that 8 times out of 10 we should pick the number 1 as the answer since it's
 * the second element of the array (w[1] = 8).
 * Example 1:
 * Input
 * ["Solution","pickIndex"]
 * [[[1]],[]]
 * Output
 * [null,0]
 * Explanation
 * Solution solution = new Solution([1]);
 * solution.pickIndex(); // return 0. Since there is only one single element on the array
 * the only option is to return the first element.
 * Example 2:
 * Input
 * ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
 * [[[1,3]],[],[],[],[],[]]
 * Output
 * [null,1,1,1,1,0]
 * Explanation
 * Solution solution = new Solution([1, 3]);
 * solution.pickIndex(); // return 1. It's returning the second element (index = 1) that has probability of 3/4.
 * solution.pickIndex(); // return 1
 * solution.pickIndex(); // return 1
 * solution.pickIndex(); // return 1
 * solution.pickIndex(); // return 0. It's returning the first element (index = 0) that has probability of 1/4.
 * Since this is a randomization problem, multiple answers are allowed so the following outputs can be considered correct :
 * [null,1,1,1,1,0]
 * [null,1,1,1,1,1]
 * [null,1,1,1,0,0]
 * [null,1,1,1,0,1]
 * [null,1,0,1,0,0]
 * ..... and so on.
 * Logic: https://www.youtube.com/watch?v=fWS0TCcr-lE&t=56s
 * https://leetcode.com/problems/random-pick-with-weight/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _sol {
  int *accum_sum_buf;
  int max;
  int sz;
} solution;

/*
  int *w: Input Array
  int wSize: Size of Input Array
*/
solution* solutionCreate (int *w, int wSize) {
  int i;

  //  int rand = rand() % wSize;
  solution *obj = (solution *)malloc(sizeof(solution));
  obj->accum_sum_buf =(int *)malloc(sizeof(int) * wSize);
  obj->sz = wSize;
  obj->max = 0;

  for(i = 0; i<wSize; i++){
    obj->max += w[i];
    obj->accum_sum_buf[i] = obj->max;
  }
  return obj;
}

// binary search
int solutionPickIndex(solution *obj) {
  int pick = rand() % obj->max+1;
  printf ("[%s] pickIndex = %d [L=%d] \n", __func__, pick, __LINE__);
  int l = 0, h = obj->sz - 1;

  while(l < h){
    int m = l + (h - l) / 2;
    if (pick == obj->accum_sum_buf[m])
      return obj->accum_sum_buf[m];
    if(pick > obj->accum_sum_buf[m])
      l = m + 1;
    //if(pick < obj->accum_sum_buf[m])
    //  h = m - 1;
    else {
      h = m;
    }
  }
  return l;
}

void solutionFree(solution *obj) {
  if(obj) {
    free(obj->accum_sum_buf);
    obj->accum_sum_buf = NULL;
    free(obj);
    obj = NULL;
  }
}

int main () {
  //int arr[] = {3, 14, 9, 7};
  int arr[] = {1, 2, 3};
  int size = sizeof(arr) / sizeof(arr[0]);


  solution *obj = solutionCreate(arr, size);

  int ret = solutionPickIndex(obj);
  printf ("ret--> %d \n", ret);
  solutionFree(obj);
}

/***
 * Core Loogic :
 * while(l < h){
    int m = l + (h - l) / 2;
    if(pick > obj->accum_sum_buf[m]){
      l = m + 1;
    } else {
      h = m;
    }
  }
  return l;while(l < h){
    int m = l + (h - l) / 2;
    if(obj->accum_sum_buf[m] < pick){
      l = m + 1;
    } else {
      h = m;
    }
  }
  return l;
 */
