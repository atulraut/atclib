//Write a program that prints its input one word per line.

#include <stdio.h>

#define IN 1   //Inside a word
#define OUT 0  //Outside a word

int main () {
  char c, state;
  int i;
  FILE *fr = NULL;
  FILE *fw = NULL;
  i = 0;
  state = OUT;
  fr = fopen("fr.c", "r");
  fw = fopen("fw.c", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\nCannot Open File\n");
    exit (0);
  }
  while ((c = getc(fr)) != EOF ) {
    if (c == ' ' || c== '\t' || c == '\n') {
      if (IN == state) {  // Finish the word.
	  putc('\n', fw);
	  state = OUT;
      } 
    } else if (OUT == state) {
	state = IN;  // Begining of word
	putc(c, fw);
	} else {        // Inside a word
	putc (c, fw);
      }
   } // While Loop End..
  // Close the files.
  fclose (fr);
  fclose (fw);
  return 0;
}
