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
  increment_reg();
}
