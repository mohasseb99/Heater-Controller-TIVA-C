#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <stdint.h>
#include "basic_io.h"
#include "DIO.h"
#include "lcd.h"
#include "delay.h"
#include "string.h"
#include <stdlib.h>
#include "led.h"
#include "pot.h"
#include "keypad.h"

void ADC_readMeasuredTemp(void *pvParameters);
void redTask( void *pvParameters);
void buzzerTask( void *pvParameters);
void KEYPAD_getkey(void *pvParameters);
void GPIOF_Handler (void);


int main(void)
{
	ADC0SS3_init();
	PORTF_init();
	LCD_init();
	keypad_Init(); //Initialize keypad and TM4C123 GPIO pins
	LCD_Cursor(0, 0);
	LCD_WriteString("Set Value=      ");
	LCD_Cursor(1, 0);
	LCD_WriteString("Measured Temp=");
  
	
	xMutexSetTemp = xSemaphoreCreateMutex();
	xBinarySemaphoreMeasuredTemp = xSemaphoreCreateBinary();
	vSemaphoreCreateBinary( xBinarySemaphoreKEYPAD );
	xBinarySemaphoreBuzzer = xSemaphoreCreateBinary();
	
	if( xBinarySemaphoreMeasuredTemp != NULL || xMutexSetTemp != NULL || xBinarySemaphoreBuzzer != NULL || xBinarySemaphoreKEYPAD != NULL){
		xTaskCreate( KEYPAD_getkey, "keypad get key", configMINIMAL_STACK_SIZE, NULL , 2, NULL );
		xTaskCreate( redTask, "Red Task", configMINIMAL_STACK_SIZE, NULL , 2, NULL );
		xTaskCreate( buzzerTask, "Buzzer Task", configMINIMAL_STACK_SIZE, NULL , 2, NULL );
		xTaskCreate( ADC_readMeasuredTemp, "ADC Measured Temp", configMINIMAL_STACK_SIZE, NULL , 1, NULL );
		vTaskStartScheduler(); 		
	}
    while(1)
    {
    }
}

/* keypad_getkey() function returns the value of key pressed by the user by traversing columns
and rows respectivley */
void KEYPAD_getkey(void *pvParameters){
	char value = '0';
	char i = 0;
	char j = 0;
	unsigned char total = 0;
	for(;;)
  {
		xSemaphoreTake( xBinarySemaphoreKEYPAD, portMAX_DELAY );
		LCD_Cursor(0, 10);
		LCD_WriteString("      ");
		LCD_Cursor(0, 10);
		total = 0;
		for(;;){
			for(i = 0; i < 4; i++)    //Scan columns loop
			{
				GPIO_PORTC_DATA_R = (1U << i+4);
				delay_milli(2);
				
				
				for(j = 0; j < 4; j++)  //Scan rows
				{
					if((GPIO_PORTE_DATA_R & 0x3C) & (1 << j+2)){
						value =  symbol[j][i];
						if(value == '.'){
							break;
						}						
						LCD_Data(value);
						value = value - '0';
						total = (total * 10) + value;
						while((GPIO_PORTE_DATA_R & 0x3C) & (1 << j+2)){}
					}
				}
				if(value == '.') break;
			}
			if(value == '.') {
				xSemaphoreTake( xMutexSetTemp, portMAX_DELAY );
				{
					setTemp = total;
				}
				xSemaphoreGive( xMutexSetTemp );
				value = '0';
				LCD_WriteString("    ");
				break;
			}
		}
  }
}


void ADC_readMeasuredTemp(void *pvParameters){
	unsigned int adc_value = 0;
	unsigned char measuredTemp = 0;
	unsigned char setTempValue;
	unsigned char state = 0;
	
	for(;;){
  	xSemaphoreTake( xMutexSetTemp, portMAX_DELAY );
		{
			setTempValue = (char)setTemp;
		}
		xSemaphoreGive( xMutexSetTemp );
		
		ADC0_PSSI_R |= (1<<3);        /* Enable SS3 conversion or start sampling data from AN2 */
		while((ADC0_RIS_R & 8) == 0) ;   /* Wait untill sample conversion completed*/
		adc_value = ADC0_SSFIFO3_R; /* read adc coversion result from SS3 FIFO*/
		measuredTemp = adc_value / 0x32;   // convert reading to temperature
		ADC0_ISC_R = 8;				/* clear coversion clear flag bit*/
		
		LCD_Cursor(1, 14);
		LCD_WriteNum((long int)measuredTemp);
		LCD_Data(' ');
		
		if(measuredTemp <= setTempValue && state == 1){
			state = 0;
			xSemaphoreGive( xBinarySemaphoreMeasuredTemp);
		}
		else if(measuredTemp > setTempValue && state == 0){
			state = 1;
			xSemaphoreGive( xBinarySemaphoreMeasuredTemp);
		}
		
		if(measuredTemp >= alarmTemp){
			xSemaphoreGive( xBinarySemaphoreBuzzer);
		}
		
	}
}



void redTask( void *pvParameters){
	GPIO_PORTF_DATA_R = (1<<1);
	for( ; ; )
	{
		/* used to take semaphore */
		xSemaphoreTake( xBinarySemaphoreMeasuredTemp, portMAX_DELAY );
		GPIO_PORTF_DATA_R ^= (1<<1);
	}
}

void buzzerTask( void *pvParameters){
	GPIO_PORTF_DATA_R &= ~(1<<3);
	for( ; ; )
	{
		/* used to take semaphore */
		xSemaphoreTake( xBinarySemaphoreBuzzer, portMAX_DELAY );
		GPIO_PORTF_DATA_R ^= (1<<3);
		vTaskDelay(250 / portTICK_PERIOD_MS);
		GPIO_PORTF_DATA_R ^= (1<<3);
		vTaskDelay(250 / portTICK_PERIOD_MS);
	}
}	


void GPIOF_Handler (void){
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR( xBinarySemaphoreKEYPAD, &xHigherPriorityTaskWoken );
	GPIO_PORTF_ICR_R |= 0x10; 
	while(!DIO_ReadPin(PORTF, 4)){}
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}
