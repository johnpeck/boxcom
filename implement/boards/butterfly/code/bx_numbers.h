/* bx_numbers.h
 
   Functions for handling numbers. */
#include <stdio.h>
 
/* asc2num()

   Converts an ascii character representing a hexadecimal number into
   its integer equivalent.  Accepts both upper and lower case
   characters.  

   Returns: 0 for non-numeric arguments. */
uint8_t asc2num(char n_asc);
    
/* hex2num() 

   Converts a string of ascii characters into a decimal by repeatedly
   calling asc2num(). */
uint16_t hex2num(char *hexstr);


/* uint2num( string representing unsigned integer )

   Converts a string of ascii characters into an integer.  Doesn't do
   any size checking.  If the number is larger than 65535, output will
   be undefined.
*/
uint16_t uint2num(char *uintstr);

/* sint2num( string representing signed integer )
 
   Converts a string of ascii characters into a signed integer.
   Doesn't do any size checking.  If the number is larger than 65535,
   output will be undefined.
*/
uint16_t sint2num(char *sintstr);
