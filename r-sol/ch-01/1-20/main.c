/*
* Aim : WAP detab that replaces tabs in the input with the proper number of 
* blanks to space to the next tab stop. Assume a fixed set of tab stop,
* say every n columns. Should n be a variable or a symoboic parameter ?
* Date : Thursday, July 21-07-2011. 8.05AM
* Atul Ramesh Raut 
***/

/**/
#include <stdio.h>

#define TABINC 8 /* tab increament size */

/* replace tab with the proper number of blanks */

int main () {
  int c, nb, pos;
  FILE *fr, *fw;
  
  nb = 0;             /* number of blanks necessary to reach the next tab stop*/
  pos = 1;            /* position of character in line*/
  fr = NULL;
  fw = NULL;
   
  // Open file
  fr = fopen("at.txt", "r");
  fw = fopen("wt.txt", "w");

  if (fr == NULL || fw == NULL) {
    printf ("\n Failed t open the file");
    exit (0);
  }
    
  while ((c = getc(fr)) != EOF) {
    if (c == '\t') {
      printf ("\npos = %d", pos);
      nb = TABINC - (pos - 1) % TABINC;
      printf ("\n nb = %d", nb );
      while (nb > 0) {
	c = " ";
	putc(c, fw);
	++pos;
	--nb;
      }
    } else if (c == '\n') {
      putc(c, fw);
      pos = 1;
    } else {
      putc(c, fw);
      ++pos;
    }
  }
  
  // Close file
  fclose (fr);
  fclose (fw);

  return 0;
}
