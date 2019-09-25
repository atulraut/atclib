/*
*1. Input two strings from user and perform the operations on it using following library functions. Program must be menu driven.
	i. strlen
	ii. strcpy
	iii. strcat
	iv. strcmp
	v. strrev
	vi. strcmpi
	vii. strchr
	viii. strstr
	ix. strupr
	x. strlwr
*   Date : 02-09-2009
*   Atul Raut
*   Bangalor
**/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int myStrlen(char *);
void myStrcpyPtr (char *s, char *t);
void myStrcpy(char *s, char *t);
void myStrcat(char *s, char *t);

int main()
{
    printf("Hello world!\n");
    char *str = "atul";
    char *t   = "meet";
    int i;
    i = myStrlen (str);
    printf ("\nLength = %d\n", i);
//    myStrcpy(str, t);
//    myStrcpyPtr(str, t);
    myStrcat(str, t);
    return 0;
}

void myStrcat(char *s, char *t) {
    char *buffer;
    buffer = (char *) malloc (6);
    strcpy(buffer, "Rajesh");
    int tLen = myStrlen(s);
    printf("AT :Len = %d\n", tLen);
    buffer = (char *)realloc (buffer, tLen+1);
    strcpy (buffer, "Srikant");
    printf ("::>>AT = %s", buffer);
}

int myStrlen(char *sorceStr) {
    int i = 0;
    while (sorceStr[i] != '\0')
    {
        i++;
    }
    return i;
}

//--- Subscript Version of strcpy ----//
void myStrcpyPtr (char *s, char *t) {
    printf("\nAT: %s, %s\n", s, t);
    while((*s = *t) != '\0')
    {
        printf ("\n::>>\n");
        s++;
        t++;
        printf ("\n::>>\n");
    }
    printf ("\nStrCpy = %s, Tar = %s\n", s, t);
}

//--- Subscript Version of strcpy ----//
void myStrcpy(char *s, char *t) {
    printf("\nAT: %s, %s\n", s, t);
    int i = 0;
    while(s[i] != '\0')
    {
        s[i] = t[i];
        printf ("\n::>>\n");
        i++;
    }
    printf ("\nStrCpy = %s, Tar = %s\n", s, t);
}
