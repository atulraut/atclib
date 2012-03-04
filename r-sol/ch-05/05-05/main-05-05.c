/*
* Auther : Atul R. Raut
* Date   : Sun Dec 25th 2011, 10:32PM
* End    : Sun Mar 04th 2012, 05:50PM
* AIM    : Write versions of the library functions strncpy, strncat and strncmp,
*          which operate on at most the first n characters of their argument strings
*          For ex. strncpy (s,t,n) copies at most n characters of t to s.
***/
#include <stdio.h>

char* aStrncpy (char *s, char *t, int n);
char* aStrncat (char *s, char *t, int n);
int aStrncmp (char *s, char *t, int n);

int  main () {
   char src[] = " ";
   char tar[] = "Raut";
   char *buf = NULL;

   memset(src, '\0', sizeof( src ));
   buf = aStrncpy (src, "Raut", 2);
   printf ("\n Res = %s\n", buf);
 }

 // The version of strcpy with pointers :
char* aStrncpy (char *s, char *ct, int i) {
  int n = i;
   while (*ct && n-- > 0) {
     *s++ = *ct++;
   }
   n = i; // Reset n
   while (n-- > 0) {
     *s++ = '\0';
   }
  return s;
}

char*  aStrncat (char *s, char *t, int n) {

}

int aStrncmp (char *s, char *t, int n) {

}
