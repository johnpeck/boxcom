/* bx_led.h

   LED module for boxcom
*/
#ifndef LED_H
#define LED_H


/* led_init()

   Sets the data direction of the LED pin to be an output.
*/
void led_init(void);


/* led_on()

   Turns the led on.
*/
void led_on(void);


/* led_off()

   Turns the led off.
*/
void led_off(void);


/* led_toggle()

   Changes the led state.
*/
void led_toggle(void);







#endif // End the include guard
