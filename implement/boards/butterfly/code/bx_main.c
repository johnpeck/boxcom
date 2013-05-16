/* bx_main.c
   Main file for boxcom */



// ----------------------- Include files ------------------------------
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "bx_functions.h"
#include "bx_main.h"

/* bx_clock.h

   Provides fosc_1mhz() and fosc_8mhz() for setting the system clock.
*/
#include "bx_clock.h"

/* bx_command.h 

   Contains the extern declaration of command_array -- an array
   containing all the commands understood by the system.
   
   Defines the received command state structure recv_cmd_state_t.  Use
   this to keep track of the remote interface state. */
#include "bx_command.h"
#include "bx_usart.h"

/* pgmspace.h

   Contains macros and functions for saving and reading data out of
   flash.
*/
#include <avr/pgmspace.h>

/* bx_logger.h 

   Sets up logging  
*/
#include "bx_logger.h"

/* bx_adc.h 

   Provides functions for configuring and using the Butterfly's ADC
   module.
*/
#include "bx_adc.h"

/* bx_rtc.h

   Provides functions for working with the real time clock.
*/
#include "bx_rtc.h"

/* bx_sound.h

   Provides functions for using the noisemaker.
*/
#include "bx_sound.h"

/* bx_eeprom.h

   Provides functions for writing to and reading from the eeprom.
*/
#include "bx_eeprom.h"

/* bx_led.h

   Provides functions for turning the LED on and off.
*/
#include "bx_led.h"

/* bx_current.h

   Provides functions for measuring output current.
*/
#include "bx_current.h"


/* Set the measurement array size.

   As things are now, this will also be the number of readings to
   average to create an output datum.  But this size can grow
   independent of the number of averages.
*/
#define MEASUREMENT_ARRAY_SIZE 4

/* Set the period in milliseconds for things to happen in the main
   loop
 */
#define MAIN_LOOP_PERIOD_MS 1000

/* This array will hold measurements made in the main loop.
 */
uint16_t measurement_array[MEASUREMENT_ARRAY_SIZE];




// Define a pointer to the received command state
recv_cmd_state_t  recv_cmd_state;
recv_cmd_state_t *recv_cmd_state_ptr = &recv_cmd_state;






int main() {
  int retval = 0;
  sei(); // Enable interrupts
  /* Set up the system clock.  Do this before setting up the USART,
     as the USART depends on this for an accurate buad rate.
  */
  fosc_8mhz();
  /* Set up the USART before setting up the logger -- the logger uses
     the USART for output. 
  */
  usart_init(); // Sets 9.6k baud
  usart_76k8_baud(); // Sets 76.8k baud
  logger_init();
  /* To configure the logger, first clear the logger enable register
     by disabling it with logger_disable().  Then set individual bits
     with logger_setsystem().
  */
  logger_disable(); // Disable logging from all systems
  logger_setsystem( "logger" ); // Enable logger system logging
  logger_setsystem( "rxchar" ); // Enable received character logging
  logger_setsystem( "command" ); // Enable command system logging
  logger_setsystem( "adc" ); // Enable adc module logging
  logger_setsystem( "sound" ); // Enable sound module logging
  logger_setsystem( "rtc" ); // Enable real time clock module logging
  logger_setsystem( "eeprom" ); // Enable eeprom module logging
  logger_setsystem( "current" ); // Enable output current module logging
  logger_setsystem( "cal" ); // Enable calibration module logging
  adc_init(); // Set the ADCs reference and SAR prescaler
  adc_mux(4); // Set the ADC mux to channel 4
  sound_init(); // Start the sound module, using timer1
  rtc_init(); // Start the ms counter at timer2 (needs sound)
  command_init( recv_cmd_state_ptr );
  led_init();
  current_init();
  memset(measurement_array,0,MEASUREMENT_ARRAY_SIZE);
  /* Play a startup sound after all the init functions have been called. 
   */
  sound_play_startup();

  /* The main loop 
   
     Use the old_, new_, and all_ms variables to take care of pretty
     good timing.
  */
  uint8_t old_ms = 0;
  uint8_t new_ms = 0;
  uint16_t all_ms = 0; // The elapsed time in milliseconds
  uint16_t *meas_ptr = measurement_array;
  uint8_t meas_count = 0; // Incremented when measurement made
  for(;;) {
    /* Process the parse buffer to look for commands loaded with the
       received character ISR. 
    */
    process_pbuffer( recv_cmd_state_ptr, command_array );
    
    // Use this block for pretty good timing
    new_ms = ms_counter();
    if (new_ms >= old_ms) {
      all_ms += (new_ms - old_ms);
      old_ms = new_ms; // Update the old value
    }
    else {
      all_ms += ( 0xff - old_ms + new_ms); // We've rolled over
      old_ms = new_ms; // Update the old value
    }
    /* Choose the timing interval here.  A value of 1000 means that
       something will be done roughly every second.
    */
    if (all_ms >= MAIN_LOOP_PERIOD_MS) {
      /* Do something here */

      /*  Write to the measurement array.  We'll use this array to make
	  a moving average of the incoming data.
      */
      if (meas_count == (MEASUREMENT_ARRAY_SIZE)) {
      	meas_ptr = measurement_array;
	meas_count = 0;
      }
      
      *meas_ptr = adc_read(); // Make a measurement
      current_process_array( measurement_array, MEASUREMENT_ARRAY_SIZE );
      meas_count++;
      meas_ptr++;
     
      led_toggle();
      /* end of timed tasks */ 
      all_ms = 0;
    }
    else if (all_ms >= (0xffff - 100))
      all_ms = 0; // Don't let value overflow


    
    

  }// end main for loop
  return retval;
} // end main






/* -------------------------- Interrupts -------------------------------
 * Find the name of interrupt signals in iom169p.h and not pa.  Why
 * not?  We define the mcu name to be atmega169p in the makefile, not
 * atmega169pa. 
 * 
 * See the naming convention outlined at
 * http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
 * to make sure you don't use depricated names. 
 */
 

/* Interrupt on character received via the USART */
ISR(USART0_RX_vect) {
    // Write the received character to the buffer
    *(recv_cmd_state_ptr -> rbuffer_write_ptr) = UDR0;
    if (*(recv_cmd_state_ptr -> rbuffer_write_ptr) == '\r') {
        logger_msg_p("rxchar",log_level_ISR,
            PSTR("Received a command terminator.\r\n"));
        if ((recv_cmd_state_ptr -> rbuffer_count) == 0) {
            /* We got a terminator, but the received character buffer is
             * empty.  The user is trying to clear the transmit and
             * receive queues. */
            return;
        }
        else {
            if ((recv_cmd_state_ptr -> pbuffer_lock) == 1) {
                /* We got a terminator, and there are characters in the received
                 * character buffer, but the parse buffer is locked.  This is
                 * bad -- we're receiving commands faster than we can process
                 * them. */
                logger_msg_p("rxchar",log_level_ERROR,
                    PSTR("Command process speed error!\r\n"));
                rbuffer_erase(recv_cmd_state_ptr);
                return;
            }
            else {
                /* We got a terminator, and there are characters in the received
                 * character buffer.  The parse buffer is unlocked so terminate
                 * the received string and copy it to the parse buffer. */
                *(recv_cmd_state_ptr -> rbuffer_write_ptr) = '\0';
                strcpy((recv_cmd_state_ptr -> pbuffer),
                    (recv_cmd_state_ptr -> rbuffer));
                recv_cmd_state_ptr -> pbuffer_lock = 1;
                logger_msg_p("rxchar",log_level_ISR,
                    PSTR("Parse buffer contains '%s'.\r\n"),
                    (recv_cmd_state_ptr -> pbuffer));
                rbuffer_erase(recv_cmd_state_ptr);
                return;
            }
        }
    }
    else {
        // The character is not a command terminator.
        (recv_cmd_state_ptr -> rbuffer_count)++;
        logger_msg_p("rxchar",log_level_ISR,
            PSTR("%c  <-- copied to receive buffer.  Received count is %d.\r\n"),
            *(recv_cmd_state_ptr -> rbuffer_write_ptr),
            recv_cmd_state_ptr -> rbuffer_count);
        if ((recv_cmd_state_ptr -> rbuffer_count) >= (RECEIVE_BUFFER_SIZE-1)) {
            logger_msg_p("rxchar",log_level_ERROR,
                PSTR("Received character number above limit.\r\n"));
            rbuffer_erase(recv_cmd_state_ptr);
            return;
        }
        else {
            // Increment the write pointer
            (recv_cmd_state_ptr -> rbuffer_write_ptr)++;
        }
    }
    return;
}
