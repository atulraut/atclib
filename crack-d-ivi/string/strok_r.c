/*
  strok_r : 
  Ref: https://code.woboq.org/userspace/glibc/string/strtok_r.c.html#__strtok_r
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *atstrtok_r (char *s, const char *delim, char **save_ptr) {
  char *end;
  if (s == NULL)
    s = *save_ptr;
  if (*s == '\0') {
    *save_ptr = s;
    return NULL;
  }
  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  if (*s == '\0') {
    *save_ptr = s;
    return NULL;
  }
  /* Find the end of the token.  */
  end = s + strcspn (s, delim);
  if (*end == '\0') {
    *save_ptr = end;
    return s;
  }
  /* Terminate the token and make *SAVE_PTR point past it.  */
  *end = '\0';
  *save_ptr = end + 1;
  return s;
}

char *atstrtok (char *s, const char *delim) {
  static char *olds;
  return atstrtok_r (s, delim, &olds);
}

int main() {
  char str[] = "Atul-R-Raut";

  // Returns first token
  char* token = atstrtok(str, "-");

  // Keep printing tokens while one of the
  // delimiters present in str[].
  while (token != NULL) {
    printf("%s\n", token);
    token = atstrtok(NULL, "-");
  }
  return 0;
} 
