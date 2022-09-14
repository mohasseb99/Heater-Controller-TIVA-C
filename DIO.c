#include "DIO.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "LAB3.h"
#include "types.h"

void DIO_init(uint8 port,uint8 pin,uint8 dir)
{
  switch (port){
  case 0:
    Set_Bit(SYSCTL_RCGCGPIO_R,0);
    while(Get_Bit(SYSCTL_RCGCGPIO_R,0)==0){
    }
    Set_Bit(GPIO_PORTA_CR_R,pin);
    if(dir==1){
    Set_Bit(GPIO_PORTA_DIR_R,pin);
    }
    if(dir==0){
    Clear_Bit(GPIO_PORTA_DIR_R,pin);
    Set_Bit(GPIO_PORTA_PUR_R,pin);
    }
    Set_Bit(GPIO_PORTA_DEN_R,pin);
    break;
    
    case 1:
    Set_Bit(SYSCTL_RCGCGPIO_R,1);
    while(Get_Bit(SYSCTL_RCGCGPIO_R,1)==0){
    }
    Set_Bit(GPIO_PORTB_CR_R,pin);
    if(dir==1){
    Set_Bit(GPIO_PORTB_DIR_R,pin);
    }
    if(dir==0){
    Clear_Bit(GPIO_PORTB_DIR_R,pin);
    Set_Bit(GPIO_PORTB_PUR_R,pin);
    }
    Set_Bit(GPIO_PORTB_DEN_R,pin);
    break;
    
    case 2:
    Set_Bit(SYSCTL_RCGCGPIO_R,2);
    while(Get_Bit(SYSCTL_RCGCGPIO_R,2)==0){
    }
    GPIO_PORTC_LOCK_R=0x4C4F434B;
    Set_Bit(GPIO_PORTC_CR_R,pin);
    if(dir==1){
    Set_Bit(GPIO_PORTC_DIR_R,pin);
    }
    if(dir==0){
    Clear_Bit(GPIO_PORTC_DIR_R,pin);
    Set_Bit(GPIO_PORTC_PUR_R,pin);
    }
    Set_Bit(GPIO_PORTC_DEN_R,pin);
    break;
    
    case 3:  
    Set_Bit(SYSCTL_RCGCGPIO_R,3);
    while(Get_Bit(SYSCTL_RCGCGPIO_R,3)==0){
    }
    GPIO_PORTD_LOCK_R=0x4C4F434B;
    Set_Bit(GPIO_PORTD_CR_R,pin);
    if(dir==1){
    Set_Bit(GPIO_PORTD_DIR_R,pin);
    }
    if(dir==0){
    Clear_Bit(GPIO_PORTD_DIR_R,pin);
    Set_Bit(GPIO_PORTD_PUR_R,pin);
    }
    Set_Bit(GPIO_PORTD_DEN_R,pin);
    break;
    
    case 4:
    Set_Bit(SYSCTL_RCGCGPIO_R,4);
    while(Get_Bit(SYSCTL_RCGCGPIO_R,4)==0){
    }
    Set_Bit(GPIO_PORTE_CR_R,pin);
    if(dir==1){
    Set_Bit(GPIO_PORTE_DIR_R,pin);
    }
    if(dir==0){
    Clear_Bit(GPIO_PORTE_DIR_R,pin);
    Set_Bit(GPIO_PORTE_PUR_R,pin);
    }
    Set_Bit(GPIO_PORTE_DEN_R,pin);
    break;
    
    case 5:
    Set_Bit(SYSCTL_RCGCGPIO_R,5);
    while(Get_Bit(SYSCTL_RCGCGPIO_R,5)==0){
    }
    GPIO_PORTF_LOCK_R=0x4C4F434B;
    Set_Bit(GPIO_PORTF_CR_R,pin);
    if(dir==1){
    Set_Bit(GPIO_PORTF_DIR_R,pin);
    }
    if(dir==0){
    Clear_Bit(GPIO_PORTF_DIR_R,pin);
    Set_Bit(GPIO_PORTF_PUR_R,pin);
    }
    Set_Bit(GPIO_PORTF_DEN_R,pin);
    break;
    
  } 


}
void DIO_WritePin(uint8 port,uint8 pin, uint8 bitValue){
switch(port)
{
case PORTA:
  if(bitValue)
  {
    Set_Bit(GPIO_PORTA_DATA_R,pin);
  }
  else{
    Clear_Bit(GPIO_PORTA_DATA_R,pin);
  }
  break;
  
  case PORTB:
  if(bitValue)
  {
    Set_Bit(GPIO_PORTB_DATA_R,pin);
  }
  else{
    Clear_Bit(GPIO_PORTB_DATA_R,pin);
  }
  break;
  case PORTC:
  if(bitValue)
  {
    Set_Bit(GPIO_PORTC_DATA_R,pin);
  }
  else{
    Clear_Bit(GPIO_PORTC_DATA_R,pin);
  }
  break;
  case PORTD:
  if(bitValue)
  {
    Set_Bit(GPIO_PORTD_DATA_R,pin);
  }
  else{
    Clear_Bit(GPIO_PORTD_DATA_R,pin);
  }
  break;
  case PORTE:
  if(bitValue)
  {
    Set_Bit(GPIO_PORTE_DATA_R,pin);
  }
  else{
    Clear_Bit(GPIO_PORTE_DATA_R,pin);
  }
  break;
  case PORTF:
  if(bitValue)
  {
    Set_Bit(GPIO_PORTF_DATA_R,pin);
  }
  else{
    Clear_Bit(GPIO_PORTF_DATA_R,pin);
  }
  break;
  
}
}
void DIO_WritePort(uint8 port,uint8 bitValue){
  switch(port){
  case PORTA:
    GPIO_PORTA_DATA_R=bitValue;
    break;
    
    case PORTB:
    GPIO_PORTB_DATA_R=bitValue;
    break;
    
    case PORTC:
    GPIO_PORTC_DATA_R=bitValue;
    break;
    
    case PORTD:
    GPIO_PORTD_DATA_R=bitValue;
    break;
    
    case PORTE:
    GPIO_PORTE_DATA_R=bitValue;
    break;
    
    case PORTF:
    GPIO_PORTF_DATA_R=bitValue;
    break;
  }
}

uint8 DIO_ReadPin(uint8 port, uint8 pin){
  uint8 value;
  switch(port){
  case PORTA:
    value = Get_Bit(GPIO_PORTA_DATA_R, pin);
    break;
  case PORTB:
    value = Get_Bit(GPIO_PORTB_DATA_R, pin);
    break;
   case PORTC:
    value = Get_Bit(GPIO_PORTC_DATA_R, pin);
    break;
   case PORTD:
    value = Get_Bit(GPIO_PORTD_DATA_R, pin);
    break;
   case PORTE:
    value = Get_Bit(GPIO_PORTE_DATA_R, pin);
    break;
   case PORTF:
    value = Get_Bit(GPIO_PORTF_DATA_R, pin);
    break;
  }
  return value;
}
  

uint8 DIO_ReadPort(uint8 port){
  uint8 value;
  switch(port){
    
  case PORTA:
    value = GPIO_PORTA_DATA_R;
  case PORTB:
    value = GPIO_PORTB_DATA_R;
    case PORTC:
    value = GPIO_PORTC_DATA_R;
    case PORTD:
    value = GPIO_PORTD_DATA_R;
    case PORTE:
    value = GPIO_PORTE_DATA_R;
    case PORTF:
    value = GPIO_PORTF_DATA_R;
  }
    return value;

}