/* bx_current.h

   Current output reporting module for boxcom
*/

#ifndef CURRENT_H
#define CURRENT_H


/* Calibration structure for current output

   The slope and offset coefficients will have pA units.
 */
typedef struct current_cal_struct {
    int16_t slope;
    int16_t offset;
} logger_system_t;

/* current init()

   Calls load_current_cal(pointer to cal structure) to fill in the cal
   structure members.

 */
void current_init(void);














#endif // End the include guard
