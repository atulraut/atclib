/***
	FixMe - AI - Atul
*//
#include <stdio.h>
#include "../../../at_lib.h"

int power(int x, int y) {
  int ret = 0;

  if(y == 0)
    return 1;

  ret = x * power(x, y-1);
  return ret;
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

void test (int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
  int** result = (int**)malloc(len*sizeof(int*));

  (*returnColumnSizes) = (int*)calloc(len,sizeof(int));

  for(i=0; i<len; i++) {
    result[i] = (int*)malloc(numsSize*sizeof(int));
  }

  for (int i = power(2, n); i < power(2, n + 1); ++i) {
      // generate bitmask, from 0..00 to 1..11

    char *str = at_itoa(i, str);
    //      String bitmask = Integer.toBinaryString(i).substring(1);

      // append subset corresponding to that bitmask
      //List<Integer> curr = new ArrayList();
    /*x
      for (int j = 0; j < n; ++j) {
        if (bitmask.charAt(j) == '1') curr.add(nums[j]);
      }
      output.add(curr);
    }
    return output;
  }
*/

}

  int main () {

}
