/***

    Remove all special chars and keep only
    alphabets and numbers in the string and move all chars
    left side “Hi @12345:), Welcome to TechM !!!” ->
    “Hi12345WelcometoTechM”   Remove all special chars and keep
    only alphabets and numbers in the string and move all chars
    left side “Hi @12345:), Welcome to TechM !!!” -> “Hi12345WelcometoTechM”

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 9/8/2026
    Folsom, CA.
    Tech Mahindra
*/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)


#include <stdio.h>
#include <string.h>
#include <ctype.h>

// “Hi @12345:), Welcome to TechM !!!”
// “Hi12345WelcometoTechM”

void remove_char(char *str) {
    char* src = str;
    char* dst = str;

    while(*src) {
      if(isalnum((unsigned char)*src))
            *dst++ = *src;
      src++;
    }
    *dst = '\0';
}

char* remove_char1(char *str) {

    int i = 0, j=0;
    char *p = str;
    if (NULL == p)
        return NULL;
    while (p[i] != '\0') {
        if (isalnum(p[i])) {
            // store
            str[j++] = p[i];
        }
        i++; // skip the character
    }
    str[j] = '\0';
    return str;
}

int main()  {
    char str[] = "Hi12345WelcometoTechM";
    remove_char(str);
    debug("Hello World  %s \n", str);
    //    printf("Hello World  %s \n", remove_char(str));

    return 0;
}

/**

 **/
