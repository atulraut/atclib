/*
  Reverse Integer
*/
#include <stdio.h>

int reverseInteger(int x) {
        int ans = 0;
        while (x) {
            int temp = ans * 10 + x % 10;
            printf ("x%10 = %d temp = %d \t", (x%10), temp);
            if (temp / 10 != ans)
                return 0;
            ans = temp;
            x /= 10;
            printf ("\nx= %d \t", x);
        }
        return ans;
}

int main() {
    printf("\n Reverse Int = %d\n", reverseInteger(321));

    return 0;
}

/*
x%10 = 1 temp = 1 	
x= 32
x%10 = 2 temp = 12 	
x= 3
x%10 = 3 temp = 123 	
x= 0 	
Reverse Int = 12
*/
