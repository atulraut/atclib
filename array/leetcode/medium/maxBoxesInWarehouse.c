/***
    Medium: Put Boxes Into the Warehouse I
    https://leetcode.com/problems/put-boxes-into-the-warehouse-i/

    You are given two arrays of positive integers, boxes and warehouse,
    representing the heights of some boxes of unit width and the heights
    of n rooms in a warehouse respectively. The warehouse's rooms are
    labelled from 0 to n - 1 from left to right where warehouse[i] (0-indexed)
    is the height of the ith room.

    Boxes are put into the warehouse by the following rules:

    Boxes cannot be stacked.
    You can rearrange the insertion order of the boxes.
    Boxes can only be pushed into the warehouse from left to right only.
    If the height of some room in the warehouse is less than the height of
    a box, then that box and all other boxes behind it will be stopped
    before that room.

    Return the maximum number of boxes you can put into the warehouse.

    Input: boxes = [4,3,4,1], warehouse = [5,3,3,4,1]
    Output: 3
    Status : UnResolved

    Date: 7 May, 2021
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

#define min(x, y) (((x) > (y)) ? x : y)

void insertionSort(int list[], int n) {
  // sort list[0] to list[n-1] in ascedning order
  for(int h=1; h<n; h++) {
    int key = list[h];		/* I */
    int j=h-1; /* start comparing with previous item */
    while(j>=0 && key < list[j]) { /*Copy Elememnt from Unsorted(list[j]) to Sorted Array (list[j+1])*/
      list[j+1] = list[j];	/* II */
      --j;
    }
    list[j+1] = key; /* III - key will create hole, copy that at last*/
  }//end for
}//end insertionSort


int maxBoxesInWarehouse2(int* boxes, int boxesSize, int* warehouse, int warehouseSize) {
  int i = boxesSize - 1;
  int count = 0;
  insertionSort(boxes, boxesSize);

  for (int room=0; room<warehouseSize; ++room) {
    // Iterate through boxes from largest to smallest
    // Discard boxes that doesn't fit in the current warehouse
    while (i >= 0 && boxes[i] > room) {
      i--;
    }

    if (i == -1)
      return count;
    count++;
    i--;
  }
  return count;
}

int maxBoxesInWarehouse(int* boxes, int boxesSize, int* warehouse, int warehouseSize)  {
  // Preprocess the height of the warehouse rooms to get usable heights
  for (int i = 1; i < warehouseSize; i++) {
    warehouse[i] = min(warehouse[i - 1],  warehouse[i]);
  }

  // Iterate through boxes from smallest to largest
  insertionSort(boxes, boxesSize);

  int count = 0;

  for (int i = warehouseSize - 1; i >= 0; i--) {
    // Count the boxes that can fit in the current warehouse room
    if (count < boxesSize && boxes[count] <= warehouse[i]) {
      count++;
    }
  }
  printf ("count = %d \n", count);
  if(count > 1)
    return count-1;
  else
    return count;
}

int main () {
  int ret = 0;
  int boxes[] = {4,3,4,1};
  int boxesSize = sizeof(boxes)/sizeof(boxes[0]);
  int warehouse[] = {5,3,3,4,1};
  int warehouseSize = sizeof(warehouse)/sizeof(warehouse[0]);

  ret = maxBoxesInWarehouse(boxes, boxesSize, warehouse, warehouseSize);

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
