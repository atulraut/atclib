//Write a program that count the number of occuerrenes of each digit, of white space characters
// (blankm tab, newline), and of all other character.

#include <stdio.h>

/*count digits, white space, and others. */

int main () {
  char c, i, j;
  int digCount [10];
  int nWhite, nOther;
  nOther = 0;
  i = 0;
  j = 0;
  FILE *fr = NULL;
  FILE *fw = NULL;
  fr = fopen("fr.c", "r");
  fw = fopen("fw.c", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\nCannot Open File\n");
    exit (0);
  }
  // Initialise array
  for (i=0; i<10; i++)
    digCount[i] = 0;
  while ((c = getc(fr)) != EOF ) {
    if (c >= '0' && c <= '9') {
      digCount[i] = c; // Atul's way to have sort digit's 
      //++digCount[c-'0']; // Ritchi's way this calculate numeric value of digit
      i++;
    }
    if (c == ' ' || c== '\t' || c == '\n') {
      ++nOther;
       putc('\n', fw);
    } else   {      // Inside a word
	putc (c, fw);
	++nOther;
    }
  } // While Loop End..
    for (j=0; j<=10; j++)
      printf ("\ndigCount = %d, nOther = %d", digCount[j], nOther);
  // Close the files.
  fclose (fr);
  fclose (fw);
  return 0;
}
