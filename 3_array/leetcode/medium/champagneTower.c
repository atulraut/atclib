/***
    https://leetcode.com/problems/champagne-tower
    Champagne Tower

    We stack glasses in a pyramid, where the first row has 1 glass, t
    he second row has 2 glasses, and so on until the 100th row.
    Each glass holds one cup of champagne.

    Then, some champagne is poured into the first glass at the top.
    When the topmost glass is full, any excess liquid poured will
    fall equally to the glass immediately to the left and right of it.
    When those glasses become full, any excess champagne will fall
    equally to the left and right of those glasses, and so on.
    (A glass at the bottom row has its excess champagne fall on the floor.)

    For example, after one cup of champagne is poured, the top most
    glass is full.  After two cups of champagne are poured, the two glasses
    on the second row are half full.  After three cups of champagne are poured,
    those two cups become full - there are 3 full glasses total now.  After
    four cups of champagne are poured, the third row has the middle glass
    half full, and the two outside glasses are a quarter full, as pictured below.

    Now after pouring some non-negative integer cups of champagne, return how
    full the jth glass in the ith row is (both i and j are 0-indexed.)

    Input: poured = 1, query_row = 1, query_glass = 1
    Output: 0.00000
    Explanation: We poured 1 cup of champange to the top glass of the tower
    (which is indexed as (0, 0)). There will be no excess liquid so all the
    glasses under the top glass will remain empty.

    Input: poured = 2, query_row = 1, query_glass = 1
    Output: 0.50000
    Explanation: We poured 2 cups of champange to the top glass of the tower
    (which is indexed as (0, 0)). There is one cup of excess liquid. The glass
    indexed as (1, 0) and the glass indexed as (1, 1) will share the excess
    liquid equally, and each will get half cup of champange.

    Input: poured = 100000009, query_row = 33, query_glass = 17
    Output: 1.00000

    Constraints:
    0 <= poured <= 109
    0 <= query_glass <= query_row < 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Mar  3 17:20:40 PST 2022
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


#define MAX_SIZE 10000
double tower[102][102];

double champagneTower(int poured, int query_row, int query_glass) {
  memset(tower, 0, sizeof(tower));
  tower[0][0] = poured;
  for (int i = 0; i <= query_row; i++) {
    for (int j = 0; j <= i; j++) {
      if(tower[i][j] > 1.0) {
	tower[i + 1][j] += (tower[i][j] - 1.0) / 2.0;
	tower[i + 1][j + 1] += (tower[i][j] - 1.0) / 2.0;
      }
    }
  }
  return min(1.0, tower[query_row][query_glass]);
}

void test() {
  double ret = 0;
  int poured = 2;
  int query_row = 1;
  int query_glass = 1;

  ret = champagneTower(poured, query_row, query_glass);
  debug("Output = %f", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=103 :Output = 0.500000
**/

/**
   Intuition:

   Instead of keeping track of how much champagne should end up in a glass,
   keep track of the total amount of champagne that flows through a glass.
   For example, if poured = 10 cups are poured at the top, then the total
   flow-through of the top glass is 10; the total flow-through of each
   glass in the second row is 4.5, and so on.

   Algorithm:

   In general, if a glass has flow-through X, then Q = (X - 1.0) / 2.0 quantity
   of champagne will equally flow left and right. We can simulate the entire
   pour for 100 rows of glasses. A glass at (r, c) will have excess champagne
   flow towards (r+1, c) and (r+1, c+1).
**/
