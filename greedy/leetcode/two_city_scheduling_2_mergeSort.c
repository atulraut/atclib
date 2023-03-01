/***
 * LeetCode : Two City Scheduling using C Merge Sort
 * There are 2N people a company is planning to interview.
 * The cost of flying the i-th person to city A is costs[i][0], and
 * the cost of flying the i-th person to city B is costs[i][1].
 * Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.
 * Example 1:
 * Input: [[10,20],[30,200],[400,50],[30,20]]
 * Output: 110
 * Explanation:
 * The first person goes to city A for a cost of 10.
 * The second person goes to city A for a cost of 30.
 * The third person goes to city B for a cost of 50.
 * The fourth person goes to city B for a cost of 20.
 * The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
 * Note:
 *   1 <= costs.length <= 100
 *   It is guaranteed that costs.length is even.
 *   1 <= costs[i][0], costs[i][1] <= 1000
 * Logic :
 * 1] Get Delta (A-B)  2] Arrange Delta as per ascending order.
 * https://www.youtube.com/watch?v=8Gm0jxpRBGw
 * => ./a.out
 * In getDynamicArray Input
 * A                |   B
 * arr[0][0] = |33| | 	arr[0][1] = |36| |
 * arr[1][0] = |27| | 	arr[1][1] = |15| |
 * arr[2][0] = |43| | 	arr[2][1] = |35| |
 * arr[3][0] = |36| | 	arr[3][1] = |42| |
 * head->delta = -3
 * [twoCitySchedCost] Enter [L=69]
 * [twoCitySchedCost] Enter [L=69]
 * [twoCitySchedCost] ptr = 0x221b530 ptr->index=3 ptr->delta=-6 [L=82]
 * [twoCitySchedCost] ptr = 0x221b4d0 ptr->index=0 ptr->delta=-3 [L=82]
 * [twoCitySchedCost] ptr = 0x221b510 ptr->index=2 ptr->delta=8 [L=82]
 * [twoCitySchedCost] ptr = 0x221b4f0 ptr->index=1 ptr->delta=12 [L=82]
 * Output --> 119 {36(i-3)+33(i-0) + 15(i-1)+35(i-2)}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int** arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int* L[n1];
    int* R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i][0]-L[i][1] <= R[j][0]-R[j][1]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int** arr, int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize){
    mergeSort(costs, 0, costsSize-1);

    int result = 0;
    for (int i = 0; i < costsSize; i++) {
        result += (i < costsSize/2) ? costs[i][0] : costs[i][1];
    }

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

int main () {
  int i, j, d=40, c=40, Output, row, col;
  int costsSize ;
  int costsColSize;

  int costs[4][2] = {
		 {10,20},
		 {30,200},
		 {400,50},
		 {30,20},
		};
  row = costsSize = 4;
  col = costsColSize = 2;

  int **arr = getDynamicArray(4, 2);

  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      arr[i][j] = rand() % 50;//i + d  + j + c;
      printf ("arr[%d][%d] = |%d| | \t",i,j, arr[i][j]);
    }
    printf ("\n");
  }
  /*
  arr[4][2] = {
		 {10,20},
		 {30,200},
		 {400,50},
		 {30,20},
  };
  */
  Output =  twoCitySchedCost(arr, costsSize, &costsColSize);
  printf ("Output --> %d \n", Output);

  return 0;
}
