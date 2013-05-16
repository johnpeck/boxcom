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

// ----------------------- Functions ----------------------------------

/* The current calibration
 */
current_cal_t current_cal;
current_cal_t *current_cal_ptr = &current_cal;

/* current status
 */
current_state_t current_state;
current_state_t *current_state_ptr = &current_state;

/* current_init()

   Calls load_current_cal(pointer to cal structure) to fill in the cal
   structure members.

 */
void current_init(void) {
  cal_load_current(current_cal_ptr);
  (current_state_ptr -> lastmeas) = 0;
  logger_msg_p("current",log_level_INFO,
	       PSTR("Current slope value is %u pA/count\r\n"),
	       (current_cal_ptr -> slope));
  logger_msg_p("current",log_level_INFO,
	       PSTR("Current offset value is %i pA\r\n"),
	       (current_cal_ptr -> offset));
}

/* current_process_array( array of raw data, number of averages )

   The array of raw data probably comes directly from the ADC.  Use
   the calibration values to turn them into currents in uA.

   The number of averages may be less than the size of the data array.
 */
void current_process_array( uint16_t *array, uint8_t averages ) {
  uint8_t shiftnum = bitshifts_max8(averages);
  uint16_t sum = 0;
  /* Average the array */
  for (uint8_t count = 0; count < (1 << shiftnum); count++) {
    sum += array[count];
  }
  sum >>= shiftnum;  // Make the average value of raw data

}