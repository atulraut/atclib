/*
* Aim : Write a function strInex(s,t), which returns the position
*       of the rightmost occurence of t in s, or -1 if there is none.
* Date : Sunday, November 27  2011 03:49 PM
* End  : 4.23PM
* By : Atul R. Raut
* 
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
    if (found = strIndex (line, pattern) >= 0) {
      printf ("\n\t $: %s\n", line);
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

  for (i=0; source[i] != '\0'; i++) {   //Search In String
    for (k=0, j=i; searchFor[k] != '\0' && source[j] == searchFor[k]; j++, k++) //Search In Word
      ;
    if (k >=0 && searchFor[k] == '\0') {
      found = i;
      printf (" Found at = %d\n", found);
      return found;
    }
  } // 1st while end
  return found;
}


