#include "pot.h"

void ADC0SS3_init(void){
		/* Enable Clock to ADC0 and GPIO pins*/
    SYSCTL_RCGCGPIO_R |= (1<<4);   /* Enable Clock to GPIOE or PE1/AN2 */
    SYSCTL_RCGCADC_R |= (1<<0);    /* AD0 clock enable*/
    
    /* initialize PE1 for \AIN2 input  */
    GPIO_PORTE_AFSEL_R |= (1<<1);       /* enable alternate function */
    GPIO_PORTE_DEN_R &= ~(1<<1);        /* disable digital function */
    GPIO_PORTE_AMSEL_R |= (1<<1);       /* enable analog function */
   
    /* initialize sample sequencer3 */
    ADC0_ACTSS_R &= ~(1<<3);        /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;    /* software trigger conversion */
    ADC0_SSMUX3_R = 2;         /* get input from channel 0 */
    ADC0_SSCTL3_R |= (1<<1)|(1<<2);        /* take one sample at a time, set flag at 1st sample */
   
	  ADC0_ACTSS_R |= (1<<3);         /* enable ADC0 sequencer 3 */
}







