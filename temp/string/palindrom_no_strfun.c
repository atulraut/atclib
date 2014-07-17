/*  
* Aim : C program for palindrome without using string functions
* Date : Wednesday, 16-07-2014
* Author : Atul Raut
***/

#include <stdio.h>
#include <string.h>

int my_word_palindrome(const char *);

int main()
{
   int res;
   char text[100];
   gets(text);
   res = my_word_palindrome(text);
   if (1 == res)
           printf ("Word is Palindrome");
   else
           printf ("Word not Palindrome");
}

int my_word_palindrome(const char *text) {
   int res, begin, middle, end, length = 0;
   while ( text[length] != '\0' )
      length++;

   end = length - 1;
   middle = length/2;
   printf ("middle = %d\n", middle);
   for( begin = 0 ; begin < middle ; begin++ )
   {
      printf ("begin= %d, middle= %d end = %d\n", begin, middle, end);
      if ( text[begin] != text[end] )
      {
         printf("Not a palindrome.\n");
         res = 0;
         break;
      }
      end--;
   }
   if( begin == middle ) {
     res = 1;
     printf("Palindrome.\n");
   }
   return res;
}