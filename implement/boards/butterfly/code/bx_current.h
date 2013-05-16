/* bx_current.h

   Current output reporting module for boxcom
*/

#ifndef CURRENT_H
#define CURRENT_H


/* Calibration structure for current output

   The slope and offset coefficients will have pA units.  The slope
   value will always be positive, but the offset may be negative.
*/
typedef struct current_cal_struct {
  uint16_t slope;
  int16_t offset;
} current_cal_t;



/* Structure containing the state of the current module

   Contains:
     Most recent measurement
 */
typedef struct current_state_struct {
  uint16_t lastmeas;
} current_state_t;


/* current init()

   Calls load_current_cal(pointer to cal structure) to fill in the cal
   structure members.

*/
void current_init(void);





/* current_process_array( array of raw data, number of averages )

   The array of raw data probably comes directly from the ADC.  Use
   the calibration values to turn them into currents in uA.

   The number of averages may be less than the size of the data array.
 */
void current_process_array( uint16_t *array, uint8_t averages );








#endif // End the include guard
