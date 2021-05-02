/***
    Hard: 630. Course Schedule III
    https://leetcode.com/problems/course-schedule-iii/

    There are n different online courses numbered from 1 to n.
    You are given an array courses where courses[i] = [durationi, lastDayi]
    indicate that the ith course should be taken continuously for durationi
    days and must be finished before or on lastDayi.

    You will start on the 1st day and you cannot take two or more courses
    simultaneously.

    Return the maximum number of courses that you can take.

    Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
    Output: 3
    Explanation:
    There are totally 4 courses, but you can take 3 courses at most:
    First, take the 1st course, it costs 100 days so you will finish it on
    the 100th day, and ready to take the next course on the 101st day.
    Second, take the 3rd course, it costs 1000 days so you will finish it
    on the 1100th day, and ready to take the next course on the 1101st day.
    Third, take the 2nd course, it costs 200 days so you will finish it
    on the 1300th day.
    The 4th course cannot be taken now, since you will finish it on
    the 3300th day, which exceeds the closed date.

    Input: courses = [[1,2]]
    Output: 1

    Input: courses = [[3,2],[4,3]]
    Output: 0

    Constraints:
    1 <= courses.length <= 104
    1 <= durationi, lastDayi <= 104

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
#define ROWS 4//2
#define COLS 2

typedef struct heap_s {
  int capacity;
  int size;
  int* arr;
} heap_t;

heap_t* init(int);
void insert(heap_t*, int);
int top(heap_t*);
void pop(heap_t*);

// course list sorted by deadline asc
int deadlinecmp(void** a, void** b) {
  return (*(int**)a)[1] - (*(int**)b)[1];
}

int scheduleCourse(int** courses, int coursesRowSize, int* coursesColSizes) {
  heap_t* heap = init(coursesRowSize);
  qsort(courses, coursesRowSize, sizeof(int*), deadlinecmp);
  int t = 0;
  for (int i = 0; i < coursesRowSize; i++) {
    // learn course i
    t += courses[i][0];
    insert(heap, courses[i][0]);
    // when time is over deadline
    if (t > courses[i][1]) {
      // remove the most long duration course
      t -= top(heap);
      pop(heap);
    }
  }

  return heap->size;
}

heap_t* init(int max) {
  heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
  heap->capacity = max;
  heap->size = 0;
  heap->arr = (int*)malloc(sizeof(int) * (max + 1));
  return heap;
}

int top(heap_t* heap) {
  return heap->arr[1];
}

void swap(int* a, int i, int j) {
  a[i] = a[i] ^ a[j];
  a[j] = a[i] ^ a[j];
  a[i] = a[i] ^ a[j];
}

void insert(heap_t* heap, int val) {
  heap->arr[++heap->size] = val;
  for (int i = heap->size; i > 1 && heap->arr[i] > heap->arr[i / 2]; i /= 2)
    swap(heap->arr, i, i / 2);
}
void pop(heap_t* heap) {
  heap->arr[1] = heap->arr[heap->size--];
  for (int i = 1; i * 2 <= heap->size;) {
    // find smaller child to compare with the current node
    int child = heap->arr[i * 2] > heap->arr[i * 2 + 1] ? i * 2 : i * 2 + 1;
    if (heap->arr[child] > heap->arr[i]) {
      // swap if child is smaller
      swap(heap->arr, child, i);
      i = child;
    } else
      break;
  }
}

int** create_matrix(int rows, int cols) {
  int** mat = (int**) malloc(rows * sizeof(int*));
  int i;
  for (i = 0; i < rows; i++)
    mat[i] = (int*)malloc(cols * sizeof(int));
  return mat;
}

int main () {
  int ret = 0;
  int **courses = create_matrix(ROWS, COLS);
  int coursesRowSize= ROWS;
  int coursesColSizes = COLS;
  //courses = [[3,2],[4,3]]
  //courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
  /*
  *(*(courses + 0) + 0) = 3;
  *(*(courses + 0) + 1) = 2;

  *(*(courses + 1) + 0) = 4;
  *(*(courses + 1) + 1) = 3;
  */

  *(*(courses + 0) + 0) = 100;
  *(*(courses + 0) + 1) = 200;

  *(*(courses + 1) + 0) = 200;
  *(*(courses + 1) + 1) = 1300;

  *(*(courses + 2) + 0) = 1000;
  *(*(courses + 2) + 1) = 1250;

  *(*(courses + 3) + 0) = 2000;
  *(*(courses + 3) + 1) = 3200;

  ret = scheduleCourse(courses, coursesRowSize, &coursesColSizes);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=165 :Output = 3
**/
