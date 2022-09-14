#include "keypad.h"

/* Keypad_Init() configures PORTC and PORTE to scan keypad keys */
void keypad_Init(void)
{
	SYSCTL_RCGCGPIO_R |= (1<<2) | (1<<4);        //Enable clock to PORTC and PORTE  
  while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be setted
  GPIO_PORTC_CR_R  |= 0xF0;             //Allow settings for all pins of PORTC
  GPIO_PORTE_CR_R  |= 0x3C;             //Allow settings for all pins of PORTE
  GPIO_PORTE_DIR_R &= ~(0x3C);             //PE2-PE5 are used with row and set them as digital input pins
  GPIO_PORTC_DIR_R |= (0xF0);             //PC4-PC7 are used with row and set them as digital output pins
	GPIO_PORTE_PDR_R |= 0x3C;          //Enable pull down resistor on PORTE
  GPIO_PORTC_DEN_R |= 0xF0;             //Set PORTC as digital pins
  GPIO_PORTE_DEN_R |= 0x3C;             //Set PORTE as digital pins
	
	// enable switch 1 on portf interrupt
	// if user press it it will make interrupt and give semaphore to keypad get key
	DIO_init(PORTF, 4, IN);
	GPIO_PORTF_IS_R &= ~0x10;
	GPIO_PORTF_IBE_R &= ~0x10;
	GPIO_PORTF_IEV_R &= ~0x10;
	GPIO_PORTF_ICR_R |= 0x10;
	GPIO_PORTF_IM_R |= 0x10;
	NVIC_PRI7_R = 6 << 21;
	NVIC_EN0_R |= 1<< 30;
	__enable_irq();
}
