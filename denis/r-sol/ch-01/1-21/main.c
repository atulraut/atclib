/*
* Prgram : Exercise 1-21: (page 34 K&R) 
* WAP entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing.
* Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach
* a tab stop, which should be given preference ?
* Date : July 22 2011, 12:13AM
* Atul R. Raut
***/

#include <stdio.h>

#define TABINC 8         /* Tab increment size */

/* Replace Strings of blanks with tabs and blanks */
int main (){

  int c, nb, nt, pos;
  FILE *fr, *fw;
  fr = NULL;
  fw = NULL;
  nb = 0;                /* # of blanks necessary */
  nt = 0;                /* # of tabs necessary   */

  fr = fopen ("at.txt", "r");
  fw = fopen ("wr.txt", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\nFile Open Operation failed.");
    exit (0);
  }
  
  for (pos = 1; (c = getc (fr)) != EOF; ++pos) 
    if (c == " ") {
      if (pos % TABINC != 0)
	++nb;                  /* increment # of blanks */
      else {
	nb = 0;                /* reset # of blanks  */
	++nt;                  /* one more tab */
      }
    } else {
      for (; nt > 0; --nt)
	putc ('\t', fw);           /* output tab(s) */
      if (c == '\t')           /* forget the blank(s) */
	nb = 0;
      else
	for (; nb > 0; --nb)
	  putc(' ', fw);
      putc (c, fw);
      if (c == '\n')
	pos = 0;
      else if (c == '\t')
	pos = pos + (TABINC - (pos -1) % TABINC) -1;
    }   
  
  //File close
  fclose (fr);
  fclose (fw);
  return 0;
}


