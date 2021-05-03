/***
    1229. Meeting Scheduler
    Given the availability time slots arrays slots1 and slots2 of two people
    and a meeting duration duration, return the earliest time slot that works
    for both of them and is of duration duration.

    If there is no common time slot that satisfies the requirements, return an
    empty array.

    The format of a time slot is an array of two elements [start, end] representing
    an inclusive time range from start to end.

    It is guaranteed that no two availability slots of the same person intersect
    with each other. That is, for any two time slots [start1, end1] and [start2, end2]
    of the same person, either start1 > end2 or start2 > end1.

    Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
    Output: [60,68]

    Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
    Output: []

    Constraints:
    1 <= slots1.length, slots2.length <= 104
    slots1[i].length, slots2[i].length == 2
    slots1[i][0] < slots1[i][1]
    slots2[i][0] < slots2[i][1]
    0 <= slots1[i][j], slots2[i][j] <= 109
    1 <= duration <= 106

    https://leetcode.com/problems/meeting-scheduler/
    Date: 02 May 2021.
    San Diego, CA.
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
typedef struct {
  int start;
  int end;
} data_t;

data_t* pq;
int pq_i;

bool is_less(int i, int j) {
  data_t source = pq[i];
  data_t target = pq[j];

  if (source.start < target.start) {
    return true;
  } else if (source.start == target.start && source.end < target.end) {
    return true;
  } else {
    return false;
  }
}

void swap(int i, int j) {
  data_t temp = pq[i];
  pq[i] = pq[j];
  pq[j] = temp;
}

void swim(int i) {
  while (i > 1 && is_less(i, i/2)) {
    swap(i, i/2);
    i = i/2;
  }
}

void sink(int i) {
  int j;

  while (i * 2 <= pq_i && is_less(i*2, i)) {
    j = i * 2;

    if (j+1 <= pq_i && is_less(j+1, j)) {
      j += 1;
    }

    swap(i, j);
    i = j;
  }
}

void push(int* arr) {
  pq_i++;
  pq[pq_i].start = arr[0];
  pq[pq_i].end = arr[1];
  swim(pq_i);
}

data_t pop() {
  assert(pq_i >= 1);
  data_t top = pq[1];

  if (pq_i > 1) {
    pq[1] = pq[pq_i];
    pq_i--;
    sink(1);
  } else {
    pq_i = 0;
  }

  return top;
}

void pq_init(int size) {
  pq = (data_t*) malloc((size + 1) * sizeof(data_t));
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minAvailableDuration(int** slots1, int slots1Size, int* slots1ColSize,
                          int** slots2, int slots2Size, int* slots2ColSize,
                          int duration, int* returnSize) {

  pq_i = 0;
  pq_init(slots1Size + slots2Size);
  int* ans = (int*) malloc(2 * sizeof(int));
  *returnSize = 0;

  for (int i = 0; i < slots1Size; i++) {
    int start = slots1[i][0];
    int end = slots1[i][1];

    if (end - start >= duration) {
      push(slots1[i]);
    }
  }

  for (int i = 0; i < slots2Size; i++) {
    int start = slots2[i][0];
    int end = slots2[i][1];

    if (end - start >= duration) {
      push(slots2[i]);
    }
  }

  while (pq_i >= 2) {
    data_t a = pop();
    data_t b = pq[1];
    int start = (a.start > b.start) ? a.start : b.start;
    int end = (a.end < b.end) ? a.end : b.end;

    if (end - start >= duration) {
      ans[0] = start;
      ans[1] = start + duration;
      *returnSize = 2;
      break;
    }
  }

  free(pq);

  return ans;
}


int** create_matrix(int rows, int cols) {
  int** mat = (int**) malloc(rows * sizeof(int*));
  int i;
  for (i = 0; i < rows; i++)
    mat[i] = (int*)malloc(cols * sizeof(int));
  return mat;
}

int main () {
  int *ret = 0;
  // Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
  int** slots1 = create_matrix(3, 2);
  int slots1Size = 3;
  int slots1ColSize = 2;
  int** slots2 = create_matrix(2, 2);
  int slots2Size = 2;
  int slots2ColSize = 2;
  int duration = 8;
  int returnSize;

  *(*(slots1 + 0) + 0) = 10;
  *(*(slots1 + 0) + 1) = 50;

  *(*(slots1 + 1) + 0) = 60;
  *(*(slots1 + 1) + 1) = 120;

  *(*(slots1 + 2) + 0) = 140;
  *(*(slots1 + 2) + 1) = 210;

  *(*(slots2 + 0) + 0) = 0;
  *(*(slots2 + 0) + 1) = 15;

  *(*(slots2 + 1) + 0) = 60;
  *(*(slots2 + 1) + 1) = 70;

  ret = minAvailableDuration(slots1, slots1Size, &slots1ColSize,
                          slots2, slots2Size, &slots2ColSize,
			     duration, &returnSize);

  for (int i=0; i<returnSize; i++)
    debug("Output = %d", ret[i]);

  return 0;
}

/**
=> ./a.out
[main] L=213 :Output = 60
[main] L=213 :Output = 68
 **/
