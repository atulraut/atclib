/*
	21st-century-c-o-reilly-ben-klemens.pdf
	Example 66.7_Page Num - 112
	1. Array of Pointers
	2. Pointer to an Array : https://www.geeksforgeeks.org/pointer-array-array-pointer/
*/
#include <stdio.h>

void  test_array_of_pointers() {
  int *ptr[5];
  int arr[5] = {2,3,4,5,6};
  int i;

  for(i=0; i<5; i++)
    ptr[i] = &arr[i];

  for(i=0; i<5; i++)
    printf ("--> i=%d\n", *ptr[i]);
}

void test_pointers_to_an_array() {
    int arr[] = { 3, 5, 6, 7, 9 };
    int *p = arr;
    int (*ptr)[5] = &arr;

    printf("p = %p, ptr = %p\n", p, ptr);
    printf("*p = %d, *ptr = %p\n", *p, *ptr);

    printf("sizeof(p) = %lu, sizeof(*p) = %lu\n", sizeof(p), sizeof(*p));
    printf("sizeof(ptr) = %lu, sizeof(*ptr) = %lu\n", sizeof(ptr), sizeof(*ptr));
}
/*
  o/p:
  p = 0x7ffdaba606d0, ptr = 0x7ffdaba606d0
  *p = 3, *ptr = 0x7ffdaba606d0
  sizeof(p) = 8, sizeof(*p) = 4
  sizeof(ptr) = 8, sizeof(*ptr) = 20
*/

int main () {
  char *list[] = {"Atul", "Ramesh", "Raut", NULL};
  for(char **p = list; *p != NULL; p++) {
    printf ("--> %s \t", p[0]);
  }
  printf ("\n");
  test_array_of_pointers();
  test_pointers_to_an_array();
  printf ("\n\n");
}

/***
    => ./a.out
    --> Atul 	--> Ramesh 	--> Raut
    --> i=2
    --> i=3
    --> i=4
    --> i=5
    --> i=6
    p = 0x7ffc2aa70930, ptr = 0x7ffc2aa70930
    *p = 3, *ptr = 0x7ffc2aa70930
    sizeof(p) = 8, sizeof(*p) = 4
    sizeof(ptr) = 8, sizeof(*ptr) = 20
*/
