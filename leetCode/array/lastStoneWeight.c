/*
  We have a collection of stones, each stone has a positive integer weight.
  Each turn, we choose the two heaviest stones and smash them together.
  Suppose the stones have weights x and y with x <= y.  The result of this smash is:
  If x == y, both stones are totally destroyed;
  If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
  At the end, there is at most 1 stone left.  Return the weight of this stone (or 0 if there are no stones left.)
  Example 1:
  Input: [2,7,4,1,8,1]
  Output: 1
  Explanation:
  We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
  we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
  we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
  we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of last stone.
  Note:
  1 <= stones.length <= 30
  1 <= stones[i] <= 1000
  Date: 06/07/2020 08:07AM - PDT
  Logic : https://www.youtube.com/watch?v=fWS0TCcr-lE&t=56s

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
    if(obj->accum_sum_buf[m] < pick){
      l = m + 1;
    } else {
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
  int arr[] = {3, 14, 9, 7};
  int size = sizeof(arr) / sizeof(arr[0]);


  solution *obj = solutionCreate(arr, size);

  int ret = solutionPickIndex(obj);
  printf ("ret--> %d \n", ret);
  solutionFree(obj);
}
