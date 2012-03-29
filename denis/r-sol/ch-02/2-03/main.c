/*
* Write a function htoi(s), which converts a string of hexadecimal digits 
* (including an optional 0x or 0X) into its equivalent integer value.
* The allowable digits are 0 through 9, a through f, and A through F.
* Date : Sunday July 24, 2011, 01:37PM
***/

#include <stdio.h>

#define YES 1
#define NO  0

int htoi (char []);

int main () {

  int n;
  char s[] = "0xAF3";
  n = htoi (s);
  printf ("\n n = %d\n", n);
  
  return 0;
}

/* htoi: Converts hexadecimal string s to integer */
int htoi (char s[]) {
  int i, n, hexDigit, inHex;
  i = 0;
  if (s[i] == '0') {                     /* Skip optional 0x or 0X */
    ++i;
    if (s[i] == 'x' || s[i] == 'X')
      ++i;
  }
  
  n = 0;                                /* Integer value to be returned */
  inHex = YES;                          /* Assume valid hexadecimal digit */

  for (; inHex == YES; ++i) {           /* Assume valid Hexadecimal digit */
    if (s[i] >= '0' && s[i] <= '9')      
      hexDigit = s[i] - '0';
    else if (s[i] >= 'a' && s[i] <= 'f')
      hexDigit = s[i] - 'a' + 10;
    else if (s[i] >= 'A' && s[i] <= 'F') {
      hexDigit = s[i] - 'A' + 10;
      printf ("\n s =====> %c, i=%d, hexDigit = %d", s[i], i, hexDigit);
    }
    else 
      inHex = NO;                      /* Not a valid hexadecimal digit*/
    if (inHex == YES)
      n = 16 * n + hexDigit ;
  }
  printf ("\n hexDigit = %d", n);
  return n;
}

/*In mathematics and computer science, hexadecimal (also base 16, or hex) is a 
positional numeral system with a radix, or base, of 16. It uses sixteen distinct 
symbols, most often the symbols 0–9 to represent values zero to nine, and A, B, 
C, D, E, F (or alternatively a–f) to represent values ten to fifteen. For example, 
the hexadecimal number 2AF3 is equal, in decimal, to (2 × 16^3) + (10 × 16^2) + (15 × 16^1) + (3 × 16^0) , or 10,995.
 */
