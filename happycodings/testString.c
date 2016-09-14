#include <stdio.h>
char* atReverse (char s[]);

int main () {
  char r[4] = "Atul";
  printf ("\nAT r = %s\n", r);
  char *p;
  p = NULL;
  p = atReverse (r);
  printf ("\n Reverser = %s", p); 
}

/* atReverse : that reverses the charcater string s */
char* atReverse (char s[]) {
  int i, j;
  char *copy = s;
  i = 0; j = 0;
  while (s[i] != '\0') 
    i++;
  i--;
  while (i >= 0) {
    printf ("\ni=%d, j=%d, copy=%s, s=%s", i, j, copy, s);
    copy [j] = s [i];
    j++;
    i--;
  }
  copy[j] = '\0';
  printf ("\nAT>>>>>>>>>>>> New Copy = %s, J=%d", copy, j);
  return copy;
}

void reverseString(char s[]) {
    int length = strlen(s) ;
    int c, i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
