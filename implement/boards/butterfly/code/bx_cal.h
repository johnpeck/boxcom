/* bx_cal.h

   Calibration management module for boxcom
*/
#ifndef CAL_H
#define CAL_H



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











#endif // End the include guard
