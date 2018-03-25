/*
  Design an algorithm and write code to remove the duplicate characters 
  in a string without using any additional buffer.
*/
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define NO_OF_CHARS 256
#define bool int

char *removeDuplicateString(char *str) {
  int i, j, k;
  int len = strlen (str);
  for (i=0; i<len; i++) {
    for (j=i+1; j<len; j++) {
      if (str[i] == str[j]) {
	for (k=j; k<len; k++) {
	  str[k] = str[k+1];
	  //	  str[k+1] = '\0';
	  //len--;
	  printf ("c = %c\n", str[k]);
	}
      }
    }
  }
  
  return str;
}
 
void sort_String_array (char *start, char *endstr) {
  int i, j;
  char temp;
  int len = strlen (start);
  for (i=1; i<len; i++) {
    for (j=0; j<len-i; j++) {
      if (start[j] >  start[j+1]) {
	temp       = start[j];
	start[j]   = start[j+1];
	start[j+1] = temp; 
      }
    }
   }
  printf ("sort String = [%s] \n", start);
}


/* Function to remove duplicates in a sorted array */
char *removeDupsSorted(char *str) {
    int res_ind = 1, ip_ind = 1;
 
    /* In place removal of duplicate characters*/
    while (*(str + ip_ind)) {
      printf ("->%c \n", *(str + ip_ind));
        if (*(str + ip_ind) != *(str + ip_ind - 1)) {
            *(str + res_ind) = *(str + ip_ind);
            res_ind++;
        }
        ip_ind++;
    }
    /* After above step string is efgkorskkorss.
       Removing extra kkorss after string*/
    *(str + res_ind) = '\0'; 
    return str;
}
 
/* Function removes duplicate characters from the string
   This function work in-place and fills null characters
   in the extra space left */
char *removeDups(char *str) {
   int n = strlen(str);
   // Sort the character array
   sort_String_array(str, str+n);
   // Remove duplicates from sorted
   return removeDupsSorted(str);
}

/* Function removes duplicate characters from the string
   This function work in-place and fills null characters
   in the extra space left */
char *removeDups2(char *str) {
  bool bin_hash[NO_OF_CHARS] = {0};
  int ip_ind = 0, res_ind = 0;
  char temp;    
 
  /* In place removal of duplicate characters*/
  while (*(str + ip_ind)) {
    temp = *(str + ip_ind);
    if (bin_hash[temp] == 0) {
        bin_hash[temp] = 1;
        *(str + res_ind) = *(str + ip_ind);
        res_ind++;
    }
    ip_ind++;
  }      
 
  /* After above step string is stringiittg.
     Removing extra iittg after string*/
  *(str+res_ind) = '\0';   
 
  return str;
}
 
int main() {
  char str[] = "aatauulll";
  printf("--> %s \n", removeDups(str));
  //printf("%s", removeDups2(str));
  printf("--> %s \n", removeDupsSorted(str));
  printf("-> %s \n", removeDuplicateString(str));
  return 0;
}

/*
  0 1 2 3 4 5 6 7 8 
  a a t u l a t t t '\0'
    r       r   
    i
      i       i 
*/  
