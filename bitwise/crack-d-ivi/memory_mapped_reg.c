/***
    Memory Mapped Registers Read/Write :
    Thoery :
    https://www.quora.com/How-are-mmap-ioremap-and-kmap-different
    https://subscription.packtpub.com/book/hardware_and_creative/9781838558802/app04/app04lvl1sec65/getting-access-to-i-o-memory
    Program :
    https://stackoverflow.com/questions/4166201/further-question-with-memory-mapped-interface?rq=1
    https://stackoverflow.com/questions/46967682/accessing-memory-mapped-register

    Good One : https://blog.feabhas.com/2019/01/peripheral-register-access-using-c-structs-part-1/
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/***
    dev/c/to_push/desgin_patterns_c/ch-03/
    https://elixir.bootlin.com/linux/latest/source/arch/ia64/include/asm/bitops.h#L22

     #include <linux/io.h>
     struct resource *iomem;
     void clear_bit (int *addr, int bit) {
        int data = readl(addr);
        mb();
        data &= ~(1 << bit);
        writel(data, (void *)addr);
     }

*/
int linux_set_bit (int nr, volatile void *addr) {
  int bit, old_num, new;
  volatile int *m;

  m = (volatile int *) addr;
  old_num = *m;


  old_num |= (1 << nr);
  return old_num;

  // Below Also works
  //  *m |= (1 << nr);
  //return (old_num = *m);
}

void write_REG(unsigned int address, int offset, int data) {
  *((volatile unsigned int*)address + offset) = data;
}

void increment_reg() {

  int c;    //to save the address read from memory
  volatile char *control_register_ptr= (char*) 0x1ffff670;//memory mapped address. using char because it is 8 bits

  c=(int) *control_register_ptr;// reading the register and save that to c as an integer
  c++;//increment by one
  *control_register_ptr=c;//write the new bit pattern to the control register
}

int main () {
  //  increment_reg();
  int i = 10;
  int *ptr = &i;
  int bit = 2;

  int ret = linux_set_bit(bit, ptr);
  debug ("ret = %d", ret);

  return 0;
}


/***
    => ./a.out
    [main] L=63 :ret = 14
*/
