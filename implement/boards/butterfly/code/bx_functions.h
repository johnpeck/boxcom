/* bx_functions.h
   
   Miscellaneous functions for the boxcom project 
*/
#ifndef FUN_H
#define FUN_H

/* bx_command.h 

   Contains the definition of command_t -- the variable type containing
   the attributes of each remote command. */
#include "bx_command.h"


/* Structure containing miscellaneous system state variables
 
   -- Serial number
*/
typedef struct system_status_struct {
  uint16_t sernum;
} system_state_t;


/* Function called by help

   Writes all the help strings to the remote interface.
*/
void cmd_help( command_arg_t *command_arg_ptr );

/* print_help()
 * Called by cmd_help().  Prints the help strings for all recognized
 * commands.
 */
void print_help(command_t *command_array);

/* cmd_idn_q( pointer to command argument structure )

   The function called by the "*IDN?" query
*/
void cmd_idn_q( command_arg_t *command_arg_ptr );

/* functions_init()

   Calls cal_load_sernum(pointer to system status structure) to fill
   in the serial number.
*/
void functions_init(void);

#endif // End the include guard
