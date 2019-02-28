#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare_string(char *first, char *second) {
//  printf ("[AR]-->s1=%c s2=%c \n", *first, *second);    
   while (*first == *second) {
  printf ("[AR]-->s1=%c s2=%c \n", *first, *second);    
      if (*first == '\0' || *second == '\0')
         break;
         
      first++;
      second++;
   }
 
   if (*first == '\0' && *second == '\0')
      return 0;
   else
      return -1;
}

int strcmp_2char2(char *str1, char *str2) {
  int index = 0, l = 0, cnt = 0;
  if (strlen(str1) != strlen(str2))
    return -1;
  while (*str1 != '\0') {
    printf ("[AR] c=%c c=%c \n", *str1, *str2);
    if (*str1 != *str2)
      index = l++;
    else
      cnt++;
    str1++;str2++;
  }
  l = strlen(str2);
  printf ("cnt=%d l=%d \n", cnt, (l-1));
  if (cnt == (l-1))
    return 0;
  else
    return 1;
}


int strcmp_2char (char *str1, char *str2) {
  int l = strlen(str1)-1;
  int h = strlen(str2)-1;
  int flag = 0;
  int cnt  = 0; 
  int index = 0;
  if(l != h)
    return 1;// fails
  l = h = 0;
  while (str2[h] != '\0') {
    printf ("[AR] -->s1=%c s2=%c \n", str1[l], str2[h]);  
    if (str2[h] != str1[l])  {
        index = l;
        printf ("[AT]-->s1=%c s2=%c index=%d\n", str1[l], str2[h], index);
    }
    else
        ++cnt;
    h++; l++;
  }
  printf ("cnt = %d l-2=%d \n",cnt, (l-1));
  if(cnt == (l-1))
    return 0;  // success
  else
    return 1; // fail
}

int main () {
  char ar [] = "IT !I";
  printf ("O/P--> [%d] \n", strcmp_2char2("CAT", "STD"));
  printf ("A--> [%d] \n", *(ar-1) );
  printf ("--> ar= [%p] (ar-1)= [%p] \n", ar, (ar-1));
}
