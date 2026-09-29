/***

    Implement Delay Timer In C.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Sep 28 17:02:05 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

/**
   I convert the requested delay into hardware-counter ticks,
   save the initial counter value, and busy-wait until the
   elapsed tick count reaches the requested number.
   Using unsigned subtraction also handles counter rollover.”
**/
#define REG_COUNTER (*(volatile uint32_t *)0x10000000)
#define CLK_FREQ    1000000U   // 1 MHz: 1,000,000 ticks/sec

void timer_delay(uint32_t delay_sec) {
  uint32_t start = REG_COUNTER;
  uint32_t delay_ticks = delay_sec * CLK_FREQ;

  while ((uint32_t)(REG_COUNTER - start) < delay_ticks)
    ;          // busy wait
}

int main(void) {
  printf("Counter = %llu\n", (unsigned long long)REG_COUNTER);

  printf("Starting 5 second delay...\n");
  timer_delay(5);
  printf("Done!\n");

  return 0;
}
