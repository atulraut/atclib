/***
 * C program to print all permutations with duplicates allowed
 */

#include <stdio.h>
#include <string.h>

/* Function to swap values at two pointers */
void swap(char *x, char *y) {
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

/*** Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string.
*/
void do_permute(char *a, int l, int r) {
  int i;
  if (l == r)
    printf("%s\n", a);
  else {
    for (i = l; i <= r; i++) {
      swap((a+l), (a+i));
      do_permute(a, l+1, r);
      swap((a+l), (a+i)); //backtrack
    }
  }
}

/* Program to test above functions */
int main() {
  char str[] = "ABC";
  int n = strlen(str);
  do_permute(str, 0, n-1);
  return 0;
}
