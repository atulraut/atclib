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
   char src[] = "  ";
   char tar[] = "Raut";
   char *output_str = NULL;
   //   memset(src, '\0', sizeof( src ));
   output_str = aStrncpy (src, "Raut", 2);
   printf ("\n Res = %s\n", output_str);
   memset(output_str, '\0', sizeof( output_str ));
   output_str = aStrncat ("Atul ", "Raut", 2);
   printf ("\n Res = %s\n", output_str);
 }

/* aStrncpy : The version of aStrcpy with pointers */
char* aStrncpy (char *s, char *ct, int i) {
  printf ("\n[AT-aStrncpy] s= %s, ct=%s \n", s, ct);
  int n = i;
  while (*ct && n-- > 0) {
    *s++ = *ct++;
  }
  n = i;    // Reset n
  while (n-- >= 0) {
     *s++ = '\0';
  }
  printf ("[AT-aStrncpy] = %s", s);
  return s;
}

/* aStrnccat : Concate n characters of t to the end of s */
char*  aStrncat (char *s, char *t, int i) {
  char *buf = NULL;
  printf ("\n[AT-aStrncat] = s=%s t=%s, i=%d\n", s, t, i);
  // char* aStrncpy (char *s, char *t, int i);
  //int strlen (char *);
  //buf = aStrncpy (s+strlen(s), t, i);
  
  printf ("\n[AT] buf = %s \n", buf);
  return buf;
}

int aStrncmp (char *s, char *t, int n) {
  
}
