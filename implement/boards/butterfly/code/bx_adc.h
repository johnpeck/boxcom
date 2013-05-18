/* bx_adc.h
   Used to set up the ADC for the boxcom project. */


/* ADC measurement calibration structure. 
 */
typedef struct adc_cal_struct { 
    uint16_t cal_slope; // Slope calibration factor
    uint16_t cal_offset; // Offset calibration factor
} adc_cal_t;

/* adc_init(void)
 * Initialize the Butterfly's 10-bit SAR ADC module.
 *     Set the default ADC mux position to 1: the voltage reader
 */
void adc_init(void);

/* adc_mux(uint8_t channel)
 * Set the ADCs input channel.
 */
void adc_mux(uint8_t channel);


/* adc_read(void)
 * Get a single 16-bit measurement from the currently selected ADC
 * channel.  The ADC has 10 bits of resolution.
 */
uint16_t adc_read(void);

/* Function called by the remote command "adcval?" 
   
   Query the raw ADC counts.
*/
void cmd_adcval_q(command_arg_t *command_arg_ptr );

