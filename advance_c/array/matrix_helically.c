/*
* Write C program to print a matrix helically. 
* Printing a matrix helically means printing it in this spiral fashion
>-----------+
            |
+---->--+   |
|       |   |
|       |   |
|   <---+   |
|           |
+-----------+
* Date : August 09, 2017
* Author : Atul Raut
* **/
#include <stdio.h>
int main () {
	int i = 0;
	int arr[4] = {0}; int h = 0, v = 0, flag = 0; int sz = 8;
	for (h=0; h<sz; h++) {
		for (v=0; v<sz; v++) {
			if (h==0 && v == 0)
				printf (">");
			if(v == 0)
				printf ("--");
			if (h == sz-1) {
				if(h==sz-1 && v == 0)
					printf ("+");
				printf("\n");
				if(v != 0)
					printf ("|");
				printf ("\t\t |");
			}
		}
	}
	printf ("\n");
	if (h=sz-1) {
		printf("+");
		for(i=0; i<sz; i++)
			printf ("--");
	}
	printf ("+\n");
}
