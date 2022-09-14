#include "stdint.h"


// used to initialize lcd 
void LCD_init(void);

// used to send commands to lcd
void LCD_Cmd(unsigned char command);

// used to move cursor to specific location x -> row, y -> column 
void LCD_Cursor(char x, char y);

// used to write single char on lcd
void LCD_Data(unsigned char data);

// used to write string on lcd
void LCD_WriteString(char * str);

void LCD_WriteNum(long int print_val);
