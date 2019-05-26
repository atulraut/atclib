#include <stdio.h>
#include <string.h>

void rotate(int matrix[][4], int n) {
  for (int layer = 0; layer < n / 2; ++layer) {
    int first = layer;
    int last = n - 1 - layer;
    for(int i = first; i < last; ++i) {
      int offset = i - first;
      int top = matrix[first][i]; // save top
      // left -> top
      matrix[first][i] = matrix[last-offset][first];
      // bottom -> left
      matrix[last-offset][first] = matrix[last][last - offset];
      // right -> bottom
      matrix[last][last - offset] = matrix[i][last];
    }
  }
}

int main() {
  int i, j;
  int sz = 4;
  int arr[][4] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,16},
  };
  for(i=0; i<sz; i++) {
    for(j=0; j<sz; j++) {
      printf("--> %d \t", arr[i][j]);
    }
    printf("\n");
  }
  printf ("Start Rotate \n");

  rotate(arr, sz);
  for(i=0; i<sz; i++) {
    for(j=0; j<sz; j++) {
      printf("--> %d \t", arr[i][j]);
    }
    printf("\n");
  }
  printf ("End\n");
}
