/*
* Aim    : Write a func for Acromatic string.
*        : I/P : "Goverment of India" O/P : "GoI";
* Author : Atul Ramesh Raut
* Date   : March 30, 2012 08:47PM
* End    : April 02, 2012 02.30PM
***/

#include <stdio.h>
#include <stdlib.h>

void strAcromatic (char *, int);
void org_strAcromatic (char *, int);

int main () {
  char acr_str[30] = "Goverment of India";
  char *acr = acr_str;
  int acr_len = 0;
  int flag= 0;

  while (*acr != '\0') {
    while (*acr != ' ') {
	    flag++;
	    acr++;
	    if (*acr == '\0')
		    break;
    }
    if (flag > 0)
	    acr_len++;
    else
	    flag = 0;
      acr++;
  }
  acr_len++;
  printf ("\nAT :: acr_len = %d\n", acr_len);
//  strAcromatic (acr_str, acr_len);
  org_strAcromatic (acr_str, acr_len);
}

void strAcromatic (char *s, int str_len) {
  char *t;

  while (*s != '\0') {
    *t = *s;
    printf ("\n t = %s t = %p\n", t, t);
    while (*s != ' ') { // Moved til end of space
	    s++;
	    if (*s == '\0')
		    break;
    }  // 2nd while end
      s++;
      t++;
  } // 1st while
  *t = '\0';
  while (str_len > 1) {
	  t--;
	  str_len--;
  }
  printf ("\n O/P without Malloc = %s !!!\n", t);
}

void org_strAcromatic (char *s, int str_len) {
  char *t;
  int i;

  t = (char*)malloc(sizeof (str_len));

  while (*s != '\0') {
	  i++;
	  *t = *s;
    printf ("\n AT :: i[%d], t = %s t = %p, s=%s\n", i, t, t, s);
    while (*s != ' ') {
	    s++;
	    if (*s == '\0')
		    break;
    }
      s++;
      t++;
  }
  *t = '\0';
  while (str_len > 1) {
	  t--;
	  str_len--;
  }
  printf ("\n With Malloc : new t =%s, t=%p\n", t, t);
 }
