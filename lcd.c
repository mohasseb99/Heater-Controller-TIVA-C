#include "lcd.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "delay.h"


void LCD_init(void){
	SYSCTL_RCGCGPIO_R |= 0x01; //PORTA clock
	SYSCTL_RCGCGPIO_R |= 0x02;
	GPIO_PORTA_DIR_R |=0xE0; //PORTA controls RS,E and R/W
	GPIO_PORTA_DEN_R |=0xE0;
	GPIO_PORTB_DIR_R |=0xFF; //PORTB D0-D7
	GPIO_PORTB_DEN_R |=0xFF; //PORTB D0-D7
	LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
	LCD_Cmd(0x06); //increments automatically
	LCD_Cmd(0x0F); //Turn on display
	LCD_Cmd(0x01); //clear display
	LCD_Cmd(0x80); //Takes cursor to beginning of first row 
}


void LCD_Cmd(unsigned char command){
	GPIO_PORTA_DATA_R = 0x00; //RS =0, E=0, RW=0
	GPIO_PORTB_DATA_R =command;
	GPIO_PORTA_DATA_R =0x80; //E=1 to secure command
	delay_milli(2);
	GPIO_PORTA_DATA_R =0x00;
	delay_milli(2);
}


void LCD_Cursor(char x, char y){
    if (x==0) {
        LCD_Cmd(0x80 + (y % 16));
        return;
    }
    LCD_Cmd(0xC0 + (y % 16));
}


void LCD_Data(unsigned char data) {
	GPIO_PORTA_DATA_R =0x20; //RS=1, E=0,RW=0
	GPIO_PORTB_DATA_R =data;
	GPIO_PORTA_DATA_R |= 0x80;
	GPIO_PORTA_DATA_R =0x00;
	delay_milli(2);
}


void LCD_WriteString(char * str){  
	volatile int i = 0;          //volatile is important 
	
	while(*(str+i) != '\0')       //until the end of the string
	{
		LCD_Data(*(str+i));    //Write each character of string
		i++;                        //increment for next character
	}
}

void LCD_WriteNum(long int print_val){
		uint16_t i=0,buff[20];
		if (print_val<0)
		{
			LCD_Data('-');
			print_val*=(-1);
		}
		int temp=print_val;
		for(i=0;print_val!=0;i++){
			buff[i]=temp%10;
			print_val=print_val/10;
			temp=print_val;
		}
		for(;i!=0;--i){
			LCD_Data(buff[i-1]+48);
		}	
}
