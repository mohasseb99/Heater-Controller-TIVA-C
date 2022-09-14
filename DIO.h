#include "stdint.h"
#include "types.h"
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define IN 0
#define OUT 1

void DIO_init(uint8 port,uint8 pin,uint8 dir);
void DIO_WritePin(uint8 port,uint8 pin, uint8 bitValue);
void DIO_WritePort(uint8 port,uint8 bitValue);
uint8 DIO_ReadPin(uint8 port, uint8 pin);
uint8 DIO_ReadPort(uint8 port);