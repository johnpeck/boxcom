/* bx_cal.c

   Calibration management module for boxcom

   This will provide a central place for all calibration factors.
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

/* Define the offset for each calibration coefficient in the array
 */
#define TEST_OFF_LOW 0
#define END_OF_CALARRAY 1

uint8_t cal_array[END_OF_CALARRAY]; 




// ----------------------- Functions ----------------------------------

/* cal_init()

   Read cal elements out of eeprom
*/
void cal_init(void) {
  memset(cal_array,0,END_OF_CALARRAY);
  return;
}
