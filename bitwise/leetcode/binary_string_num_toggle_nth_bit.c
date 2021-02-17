/***
    Given a string representing binary number toggle the nth bit. - Juniper
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../at_lib.h"

void reverseString(char* s, int sSize){
    int len = sSize/2;
    char c;

    for (int i=0; i<len; i++) {
        c = s[sSize-1-i];
        s[sSize-1-i] = s[i];
        s[i] = c;
    }

    printf("\n Reverse String --> %s \n", s);
}

/* Linux Implemention */
long atoi_linux(const char *s) {
  unsigned long ret = 0;
  unsigned long d;
  int neg = 0;

  if (*s == '-') {
    neg = 1;
    s++;
  }

  while (1) {
    d = (*s++) - '0';
    if (d > 9)
      break;
    ret *= 10;
    ret += d;
  }

  return neg ? -ret : ret;
}

void itoa_atclib (int n, char s[]) {
  printf ("\n >>>> n = %d", n);
  int i, sign;
  char k;
  if ((sign = n) < 0) { /* record sign */
    n = -n;           /* make n positive */
  }
  i = 0;
  do {               /* Generate digits in reverse order */
    // printf ("\n (n%10)      >>>>> %ds and n = %d", (n % 10) , n);
    k = n % 10 + '0';   /* get next digit */
    //printf ("\n (n%10)+ '0' >>>>> %c", k);
    s[i++] = k;
  } while ((n /= 10) > 0); /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  printf ("\n string = %s\n", s);
  reverseString (s, strlen(s));
  printf ("\n string = %s\n", s);
}

int toggle (int num, int bit) {
  debug ("org num = %d bit = %d", num, bit);
  num ^= (1 << bit-1);
  debug ("org num = %ld", num);
  return num;
}

int bin_str_toggle_nth_bit(char *str, int n) {
  /* Covert string to Number */
  long num = atoi_linux(str);
  debug ("org num = %ld", num);
  /* Togle ask Nth Bit */
  num = toggle (num, n);
  debug ("org num = %ld", num);
  /* Bring back num to string*/
  itoa_atclib(num, str);

  return 0;
}

void brute_force (char *str, int n) {
  for (int i=0; i<strlen(str); i++) {
    if (i == n) {
      if (str[i] == '1')
	str[i] = '0';
      else
	str[i] = '1';
    }
  }
}

int main () {
  int n = 2;
  char str[] = "1010";
  char str1[] = "110010001";
  int ret = 0;
  // ret = bin_str_toggle_nth_bit(str, n);
  brute_force(str, n);
  debug ("str-> %s ret = %d \n", str, ret);
  return 0;
}


/**
   => ./a.out

   >>>> n = 1010
   string = 0101
**/
