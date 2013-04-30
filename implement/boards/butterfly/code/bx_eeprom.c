/* bx_eeprom.c

   EEPROM module for boxcom

   The ATmega169PA contains 512 bytes of data EEPROM memory.  It is
   organized as a separate data space in which single bytes can be
   read and written.
*/

// ----------------------- Include files ------------------------------
#include <stdio.h>

/* avr/io.h
   
   Device-specific port definitions.  Also provides special
   bit-manipulations functions like bit_is_clear and
   loop_until_bit_is_set.
*/
#include <avr/io.h>

/* bx_logger.h

   Provides logger_msg and logger_msg_p for log messages tagged with a
   system and severity.
*/
#include "bx_logger.h"

/* pgmspace.h
   
   Provides macros and functions for saving and reading data out of
   flash.
*/
#include <avr/pgmspace.h>

/* avr/interrupt.h

   Provides sei() and cli() for enabling and disabling all interrupts.
 */
#include <avr/interrupt.h>

// ----------------------- Functions ----------------------------------

/* eeprom_write_char( address, data )

   Writes an 8-bit data value to an eeprom address.
*/
void eeprom_write_char( uint16_t address, uint8_t data ) {
  /* Disable all interrupts by clearing the global interrupt mask.
     Writing to the eeprom takes a long time (few ms).
   */
  cli();
  /* Wait for all writes to finish.  If the EEWE (eeprom write enable)
     bit in the EECR register is set, data is being written.
   */
  loop_until_bit_is_clear(EECR, EEWE);
  /* EEAR is the eeprom address register.  Even though there's 9 bits
     of address space, you can just write to the EEAR location. 
  */
  EEAR = address;
  EEDR = data;
  /* The EEMWE (eeprom master write enable bit) must be set before the
     eeprom-writing strobe EEWE can be set.  Furthermore, EEMWE will
     be cleared automatically in 4 cycles, so you can't just set it in
     an init function.
   */
  EECR |= _BV(EEMWE);
  EECR |= _BV(EEWE); // Write the data
  sei(); // Turn interrupts back on 
  logger_msg_p("eeprom",log_level_INFO,
	       PSTR("Wrote %i to address %i"),data,address);
}






