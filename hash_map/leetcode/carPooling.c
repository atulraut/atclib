/***
    https://leetcode.com/problems/car-pooling/
    1094. Car Pooling

    There is a car with capacity empty seats. The vehicle only
    drives east (i.e., it cannot turn around and drive west).

    You are given the integer capacity and an array trips
    where trip[i] = [numPassengersi, fromi, toi] indicates that
    the ith trip has numPassengersi passengers and the location
    to pick them up and drop them off are fromi and toi respectively.
    The locations are given as the number of kilometers due
    east from the car's initial location.

    Return true if it is possible to pick up and drop off all
    passengers for all the given trips, or false otherwise.

    Input: trips = [[2,1,5],[3,3,7]], capacity = 4
    Output: false

    Input: trips = [[2,1,5],[3,3,7]], capacity = 5
    Output: true

    Constraints:
    1 <= trips.length <= 1000
    trips[i].length == 3
    1 <= numPassengersi <= 100
    0 <= fromi < toi <= 1000
    1 <= capacity <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 5 Jan, 2021
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

bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity){
  int rem[1001] = {0};

  for(int i = 0; i < tripsSize; i++) {
    rem[trips[i][1]] += trips[i][0];
    rem[trips[i][2]] += -trips[i][0];
  }
  int curr = 0;
  for(int i = 0; i <= 1000; i++) {
    curr += rem[i];
    if(curr > capacity) {
      return false;
    }
  }
  return true;
}


int** create_matrix(int row, int col) {
  int** mat = (int **)malloc(sizeof(int *) * row);
  for (int i=0; i<row; ++i)
    mat[i] = (int *)malloc(sizeof(int) * col);

  return mat;
}

void test(int** trips) {
  int tripsSize = 2;
  int tripsColSize = 3;
  int capacity = 4;
  bool ret = carPooling(trips, tripsSize, &tripsColSize, capacity);
  debug ("Output = %d", ret);
  capacity = 5;
  ret = carPooling(trips, tripsSize, &tripsColSize, capacity);
  debug ("Output = %d", ret);
}

int main (int argc, char **argv) {
  int ret = 0;
  int row = 2;
  int col = 3;
  int** grid = create_matrix(2, 3);

  *(*(grid + 0) + 0) = 2;
  *(*(grid + 0) + 1) = 1;
  *(*(grid + 0) + 2) = 5;
  *(*(grid + 1) + 0) = 3;
  *(*(grid + 1) + 1) = 3;
  *(*(grid + 1) + 2) = 7;

  debug ("Input :> ");
  for (int i=0; i<row; ++i) {
    for (int j=0; j<col; ++j) {
      debug("Output = %d", grid[i][j]);
    }
    printf ("\n");
  }
  test(grid);
  return 0;
}

/**
   => ./a.out
   [main] L=113 :Input :>
   [main] L=116 :Output = 2
   [main] L=116 :Output = 1
   [main] L=116 :Output = 5

   [main] L=116 :Output = 3
   [main] L=116 :Output = 3
   [main] L=116 :Output = 7

   [test] L=94 :Output = 0
   [test] L=97 :Output = 1
**/
