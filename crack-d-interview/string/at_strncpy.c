/*<
 * Aim : strncpy
 * Date : Thurday, 07/02/2013 09:23:37PM
 * File : at_strncpy.c
 ***/

#include <stdio.h>
#include <string.h>

/*< Atul Finish >*/

/**
 * strlcpy - Copy a C-string into a sized buffer
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @size: size of destination buffer
 *
 * Compatible with ``*BSD``: the result is always a valid
 * NUL-terminated string that fits in the buffer (unless,
 * of course, the buffer size is zero). It does not pad
 * out the result like strncpy() does.
 */
size_t strlcpy(char *dest, const char *src, size_t size) {
        size_t ret = strlen(src);
        if (size) {
                size_t len = (ret >= size) ? size - 1 : ret;
                memcpy(dest, src, len);
                dest[len] = '\0';
        }
        return ret;
}

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

/* http://www.opensource.apple.com/source/Libc/Libc-166/gen.subproj/ppc.subproj/strncpy.c */
/*< copy n character of src into dest >*/
char *at_strncpy(char *dest, const char *src, size_t n)
{
    char *save = dest;
    while (n > 0 && *src != '\0') {
	*save++ = *src++;
	--n;
    }
    while (n > 0) {
	*save++ = '\0';
	--n;
    }
    *save = '\0';
    return dest;
}

int at_strncmp(const char *s1, const char *s2, size_t n) {
  char *save1 = s1;
  char *save2 = s2;
  while (n--) {
    if(*save1++ != *save2++)
      return *(unsigned char *)(save1-1) - *(unsigned char *)(save2-1);
  }
  return 0;
}

/**
 * strlcat - Append a length-limited, C-string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 * @count: The size of the destination buffer.
 */
size_t strlcat(char *dest, const char *src, size_t count) {
        size_t dsize = strlen(dest);
        size_t len = strlen(src);
        size_t res = dsize + len;
        /* This would be a bug */
        BUG_ON(dsize >= count);
        dest += dsize;
        count -= dsize;
        if (len >= count)
                len = count-1;
        memcpy(dest, src, len);
        dest[len] = 0;
        return res;
}

char* at_strncat(char *dest, char *src, size_t n) {
  char *d = dest;
  char *s = src;
  if(n != 0) {
    while (*d != '\0')
      d++;
    do {
      if ((*d = *s++) == '\0')
	break;
      d++;
    } while (--n != 0);
    *d = '\0';
  } // if ends
  return (dest);
}

int main () {
	char src[]  = "Atul";
	char s[]   = "Atul ";
	char dest[] = {'\0'};
	char *s1 = "Ar";
	char *s2 = "Ar";
	char *output;
	int ret;
	output = at_strncpy(dest, src, 4);
	printf ("output = %s \n", output);
	ret = at_strncmp(s1, s2, 4);
	printf ("ret = %d \n", ret);
	output = at_strncat(s, "Raut", 4);
	printf ("output = %s \n", output);
}


