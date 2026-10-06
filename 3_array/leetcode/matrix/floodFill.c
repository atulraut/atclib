/***
    https://leetcode.com/problems/flood-fill/
    Flood Fill
    An image is represented by an m x n integer grid image
    where image[i][j] represents the pixel value of the image.

    You are also given three integers sr, sc, and newColor.
    You should perform a flood fill on the image starting
    from the pixel image[sr][sc].

    To perform a flood fill, consider the starting pixel,
    plus any pixels connected 4-directionally to the starting
    pixel of the same color as the starting pixel, plus any
    pixels connected 4-directionally to those pixels (also
    with the same color), and so on. Replace the color of all
    of the aforementioned pixels with newColor.

    Return the modified image after performing the flood fill.

    Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, newColor = 2
    Output: [[2,2,2],[2,2,0],[2,0,1]]
    Explanation: From the center of the image with position (
    sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected
    by a path of the same color as the starting pixel (i.e., the
    blue pixels) are colored with the new color.
    Note the bottom corner is not colored 2, because it is not 4
    -directionally connected to the starting pixel.

    Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, newColor = 2
    Output: [[2,2,2],[2,2,2]]

    Constraints:
    m == image.length
    n == image[i].length
    1 <= m, n <= 50
    0 <= image[i][j], newColor < 216
    0 <= sr < m
    0 <= sc < n

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 26 Oct 2021
    Fair Oaks, CA.
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
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*--------------------------------- Micro Ends ------------------------------------*/

void paint(int** image, int imageSize, int* imageColSize,
	   int sr, int sc, int newColor, int oldColor) {
  if (sr < 0 || sr >= imageSize)
    return;
  if (sc < 0 || sc >= imageColSize[0])
    return;

  debug ("sr=%d, sc=%d, newColor=%d, image[sr][sc]=%d oldColor=%d", sr, sc, newColor, image[sr][sc], oldColor);
  if (image[sr][sc] == oldColor) {
    image[sr][sc] = newColor;
    paint(image, imageSize, imageColSize, sr - 1, sc, newColor, oldColor);
    paint(image, imageSize, imageColSize, sr + 1, sc, newColor, oldColor);
    paint(image, imageSize, imageColSize, sr, sc - 1, newColor, oldColor);
    paint(image, imageSize, imageColSize, sr, sc + 1, newColor, oldColor);
  }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array
 * must be malloced, assume caller calls free().
 */
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes) {
  int i;

  for (int j=0; j<3; j++)
    for (int i=0; i<3; ++i)
      debug("Input = %d", image[j][i]);

  *returnSize = imageSize;
  *returnColumnSizes = malloc(sizeof(int) * imageSize);

  for (i = 0; i < imageSize; i++)
    (*returnColumnSizes)[i] = imageColSize[i];

  if (newColor != image[sr][sc])
    paint(image, imageSize, imageColSize,
	  sr, sc, newColor, image[sr][sc]);

  return image;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)malloc(sizeof(int) * rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)malloc(sizeof(int *) * cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int** ret;
  int imageSize = 3;
  int imageColSize = 3;
  int** image = create_matrix(imageSize, imageColSize);
  int sr = 1, sc = 1, newColor = 2;

  int returnSize;
  int* returnColumnSizes;

  *(*(image + 0) + 0) = 1;
  *(*(image + 0) + 1) = 1;
  *(*(image + 0) + 2) = 1;
  *(*(image + 1) + 0) = 1;
  *(*(image + 1) + 1) = 1;
  *(*(image + 1) + 2) = 0;
  *(*(image + 2) + 0) = 1;
  *(*(image + 2) + 1) = 0;
  *(*(image + 2) + 2) = 1;

  ret = floodFill(image, imageSize, &imageColSize, sr, sc, newColor, &returnSize, &returnColumnSizes);

  for (int j=0; j<returnSize; j++)
    for (int i=0; i<*returnColumnSizes; ++i) {
      debug("Output = %d", ret[j][i]);
    }
  return 0;
}

/**
   => ./a.out
   [floodFill] L=99 :Input = 1
   [floodFill] L=99 :Input = 1
   [floodFill] L=99 :Input = 1
   [floodFill] L=99 :Input = 1
   [floodFill] L=99 :Input = 1
   [floodFill] L=99 :Input = 0
   [floodFill] L=99 :Input = 1
   [floodFill] L=99 :Input = 0
   [floodFill] L=99 :Input = 1
   [paint] L=79 :sr=1, sc=1, newColor=2, image[sr][sc]=1 oldColor=1
   [paint] L=79 :sr=0, sc=1, newColor=2, image[sr][sc]=1 oldColor=1
   [paint] L=79 :sr=1, sc=1, newColor=2, image[sr][sc]=2 oldColor=1
   [paint] L=79 :sr=0, sc=0, newColor=2, image[sr][sc]=1 oldColor=1
   [paint] L=79 :sr=1, sc=0, newColor=2, image[sr][sc]=1 oldColor=1
   [paint] L=79 :sr=0, sc=0, newColor=2, image[sr][sc]=2 oldColor=1
   [paint] L=79 :sr=2, sc=0, newColor=2, image[sr][sc]=1 oldColor=1
   [paint] L=79 :sr=1, sc=0, newColor=2, image[sr][sc]=2 oldColor=1
   [paint] L=79 :sr=2, sc=1, newColor=2, image[sr][sc]=0 oldColor=1
   [paint] L=79 :sr=1, sc=1, newColor=2, image[sr][sc]=2 oldColor=1
   [paint] L=79 :sr=0, sc=1, newColor=2, image[sr][sc]=2 oldColor=1
   [paint] L=79 :sr=0, sc=2, newColor=2, image[sr][sc]=1 oldColor=1
   [paint] L=79 :sr=1, sc=2, newColor=2, image[sr][sc]=0 oldColor=1
   [paint] L=79 :sr=0, sc=1, newColor=2, image[sr][sc]=2 oldColor=1
   [paint] L=79 :sr=2, sc=1, newColor=2, image[sr][sc]=0 oldColor=1
   [paint] L=79 :sr=1, sc=0, newColor=2, image[sr][sc]=2 oldColor=1
   [paint] L=79 :sr=1, sc=2, newColor=2, image[sr][sc]=0 oldColor=1
   [main] L=146 :Output = 2
   [main] L=146 :Output = 2
   [main] L=146 :Output = 2
   [main] L=146 :Output = 2
   [main] L=146 :Output = 2
   [main] L=146 :Output = 0
   [main] L=146 :Output = 2
   [main] L=146 :Output = 0
   [main] L=146 :Output = 1
**/
