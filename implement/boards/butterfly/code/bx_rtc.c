/* bx_rtc.c 

   Real Time Clock (RTC) module for boxcom

   The real time clock uses the timer2 counter clocked by a quartz
   crystal.  The butterfly board has a 32kHz crystal connected between
   the TOSC1 and TOSC2 pins.  
*/

// ----------------------- Include files ------------------------------
#include <stdio.h>

/* avr/io.h
   
   Device-specific port definitions
*/
#include <avr/io.h>

#include "bx_rtc.h"


// ----------------------- Functions ----------------------------------

/* rtc_init()

   Configures timer2 to be clocked by the watch crystal.
*/
void rtc_init(void) {
  /* Set ASSR (asynchronous status register) value

     Set the AS2 bit to clock timer2 by the crystal oscillator.  Clear
     all other bits. 
  */
  ASSR = (1<<AS2);
  
  /* Set TCCR2A (timer/counter control regiser A) value

     Clear WGM21, WGM20 for normal mode (just counts and rolls over).
     Set prescaler for a 1ms counter (CS22=0,CS21=1,CS20=1)
   */
  TCCR2A &= ~(_BV(WGM21) | _BV(WGM20));
  TCCR2A &= ~(_BV(CS22));
  TCCR2A |= (_BV(CS21) | _BV(CS20));
  /* Look at the asynchronous status register to figure out if timer 2
     has settled in to normal operation.  This means that the counter
     value is being automatically updated (TCN2UB = 0) and that the
     configuration register is ready to take new values (TCR2UB = 0).
    */
  while((ASSR & _BV(TCR2UB)) | (ASSR & _BV(TCN2UB)));
}

/* ms_counter()

   Returns the value of the millisecond counter.  Note that this is
   only 8 bits.

   Returns: uint8_t counter value (0-255)
*/
uint8_t ms_counter(void) {
  uint8_t countval = TCNT2;
  return countval;
}
