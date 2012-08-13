/*
* Array of Pointer  : char *lineptr [MAXLINE]
* Point to an Array : char (*lineptr) [MAXLINE]
* Aim : Sort Input line
* Logic :
*         read all the lines of input
*         sort them
*         print them in order
* ASCII Code for String :
* a] A-Z ===> 65-91
* b] a-z ===> 97-123
***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 1000 /* lines to be sorted */

char *lineptr [MAXLINES]; /*pointers to next line*/

int readlines (char *lineptr[], int nlines, FILE *fr);
void writelines (char *lineptr[], int nlines);
void qsort_n (char *lineptr[], int left, int right);
int getLine (char line[], int max, FILE *fr);

/* sort input lines*/
int main () {

  char c;
  char line [MAXLINES];
  int nlines; /* number of input lines read*/
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

  if ( (nlines = readlines (lineptr, MAXLINES, fr)) >= 0) {
    qsort_n (lineptr, 0, nlines-1);
    writelines (lineptr, nlines);
    return 0;
  } else {
    printf ("\nerror: input line too big to handled.\n");
    return 1;
  }

   // close file
  fclose (fr);
  fclose (fw);
  return 0;
}

/*
 * readlines : read input lines.
 * collect & save the characters
 * of each line, & build an array of pointers
 * to the lines.
*/
int readlines (char *lineptr[], int nlines, FILE *fr) {
  int iLine; nlines;
  char *p, line[MAXLINES];

  nlines = 0; // count no. of element in array
  while ( iLine = getLine (line, MAXLINES, fr) > 0 ) {
    if (iLine >= MAXLINES || (p = (char*)malloc (strlen(line+1))) == NULL) {
      printf ("\nReturning\n");
      return -1;
    }
    else {
      if (p == NULL)
	printf ("\n Returning");
      //line[iLine -1] = '\0'; // delete newline
      strcpy (p, line);
      lineptr[nlines++] = p;
      //printf ("\n ATUL: lineptr = %s, p=%s, line=%s\n", lineptr[nlines-1], p, line);
    } // else
  }
  return nlines;
}

/*
 * getLine : get line into s, return length
*/
int getLine (char s[], int lim, FILE *fr) {
  int c, i;
  i = 0 ;
  while (--lim>0 && (c=getc(fr)) != EOF && c!= '\n' ) {
    s[i] = c;
    i++;
  }
  if (c == '\n') {
    s[i] = '\0';
    i++;
  }
  return i;
}

void qsort_n (char *lineptr[], int left, int right) {

  printf ("\nATUL: lineptr = %c lef=%d, right=%d\n", lineptr[0][0], left, right);

}

void writelines (char *lineptr[], int nlines) {

}


