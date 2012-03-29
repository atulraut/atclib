// WAP to print all input lines that 
// are longer than 80 characters.

#include <stdio.h>

#define MAXLINE 1000

int getLine (char [], int, FILE *);
void copy (char [], char[]);

int main () {
  int len;  /* current line length*/
  int max;  /* max length seen so far*/
  char line[MAXLINE];  /* current input line */
  char longest[MAXLINE]; /* longest line save here */
  
  max = 0;  
  FILE *fr = NULL;
  fr = fopen ("at.txt", "r");
  if (fr == NULL) {
    printf ("\nFile can't open !");
    exit (0);
  }
  
  while((len  = getLine(line, MAXLINE,  fr)) > 0) {
    if (len > max) {
	max = len;
	copy(longest, line);
    }
  }
  if (max > 6) /* there was a line */
      printf ("\n Longest line = %s\n", longest);
  // close file 
  fclose (fr);

  return 0;
}

/* getLine : find the largest word's length. */
int getLine(char s[], int lim, FILE *fr) {
  int i,c;
 
  for (i=0; i<lim-1 && (c = getc(fr)) != EOF && c !='\n'; ++i )
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  } 
  s[i] = '\0';
   return i;
}

/*copy: copy  'from' content to 'to' */
void copy (char to[], char from[]) {
  int i;
  i = 0;
  while ( (to[i] = from[i]) != '\0' )
    i++;
} 
