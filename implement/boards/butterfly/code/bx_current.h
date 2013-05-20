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
*/
typedef struct current_state_struct {
  uint16_t period_ms; // Time between current samples in ms
  /* Most recent measurement.  Slope calibration factor is 16-bit, ADC
     value is 16-bit, so the result has to be 32.  And it has be
     signed, since calibration could make it negative.
   */
  int32_t lastmeas;
} current_state_t;

/* Extern declaration of current_state_ptr

   The current state pointer is defined inside the current module, but
   made available everywhere this header is included.
 */
extern current_state_t *current_state_ptr;

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


/* Command called by curout?
   
   Writes the latest value of the measured output current in uA
 */
void cmd_curout_q( command_arg_t *command_arg_ptr );

/* Function called by curper
 
   Writes a new value for the sample period to the current module
   status structure.
*/
void cmd_curper( command_arg_t *command_arg_ptr );



#endif // End the include guard
