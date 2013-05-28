/* bx_functions.h
   Sample functions for the boxcom project */

/* bx_command.h 

   Contains the definition of command_t -- the variable type containing
   the attributes of each remote command. */
#include "bx_command.h"

/* Calibration structure */
struct cal_struct {
    uint8_t slope; // Measurements are multiplied by this factor
		   // before offset
    uint8_t offset; // Measurements are offset by this factor after
		    // slope is applied
};



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
