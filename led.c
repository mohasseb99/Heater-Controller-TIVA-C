#include "led.h"




void PORTF_init(void){
	DIO_init(PORTF, 1, OUT);
	DIO_WritePin(PORTF, 1, 0);
	DIO_init(PORTF, 3, OUT);
	DIO_WritePin(PORTF, 3, 0);
}
