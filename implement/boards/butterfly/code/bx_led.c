/* bx_led.c

   LED module for boxcom

   The Butterfly board has an LED soldered at PB4 (OC0 -- output
   compare for timer0.
*/
// ----------------------- Include files ------------------------------
#include <stdio.h>

/* avr/io.h
   
   Device-specific port definitions.  Also provides special
   bit-manipulations functions like bit_is_clear and
   loop_until_bit_is_set.
*/
#include <avr/io.h>



// ----------------------- Functions ----------------------------------

/* led_init()

   Sets the data direction of the LED pin to be an output.
*/
void led_init(void) {
  DDRB |= _BV(DDB4);
}



/* led_on()

   Turns the led on.
*/
void led_on(void) {
  PORTB |= _BV(PORTB4);
}

/* led_off()

   Turns the led off.
*/
void led_off(void) {
  PORTB &= ~(_BV(PORTB4));
}

/* led_toggle()

   Changes the led state.
*/
void led_toggle(void) {
  if ( bit_is_set(PORTB,PORTB4) )
    led_off();
  else
    led_on();
}
