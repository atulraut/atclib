/*
* WAP to "fold" long input lines into two or more shorted lines after 
* the last nonblank character that occuers before the n-th column
* of input. Make sure your program does something with very long lines,
* and if there are no blanks or tabs before the specifies column.
* Excercie 1-22: (page 344 K&R)
***/

#include <stdio.h>

#define MAXCOL        10   /* Maximum column of input */
#define TABINC        08   /* Tab Increment Size */

char line [MAXCOL];        /* Input Line */

int expTab (int, FILE*);
int findBlank(int);
int newPos(int);
void printL(int, FILE*);

/* Fold long input lines into two or more shorter lines. */
int main () {
  int c, pos;
  pos = 0;                             /* Position in the line. */
 
  FILE *fr, *fw;
  fr = NULL;
  fw = NULL;
  fr = fopen ("at.txt", "r");
  fw = fopen ("bt,txt", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\nfailed to open file.");
    exit(0);
  }

  while ((c = getc(fr)) != EOF ) {
    line[pos] = c;                /* Store current character */
    if (c == '\t')
      pos = expTab (pos, fw);     /* expand tab character. */
    else if (c == '\n') {
      printL(pos, fw);           /* Print current input Line */
      pos = 0;
    } else if (++pos >= MAXCOL) {
      pos = findBlank(pos);
      printL(pos, fw);
      pos = newPos(pos);
    }
  }
  // Close File.
  fclose (fr);
  fclose (fw);

  return 0;
}

/* PrintL: print line until pos column */
void printL(int pos, FILE *fw) {
  int i;
  for (i=0; i<pos; ++i) {
    putc(line[i], fw);
  if (pos > 0)
    putc('\n', fw);
  }
}

/* expTab: expand tab into blanks */
int expTab (int pos, FILE *fw) {
  line [pos] = ' ';               /* Tab is at least one blank */
  for (++pos; pos < MAXCOL && pos%8 != 0; ++pos)
    line[pos] = ' ';
  if (pos < MAXCOL)              /* room left in current line */
    return pos;
  else {
    printL(pos, fw);
    return 0;                    /* Reset current position */
  }
}

/* findBlank: find blank's position */
int findBlank(int pos) {
  while (pos > 0 && line[pos] != ' ')
    --pos;
  if (pos == 0)                  /* no blanks in the line */
    return MAXCOL;
  else                           /* at least one blank */ 
    return pos+1;                /* position after the blank */
}

/* newPos: rearrange line with new position */
int newPos(int pos) {
  int i, j;
  if (pos <=0 || pos >= MAXCOL)			
    return 0;                    /* nothing to rearrange */
  else {
    i = 0; 
    for (j = pos; j < MAXCOL; ++j) {
      line [i] = line[j];
      ++i;
    }
    return i;                   /* new position in line */
  }
}
