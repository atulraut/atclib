/*
* Program : routine to convert given word to Upper case or Lower
*/
#include <stdio.h>
#include <ctype.h>

char* toUpper(char *string);
char* toLower(char *string);

int main() {
   int i = 0;
   char c;
   char *ret;
   char str[] = "Tutorials Point";
   ret = toUpper (str);
   printf ("ret = %s\n", ret);
   ret = toLower (str);
   printf ("ret = %s\n", ret);
return(0);
}

/* 65-A, 97-a */
char* toUpper(char *string) {
    char *save=string;
    for (; *save!='\0'; save++) {
        if (*save > 96 && *save < 122)
            *save = *save - 32;    
    }
    return string;
}
/* 65-A, 90-Z */
char* toLower(char *string) {
    char *save=string;
    for (; *save!='\0'; save++) {
        if (*save > 64 && *save < 91)
            *save = *save + 32;    
    }
    return string;
}
