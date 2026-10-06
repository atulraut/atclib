/***
    https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/
    1996. The Number of Weak Characters in the Game

    You are playing a game that contains multiple characters,
    and each of the characters has two main properties: attack and
    defense. You are given a 2D integer array properties where
    properties[i] = [attacki, defensei] represents the properties
    of the ith character in the game.

    A character is said to be weak if any other character has both
    attack and defense levels strictly greater than this character's
    attack and defense levels. More formally, a character i is said
    to be weak if there exists another character j
    where attack[j] > attack[i] and defense[j] > defense[i].

    Return the number of weak characters.

    Input: properties = [[5,5],[6,3],[3,6]]
    Output: 0
    Explanation: No character has strictly greater attack and defense than the other.

    Input: properties = [[2,2],[3,3]]
    Output: 1
    Explanation: The first character is weak because the second
    character has a strictly greater attack and defense.

    Input: properties = [[1,5],[10,4],[4,3]]
    Output: 1
    Explanation: The third character is weak because the second
    character has a strictly greater attack and defense.

    Constraints:
    2 <= properties.length <= 105
    properties[i].length == 2
    1 <= attacki, defensei <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Sep 10 11:55:01 PM PDT 2022
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

int cmp(const void *a, const void *b) {
  return (*(int **)a)[0] == (*(int **)b)[0] ? (*(int **)a)[1] < (*(int **)b)[1] : (*(int **)a)[0] > (*(int **)b)[0];
}

int numberOfWeakCharacters(int** properties, int propertiesSize, int* propertiesColSize) {
  int result = 0, max = INT_MIN;
  qsort(properties, propertiesSize, sizeof(int **), cmp);
  for(int i = propertiesSize - 1; i >= 0; i--) {
    if(properties[i][1] < max)
      result++;
    max = max > properties[i][1] ? max : properties[i][1];
  }
  return result;
}

int numberOfWeakCharacters2(int** properties, int propertiesSize, int* propertiesColSize) {
  int row = propertiesSize;
  int col = *propertiesColSize;
  int cnt = 0;
  int flag = 0;
  printf ("row = %d col = %d\n", row, col);

  for (int i=0; i<row; ++i) {
    for (int j=0; j<col-1; ++j) {
      if (properties[i][j] > properties[i][j+1]) {
          printf ("i=%d j=%d properties[i][j]=%d \n", i, j, properties[i][j]);
          ++flag;
      }
    }
    if (flag == 2) {
      ++cnt;
    }
    flag = 0;
  }
  return cnt;
}


int** create_matrix(int rows, int cols) {
  int** max = (int**)malloc(sizeof(int) * rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)malloc(sizeof(int *) * cols);
  }
  return max;
}

void test() {
  int ret = 0;
  int** properties = create_matrix(3, 2);
  int propertiesSize = 3;
  int propertiesColSize = 2;

  *(*(properties + 0) + 0) = 1;
  *(*(properties + 0) + 1) = 5;

  *(*(properties + 1) + 0) = 10;
  *(*(properties + 1) + 1) = 4;

  *(*(properties + 2) + 0) = 4;
  *(*(properties + 2) + 1) = 3;

  ret = numberOfWeakCharacters(properties, propertiesSize, &propertiesColSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=132 :Output = 1
**/
