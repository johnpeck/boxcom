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

/* bx_eeprom.h
   
   Provides eeprom_write_char() and eeprom_read_char()
*/
#include "bx_eeprom.h"

/* bx_current.h

   Defines current_cal_t for the output current calibration.
*/
#include "bx_current.h"

/* bx_functions.h

   Defines system_state_t for the instrument serial number
*/
#include "bx_functions.h"





// --------------------- EEPROM addresses ----------------------------

/* Define the offset for general system variables. The eeprom has 512
   total locations.  I'll allocate addresses 0-99 for general system
   storage.
*/
/* The base address for the serial number.  The serial number is two
   bytes wide.  The next open address is 2.
*/
#define SERNUM_ADDR 0


/* Define the offset for each calibration coefficient in the array.
   I'll allocate addresses 100-200 for calibration factors.
*/
/* The base address for the current slope factor.  The slope occupies
   two locations. The next open address is 102.
*/
#define I_SLOPE_ADDR 100
/* The base address for the current offset factor.  The offset
   occupies two locations.  The next open address is 104.
*/
#define I_OFFSET_ADDR 102




// ----------------------- Functions ----------------------------------



/* cal_save_islope( current output slope calibrationa factor )

   Writes the current output slope calibration factor to eeprom.  The
   slope factor is a 16-bit unsigned integer with units of pA/count.

   The eeprom is organized into 8-bit bytes.  So we'll need two memory
   locations.

*/
void cal_save_islope(uint16_t slope){
  logger_msg_p( "cal", log_level_INFO,
		PSTR("Writing current slope value of %u\r\n"),slope);
  uint8_t lowbyte = (uint8_t)(slope & 0xff);
  uint8_t highbyte = (uint8_t)( (slope & 0xff00) >> 8);
  eeprom_write_char(I_SLOPE_ADDR,lowbyte);
  eeprom_write_char(I_SLOPE_ADDR + 1, highbyte);
}

/* cmd_write_islope( pointer to command argument structure )

   Function called by the remote command "$curslp."  Writes the
   current output slope calibration factor to a value supplied over
   the remote interface.
 */
void cmd_write_islope( command_arg_t *command_arg_ptr ) {
  uint16_t slope = (command_arg_ptr -> uint16_arg);
  cal_save_islope(slope);
  current_init();
}

/* cal_save_ioffset( current output offset calibration factor )

   Writes the current output offset calibration factor to eeprom.  The
   offset factor is a 16-bit signed integer with units of pA.

   The eeprom is organized into 8-bit bytes.  So we'll need two memory
   locations.
 */
void cal_save_ioffset(int16_t offset) {
  logger_msg_p( "cal", log_level_INFO,
		PSTR("Writing current offset value of %i\r\n"),offset);
  uint8_t lowbyte = (uint8_t)(offset & 0xff);
  uint8_t highbyte = (uint8_t)( (offset & 0xff00) >> 8);
  eeprom_write_char(I_OFFSET_ADDR,lowbyte);
  eeprom_write_char(I_OFFSET_ADDR + 1, highbyte);
}

/* cmd_write_ioffset( pointer to command argument structure )

   Function called by the remote command "$curoff."  Writes the
   current output slope calibration factor to a value supplied over
   the remote interface.
 */
void cmd_write_ioffset( command_arg_t *command_arg_ptr ) {
  int16_t offset = (command_arg_ptr -> sint16_arg);
  cal_save_ioffset(offset);
  current_init();
}


/* cal_load_current( pointer to current calibration structure )

   Loads the values for the current output calibration from eeprom.
 */
void cal_load_current( current_cal_t *current_cal ) {
  uint8_t lowbyte = eeprom_read_char(I_SLOPE_ADDR);
  uint8_t highbyte = eeprom_read_char(I_SLOPE_ADDR + 1);
  current_cal -> slope = (uint16_t)( (highbyte << 8) + lowbyte);
  lowbyte = eeprom_read_char(I_OFFSET_ADDR);
  highbyte = eeprom_read_char(I_OFFSET_ADDR + 1);
  current_cal -> offset = (int16_t)( (highbyte << 8) + lowbyte);
}


/* cal_save_sernum( instrument serial number )
 */
void cal_save_sernum( uint16_t sernum ) {
  logger_msg_p( "cal", log_level_INFO,
		PSTR("Writing serial number %u\r\n"),sernum);
  uint8_t lowbyte = (uint8_t)(sernum & 0xff);
  uint8_t highbyte = (uint8_t)( (sernum & 0xff00) >> 8);
  eeprom_write_char(SERNUM_ADDR,lowbyte);
  eeprom_write_char(SERNUM_ADDR + 1, highbyte);
}

/* cal_load_sernum( pointer to system status structure )

   Loads the serial number out of eeprom.
*/
void cal_load_sernum( system_state_t *sys_state ) {
  uint8_t lowbyte = eeprom_read_char(SERNUM_ADDR);
  uint8_t highbyte = eeprom_read_char(SERNUM_ADDR + 1);
  sys_state -> sernum = (uint16_t)( (highbyte << 8) + lowbyte );
  logger_msg_p( "cal", log_level_INFO,
		PSTR("Writing serial number of %u\r\n"),
		sys_state -> sernum);
}

/* Function called by the remote comand $setser
 
   Sets the instrument's serial number.
*/
void cmd_write_sernum( command_arg_t *command_arg_ptr ) {
  uint16_t sernum = (command_arg_ptr -> uint16_arg);
  cal_save_sernum(sernum);
  functions_init();
}
