/* bx_current.c

   Output current reporting module for boxcom

   The Butterfly board gets output current information from the USB
   board via ADC channel 4.  The ADC module should be initialized and
   the channel set to 4 before current output results will be
   accurate.

*/

// ----------------------- Include files ------------------------------


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

/* bx_usart.h

   Provides usart_printf.
*/
#include "bx_usart.h"

/* bx_cal.h

   Provides functions to supply calibration factors.
*/
#include "bx_cal.h"

/* bx_adc.h 

   Provides functions for configuring and using the Butterfly's ADC
   module.
*/
#include "bx_adc.h"

/* bx_numbers.h

   Provides bitshifts_max8 to get the bit shifts in a number.
*/
#include "bx_numbers.h"

#include "bx_current.h"




// ----------------------- Globals ------------------------------------

/* The current calibration
 */
current_cal_t current_cal;
current_cal_t *current_cal_ptr = &current_cal;

/* current status structrue

   Keeps track of the current module status:
   -- Sample period
   -- Most recent measurement
 */
current_state_t current_state;
current_state_t *current_state_ptr = &current_state;





// ----------------------- Functions ----------------------------------


/* current_init()

   Calls load_current_cal(pointer to cal structure) to fill in the cal
   structure members.

 */
void current_init(void) {
  cal_load_current(current_cal_ptr);
  current_state_ptr -> period_ms = 100;
  current_state_ptr -> lastmeas = 0;
  logger_msg_p("current",log_level_INFO,
	       PSTR("Current slope value is %u nA/count\r\n"),
	       (current_cal_ptr -> slope));
  logger_msg_p("current",log_level_INFO,
	       PSTR("Current offset value is %i uA\r\n"),
	       (current_cal_ptr -> offset));
}

/* current_process_array( array of raw data, number of averages )

   The array of raw data probably comes directly from the ADC.  Use
   the calibration values to turn them into currents in uA.

   The number of averages may be less than the size of the data array.
 */
void current_process_array( uint16_t *array, uint8_t averages ) {
  /* Get the bitshifts in the 8-bit number */
  uint8_t shiftnum = bitshifts_max8(averages);
  uint16_t sum = 0;
  for (uint8_t count = 0; count < (1 << shiftnum); count++) {
    sum += array[count];
  }
  /* I want to keep 2 extra bits in the number for better averaging.
     Divide the sum by a factor of 4 less than the number of data
     points to make the average.
   */
  if (shiftnum >= 2) {
    shiftnum -= 2;
  }
  sum >>= shiftnum;  // Make the average value of raw data
  /* Calculate calibrated uA from raw ADC counts:
     
     Slope and offset calibration factors are in nA/count and nA, so
     the 1mA constant has to be expressed in nA.

     (( adcval * slope - 1mA ) >> 10 ) + offset
  */

  current_state_ptr -> lastmeas = 
    ((( (int32_t)sum * current_cal_ptr -> slope ) - 1000000 ) >> 10) +
    current_cal_ptr -> offset;

}

/* Function called by curout?
   
   Writes the latest value of the measured output current in uA
 */
void cmd_curout_q( command_arg_t *command_arg_ptr ) {
  usart_printf_p( PSTR("%li\r\n"), current_state_ptr -> lastmeas);
}

/* Function called by curper
 
   Writes a new value for the sample period to the current module
   status structure.
*/
void cmd_curper( command_arg_t *command_arg_ptr ) {
  current_state_ptr -> period_ms = command_arg_ptr -> uint16_arg;
}
