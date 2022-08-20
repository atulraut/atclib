/***
    https://leetcode.com/problems/minimum-number-of-refueling-stops/
    Minimum Number of Refueling Stops
    Hard

    A car travels from a starting position to a destination which is
    target miles east of the starting position.

    There are gas stations along the way. The gas stations are represented
    as an array stations where stations[i] = [positioni, fueli] indicates
    that the ith gas station is positioni miles east of the starting
    position and has fueli liters of gas.

    The car starts with an infinite tank of gas, which initially has startFuel
    liters of fuel in it. It uses one liter of gas per one mile that it drives.
    When the car reaches a gas station, it may stop and refuel, transferring
    all the gas from the station into the car.

    Return the minimum number of refueling stops the car must make in order
    to reach its destination. If it cannot reach the destination, return -1.

    Note that if the car reaches a gas station with 0 fuel left, the car
    can still refuel there. If the car reaches the destination with 0 fuel
    left, it is still considered to have arrived.

    Input: target = 1, startFuel = 1, stations = []
    Output: 0
    Explanation: We can reach the target without refueling.

    Input: target = 100, startFuel = 1, stations = [[10,100]]
    Output: -1
    Explanation: We can not reach the target (or even the first gas station).

    Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
    Output: 2
    Explanation: We start with 10 liters of fuel.
    We drive to position 10, expending 10 liters of fuel.  We refuel
    from 0 liters to 60 liters of gas.
    Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
    and refuel from 10 liters to 50 liters of gas.  We then drive to and
    reach the target.
    We made 2 refueling stops along the way, so we return 2.

    Constraints:
    1 <= target, startFuel <= 109
    0 <= stations.length <= 500
    0 <= positioni <= positioni+1 < target
    1 <= fueli < 109

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Aug 20 05:28:49 AM PDT 2022
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

void heapPush(int* heap, int* heapSize, int element) {
  (*heapSize)++;
  heap[*heapSize] = element;

  int parent = *heapSize/2, child=*heapSize;

  while (parent>=1 && heap[parent] < element) {
    heap[child] = heap[parent];
    child       = parent;
    parent      = child/2;
  }
  heap[child] = element;
}


int heapPop(int* heap, int* heapSize) {
  int max = heap[1], last = heap[*heapSize], now=1, child=2;
  (*heapSize)--;

  for(; now*2 <= *heapSize; now=child) {
    child = now*2;

    if (child != *heapSize && heap[child + 1] > heap[child])
      child++;

    if (last < heap[child])
      heap[now] = heap[child];
    else
      break;
  }
  heap[now] = last;
  return max;
}

int minRefuelStops(int target, int startFuel, int** stations, int n, int* stationsColSize) {
  if (startFuel >= target)
    return 0;

  int tank = startFuel, prevStop=0, ans=0, heapSize=0;
  int* maxHeap = (int *) calloc(n+1,sizeof(int));

  for (int i=0; i<n; i++) {
    int position = stations[i][0];
    int capacity = stations[i][1];
    tank -= (position - prevStop);

    while (heapSize && tank < 0) {
      tank += heapPop(maxHeap, &heapSize);
      ans++;
    }

    if (tank < 0)
      return -1;

    if (tank >= target - position)
      return ans;
    if (tank + capacity >= target-position)
      return ans + 1;

    heapPush(maxHeap, &heapSize, capacity);
    prevStop = position;
  }

  tank -= (target - prevStop);
  while (heapSize && tank < 0) {
    tank += heapPop(maxHeap, &heapSize);
    ans++;
  }

  if (tank < 0)
    return -1;

  return ans;
}

int minRefuelStops2(int target, int startFuel, int** stations, int stationsSize, int* stationsColSize) {
  int stops = 0;

  if(stationsSize == 0) {
    return (startFuel >= target)? 0:-1;
  }

  while(startFuel < target) {
    int choice = -1;
    //find available/reachable stations
    for(int i = 0; i<stationsSize; i++) {
      if(stations[i][0] <= startFuel) choice = i;
      else break;
    }

    //find station with the most startFuel
    int largest = 0;
    int ind = 0;
    for(int i = 0; i<=choice; i++) {
      if(stations[i][1] > largest) {
	largest = stations[i][1];
	ind = i;
      }
    }

    //if not found/ possible, return -1
    if(largest == 0)
      return -1;

    startFuel += stations[ind][1];
    stations[ind][1] = -1;
    stops++;
  }
  return stops;
}

int** create_matrix(int rows, int cols) {
  int** max = (int **)calloc(sizeof(int *), rows);
  for (int i=0; i<rows; ++i)
    max[i] = (int *)calloc(sizeof(int), cols);

  return max;
}

void test() {
  int ret = 0;
  int target = 100;
  int startFuel = 10;
  // [[10,60],[20,30],[30,30],[60,40]]
  int n = 4;
  int stationsColSize = 2;
  int** stations = create_matrix(4, 2);
  *(*(stations + 0) + 0) = 10;
  *(*(stations + 0) + 1) = 60;

  *(*(stations + 1) + 0) = 20;
  *(*(stations + 1) + 1) = 30;

  *(*(stations + 2) + 0) = 30;
  *(*(stations + 2) + 1) = 30;

  *(*(stations + 3) + 0) = 40;
  *(*(stations + 3) + 1) = 60;

  ret = minRefuelStops(target, startFuel, stations, n, &stationsColSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   [test] L=221 :Output = 2
**/
