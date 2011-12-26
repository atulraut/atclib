 #include <stdio.h>
 int main () {
   int res;
   char src [] = "Atul";
   char tar [] = "Atul";

   // call to array version :
   //  aStrcpy (src, tar);
   // call to poiner version :
   //pStrcpy (src, tar);
   res = 0;
   res = aStrcmp (src, tar);
   printf ("\nres = %d\n", res);
 }

 // The array version of strcpy : !
 void aStrcpy (char *s, char *t) {
   int i = 0;

   while (s[i] != '\0') {
     s[i] = t[i];
     i++;
   }
   printf ("\nATUL >>> aStrcpy : %s\n", t);
 }

 // The version of strcpy with pointers :
 void pStrcpy (char *s, char *t) {

   printf ("\nAtul : *s = %s and *t = %s\n", s, t);
   //  while ((*s++ = *t++) != '\0') 
   //  ;
   while (*s != '\0') {
     *t = *s;
     printf ("\n ATUL >>> astrcpy t :  %s: and c = %c \n", t, *t);
     s++;
     t++;
   }
   printf ("\n ATUL >>> astrcpy t :  %s: \n", t);
   ///  Printf ("\n ATUL >>> aStrcpy s: %s: \n\n", s);
 }

/* aStrcmp : return <0 if s<t, 0 if s==t, >0 if s>t */
int aStrcmp (char *s, char *t) {

  printf ("\n*s = %s *t = %s\n", s, t);

  for ( ; *s == *t; s++, t++) 
    if (*s == '\0')
      return 0;
    return *s-*t;
 }
        
