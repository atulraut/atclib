/*
* Find pattern in string.
* Data : Sunday, September 11 2011 11:02 AM
* By : Atul R. Raut
***/
#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length. */

int getLine (char line[], int max, FILE *fr);
int strIndex (char souce[], char searchfor[]);

char pattern [] = "ould";    /* pattern to search for*/

int main () {

  char c;
  char line [MAXLINE] = ;
  int found = 0;
  FILE *fr = NULL;
  FILE *fw = NULL;
  fr = fopen ("at.txt", "r");
  fw = fopen ("wt.txt", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\nFile can't open !");
    exit (0);
  }

  // while (there's another line)
  //   if (the line contains the pattern)
  //        print it
   
  while ( getLine (line, MAXLINE, fr) > 0 ) {
    if (strIndex (line, pattern) >= 0)
      printf ("%s", line);
    found++;
  }

   // close file 
  fclose (fr);
  fclose (fw);
  return 0;
}

/* getLine : get line into s, return length */
int getLine (char s[], int lim, FILE *fr) {
  int i, j, k;
  while ()
}

/* strIndex : return Index of t in s, -1 if none */
int strIndex (char souce[], char searchfor[]) {

}


