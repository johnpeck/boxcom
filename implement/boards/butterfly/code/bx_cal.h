/* bx_cal.h

   Calibration management module for boxcom
*/
#ifndef CAL_H
#define CAL_H

/* bx_current.h

   Defines current_cal_t for the output current calibration.
*/
#include "bx_current.h"

/* bx_functions.h
 
   Defines system_state_t for the overall system state.
*/
#include "bx_functions.h"

/* bx_command.h 

   Contains the definition of command_arg_t -- the data type used to
   hold arguments to functions executed by remote commands.
   
 */
#include "bx_command.h"


/* cal_save_islope( current output slope calibrationa factor )

   Writes the current output slope calibration factor to eeprom.  The
   slope factor is a 16-bit unsigned integer with units of pA/count.

   The eeprom is organized into 8-bit bytes.  So we'll need two memory
   locations.

*/
void cal_save_islope(uint16_t slope);


/* cal_save_ioffset( current output offset calibration factor )

   Writes the current output offset calibration factor to eeprom.  The
   offset factor is a 16-bit signed integer with units of pA.

   The eeprom is organized into 8-bit bytes.  So we'll need two memory
   locations.
 */
void cal_save_ioffset(int16_t offset);

/* cal_load_current( pointer to current calibration structure )

   Loads the values for the current output calibration from eeprom.
 */
void cal_load_current( current_cal_t *current_cal );

/* cmd_write_islope( pointer to command argument structure )

   Function called by the remote command "$curslp."  Writes the
   current output slope calibration factor to a value supplied over
   the remote interface.
 */
void cmd_write_islope( command_arg_t *command_arg_ptr );

/* cmd_write_ioffset( pointer to command argument structure )

   Function called by the remote command "$curoff."  Writes the
   current output slope calibration factor to a value supplied over
   the remote interface.
 */
void cmd_write_ioffset( command_arg_t *command_arg_ptr );


/* cal_save_sernum( instrument serial number )
 */
void cal_save_sernum( uint16_t sernum );

/* cal_load_sernum( pointer to system status structure )

   Loads the serial number out of eeprom.
*/
void cal_load_sernum( system_state_t *sys_state );

/* Function called by the remote comand $setser
 
   Sets the instrument's serial number.
*/
void cmd_write_sernum( command_arg_t *command_arg_ptr );



#endif // End the include guard
