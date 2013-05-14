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


void cal_save_islope(uint16_t slope);


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



#endif // End the include guard
