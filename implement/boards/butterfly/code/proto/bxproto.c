/* bxproto.c

   Where I can prototype things for use in boxcom.
*/
#include <stdio.h>

/* stdlib.h

   Provides atoi() -- converts ascii number to integer.  Note that
   atoi emits an int, which for the AVR architecture is 2 bytes (16
   bits).  An input that won't fit into 16 bits will cause undefined
   behavior.
*/
#include <stdlib.h>

#include <stdint.h> // Fixed width integer types






int main(void) {
  uint32_t bignum = 4233600;
  printf("bignum is %u\r\n",bignum);
  return 0;
}
