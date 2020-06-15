/***
 * LeetCode: Queue Reconstruction by Height
 * Suppose you have a random list of people standing in a queue.
 * Each person is described by a pair of integers (h, k), where h
 * is the height of the person and k is the number of people in front
 * of this person who have a height greater than or equal to h. Write
 * an algorithm to reconstruct the queue.
 * Note:
 * The number of people is less than 1,100.
 * Example
 * Input:
 * [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
 * Output:
 * [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
 * Logic : https://www.youtube.com/watch?v=khddrw6Bfyw&t=59s
 * https://leetcode.com/problems/queue-reconstruction-by-height/discuss/386690/My-C-code
 * Date: 06/07/2020 12.58PM PDT
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmpfunc(int** a, int** b) {
    int* pa = (*a);
    int* pb = (*b);

    if(pa[0]==pb[0]) // if same height, position small at the front
        return pa[1] - pb[1];
    else             // bigger height at the front
        return pb[0] - pa[0];
}

void helper(int** result, int size, int* people) {
    int i;

    for(i=size; i>people[1]; i--) {
        result[i][0] = result[i-1][0];
        result[i][1] = result[i-1][1];
    }
    result[i][0] = people[0];
    result[i][1] = people[1];
}

 /**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes
 * array.
 * Note: Both returned array and *columnSizes array must be
 * malloced, assume caller calls free().
 */
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize,
		       int* returnSize, int** returnColumnSizes) {

    int** result = (int**)malloc(peopleSize*sizeof(int*));
    int i;

    (*returnColumnSizes) = (int*)malloc(peopleSize*sizeof(int));
    for(i=0;i<peopleSize;i++) {
        result[i] = (int*)malloc(2*sizeof(int));
        (*returnColumnSizes)[i] = 2;
    }

    /* sort array based on hieght in ASC order */
    qsort(people, peopleSize, sizeof(int*), cmpfunc);
    for (int i=0; i<6; i++) {
      for (int j=0; j<2; j++) {
	printf ("qsort [%d][%d] = |%d| | \t",i,j, people[i][j]);
      }
      printf ("\n\n");
    }


    for(i=0; i<peopleSize; i++) {
        helper(result, i, people[i]);
    }

    *returnSize = peopleSize;

    return result;
}

int **getDynamicArray(int row, int col) {
  int i, j;
  int **ar;
  ar = (int **)malloc(row * sizeof(int *));
  for (i=0; i<row; i++)
    ar[i] = (int *)malloc(col * sizeof(int));
  printf ("In getDynamicArray Input \n");
  return ar;
}

int main() {
  int arr[6][2] = {
    {7,0},
    {4,4},
    {7,1},
    {5,0},
    {6,1},
    {5,2}
  };
  int i,j;
  int row=6, col=2;
  int peopleSize;
  int peopleColSize;
  int  returnSize;
  int** returnColumnSizes;

  int **people = getDynamicArray(6, 2);

  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      people[i][j] = rand() % 10;
      printf ("Input[%d][%d] = |%d| | \t",i,j, people[i][j]);
    }
    printf ("\n");
  }
  peopleSize = 6;
  peopleColSize = 2;

 people = reconstructQueue(people, peopleSize, &peopleColSize,
			 &returnSize, returnColumnSizes);

 for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      printf ("Output[%d][%d] = |%d| | \t",i,j, people[i][j]);
    }
    printf ("\n");
  }

}

