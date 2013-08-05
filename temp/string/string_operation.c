
/*
 * Aim : 1.Input two strings from user and perform the operations on it 
 using following library functions. Program must be menu driven.
 i. strlen
 ii. strcpy
 iii. strcat
 iv. strcmp
 v. strrev
 vi. strcmpi
 vii. strchr
 viii. strstr
 ix. strupr
 x. strlwr
 * Date : Thurday, 07/02/2013 09:23:37PM
 * File : main.c
 * Refer: http://www.tutorialspoint.com/c_standard_library/string_h.htm
 ***/

#include <stdio.h>
#include <string.h>

/*< Atul Finish >*/
size_t at_strlen(const char *);
char * at_strcpy(char *,const char *);
char * at_strncpy(char *,const char *, size_t);
char * at_strcat(char *dest, const char *src);

/*< Neet to complete >*/
size_t at_strlcpy(char *, const char *, size_t);
char * at_strcat(char *, const char *);
char * at_strncat(char *, const char *, size_t);
size_t at_strlcat(char *, const char *, size_t);
int at_strcmp(const char *,const char *);
int at_strncmp(const char *,const char *, size_t);
int at_strnicmp(const char *, const char *, size_t);
int at_strcasecmp(const char *s1, const char *s2);
int at_strncasecmp(const char *s1, const char *s2, size_t n);
char * at_strchr(const char *,int);
char * at_strnchr(const char *, size_t, int);
char * at_strrchr(const char *,int);
char *at_strim(char *);
char * at_strstr(const char *, const char *);
char * at_strnstr(const char *, const char *, size_t);
char * at_strpbrk(const char *,const char *);
char * at_strsep(char **,const char *);
size_t at_strspn(const char *,const char *);
size_t at_strcspn(const char *,const char *);

int main () {

  /*< at_strlen: >*/
  char *str = "Atul";
  char *out = NULL;
  size_t len;
  len = at_strlen(str);
  printf ("\n at_strlen = %zd\n", len);

  char src[5]   = "Raut";
  char dest[15] = " Raj ";
  /*< at_strcpy >*/
  out = at_strncpy (dest, src, 4);
  printf ("at_strncpy = %s\n", out);

  /*< at_strcat: >*/
  //out = at_strcat (dest, src); 
  ///printf ("\n at_strcat = %s\n", out);
  
  return 0;
}

size_t at_strlen(const char *_str) {
  size_t at_len = 0;
  while (*_str != '\0') {
    _str++;
    at_len++; 
  }
  printf ("\nstrlen = %zd\n", at_len);
  return at_len;
}

char * at_strncpy(char *dest, const char *src, size_t _len) {
  int i = 0;
  char c;
  printf ("[strncpy] dest->%s src->%s\n", dest, src);
  while (*dest != '\0')
    *dest++;
  do {
    c = *src++;
    *dest++ = c;
    printf (":: = %c\n", *dest);
  } while (c != '\0');
  printf ("[at_strncpy] = %s\n", dest);
  return dest;
}

char *at_strcat(char *dest, const char *src) {
  while (*dest != '\0')
    *dest++;
  do {
    *dest++ = *src++;
  } while (*src != '\0');
  printf ("[at_strcat] = %s", dest);
  return dest;
}
/*
char *at_strcat(char *dest, const char *src) {
  int i, j;
  char *out = dest;
  size_t len = strlen (dest) + strlen (src);
  dest = (char*)malloc(sizeof(len));
  for (i=0; i<strlen(src); i++) 
    *(dest+i) = *(src+i);
  for (j=0; j<strlen(out); j++, i++)
    *(dest+i) = *(out+j); 
  return dest;
}
*/
