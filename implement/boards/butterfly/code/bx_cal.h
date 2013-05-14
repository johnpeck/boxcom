/* bx_cal.h

   Calibration management module for boxcom
*/
#ifndef CAL_H
#define CAL_H

/* bx_current.h

   Defines current_cal_t for the output current calibration.
*/
#include "bx_current.h"

/* bx_command.h 

   Contains the definition of command_arg_t -- the data type used to
   hold arguments to functions executed by remote commands.
   
 */
#include "bx_command.h"

/* calval_t

   Each calibration value will be composed of a signed and unsigned
   8-bit integer, along with an eeprom address.
*/
typedef struct calfactor_struct {
  int8_t sfactor; // The signed factor
  uint8_t ufactor; // The unsigned factor
  uint16_t address; // The eeprom address
} calfactor_t;




void cal_init(void);

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



#endif // End the include guard
