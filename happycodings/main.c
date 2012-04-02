// understanding ivt table
#include <stdio.h>
#include <stdlib.h>
//#include<dos.h>
main ()
{
  unsigned long far *address = (unsigned long far *) 0x00000000;
  unsigned long intadd[256];
  unsigned int segment, offset;
  int i;
  FILE *fp;
  fp = fopen ("IVT.txt", "wb");
  for (i = 0; i < 256; i++)
    {
      intadd[i] = *(address++);
      segment = FP_SEG (intadd[i]);
      offset = FP_OFF (intadd[i]);
      fprintf (fp, "interrupt %3X : vector %Fp(hex) : %lu(dec)
", i, intadd[i], (unsigned long) segment * 16 + offset);
    }
  fclose (fp);
}
