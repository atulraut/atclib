/***
    https://leetcode.com/problems/multiply-strings/
    Multiply Strings

    Given two non-negative integers num1 and num2 represented
    as strings, return the product of num1 and num2, also
    represented as a string.

    Note: You must not use any built-in BigInteger library
    or convert the inputs to integer directly.

    Input: num1 = "2", num2 = "3"
    Output: "6"

    Input: num1 = "123", num2 = "456"
    Output: "56088"

    Constraints:
    1 <= num1.length, num2.length <= 200
    num1 and num2 consist of digits only.
    Both num1 and num2 do not contain any leading zero,
    except the number 0 itself.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Nov, 6, 2021
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

char* multiply(char* num1, char* num2) {
  char* Result = "0";

  if(strcmp(num1, "0")!=0 && strcmp(num2, "0")!=0) {
    int Length = strlen(num1)+strlen(num2);
    Result = (char*)calloc(Length+1, sizeof(char));

    {
      int Index = 0;
      for(Index=0; Index<Length; Index++)
	Result[Index] = '0';
    }

    {
      int Value = 0;
      int LevelIndex1 = 0;
      int LevelIndex2 = 0;

      for(LevelIndex2=strlen(num2)-1; LevelIndex2>=0; LevelIndex2--) {
	if(num2[LevelIndex2]=='0')
	  continue;

	for(LevelIndex1=strlen(num1)-1; LevelIndex1>=0; LevelIndex1--) {
	  int Index = 0;
	  Value = (num1[LevelIndex1]-'0')*(num2[LevelIndex2]-'0');

	  for(Index=strlen(num2)-1-LevelIndex2+strlen(num1)-1-LevelIndex1; Value!=0; Index++) {
	    Value += Result[Length-1-Index]-'0';
	    Result[Length-1-Index] = (Value%10)+'0';

	    Value /= 10;
	  }
	}
      }
    }

    {
      char* pCursor = Result;
      char* pCursor2 = NULL;

      for(; *pCursor=='0'; pCursor++);
      pCursor2 = pCursor;

      for(pCursor=Result; *pCursor2!=0; pCursor++,pCursor2++)
	*pCursor = *pCursor2;
      *pCursor = *pCursor2;
    }
  }
  return Result;
}

char* multiply2(char* num1, char* num2) {
    if(*num1=='0' || *num2=='0')
        return "0";
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len = len1+len2;
    int *arr = (int*)malloc(sizeof(int)*len); //the number of digits of the result - len is the top;
    memset(arr, 0, sizeof(int)*len); //this is critical;

    for(int i=len1-1; i > -1; i--)
        for(int j=len2-1; j > -1; j--)
            arr[i+j+1] += (num1[i]-'0')*(num2[j]-'0'); //collect result of each position;

    for(int i=len-1; i > 0; i--) { //restore the carry for each position and get the final result;
        arr[i-1] += arr[i]/10;
        arr[i] %= 10;
    }

    char *s = (char*)malloc(sizeof(char)*(len+1)); //converting the digits result to string;
    int index = 0;
    int i = 0;

    if(arr[i]==0)
        i++; //in case the zero position has no carry, if it does, ignore it;
    while(i < len)
        s[index++] = arr[i++]+'0';
    s[index] = '\0';
    return s;
}

int main (int argc, char **argv) {
  char* ret;
  char num1[] = "123";
  char num2[] = "456";

  ret = multiply(num1, num2);
  //  debug("Output = %s", ret);
  return 0;
}

/**

 **/
