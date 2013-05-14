/* bx_functions.c

   Miscellaneous system functions for the boxcom project 
*/




// ----------------------- Include files ------------------------------
#include <stdio.h>
#include <string.h>

/* pgmspace.h
 * Contains macros and functions for saving and reading data out of
 * flash.
 */
#include <avr/pgmspace.h>
#include "bx_usart.h"


#include "bx_functions.h"

/* pgmspace.h
 * Contains macros and functions for saving and reading data out of
 * flash.
 */
#include <avr/pgmspace.h>

/* bx_logger.h 

   Sets up logging */
#include "bx_logger.h"



const char idnstr[] PROGMEM = "johnpeck,bx100,sn001,0.0.1\r\n";

// ----------------------- Functions ----------------------------------




/* cmd_idn_q( pointer to command argument structure )

   The function called by the "*IDN?" query
*/
void cmd_idn_q( command_arg_t *command_arg_ptr ) {
  usart_printf_p(idnstr);
}


void cmd_help( uint16_t nonval ) {
    print_help( command_array );
    return;
}

void print_help( command_t *command_array ) {
    while ((command_array -> execute) != 0) {
        usart_printf_p(command_array -> help);
        command_array++;
    }
    return;
}
