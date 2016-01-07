*
* Aim : Implement itoa & atoi 
* Author : Atul Ramesh Raut
* Date   : Jan 06, 2016 11:15PM
*
***/
#include <stdio.h>

int myatoi (const char *string);
int _yatoi (const char *string);

int main () {
	printf ("\n Li = %d \n", at_itoa(1998));
	printf ("\n Ai = %d \n", _yatoi("1998"));
}


/* String to Integer */
int myatoi (const char *string) {
	int i;
	i = 0;
	while (*string) {
		i = (i<<3)+(i<<1)+(*string-'0');
		string++;
	}
	return i;
}

int _yatoi (const char *string) {
	int res = 0;
	for (int i=0; string[i] != '\0'; i++) {
	 //   res = (res << 3) + (res << 1) + (string[i] - '0'); // This also works perfectly
	    res = (res * 10) + (string[i] - '0');
	}
	return res;
}

/* itoa:  convert intger n to characters in string s {is == +} */
 void at_itoa(int n, char s[])
 {
     int i, sign;
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
	 s[i++] = n % 10 + '0';   /* ASCII-0 = 48-get next digit, 55-7 */
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
