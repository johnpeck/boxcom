/* bx_rtc.c 

   Real Time Clock (RTC) module for boxcom

   The real time clock uses the timer2 counter (8-bit) clocked by a
   quartz crystal.  The butterfly board has a 32kHz crystal connected
   between the TOSC1 and TOSC2 pins.
*/

// ----------------------- Include files ------------------------------
#include <stdio.h>

/* avr/io.h
   
   Device-specific port definitions.  Also provides special
   bit-manipulations functions like bit_is_clear and
   loop_until_bit_is_set.
*/
#include <avr/io.h>

/* pgmspace.h
   
   Provides macros and functions for saving and reading data out of
   flash.
*/
#include <avr/pgmspace.h>

/* bx_logger.h

   Provides logger_msg and logger_msg_p for log messages tagged with a
   system and severity.
*/
#include "bx_logger.h"

/* bx_sound.h

   Provides functions for using timer1 -- the timer used for the sound
   module.
*/
#include "bx_sound.h"

#include "bx_rtc.h"


// ----------------------- Functions ----------------------------------

/* rtc_init()

   Configures timer2 to be clocked by the watch crystal.
*/
void rtc_init(void) {
  logger_msg_p("rtc",log_level_INFO,
	       PSTR("Initializing rtc\r\n"));
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
  /* Wait for timer2 to settle.  It doesn't actually start counting
     for a while after the board is turned on.  So we'll compare its
     value against what we read from timer1 to see when it's counting
     normally.
  */
  uint8_t mscount = 0;
  uint16_t t1_topval = 10000; // What timer1 will count to
  OCR1AH = (uint8_t)(t1_topval >> 8);
  OCR1AL = (uint8_t)(t1_topval & 0xff);
  /* Specify how tightly the millisecond timer should match up with
     timer1.  The RC clock that sets the 1MHz clock for timer1 is
     pretty good, and 10000 timer1 counts should be 10 timer2 counts
     within 10 percent.
  */
  uint8_t lowlimit = (uint8_t)(t1_topval/1000 - 1);
  uint8_t highlimit = lowlimit + 2;

  while( (mscount < lowlimit) | (mscount > highlimit) ) {
    sound_counter_stop();
    sound_counter_zero(); // Zero counter and clear overflow flag
    TCNT2 = 0; // Reset timer2 with it still running
    sound_counter_start();
    /* Busy loop while timer1 counts to the output compare value
       t1_topval.  This should take t1_topval/1000 milliseconds. */
    loop_until_bit_is_set(TIFR1,OCF1A);
    /* The timer2 value after the busy loop will be too low until the
       counter warms up. */
    mscount = TCNT2;
  }
  logger_msg_p("rtc",log_level_INFO,
  		 PSTR("Expected 10ms, got %ims\r\n"),mscount);
} // End rtc_init

/* ms_counter()

   Returns the value of the millisecond counter.  Note that this is
   only 8 bits.

   Returns: uint8_t counter value (0-255)
*/
volatile uint8_t ms_counter(void) {
  uint8_t countval = TCNT2;
  return countval;
}

/* ms_delay( uint_16 duration_ms )
   
   Provides a delay by polling the ms_counter.

   Returns: The number of ms actually waited
*/
uint16_t ms_delay( uint16_t duration_ms ) {
  uint8_t old_ms = ms_counter();
  uint8_t new_ms = 0;
  uint16_t all_ms = 0;
  while ( all_ms < duration_ms ) {
    new_ms = ms_counter();
    if ( new_ms >= old_ms ) {
      all_ms += ( new_ms - old_ms );
      old_ms = new_ms; // Update the old value
    }
    else {
      all_ms += ( 0xff - old_ms + new_ms ); // We've rolled over
      old_ms = new_ms; // Update the old value
    }
  }// End delay while loop
  return all_ms;
} // End ms_delay


    
  
