/*
*
* Find pattern in string.
* Date : Sunday, September 11 2011 11:02 AM
* End  : Nov 27-11-2011
* By : Atul R. Raut
* Logic :
*         read all the lines of Input, at.txt
*         match the pattern
*         print then in order
***/

#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length. */

int getLine (char line[], int max, FILE *fr);
int strIndex (char souce[], char searchfor[]);

char pattern [] = "ould";    /* PATTERN TO SEARCH FOR*/

int main () {

  char c;
  char line [MAXLINE] ;
  int iLine = 0;
  int found = 0;
  FILE *fr = NULL;
  FILE *fw = NULL;
  fr = fopen ("at.txt", "r");
  fw = fopen ("wt.txt", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\n File can't open !");
    exit (0);
  }
  /*
   * Program Logic based on :
   **/
  // while (there's another line)
  //   if (the line contains the pattern)
  //        print it
  while ( iLine = getLine (line, MAXLINE, fr) > 0 ) {
    if (strIndex (line, pattern) >= 0) {
	  printf ("\n\t Found Line is = %s\n", line);
	found++;
    }
  }

  // close file
  fclose (fr);
  fclose (fw);
  return 0;
}

/* getLine : get line into s, return length */
int getLine (char s[], int lim, FILE *fr) {
  int c, i;
  i = 0;

  while (--lim>0 && (c=getc(fr)) != EOF && c !='\n') {
    //    printf ("\n c >>>>> %c\n", c);
    s[i] = c;
    i++;
  }
  if (c == '\n') {
    s[i] = '\0';
    i++;
  }
    return i;
}

/* strIndex : return Index of t in s, -1 if none */
int strIndex (char source[], char searchFor[]) {
  int i, j, k, found;
  found = -1;

  for (i=0; source[i] != '\0'; i++) {
    for (k=0, j=i; searchFor[k] != '\0' && source[j] == searchFor[k]; j++, k++)
      ;
    if (k >=0 && searchFor[k] == '\0')
      return i;
  } // 1st while end
  return found;
}


