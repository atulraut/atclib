#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * defangIPaddr(char * address){
        int len = strlen(address);
        char *res = malloc(sizeof(char) * (len + 7)); // 6 for 3 sets of brackets + 1 NULL

        int i = 0, j = 0;
        while (i < len) {
                res[j++] = address[i];

                if (address[i+1] == '.')
                {
                        res[j++] = '[';
                        res[j++] = address[++i];
                        res[j++] = ']';
                }
                i++;
        }
        res[j] = '\0';
        return res;
}

char* defangIPaddr(char *address){
        int i = 0, cnt = 0, newsz;
        int len = strlen(address);
        char *newstr;
        while (address[i] != '\0') {
                if(address[i] == '.') {
                        cnt++;
                }
                i++;
        }
        newsz = (len-cnt)+(cnt*3);
        printf ("\nAR- len =%d, new=%d\n", len, newsz);
        newstr = (char *)malloc(sizeof(char) * newsz);
        newstr[newsz] = '\0';
        for (i=len-1; i >= 0; i--) {
                if(address[i] == '.') {
                        newstr[newsz-1] = ']';
                        newstr[newsz-2] = '.';
                        newstr [newsz-3] = '[';
                        newsz -= 3;
                } else {
                        newstr[newsz-1] = address[i];
                        newsz -= 1;
                }
        }
        address = newstr;
        //free(newstr); newstr = NULL;
        return address;
}

int main()
{
        char *temp;
        char address[] = "255.100.50.0";
        temp = defangIPaddr(address);
        printf("Hello World %s \n\n", temp);
        free(temp);
        temp = NULL;
        return 0;
}
