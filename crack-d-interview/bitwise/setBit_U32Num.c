/*
 * https://stackoverflow.com/questions/1680365/integer-to-ip-address-c
 * 12/15/2019
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // uint8_t

struct ntb_msg {
  int len;
  void *buf;
};

void print_ip2(unsigned int ip) {
  unsigned char bytes[4] = {0};
  bytes[0] = ip & 0xFF;
  bytes[1] = (ip >> 8) & 0xFF;
  bytes[2] = (ip >> 16) & 0xFF;
  bytes[3] = (ip >> 24) & 0xFF;

  printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
}

void print_ip(int ip) {
   unsigned char bytes[4];
   int i;
   for(i=0; i<4; i++) {
      bytes[i] = (ip >> i*8) & 0xFF;
   }
   printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
}

void send_msg1(struct ntb_msg *b) {
  char *m = (char *)b[0].buf;
  printf("%d.%d.%d.%d\n", m[3], m[2],
	 m[1], m[0]);
}

uint32_t set_MSBLSB(uint8_t msb,
		uint8_t lsb) {
  char bytes[4] = {0};
  uint16_t b1[] = {1};

  bytes[3] = msb;
  bytes[0] = lsb;

  struct ntb_msg msg[2] = {
    {
      .len = 4,
      .buf = (void *)bytes,
    },
    {
      .len = 1,
      .buf = b1,
    },
  };

  /*
  bytes[0] = msb & 0xFF;
  bytes[1] = (lsb >> 8) & 0xFF;
  bytes[2] = (lsb >> 16) & 0xFF;
  bytes[3] = (lsb >> 24) & 0xFF;
  */
  printf("B: %d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
  send_msg1(msg);
  return bytes;
}

uint32_t get_MSBLSB(unsigned char *bytes, uint16_t msb,
		uint16_t lsb) {
  bytes[0] = msb & 0xFF;
  bytes[1] = (lsb >> 8) & 0xFF;
  bytes[2] = (lsb >> 16) & 0xFF;
  bytes[3] = (lsb >> 24) & 0xFF;
  printf("A: %d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
  return bytes;
}

int main() {
  char bytes[4] = {0};
  //   int ip = 0xDEADBEEF;
  int ip = 0, i;
  int msb = 127;
  int lsb = 24;
  uint32_t res = set_MSBLSB(msb, lsb);
  for(i=0; i<4; i++)
    printf ("--> %d b=%d \n", res, bytes[i]);
}
