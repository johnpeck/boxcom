/* bx_logger.c
   
   Functions for handling log messages. 
*/


// ----------------------- Include files ------------------------------

#include <stdio.h>
#include <string.h>
#include <stdarg.h> // Allows functions to accept an indefinite number
		    // of arguments
#include <stdint.h> // Defines uint8_t
#include "bx_logger.h"
#include "bx_usart.h"

/* pgmspace.h
 * Contains macros and functions for saving and reading data out of
 * flash.
 */
#include <avr/pgmspace.h>

/* bx_sound.h

   Provides functions for using the noisemaker.
*/
#include "bx_sound.h"


/* bx_command.h 

   Contains the definition of command_arg_t -- the data type used to
   hold arguments to functions executed by remote commands.
   
 */
#include "bx_command.h"

// Define a pointer to the logging configuration
log_config_t logger_config;
log_config_t *logger_config_ptr = &logger_config;

/* Define the recognized systems.  The freeform system name will need
 * to match calls to logger_msg() and logger_msg_p().  Group systems to
 * have shared bitshifts if you run out of space. 
 */
logger_system_t system_array[] ={
    // The logger system
    {"logger", // Name
    0 // Bitshift -- bit location in logging configuration bitfields
    },
    // The command system
    {"command",
    1
    },
    // The received character interrupt
    {"rxchar",
    2
    },
    // The ADC module
    {"adc",
    3
    },
    // The voltage measurement
    {"vmeasure",
    4
    },
    // Miscellaneous system functions
    {"functions",
    5
    },
    // The sound module
    {"sound",
     6
    },
    // The real time clock module (rtc)
    {"rtc",
     7
    },
    // The eeprom module
    {"eeprom",
     8
    },
    // The calibration module
    {"cal",
     9
    },
    // The output current measurement module
    {"current",
     10
    },
    // End of table indicator.  Must be last.
    {"",0}
};

// ----------------------- Functions ----------------------------------


/* Initialize the logger system:
 * Log messages above the "informational" level
 * All systems enabled for logging.
 */
void logger_init() {
    logger_config_ptr -> enable = 0xffff;  /* Logs from all systems enabled
                                            * by default. */
    logger_config_ptr -> loglevel = log_level_INFO;
}

/* Set the logging threshold level.
 */
void logger_setlevel( logger_level_t loglevel ) {
    logger_config_ptr -> loglevel = loglevel;
    logger_msg_p( "logger", log_level_INFO,
                 PSTR("Logging set to level %i\r\n"),loglevel);
}

/* Function called by the remote command "loglev"
 
   Sets the logger's loglevel member.  If no level matches the user's
   parameter, issue an error and leave the level as it was.
*/
void cmd_loglevel( command_arg_t *command_arg_ptr ) {
  uint16_t setval = command_arg_ptr -> uint16_arg;
  switch(setval) {
  case 0: logger_setlevel(log_level_ISR);
    break;
  case 1: logger_setlevel(log_level_INFO);
    break;
  case 2: logger_setlevel(log_level_WARNING);
    break;
  case 3: logger_setlevel(log_level_ERROR);
    break;
  default: logger_msg_p( "logger", log_level_ERROR,
			 PSTR("Log level %u is not recognized.\r\n"),setval);
  }
}



/* Function called by the remote command "logreg." 

   Sets the logger configuration enable byte directly.  You have to
   know which systems correspond to which bitshifts to make use of
   this.
 
*/
void cmd_logreg( command_arg_t *command_arg_ptr ) {
  logger_config_ptr -> enable = command_arg_ptr -> uint16_arg;
  logger_msg_p( "logger", log_level_INFO,
		PSTR("Logger enable register set to %u.\r\n"),
		command_arg_ptr -> uint16_arg );
}




/* Called by the remote command "logreg?" Returns the logger configuration
 * register value in hex.
 */
void cmd_logreg_q( command_arg_t *command_arg_ptr ) {
    usart_printf_p(PSTR("%u\r\n"),logger_config_ptr -> enable);
}

/* Set a bit in the logger configuration enable bitfield.  The system 
 * whose bitshift corresponds to that bit will then be enabled for
 * logging.
 */
void logger_setsystem( char *logsys ) {
    struct system_struct *system_array_ptr = system_array;
    // Go through all systems looking for a match to the system name
    while (strcmp( system_array_ptr -> name, "" ) != 0) {
        if (strcmp( logsys, system_array_ptr -> name ) == 0) {
            // We've found a matching system
            (logger_config_ptr -> enable) |= (1<< (system_array_ptr -> bitshift));
            logger_msg_p("logger", log_level_INFO, 
                PSTR("Now logging system %s\r\n"), system_array_ptr -> name);
            break;
        }
        system_array_ptr++;
    }
    return;
}

/* Clear all bits in the logger enable bitfield */
void logger_disable() {
    logger_config_ptr -> enable = 0;
    return;
}



/* logger_msg_p()

   Send a log message with a string located in flash memory. 
   Usage: logger_msg_p( system string (see system_array above),
                        log level (see logger_level_t),
			message format string, values for format string)
*/
void logger_msg_p( char *logsys, logger_level_t loglevel,
		   const char *logmsg, ... ) 
{
    va_list args; 
    char printbuffer[LOGGER_BUFFERSIZE]; 
    
    if (logger_config_ptr -> enable == 0) {
        // Logging has been disabled.  Nothing to do.
        return;
    }
    
    if (loglevel >= (logger_config_ptr -> loglevel)) {
        /* If this message's level is high enough to be logged, we send
	   it on to be filtered by system name. 
	*/
        va_start (args, logmsg); 
            /* Make sure messages are never longer than printbuffer */
            vsnprintf_P (printbuffer, LOGGER_BUFFERSIZE, logmsg, args); 
        va_end (args);
        logger_system_filter( logsys, loglevel, printbuffer );
    }
    return;
}

/* Decide if a message should be logged based on the logger configuration
 * and the message tag.  If it's enabled for logging, print: 
 * [The message severity] (The origin system) The message
 * 
 * Message severity tags:
 * [R] Interrupt service routine (ISR)
 * [I] Informational
 * [W] Warning
 * [E] Error
 */
void logger_system_filter( char *logsys, logger_level_t loglevel, char *logmsg ) {
  char sysname[LOGGER_BUFFERSIZE];
  struct system_struct *system_array_ptr = system_array;
  // Go through all systems looking for a match to the system name
  while (strcmp( system_array_ptr -> name, "" ) != 0) {
    if (strcmp( logsys, system_array_ptr -> name ) == 0) {
      // We've found a matching system
      if ((logger_config_ptr -> enable) & 
	  (1<< (system_array_ptr -> bitshift))) {
	/* The system is enabled for logging.  Send three strings
	 * to the logging device:
	 * 1. [Severity] 
	 * 1. (System name)
	 * 2. Log message */
	switch( loglevel ) {
	case log_level_ISR:
	  logger_output("[R]");
	  break;
	case log_level_INFO:
	  logger_output("[I]");
	  break;
	case log_level_WARNING:
	  sound_play_warn();
	  logger_output("[W]");
	  break;
	case log_level_ERROR:
	  sound_play_error();
	  logger_output("[E]");
	  break;    
	}
	snprintf(sysname,LOGGER_BUFFERSIZE,"(%s) ", system_array_ptr -> name);
	logger_output(sysname);
	logger_output(logmsg);
	break;
      }
    }
    system_array_ptr++;
  }
  return;
}

/* Send the final string to the output device.  Change this function to
 * suit whatever output device you'd like to use.
 */
void logger_output( char *logmsg ) {
    usart_printf("%s",logmsg);
}
