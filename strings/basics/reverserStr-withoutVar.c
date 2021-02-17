#include <stdio.h>
#include <string.h>

void revStr (char *);

main() {
  char *ret;
  char mrr[5] = "Atul";
  char arr[5] = "RAUJ";
  //char *arr = "Atul";     // Ptr holding address of const;
  revStr (arr);
  printf ("\n....END....\n");
  printrev (mrr);
  puts ("\n\nReplace me with your code!");
}

void revStr (char *ar) {
  char *p  = ar;
  char temp;
  while (*p != '\0')
    p++;
  p--;
  while(ar < p) {
    temp = *ar;
    *ar = *p;
    *p = temp;
    ar++;
    p--;
  }
  p--;
  printf ("\np = %s\n", p);
}

void printrev (char *s) {
  if (*s != 0) {
    printrev(s+1);
    putchar (*s);
  }
}
