// Character array : Program that reast set of text line and print longest. 

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* Maximux Input Line Size. */

int getLine(char [], int, FILE*);
void copy (char [], char []);

int main () {
  int len;    /* current line length*/
  int max;    /* maximux length seen so far */
  char line[MAXLINE];  /* current input line */
  char longest[MAXLINE]; /* longest line saved here. */

  FILE *fr = NULL;
  fr = fopen("raj.txt", "r");
  if (fr == NULL) {
    printf ("\nCannot Open File\n");
    exit (0);
  }

  max = 0;
  while ((len = getLine(line, MAXLINE, fr)) > 0) {
    if (len > max) {
      max = len;
      copy (longest, line);
    }
  }
  if (max > 0) /* there was a line */
    printf ("\n Longests line = %s", longest);
  
    // Close the files.
  fclose (fr);
  return 0;
}

/*getline : read a line into s, return length*/
int getLine(char s[], int lim, FILE *fr) {
  int c, i;
 
  for (i=0; i<lim-1 && (c = getc(fr)) != EOF && c!='\n'; ++i) 
    s[i] = c;
   if (c == '\n') {
    s[i] = c;
    ++i;
  } 
  s[i] = '\0';
  return i;
 }

/*copy : copy 'from' into 'to'; assume to is big enough*/
void copy (char to[], char from[]) {
  int i;
  i = 0;
  while ((to[i] = from[i]) != '\0')
    i++;
}
