/* bx_current.h

   Current output reporting module for boxcom
*/

#ifndef CURRENT_H
#define CURRENT_H


/* Calibration structure for current output

   The slope and offset coefficients will have pA units.  The slope
   value will always be positive, but the offset may be negative.
 */
typedef struct current_cal_struct {
    uint16_t slope;
    int16_t offset;
} current_cal_t;

/* current init()

   Calls load_current_cal(pointer to cal structure) to fill in the cal
   structure members.

*/
void current_init(void);














#endif // End the include guard
