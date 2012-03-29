/// Programs to counts blanks, tabs and newlines.

#include <stdio.h>

int main () {
  int c, nb, nt, nl;
  FILE *fp = NULL;
  nb = 0; //number of blanks
  nt = 0; //number of tabs
  nl = 0; //number of lines 
  fp = fopen("pr1.c", "r");
  if (fp == NULL) {
    puts ("cannot open file");
    exit (0);
  }
  while ((c = getc(fp)) != EOF ) {
    if (c == ' ')
      ++nb;
    if (c == '\t')
      ++nt;
    if (c == '\n')
      ++nl;
  } 
  printf ("\nBlancks =%d, Tabs = %d, Lines = %d\n", nb, nt, nl);
  fclose (fp);
  return 0;
}
