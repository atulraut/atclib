#include <stdio.h>

int main () {
  float value [10] = {2, 4, 5, 3, 3, 2, 10, 8, 6, 6};
  int i, low, high;
  int group [3] = {0,0,0};
  
  for (i=0; i<10; i++) {
    ++group [ (int) (value[i]) / 1];
  }

  printf ("\nGROUP    FREQUENCY\n");
  for (i=0; i<10; i++) {
    printf ("%2d    %d\n", i+1, group[i]);
  }
}
