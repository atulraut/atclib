/*
  Packing and unpacking two 32-bit integers into an unsigned 64-bit integer
  https://stackoverflow.com/questions/3133376/implicit-typecasting-in-c-converting-32-bit-unsigned-in-to-8-bit-u-int
  https://codereview.stackexchange.com/questions/80386/packing-and-unpacking-two-32-bit-integers-into-an-unsigned-64-bit-integer
*/
#include <stdio.h>
#include <stdint.h> // uint8_t
#include <stdlib.h>
#include <string.h>

struct ntb_msg {
  uint16_t flag;
  uint16_t len;
  uint8_t *buf;
};
void recv(uint32_t lsb, uint32_t msb, uint32_t cm, struct ntb_msg rmsg[], uint32_t flag);

void send(struct ntb_msg smsg[], struct ntb_msg rmsg[]) {
  uint64_t data_back;
  uint32_t cid, lsb, msb, cmd, wid, flag = 1;
  uint64_t data = 0xffffffc0f882fca1;

  lsb = ( (smsg[0].buf[3] << 24) | (smsg[0].buf[2] << 16) | (smsg[0].buf[1] <<  8) | (smsg[0].buf[0] << 0 ) );
  msb = ( (smsg[1].buf[3] << 24) | (smsg[1].buf[2] << 16) | (smsg[1].buf[1] <<  8)| (smsg[1].buf[0] << 0) );
  cid = ( (smsg[2].buf[3] << 24) | (smsg[2].buf[2] << 16) | (smsg[2].buf[1] <<  8)| (smsg[2].buf[0] << 0) );

  data_back = ( ( (uint64_t) ( ( (msb) >> 16) >> 16)  ) | lsb);
  data_back = (((uint64_t) msb) << 32) | ((uint64_t) lsb);

  printf("[%s] Unpacked: data_back=0x%lx msb=0x%x lsb=0x%x cid=%d L=%d \n",__func__, data_back, msb, lsb, cid, __LINE__);
  cmd = smsg[2].buf[0];
  wid = smsg[2].buf[1];
  printf ("[%s] data_back=0x%lx cmd=%d wid=%d L=%d \n\n", __func__, data_back, cmd, wid, __LINE__);

  for(int i=0; i<4; i++) {
    rmsg[0].buf[i] = lsb >> i*8;
    rmsg[1].buf[i] = msb >> i*8;
    rmsg[2].buf[i] = cid >> i*8;
  }
  //  memcpy(&rmsg[0], smsg[0].buf, smsg[0].len);
  //  memcpy(&rmsg[1], smsg[1].buf, smsg[1].len);
  //  memcpy(&rmsg[2], smsg[2].buf, smsg[2].len);

}

static uint32_t *l, *m, *c;
void recv(uint32_t lsb, uint32_t msb, uint32_t cm, struct ntb_msg rmsg[], uint32_t send) {
  uint64_t data = 0xffffffa0f882faa0;

  if(send)
    printf ("[%s] cm=%d L=%d \n\n", __func__, cm, __LINE__);
  if(!send) {
    l = &lsb;
    m = &msb;
    c = &cm;
  } else
      return;

  uint8_t i1[4] = {0};
  uint8_t i2[4] = {0};
  uint8_t i3[4] = {0};

  i1[0] = (cm >>  0);
  i1[1] = (cm >>  8);
  i1[2] = (cm >> 16);
  i1[3] = (cm >> 24);

  i2[0] = (data >> 32);
  i2[1] = (data >> 40);
  i2[2] = (data >> 48);
  i2[3] = (data >> 56);

  i3[0] = 18;
  i3[1] = 91;

  if(!send) {
    printf ("[%s] cm=%d i1=%d i1=%d L=%d \n\n", __func__, cm, i1[0], i1[1], __LINE__);
    rmsg[0].buf = (uint8_t*)l;//i1;
    rmsg[1].buf = (uint8_t*)m;//;i2;
    rmsg[2].buf = c;
  }
}

int main() {
  uint64_t data = 0xffffffc0f882fcc0;
  uint32_t cm, flag = 0;

  uint8_t i1[4] = {0};
  uint8_t i2[4] = {0};
  uint8_t i3[4] = {0};
  uint32_t lsb=0, msb=0;
  uint8_t cmd=0, wid=0;
  int i;
  printf ("[%s] Enter data=0x%lx L=%d \n", __func__, data, __LINE__);

  /* Send Data */
  for(i=0; i<4; i++)
    i1[i] = (data >>  i*8);

  for(i=1; i<4; i++)
    i2[i-1] = (data >> (32+(i*8)));


  i3[0] = 8;
  i3[1] = 9;

  for(i=0; i<4; i++) {
    lsb |= (i1[i] << i*8);
    msb |= (i2[i] << i*8);
  }
  //msg[0].buf[i] = lsb >> i;

  //  lsb = ( (i1[3] << 24) | (i1[2] << 16) | (i1[1] <<  8) | (i1[0] << 0 ));
  //  msb = ( (i2[3] << 24) | (i2[2] << 16) | (i2[1] <<  8) | (i2[0] << 0 ));
  data = (((uint64_t) msb) << 32) | ((uint64_t) lsb);

  printf ("[%s] Unpack data=0x%lx msb=0x%x lsb=0x%x L=%d \n", __func__, data, msb, lsb,__LINE__);
  printf ("[%s] Enter i1=0x%lx i2=0x%lx L=%d \n", __func__, i1, i2, __LINE__);
  /* Send Message */
  struct ntb_msg Smsg[3] = {
    {
      .len = 4,
      .buf = i1,
    },
    {
      .len = 4,
      .buf = i2,
    },
    {
      .len = 4,
      .buf = i3,
    },
  };

  //send(Smsg);
  // lsb = ( (rmsg[0].buf[3] << 24) | (rmsg[0].buf[2] << 16) | (rmsg[0].buf[1] <<  8) | (rmsg[0].buf[0] << 0) );
  //msb = ( (rmsg[1].buf[3] << 24) | (rmsg[1].buf[2] << 16) | (rmsg[1].buf[1] <<  8) | (rmsg[1].buf[0] << 0) );
  //data = ( ( (uint64_t) ( ( (msb) >> 16) >> 16)  ) | lsb);
  //data = (((uint64_t) msb) << 32) | ((uint64_t) lsb);

  //  printf ("[%s]_Recv: Unpack data=0x%lx msb=0x%x lsb=0x%x L=%d \n", __func__, data, msb, lsb,__LINE__);
  //  cmd = rmsg[2].buf[0];
  //  wid = rmsg[2].buf[1];
  //  printf ("[%s]_Recv: data_back=0x%lx cmd=%d wid=%d L=%d \n\n", __func__, data, cmd, wid, __LINE__);

  /* Recv Data */
  //memset((void *)i1, 0, 8);
  //memset((void *)i2, 0, 8);
  // memset((void *)i3, 0, 8);

  struct ntb_msg rmsg[3] = {
    {
      .len = 4,
      .buf = i1,
    },
    {
      .len = 4,
      .buf = i2,
    },
    {
      .len = 4,
      .buf = i3,
    },
  };

  /**************************************************************************************************************/
  send(Smsg, rmsg);
  lsb = ( (rmsg[0].buf[3] << 24) | (rmsg[0].buf[2] << 16) | (rmsg[0].buf[1] <<  8) | (rmsg[0].buf[0] << 0 ) );
  msb = ( (rmsg[1].buf[3] << 24) | (rmsg[1].buf[2] << 16) | (rmsg[1].buf[1] <<  8)| (rmsg[1].buf[0] << 0) );
  cm  = ( (rmsg[2].buf[3] << 24) | (rmsg[2].buf[2] << 16) | (rmsg[2].buf[1] <<  8)| (rmsg[2].buf[0] << 0) );
  data = ( ( (uint64_t) ( ( (msb) >> 16) >> 16)  ) | lsb);
  data = (((uint64_t) msb) << 32) | ((uint64_t) lsb);
  printf ("[%s]_Recv: ATUL Unpack data=0x%lx msb=0x%x lsb=0x%x sz=%d L=%d \n", __func__, data, msb, lsb, sizeof(rmsg)/sizeof(rmsg[0]),__LINE__);
  cmd = rmsg[2].buf[0];
  wid = rmsg[2].buf[1];
  printf ("[%s]_Recv: ATUL Unpack cid=%d cmd=%d wid=%d L=%d \n", __func__, cm, cmd, wid,__LINE__);
  /**************************************************************************************************************/ 
  flag = 0;
  /* Recieve Message */
  recv(lsb, msb, cmd, rmsg, flag);
  lsb = ( (rmsg[0].buf[3] << 24) | (rmsg[0].buf[2] << 16) | (rmsg[0].buf[1] <<  8) | (rmsg[0].buf[0] << 0) );
  msb = ( (rmsg[1].buf[3] << 24) | (rmsg[1].buf[2] << 16) | (rmsg[1].buf[1] <<  8) | (rmsg[1].buf[0] << 0) );
  data = ( ( (uint64_t) ( ( (msb) >> 16) >> 16)  ) | lsb);
  data = (((uint64_t) msb) << 32) | ((uint64_t) lsb);

  printf ("[%s]_Recv: Unpack data=0x%lx msb=0x%x lsb=0x%x L=%d \n", __func__, data, msb, lsb,__LINE__);
  cmd = rmsg[2].buf[0];
  wid = rmsg[2].buf[1];
  printf ("[%s]_Recv: data_back=0x%lx cmd=%d wid=%d L=%d \n\n", __func__, data, cmd, wid, __LINE__);
}

