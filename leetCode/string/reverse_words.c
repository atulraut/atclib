/* Given a string, you need to reverse the order of characters
   in each word within a sentence while still preserving
   whitespace and initial word order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(int b, int e, char *s){
        while(b < e) {
                s[b] = s[b] ^ s[e];
                s[e] = s[b] ^ s[e];
                s[b] = s[b] ^ s[e];
                b++;
                e--;
        }
}

char* reverseWords(char* s) {
        int i, s_len = strlen(s), index = 0;

        for(i = 0; i <= s_len; i++) {
                if((s[i] == ' ') || (s[i] == '\0')){
                        reverse(index, i - 1, s);
                        index = i + 1;
                }
        }
        return s;
}

int main() {
        char arr[] = "Atul Ramesh Raut";
        char *ret = reverseWords(arr);
        printf ("--> o/p = %s \n", ret);
}
