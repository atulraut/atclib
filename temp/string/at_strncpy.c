/*<
 * Aim : strncpy
 * Date : Thurday, 07/02/2013 09:23:37PM
 * File : at_strncpy.c
 ***/

#include <stdio.h>
#include <string.h>

/*< Atul Finish >*/

/*< 
 *   The `strncpy' function copies not more than `n' characters (characters
 *   that follow a null character are not copied) from the array pointed to
 *   by `s2' to the array pointed to by `s1'.  If copying takes place between
 *   objects that overlap, the behavior is undefined.
 *   If the array pointed to by `s2' is a string that is shorter than `n'
 *   characters, null characters are appended to the copy in the array
 *   pointed to by `s1', until `n' characters in all have been written.
 *   The `strncpy' function returns the value of `s1'.  
>*/
//http://www.opensource.apple.com/source/Libc/Libc-166/gen.subproj/ppc.subproj/strncpy.c
/*< copy n character of s2 into s1 >*/
char * strncpy(char *s1, const char *s2, size_t n);

int main () {

}

/*< copy n character of s2 into s1 >*/
char * strncpy(char *s1, const char *s2, size_t n) {

  


