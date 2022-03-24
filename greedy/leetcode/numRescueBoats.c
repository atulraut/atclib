/***
    https://leetcode.com/problems/boats-to-save-people
    Boats to Save People

    You are given an array people where people[i] is the
    Weight of the ith person, and an infinite number of
    boats where each boat can carry a maximum weight of
    limit. Each boat carries at most two people at the
    same time, provided the sum of the weight of those
    people is at most limit.

    Return the minimum number of boats to carry every given person.

    Input: people = [1,2], limit = 3
    Output: 1
    Explanation: 1 boat (1, 2)

    Input: people = [3,2,2,1], limit = 3
    Output: 3
    Explanation: 3 boats (1, 2), (2) and (3)

    Input: people = [3,5,3,4], limit = 5
    Output: 4
    Explanation: 4 boats (3), (3), (4), (5)

    Constraints:
    1 <= people.length <= 5 * 104
    1 <= people[i] <= limit <= 3 * 104

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Mar 23 21:34:33 PDT 2022
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

/***
    Approach 1: Greedy (Two Pointer)
    Intuition:
    If the heaviest person can share a boat with the lightest
    person, then do so. Otherwise, the heaviest person can't
    pair with anyone, so they get their own boat.

    The reason this works is because if the lightest person
    can pair with anyone, they might as well pair with the
    heaviest person.

    Algorithm:
    Let people[i] to the currently lightest person, and people[j]
    to the heaviest.

    Then, as described above, if the heaviest person can share a
    boat with the lightest person (if people[j] + people[i] <= limit)
    then do so; otherwise, the heaviest person sits in their own boat.
*/

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


int numRescueBoats1(int* people, int peopleSize, int limit){
  insertionSort(people, peopleSize);
  int i = 0, j = peopleSize - 1;
  int ans = 0;

  while (i <= j) {
    ans++;
    if (people[i] + people[j] <= limit)
      i++;
    j--;
  }
  return ans;
}

int comp(const void* v1, void* v2) {
  return *(int*) v1 - *(int*) v2;
}

int numRescueBoats(int* people, int peopleSize, int limit) {
  qsort((void*) people, peopleSize, sizeof(int), comp);
  //    insertionSort(people, peopleSize); // Error - 	Time Limit Exceeded
  int l = 0, r = peopleSize - 1;
  debug ("l=%d r=%d", l, r);
  int count = 0;
  while(r >= 0 && l < r + 1) {
    if(people[r] + people[l] > limit) {
      debug ("l=%d r=%d count=%d", people[l], people[r], count);
      count++;
      r--;
    } else {
      debug ("l=%d r=%d count=%d", people[l], people[r], count);
      count++;
      r--;
      l++;
    }
     debug ("l=%d r=%d count=%d", people[l], people[r], count);
  }
  return count;
}

void test() {
  int ret = 0;
  int people[] ={1,2};
  int peopleSize = 2;
  int limit = 3;

  ret = numRescueBoats(people, peopleSize, limit);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [numRescueBoats] L=118 :l=0 r=1
   [numRescueBoats] L=126 :l=1 r=2 count=0
   [numRescueBoats] L=131 :l=2 r=1 count=1
   [test] L=143 :Output = 1
**/
