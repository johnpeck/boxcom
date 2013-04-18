/* bx_sound.c

   Sound module for boxcom

   The piezo noisemaker on the Butterfly board is connected to PB5,
   which is also OC1A.  So it's natural to use timer1 to do waveform
   generation for making sound.
*/

// ----------------------- Include files ------------------------------
#include <stdio.h>

/* avr/io.h
   
   Device-specific port definitions
*/
#include <avr/io.h>

/* bx_rtc.h

   Provides functions for working with the real time clock.
*/
#include "bx_rtc.h"

/* bx_logger.h

   Provides logger_msg and logger_msg_p for log messages tagged with a
   system and severity.
*/
#include "bx_logger.h"

/* pgmspace.h
  
   Contains macros and functions for saving and reading data out of
   flash.
*/
#include <avr/pgmspace.h>

#include "bx_sound.h"


// ----------------------- Functions ----------------------------------

/* sound_init()

   Configures timer1 to be clocked by the system clock divided down to
   1MHz.  Sets Clear Timer on Compare match (CTC) mode to make square
   waves with OC1A.  Sets the OCR1A value, but leaves the data
   direction of OC1A set to input (DDB5 bit in the DDRB register set
   to 0).  When playing a tone, set a new OC1A value, then change the
   port data direction.
*/
void sound_init(void) {
  logger_msg_p("sound",log_level_INFO,
	       PSTR("Initializing sound\r\n"));
  /* Set TCCR1B (timer/counter control register B) value

     Set the clock source to internal, fosc/8 (for fosc=8MHz)
     Set CTC mode
   */
  TCCR1B &= ~(_BV(CS12) | _BV(CS10));
  TCCR1B |= _BV(CS11);
  TCCR1B &= ~_BV(WGM13);
  TCCR1B |= _BV(WGM12);

  /* Set TCCR1A (timer/counter control register A) value

     Toggle OC1A on compare match
     Set CTC mode
   */
  TCCR1A &= ~_BV(COM1A1);
  TCCR1A |= _BV(COM1A0);
  TCCR1A &= ~(_BV(WGM11) | _BV(WGM10));

  /* Set initial value for OCR1A (16-bit value) */
  OCR1AH = 0;
  OCR1AL = 0;
}


/* sound_counter_stop()

   Stops the counter used for the sound module (timer1).  Does not
   reset it.
*/
void sound_counter_stop(void) {
  // Set all CS values to 0 to remove clock source -- stoping counter
  TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
}

/* sound_counter_start()

   Starts the counter used for the sound module (timer1).  Configures
   prescaler for a 1MHz clock.
*/
void sound_counter_start(void) {
  TCCR1B &= ~(_BV(CS12) | _BV(CS10));
  TCCR1B |= _BV(CS11);
}


/* sound_play_timed( frequency (Hz), time (ms))

   Play a tone for the specified amount of time.  Timer1 is clocked at
   1MHz, so the maximum frequency is 1MHz/2 = 500kHz.  The minimum frequency is
   1MHz/(2 * 65536) = 7.6Hz.

   fout = 1MHz / (2 * (1 + OCR1A)) so
   OCR1A = 1MHz / (2 * fout) - 1
 */
void sound_play_timed( uint8_t frequency, uint16_t duration_ms ) {
  /* Use the old_, new_, and all_ms variables to take care of pretty
     good timing.
   */
  sound_counter_stop();
  TCNT1H = 0;
  TCNT1L = 0;
  DDRB |= _BV(DDB5); // Make PB5 (OCR1A) an output
  uint16_t compval = 0; // Will be the output compare value
  compval = (uint16_t) (1e6 / (2 * frequency)) - 1;
  logger_msg_p("sound",log_level_INFO,
	       PSTR("Compare value is %i\r\n"),compval);
  OCR1AH = (uint8_t)(compval >> 8);
  OCR1AL = (uint8_t)(compval & 0xff);
  sound_counter_start();

  
  // Busy loop for the specified duration
  uint16_t retval = ms_delay( duration_ms );
  logger_msg_p("sound",log_level_INFO,
	       PSTR("Played for %i ms\r\n"),retval);
  sound_counter_stop();
  //DDRB &= ~(_BV(DDB5)); // Make PB5 (OCR1A) and input, stopping the sound
  
}

     
