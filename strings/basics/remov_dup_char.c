/*
* Aim  : Print character occurring maximum number of times in a String
* Date : 22/07/2014, Tuesday.
* Author : Atul Raut
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMaxOccuringChar(char* str);

main() {  
    char *str = "atul Ramesh Raut";
    printMaxOccuringChar (str);
    return 0;
}


void printMaxOccuringChar(char* str) {
    // Boundary check
    int maxCntIdx = 0;
    int i = 0;
    // Count Array. All elements are zeros
    int cntArr[256] = {0};  // 0-256 Covers all ASCII Table e.g. a=97 & A=65

    if(str == NULL || str[0] == '\0') {
      printf("EMPTY STRING");
      return;
    }

    // Populating the Count Array
    for(i = 0; str[i] != '\0'; i++) {
        cntArr[str[i]]++; 
        //or  Same : cntArr[str[i]] = cntArr[str[i]] + 1; 
    }
    // Getting the index of Maximum count in the Array
    for(i=0; i < 256; i++) {
        if(cntArr[i] > cntArr[maxCntIdx])
        maxCntIdx = i;
    }
    printf("Character '%d' Appears Maximum %d times in \"%s\"", maxCntIdx, cntArr[maxCntIdx], str);
}