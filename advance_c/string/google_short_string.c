/*
 Input  : Google Short String : AnyString "internationalisation" 
 Output : 'i18n' 
 Date   : 19-12-2015 <- New Car
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define INT_DIGITS 19 /* enought for 64 bit integer */
char* getUniqueWord (char *astr);
void at_itoa(int n, char s[]);
void reverse(char s[]);
char *liw_strncat(char *s, const char *ct, size_t n);
char *at_strcat(char *dest, const char *src);
char get_word_pos (char *src, int pos);

int main () {
  char *name = "internationlisation";
  name =  getUniqueWord (name);
  printf ("\n[main]: short name = %s\n", name);
  return 0;
}

/*
 Input  : AnyString "internationalisation"
 Output : 'i18n' 
*/
char* getUniqueWord (char *astr) {
  char first[INT_DIGITS + 2] = {'\0'};
  char mid[INT_DIGITS + 2] = {'\0'};
  char last[2];
  int len = strlen (astr);
  if (len <=0 || len <=2)
    return 0;
  *(first+0) = get_word_pos (astr, 0);
  *(first+1) = '\0';
  last[0]  = get_word_pos (astr, len-1);
  *(last+1) = '\0';
  at_itoa((strlen(astr) - 2), mid);  // convert string to number
  printf("mid 0 = %s\n", mid);
  at_strcat (first, mid);
  at_strcat (first, last);
  return first;
}

char *apple_itoa(int i) {
  /* Room for INT_DIGITS digits, - and '\0' */
  static char buf[INT_DIGITS + 2];
  char *p = buf + INT_DIGITS + 1;/* points to terminating '\0' */
  printf ("atul- char %ld addr=%p i=%d buf=%p\n", sizeof(p), p, i, buf);
  if (i >= 0) {
    do {
      *(--p) = '0' + (i % 10);
      i /= 10;
    } while (i != 0);
    return p;
  } 
  else {/* i < 0 */
    do {
      *--p = '0' - (i % 10);
      i /= 10;
    } while (i != 0);
    *--p = '-';
  }
  return p;
}

/* itoa:  convert n to characters in s */
 void at_itoa(int n, char s[])
 {
     int i, sign;
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
	     s[i++] = n % 10 + '0';   /* ASCII-0 = 48-get next digit, 55-7 */
	 printf ("s = %c \n", s[i-1]);
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }

/* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c; 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

char *liw_strncat(char *s, const char *ct, size_t n) {
	char *p;	
	p = s;
	while (*p != '\0')
		++p;
	for (; n > 0 && *ct != '\0'; --n)
		*p++ = *ct++;
	*p = '\0';
	return s;
}

char *at_strcat(char *dest, const char *src) {
  printf ("[at_strcat] = %s src = %s \n", dest, src);  
  while (*dest != '\0')
    ++dest;
  do {
    *dest++ = *src++;
  } while (*src != '\0');
  return dest;
}

char get_word_pos (char *src, int pos) {
  int i =0;
  int len = strlen (src);
  if (len <=0 || len <2)
	  return;
  for (i=0; i<len; i++) {
	  if (i == pos) {
	     return *(src+pos);	    
	  }
  }
  return *src;
}
