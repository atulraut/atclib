#include <stdio.h>

//copy input to output 

int main () {
  FILE *fp = NULL;
  int c;
  fp = fopen("pr1.c", "r");
  if (fp == NULL) {
    puts ("cannot open file");
    exit (0);
  }
  while ((c = getc(fp)) != EOF )
    putchar (c);
  fclose (fp);
  return 0;
}
