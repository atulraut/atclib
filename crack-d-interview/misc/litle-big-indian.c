/* http://www.gamedev.net/topic/485099-big-endian-vs-small-endian/
an int is typically 32 bit or 4 bytes. The number "1" encoded as an int can be stored in memory in two ways, either like this:

00000001 00000000 00000000 00000000 (Little-endian)

or like this:

00000000 00000000 00000000 00000001 (Big-endian)

What the code you've posted does is the following:

&num - This will retrieve the address of the "num" variable
(char*) &num - This will cast the address of the "num" variable to "pointer to char" 

If you wrote

char* ptr = (char*) num;

then "ptr" would point to the first byte of "num".

In the last step, the "*" (dereference) operater is used to retrieve the value of the first byte of num. If this value is "1" then the system uses little-endian, if it is "0", the system uses big-endian. 
*/

#include <stdio.h>
int main()
{
      int num = 1;

       union a
       {
               int i;
               char ch[2];
       };
       union a z={512};
       printf("%x %x",z.ch[0],z.ch[1]);
       printf("\n %x",z.i);
       
       if(*(char *)&num == 1)
       {
               printf("\nLittle-Endian\n");
       }
       else
       {
               printf("Big-Endian\n");
       }
       return 0;
}

