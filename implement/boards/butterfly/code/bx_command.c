/* bx_command.c */

// ----------------------- Include files ------------------------------
#include <stdio.h>
#include <string.h>

/* pgmspace.h

   Provides macros and functions for saving and reading data out of
   flash. */
#include <avr/pgmspace.h>


/* bx_command.h 
 
   Provides the extern declaration of command_array -- an array
   containing all the commands understood by the system. */
#include "bx_command.h"

/* bx_functions.h 

   Provides some sample functions for the command handler to call. */
#include "bx_functions.h"

/* bx_usart.h 

   Provides functions for transmitting characters over the usart. */
#include "bx_usart.h"

/* bx_ascii.h
 
   Provides lowstring() for converting strings to lower case. */
#include "bx_ascii.h"

/* bx_logger.h
 
   Provides logger_msg and logger_msg_p for log messages tagged with a
   system and severity. */
#include "bx_logger.h"

/* bx_numbers.h

   Provides ascii to number conversion. */
#include "bx_numbers.h"

/* bx_adc.h
 
   Provides functions for calibrating and returning ADC
   measurements. */
#include "bx_adc.h"

/* bx_cal.h

   Provides cmd_write_islope()
*/
#include "bx_cal.h"

/* bx_current.h

   Provides functions for measuring output current.
*/
#include "bx_current.h"




/* Initialize command help strings.
 
   The help text for each command needs to be defined outside of the
   rest of the command array initialization.  I don't know another way
   to keep the text from being copied into RAM.  There's probably a
   better way to do this.
 
*/
const char helpstr_idn[] PROGMEM = 
    "*IDN? -- Print instrument identifier.\r\n"
    "    Argument: None\r\n"
    "    Return: Identification string\r\n";

const char helpstr_loglevel[] PROGMEM =
    "loglevel -- Set the logger severity level.\r\n"
    "    Argument: 0-3\r\n"
    "    Return: None\r\n";

const char helpstr_logreg[] PROGMEM =
    "logreg -- Set the logger enable register.\r\n"
    "    Argument: 16-bit unsigned hex number\r\n"
    "    Return: None\r\n";

const char helpstr_logreg_q[] PROGMEM =
    "logreg? -- Query the logger enable register.\r\n"
    "    Argument: None\r\n"
    "    Return: 16-bit unsigned hex number\r\n";

const char helpstr_adcval_q[] PROGMEM =
    "$adcval? -- Query the raw ADC counts.\r\n"
    "    Argument: None\r\n"
    "    Return: 16-bit unsigned hex number\r\n";

const char helpstr_volt_q[] PROGMEM =
    "volt? -- Query the calibrated voltage measurement.\r\n"
    "    Argument: None\r\n"
    "    Return: Voltage in millivolts\r\n";

const char helpstr_curslp[] PROGMEM =
  "$curslp -- Set the current slope value.\r\n"
  "    Argument: 16-bit unsigned integer\r\n"
  "    Return: None\r\n";

const char helpstr_curoff[] PROGMEM =
  "$curoff -- Set the current offset value.\r\n"
  "    Argument: 16-bit signed integer.\r\n"
  "    Return: None\r\n";

const char helpstr_setser[] PROGMEM =
  "$setser -- Set the serial number.\r\n"
  "    Argument: 16-bit unsigned integer.\r\n"
  "    Return: None\r\n";

const char helpstr_curout[] PROGMEM =
  "curout? -- Query the output current in uA.\r\n"
  "    Argument: None\r\n"
  "    Return: integer current in uA\r\n";

const char helpstr_curper[] PROGMEM =
  "curper -- Set the sampling period in ms.\r\n"
  "    Argument: 16-bit unsigned integer.\r\n"
  "    Return: None\r\n";

const char helpstr_help[] PROGMEM =
    "help -- Print the command help.\r\n";

const char nullstr[] PROGMEM = "";

/* Define the remote commands recognized by the system.
 */
command_t command_array[] ={
  // *IDN? -- Print the instrument identification string.
  {"*idn?",           // Name of the command
   "none",            // Argument type (can be "none" or "hex" right now)
   0,                 // Maximum number of characters in argument
   &cmd_idn_q,        // Address of function to execute
   helpstr_idn},      // The help text (defined above)
  //loglev -- Set the logger severity level.
  {"loglev",
   "uint16",
   1,
   &cmd_loglevel,
   helpstr_loglevel},
  // logreg -- Set the logger enable register.
  {"logreg",
   "uint16",
   4,
   &cmd_logreg,
   helpstr_logreg},
  // logreg? -- Query the logger enable register.
  {"logreg?",
   "none",
   0,
   &cmd_logreg_q,
   helpstr_logreg_q},
  // $adcval? -- Query the raw ADC counts
  {"$adcval?",
   "none",
   0,
   &cmd_adcval_q,
   helpstr_adcval_q},
  // $curslp -- Write the output current slope value
  {"$curslp",
   "uint16",
   5,
   &cmd_write_islope,
   helpstr_curslp},
  // $curoff -- Write the output current offset value
  {"$curoff",
   "sint16",
   5,
   &cmd_write_ioffset,
   helpstr_curoff},
  // curout? -- Query the output current
  {"curout?",
   "none",
   0,
   &cmd_curout_q,
   helpstr_curout},
  // curper -- Set the period between current measurements
  {"curper",
   "uint16",
   4,
   &cmd_curper,
   helpstr_curper},
  // $setser -- Set the serial number
  {"$setser",
   "uint16",
   4,
   &cmd_write_sernum,
   helpstr_setser},
  // help -- Print all the help strings
  {"help",
   "none",
   0,
   &cmd_help,
   helpstr_help},
  // End of table indicator.  Must be last.
  {"","",0,0,nullstr}
};

/* Declare a structure to hold function arguments
 */
command_arg_t command_arg;
command_arg_t *command_arg_ptr = &command_arg;





// ----------------------- Functions ----------------------------------


/* command_init( received command state pointer ) 

   Making this function explicitly take a pointer to the received
   command state structure makes it clear that it modifies this
   structure.
 
*/
void command_init( recv_cmd_state_t *recv_cmd_state_ptr ) {
    memset((recv_cmd_state_ptr -> rbuffer),0,RECEIVE_BUFFER_SIZE);
    recv_cmd_state_ptr -> rbuffer_write_ptr =
        recv_cmd_state_ptr -> rbuffer; // Initialize write pointer
    memset((recv_cmd_state_ptr -> pbuffer),0,RECEIVE_BUFFER_SIZE);
    recv_cmd_state_ptr -> pbuffer_arg_ptr =
        recv_cmd_state_ptr -> pbuffer; // Initialize argument pointer
    recv_cmd_state_ptr -> rbuffer_count = 0;
    recv_cmd_state_ptr -> pbuffer_lock = 0; // Parse buffer unlocked
    return;
}


/* check_argsize( pointer to received command state,
 *                pointer to list of commands )
 * Returns 0 if the argument size is less than or equal to the number
 * of characters specified in the command list.  Returns -1 otherwise. 
 */
uint8_t check_argsize(recv_cmd_state_t *recv_cmd_state_ptr ,
                      struct command_struct *command_array) {
    uint8_t isok = 0;
    uint8_t argsize = strlen(recv_cmd_state_ptr -> pbuffer_arg_ptr);
    logger_msg_p("command",log_level_INFO,
        PSTR("Argument size is %d.\r\n"), argsize);
    if (argsize > (command_array -> arg_max_chars)) {
        isok = -1;
    }
    return isok;
}

void rbuffer_erase( recv_cmd_state_t *recv_cmd_state_ptr ) {
    memset((recv_cmd_state_ptr -> rbuffer),0,RECEIVE_BUFFER_SIZE);
    recv_cmd_state_ptr -> rbuffer_write_ptr =
        recv_cmd_state_ptr -> rbuffer; // Initialize write pointer
    recv_cmd_state_ptr -> rbuffer_count = 0;
    return;
}

/* process_pbuffer( recv_cmd_state_t *recv_cmd_state_ptr,
   command_struct *commands )
   
   Process the command (if there is one) in the parse buffer. 
*/
void process_pbuffer( recv_cmd_state_t *recv_cmd_state_ptr ,
		      struct command_struct *command_array) {
  if ((recv_cmd_state_ptr -> pbuffer_lock) == 1) {
    // Parse buffer is locked -- there's a command to process
    logger_msg_p("command",log_level_INFO,
		 PSTR("The parse buffer is locked.\r\n"));
    recv_cmd_state_ptr -> pbuffer_arg_ptr = 
      strchr(recv_cmd_state_ptr -> pbuffer,' ');
    if (recv_cmd_state_ptr -> pbuffer_arg_ptr != NULL) {
      // Parse buffer contains a space -- there's an argument
      logger_msg_p("command",log_level_INFO,
		   PSTR("The command contains a space.\r\n"));
      // Terminate the command string
      *(recv_cmd_state_ptr -> pbuffer_arg_ptr) = '\0'; // Terminate the command string
      (recv_cmd_state_ptr -> pbuffer_arg_ptr)++;
      while (*(recv_cmd_state_ptr -> pbuffer_arg_ptr) == ' ') {
	// Move to first non-space character
	(recv_cmd_state_ptr -> pbuffer_arg_ptr)++;
      }
      // pbuffer_arg_ptr now points to the beginning of the argument
      logger_msg_p("command",log_level_INFO,
		   PSTR("The command's argument is '%s'.\r\n"),
		   (recv_cmd_state_ptr -> pbuffer_arg_ptr));
    }
    lowstring(recv_cmd_state_ptr -> pbuffer); // Convert command to lower case
    // Look through the command list for a match
    uint8_t pbuffer_match = 0;
    while ((command_array -> execute) != 0) {
      if (strcmp( recv_cmd_state_ptr -> pbuffer,
		  command_array -> name ) == 0) {
	// We've found a matching command
	logger_msg_p("command",log_level_INFO,
		     PSTR("Command '%s' recognized.\r\n"),command_array -> name);
	pbuffer_match = 1;
	if (strcmp( command_array -> arg_type, "none") != 0) {
	  // The command is specified to have an argument
	  uint8_t arg_ok = check_argsize(recv_cmd_state_ptr,command_array);
	  if (arg_ok != 0) {
	    logger_msg_p("command",log_level_ERROR,
			 PSTR("Argument to '%s' is out of range.\r\n"),
			 command_array -> name);
	  }
	  else {
	    // The argument is the right size
	    logger_msg_p("command",log_level_INFO,
			 PSTR("Argument to '%s' is within limits.\r\n"),
			 command_array -> name);
	    command_exec(command_array,recv_cmd_state_ptr -> pbuffer_arg_ptr,
			 command_arg_ptr);
	  }
	}
	else  {
	  // There's no argument specified
	  if (recv_cmd_state_ptr -> pbuffer_arg_ptr != NULL) {
	    // There's an argument, but we didn't expect one
	    logger_msg_p("command",log_level_WARNING,
			 PSTR("Ignoring argument for command '%s'.\r\n"),
			 command_array -> name);
	  }
	  command_exec(command_array,NULL,command_arg_ptr);
	}
	recv_cmd_state_ptr -> pbuffer_lock = 0;
	break;
      }
      command_array++;
    }
    // If we didn't find a match, send an error message
    if (pbuffer_match == 0) {
      logger_msg_p("command",log_level_ERROR,
		   PSTR("Unrecognized command: '%s'.\r\n"),
		   recv_cmd_state_ptr -> pbuffer);
      recv_cmd_state_ptr -> pbuffer_lock = 0;
    }
  }
  return;
}


/* command_exec( remote command string, argument string,
                 command argument structure pointer )

   Execute a valid command received over the remote interface.  The
   command's arguments simply come in as strings.  The command's
   definition sets the argument type.  This function matches a string
   to that argument type string to figure out how to convert the
   argument string to a number.
*/
void command_exec( command_t *command, char *argument, 
		   command_arg_t *command_arg_ptr ) {
  if (strcmp( command -> arg_type,"none" ) == 0) {
    // There's no argument
    logger_msg_p("command",log_level_INFO,
		 PSTR("Executing command with no argument.\r\n"));
    command -> execute(command_arg_ptr);
  }
  else if (strcmp( command -> arg_type,"hex16" ) == 0) {
    // There's a hex argument
    logger_msg_p("command",log_level_INFO,
		 PSTR("Executing command with hex argument.\r\n"));
    command_arg_ptr -> uint16_arg = hex2num(argument);

    logger_msg_p("command",log_level_INFO,
		 PSTR("The argument value is %u.\r\n"),
		 command_arg_ptr -> uint16_arg);

    command -> execute(command_arg_ptr);
  }
  else if (strcmp( command -> arg_type,"uint16" ) == 0) {
    // There's a unsigned 16-bit integer argument
    logger_msg_p("command",log_level_INFO,
		 PSTR("Executing command with unsigned int argument.\r\n"));
    command_arg_ptr -> uint16_arg = uint2num(argument);
    command -> execute(command_arg_ptr);
  }
  else if (strcmp( command -> arg_type,"sint16" ) == 0) {
    // There's a signed 16-bit integer argument
    logger_msg_p("command",log_level_INFO,
		 PSTR("Executing command with signed int argument.\r\n"));
    command_arg_ptr -> sint16_arg = sint2num(argument);
    command -> execute(command_arg_ptr);
  }
  /* If we've reached the end, we haven't found a match for the
     command's argument type.  That's an error.
   */
  else {
    logger_msg_p("command",log_level_ERROR,
		 PSTR("No handler specified for %s argument.\r\n"),
		 command -> arg_type);
  }
}

