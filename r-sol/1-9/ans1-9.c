// Programs to replace each string of one or more blank by a single blank.

#include <stdio.h>

#define NONBLANK 'a'

int main () {
  int c, nb, lastc;
  nb = 0;
  FILE *fr = NULL;
  FILE *fw = NULL;
  lastc = NONBLANK;
  fr = fopen("fr.c", "r");
  fw = fopen("fw.c", "w");
   if (fr == NULL || fw == NULL) {
    printf ("\ncannot open file\n");
    exit (0);
  }
  while ((c = getc(fr)) != EOF ) {
    if (c !=' ') 
      putc(c, fw);
    if (c == ' ') 
       if (lastc != ' ') 
	 putc(c, fw);
    lastc = c;
  } 
  printf ("\nBlank = %d\n", nb);
  fclose (fr);
  fclose (fw);
  return 0;
}
