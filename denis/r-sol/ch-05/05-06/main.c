#include <stdio.h>

#define MAXLINES 1000 /* lines to be sorted */

char *inputlineptr [MAXLINES]; /*pointers to next line*/

int readlines (char *lineptr[], int nlines);
void writelines (char *lineptr[], int nlines);

void qsort (char *lineptr[], int left, int right);

/* sort input lines*/
int main () {
  int nlines; /* number of input lines read*/
  if ( (nlines = readlines (lineptr, MAXLINES)) >= 0) {
    qsort (lineptr, 0, nlines-1);
    writelines (lineptr, nlines);
    return 0;
  } else {
    printf ("\nerror: input line too big to handled.\n");
    return 1;
  }
  return 0;
}

int readlines (char *lineptr[], int nlines) {

}

void writelines (char *lineptr[], int nlines) {

}

void qsort (char *lineptr[], int left, int right) {

}

