/***
    https://leetcode.com/problems/robot-bounded-in-circle/
    1041. Robot Bounded In Circle

    On an infinite plane, a robot initially stands at (0, 0)
    and faces north. The robot can receive one of three instructions:

    "G": go straight 1 unit;
    "L": turn 90 degrees to the left;
    "R": turn 90 degrees to the right.
    The robot performs the instructions given in order, and
    repeats them forever.

    Return true if and only if there exists a circle in the plane
    such that the robot never leaves the circle.

    Input: instructions = "GGLLGG"
    Output: true
    Explanation: The robot moves from (0,0) to (0,2), turns
    180 degrees, and then returns to (0,0).
    When repeating these instructions, the robot remains in
    the circle of radius 2 centered at the origin.

    Input: instructions = "GG"
    Output: false
    Explanation: The robot moves north indefinitely.

    Input: instructions = "GL"
    Output: true
    Explanation: The robot moves
    from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...

    Constraints:
    1 <= instructions.length <= 100
    instructions[i] is 'G', 'L' or, 'R'.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 8 Jan 2022
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

typedef enum {
  DIR_NORTH = 0,
  DIR_WEST  = 1,
  DIR_SOUTH = 2,
  DIR_EAST  = 3,
  DIR_NUM
} Direction_t;

typedef struct {
  int x;
  int y;
} Coordinate_t;

bool isRobotBounded(char* instructions) {
  Coordinate_t step[DIR_NUM] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
  Direction_t dir = DIR_NORTH;
  Coordinate_t curr = {0, 0};

  for (int j = 0; j < strlen(instructions); j++) {
    switch (instructions[j]) {
    case 'G':
      {
	curr.x += step[dir].x;
	curr.y += step[dir].y;
	break;
      }
    case 'L':
      {
	dir = (dir + 1) % DIR_NUM;
	break;
      }
    case 'R':
      {
	dir = (dir + DIR_NUM - 1) % DIR_NUM;
	break;
      }
    }
    debug("Direction = %d, Current = %d, %d", dir, curr.x, curr.y);
  }

  return dir != DIR_NORTH || (curr.x == 0 && curr.y == 0);
}

void go_robot(int *pos, int dir) {
  if (dir == 1)
    pos[1]++;
  if (dir == 2)
    pos[0]++;
  if (dir == 3)
    pos[1]--;
  if (dir == 4)
    pos[0]--;
}

bool isRobotBounded_(char *instruction) {
  int dir;
  int pos[2] = {0,0};

  dir = 1;
  while (*instruction) {
    if (*instruction == 'L') {
      dir--;
      if (dir == 0)
	dir = 4;
    }
    if (*instruction == 'R') {
      dir++;
      if (dir == 5)
	dir = 1;
    }
    if (*instruction == 'G')
      go_robot(pos, dir);
    instruction++;
  }
  if ((pos[0] == 0 && pos[1] == 0) || dir != 1)
    return (true);
  return (false);
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int *),  cols);
  }
  return max;
}

void test() {
  int ret = 0;
  char instructions[] = "GGLLGG";
  ret = isRobotBounded(instructions);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [isRobotBounded] L=106 :Direction = 0, Current = 0, 1
   [isRobotBounded] L=106 :Direction = 0, Current = 0, 2
   [isRobotBounded] L=106 :Direction = 1, Current = 0, 2
   [isRobotBounded] L=106 :Direction = 2, Current = 0, 2
   [isRobotBounded] L=106 :Direction = 2, Current = 0, 1
   [isRobotBounded] L=106 :Direction = 2, Current = 0, 0
   [test] L=160 :Output = 1
**/
