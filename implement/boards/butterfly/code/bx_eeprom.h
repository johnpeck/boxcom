/* bx_eeprom.h

   EEPROM module for boxcom
*/
#ifndef EEPROM_H
#define EEPROM_H



/* eeprom_write_char( address, data )

   Writes an 8-bit data value to an eeprom address.
*/
void eeprom_write_char( uint16_t address, uint8_t data );


/* eeprom_read_char( address )

   Reads an eeprom address.

   Returns: 8-bit unsigned integer
*/
uint8_t eeprom_read_char( uint16_t address );





















#endif // End the include guard
