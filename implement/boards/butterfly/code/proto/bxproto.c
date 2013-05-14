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
  char astring[20] = "-32767";
  uint16_t cnum = atoi(astring);
  printf("Converted string is %i\r\n",cnum);
  return 0;
}
