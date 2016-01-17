/*
* WAP :  to make string to upper case & lower case.
* Author : Atul Raut
* A-Z - 65-91
* a-z - 97-122
*/
#include <stdio.h>

char* upper(char *p);
char* lower(char *p);

int main() {
    char arr[5] = "ATUL";
    char abc[5] = "atul";
    char *ret = NULL;
    ret = upper (abc);
    printf("Return Upper = %s \n", abc);
    ret = lower (arr);
    printf("Return Lower= %s \n", arr);
    return 0;
}

char* upper(char *p) {
   int i = 0;
   while(p[i] != '\0')	{
	if(p[i] >= 97 && p[i] <= 122) {
		p[i] = (p[i] - 32);
		i++;
	} else
	    i++;
   } // end while
    printf("To Upper = %s \n", p);
    return p;
}

char* lower(char *p) {
    int i = 0;
    while(p[i] != '\0')	{
	if(p[i] >= 65 && p[i] <= 91) {
		p[i] = p[i] + 32;
		i++;
	} else
	   i++;
    } // end while
    printf("To Lower = %s \n", p);
    return p;
}
