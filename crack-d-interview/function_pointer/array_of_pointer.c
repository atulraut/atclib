/*
	21st-century-c-o-reilly-ben-klemens.pdf
	Example 66.7_Page Num - 112
	Array of Pointers
*/
#include <stdio.h>

int main () {
  char *list[] = {"Atul", "Ramesh", "Raut", NULL};
  for(char **p = list; *p != NULL; p++) {
    printf ("--> %s \t", p[0]);
  }
  printf ("\n\n");
}
