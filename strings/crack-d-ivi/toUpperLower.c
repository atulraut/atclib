/***
 * Program : routine to convert given word to Upper case or Lower
 * Date : 25th Feb 2017
 * A --> 65
 * Z --> 90
 * . --> 96
 * a --> 97
 * z --> 122
 * 65 + 32 = 97
 * { 0x20(HX) == 32 (DECIBLE) }
 * Each lowercase letter is 32 + uppercase equivalent. This means simply flipping
 * the bit at position 5 (counting from least significant bit at position 0)
 * inverts the case of a letter.
 * 0x20 == 32
 * Date : 18 Feb 2021.
 * San Diego, CA.
 * Author : Rauji (Atul) Raut
 */
#include <stdio.h>
#include <ctype.h>

/* 65-A, 97-a */
char* toUpper(char *string) {
  char *save = string;
  for (; *save !='\0'; save++) {
    if (*save > 96 && *save < 122)
      *save = *save - 32;
  }
  return string;
}

/* 65-A, 90-Z */
char* toLower(char *string) {
  char *save=string;
  for (; *save!='\0'; save++) {
    if (*save > 64 && *save < 91)
      *save = *save + 32;
  }
  return string;
}

/***
   Each lowercase letter is 32 + uppercase equivalent. This means simply flipping
   the bit at position 5 (counting from least significant bit at position 0)
   inverts the case of a letter.
   0x20 == 32
*/
/* Linux implementation */
char at_tolower(const char c) {
  return c | 0x20;
}

/***
    Routine to toggle Uppler case char to Lower case char
    & vice versa using C.
 */
char toggle_Uppler_Lower (char c) {
    c ^= 1 << 5;
    printf ("c = %c \n", c);
    return c;
}

int main() {

  int i = 0;
  char c;
  char *ret;
  char test = 'A';
  char str[] = "Tutorials Point";
  ret = toUpper (str);
  printf ("ret = %s\n", ret);
  ret = toLower (str);
  printf ("ret = %s\n", ret);
  printf (" Linux Way--> [%c] \n", at_tolower(test));
  return(0);
}

/*
  0100 0001 : 65 - A
  0010 0000 : 0x20(HX) - 32 (DECIBLE)
  ------------
  0110 0001 : 97 : OROperation -
*/
