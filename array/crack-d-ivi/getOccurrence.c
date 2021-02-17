/*
Given a method 
int getOccurence(int x,int y); 
where y is always a single digit number. 
So find the number of occurrences of number y in the range x 
E.g. 
if x=25,y=2 
function should return 9(as 22 contains two occurrences of 2) - 2,12,20,21,22,23,24,25
*/
#include <stdio.h>
#include <stdlib.h>

int countOccurences(int ,int);

int main() {
        int cnt = 0, x=26, y=6;
        cnt = getOccurence(x, y);
        printf ("cnt = %d \n", cnt);
}

int countOccurences(int x, int y) {
    while (x>0) {
        if (x==y)
            printf ("Y ->[%d]", y);
         x=x-1;
    }    
}

int getOccurence(int x, int y) {
		int count = 0;
		int itr = y;
		while(itr <= x) {
			if(itr % 10 == y) {
			    count++;
			    printf ("[itr % 10] 0 = %d count = %d\n", (itr % 10), count);
			}
			if(itr != 0 && itr/10 == y) {	
			    printf ("[itr / 10] 1 = %d \n", (itr / 10));
			    count++;
				itr++;
			} else if (itr/10 == y-1) {
			    printf ("[itr / 10] 2 = %d \n", (itr / 10));
			    itr = itr + (10 - y); 
			} else {
			    itr += 10;	
			    printf ("[itr += 10]ELSE = %d \n", itr);
			}
		}
		return count;
}
