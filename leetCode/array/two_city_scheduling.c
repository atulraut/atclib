/***
 * LeetCode : Two City Scheduling using C
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

struct person {
  struct person* next;
  int index;
  int delta;
};

/*Approch I:  4ms Solution*/
int twoCitySchedCost(int (*costs)[2], int costsSize, int* costsColSize) {
  struct person* head;
  struct person* ptr;
  struct person* new_node;
  int i;
  int cost_total = 0;
  head = malloc(sizeof(struct person));
  head->next = NULL;
  head->index = 0;

  head->delta = costs[0][0] - costs[0][1];
  printf ("head->delta = %d \n", head->delta);

  for (i=1; i<costsSize; i++) {
    new_node = malloc(sizeof(struct person));
    new_node->next = NULL;
    new_node->index = i;
    new_node->delta = costs[i][0]-costs[i][1];
    if (new_node->delta < head->delta) {
      new_node->next = head;
      head = new_node;
    } else {
      printf ("[%s] Enter [L=%d]\n", __func__, __LINE__);
      ptr = head;
      while ((ptr->next != NULL) && (ptr->next->delta < new_node->delta)) {
	ptr = ptr->next;
	printf ("[%s] Enter [L=%d]\n", __func__, __LINE__);
      }
      new_node->next = ptr->next;
      ptr->next = new_node;
    }
  }

  ptr = head;
  while (ptr != NULL) {
      printf ("[%s] ptr = %p ptr->index=%d ptr->delta=%d [L=%d]\n", __func__, ptr, ptr->index, ptr->delta, __LINE__);
      ptr = ptr->next;
  }

  for (i=0; i<costsSize/2; i++) {
    printf ("[%s] Enter =%d [L=%d]\n", __func__, costs[head->index][0], __LINE__);
    cost_total += costs[head->index][0];
    head = head->next;
  }
  for (i=0; i<costsSize/2; i++) {
    printf ("[%s] Enter =%d [L=%d]\n", __func__, costs[head->index][0], __LINE__);
    cost_total += costs[head->index][1];
    head = head->next;
  }

  /* free new nodes */
  ptr = head;
  struct person* temp = NULL;
  while (ptr != NULL) {
    temp = ptr;
    ptr =  ptr->next;
    free(temp);
    temp = NULL;
  }

  return cost_total;
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
      arr[i][j] = rand() % 50;
      printf ("arr[%d][%d] = |%d| | \t",i,j, arr[i][j]);
    }
    printf ("\n");
  }

  Output =  twoCitySchedCost(costs, costsSize, &costsColSize);
  printf ("Output --> %d \n", Output);

  return 0;
}
