/* bx_rtc.h 

   Real Time Clock (RTC) module for boxcom
*/
#ifndef RTC_H
#define RTC_H


/* rtc_init()

   Configures timer2 to be clocked by the watch crystal.
*/
void rtc_init(void);

/* ms_counter()

   Returns the value of the millisecond counter.  Note that this is
   only 8 bits.

   Returns: uint8_t counter value (0-255)
*/
volatile uint8_t ms_counter(void);





/* ms_delay( uint_16 duration_ms )
   
   Provides a delay by polling the ms_counter.

   Returns: The number of ms actually waited
*/
uint16_t ms_delay( uint16_t duration_ms );





#endif // End the include guard
