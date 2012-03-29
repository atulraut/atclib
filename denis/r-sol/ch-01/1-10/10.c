// Programs to replace each tab by \t, each backspace by \b 
// each backslash by \\. Thsi makes tabs and backspaces visible in an unambigusous way.

#include <stdio.h>

int main () {
  int c;
  FILE *fr = NULL;
  FILE *fw = NULL;
  fr = fopen("fr.c", "r");
  fw = fopen("fw.c", "w");
   if (fr == NULL || fw == NULL) {
    printf ("\ncannot open file\n");
    exit (0);
  }
  while ((c = getc(fr)) != EOF ) {
    if (c =='\t') 
      printf ("n\ \\t \n");
    if (c == '\b')
      printf ("\n \\b \n");
    if (c == '\\')
      printf ("\n \\\\ \n");
    if (c != '\b') 
      if (c != '\t')
	if (c != '\\')
	  putc(c, fw);
  } 
  fclose (fr);
  fclose (fw);
  return 0;
}
