/*
  cisco ask : pointer to array remove duplicate elements.
e.g.
0xf1 1
0xf2 3
0xf3 1
0xf4 2
0xf5 5
*/
#include <stdio.h>

int removeEle (int **arr, int sz) {
  int i, j;
  for (i=0; i<sz; i++) {
    for(j=0; j<sz; j++) {
      if (*arr[i] == *arr[j])
	continue;
      else
	*arr[i] = *arr[i];
    }
  }
  return 0;
}

int main() {
  int i;
  int a = 10, b = 20, c = 30, d = 10, e = 50;
  int *arr[] = {&a, &b, &c, &d, &e};
  for (i=0; i<5; i++) {
    printf ("--> Ans = %d \n", *arr[i]);
  }
  printf("Hello World = %d", removeEle(arr, 5));
  for (i=0; i<5; i++) {
    printf ("--> Ans = %d \n", *arr[i]);
  }
  return 0;
}
