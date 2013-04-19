/* bx_sound.h 

   Sound module for boxcom
*/
#ifndef SOUND_H
#define SOUND_H





/* sound_init()

   Configures timer1 to be clocked by the system clock divided down to
   1MHz.  Sets Clear Timer on Compare match (CTC) mode to make square
   waves with OC1A.  Sets the OCR1A value, but leaves the data
   direction of OC1A set to input (DDB5 bit in the DDRB register set
   to 0).  When playing a tone, set a new OC1A value, then change the
   port data direction.
*/
void sound_init(void);

/* sound_counter_stop()

   Stops the counter used for the sound module (timer1).  Does not
   reset it.
*/
void sound_counter_stop(void);

/* sound_counter_start()

   Starts the counter used for the sound module (timer1).  Configures
   prescaler for a 1MHz clock.
*/
void sound_counter_start(void);

/* sound_counter_zero()
   
   Clears the counter used for the sound module (timer1).
 */
void sound_counter_zero(void);



/* sound_play_timed( frequency (Hz), duration (ms))

   Play a tone for the specified amount of time.  Timer1 is clocked at
   1MHz, so the maximum frequency is 1MHz/2 = 500kHz.  The minimum frequency is
   1MHz/(2 * 65536) = 7.6Hz.

   fout = 1MHz / (2 * (1 + OCR1A)) so
   OCR1A = 1MHz / (2 * fout) - 1
 */
void sound_play_timed( uint16_t frequency, uint16_t duration_ms );


/* sound_play_array_p( uint16_t array[] of frequencies in 100Hz) Each
   frequency point will be played for 1ms.  To play 100Hz for 1ms,
   have an array value of 1.

   Plays each element in the array for 1ms
*/
void sound_play_array_p( uint16_t *data_ptr );


void sound_play_startup(void);




#endif // End the include guard
