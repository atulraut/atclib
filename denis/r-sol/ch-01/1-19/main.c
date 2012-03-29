
// Write a function reverse(s) that reverses the charcater
// string s. Use it to write  a program that reverses its input  a line at a time.

#include <stdio.h>

#define MAXLINE 1000

int getLine (char [], int, FILE *);
int atReverse (char []);

int  main () {
  
  int max;  /* max length seen so far*/
  char line[MAXLINE];  /* current input line */
  char longest[MAXLINE]; /* longest line save here */
  
  max = 0;  
  FILE *fr = NULL;
  FILE *fw = NULL;
  fr = fopen ("at.txt", "r");
  fw = fopen ("wt.txt", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\nFile can't open !");
    exit (0);
  }
  
  while((getLine(line, MAXLINE,  fr)) > 0) {
    if (atReverse(line) > 0) {
      fputs(line, fw);
      printf ("\nLine = %s  ", line);
    }
  }
  // close file 
  fclose (fr);
  fclose (fw);
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

/* atReverse : that reverses the charcater string s */
int atReverse (char s[]) {
  int i, j;
  char temp;
  i = 0;
  while (s[i] != '\0') /* Find the end of string   */ 
    ++i;
  --i;                 /* Back of from '\0'        */
  if (s[i] == '\n')
    --i;               /* Leave newline in place   */
  j = 0;               /* Begining of new string s */
  if (j < i) {
    temp = s[j];
    s[j] = s[i];       /* Swap the characters      */
    s[i] = temp;
    --i;
    ++j;
  }
  //s[j] = '\0';
  printf ("\nAT>>>>>>>>>>>> New Copy = %s, J=%d", s, j);
  return j;
}



