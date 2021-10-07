/***
    https://leetcode.com/problems/word-search/
    Word Search
    Given an m x n grid of characters board and a string word, r
    eturn true if word exists in the grid.

    The word can be constructed from letters of sequentially
    adjacent cells, where adjacent cells are horizontally or
    vertically neighboring. The same letter cell may not be
    used more than once.

    Input: board = [["A","B","C","E"],["S","F","C","S"],
    ["A","D","E","E"]], word = "ABCCED"
    Output: true

    Input: board = [["A","B","C","E"],["S","F","C","S"],
    ["A","D","E","E"]], word = "SEE"
    Output: true

    Input: board = [["A","B","C","E"],["S","F","C","S"],
    ["A","D","E","E"]], word = "ABCB"
    Output: false

    Constraints:
    m == board.length
    n = board[i].length
    1 <= m, n <= 6
    1 <= word.length <= 15
    board and word consists of only lowercase and uppercase
    English letters.

    Date: 10 Oct 2021
    Fair Oaks, CA.
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

int m, n;
bool isBorder(int i, int j) {
  if (i>=0 && i<m && j>=0 && j<n) return true;
  else return false;
}

bool hashPath(char** board, int i, int j, char * word, int count, bool* visited) {
  if(word[count] == '\0')
    return true;
  if(!isBorder(i, j))
    return false;

  bool isPath = false;

  if(!visited[i*n+j] && board[i][j] == word[count]) {
    visited[i*n+j] = true;
    isPath = hashPath(board, i-1, j, word, count+1, visited)
      || hashPath(board, i+1, j, word, count+1, visited)
      || hashPath(board, i, j+1, word, count+1, visited)
      || hashPath(board, i, j-1, word, count+1, visited);

    if(!isPath)
      visited[i*n+j] = false;
  }
  return isPath;
}

bool exist(char** board, int boardSize, int* boardColSize, char * word) {
  m = boardSize; // border of row
  n = *boardColSize; // border of col

  if(m<1 || n<1 || !board || !word)
    return false;

  bool* visited = (bool*)malloc(sizeof(bool)*m*n);
  memset(visited, 0, m*n);

  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
      if(hashPath(board, i, j, word, 0, visited))
	return true;

  return false;
}

int main (int argc, char **argv) {
  int ret = 0;
  char* board[] = {
    "ABCE",
    "SFCS",
    "ADEE"
  };
  int boardSize = 3;
  int boardColSize = 4;
  char* word = "SEE";

  ret = exist(board, boardSize, &boardColSize, word);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=105 :Output = 1
**/
