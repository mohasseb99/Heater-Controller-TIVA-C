#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include "basic_io.h"
#include "LAB3.h"
#include "delay.h"
#include "string.h"


#define HIGH 1
#define LOW 0
/* Defines the size of rows and columns of keypad */
#define  RowsSize  4
#define  ColsSize  4

/* Array of 4x4 to define characters which will be printe on specific key pressed */
static unsigned  char symbol[RowsSize][ColsSize] = {{ '1', '2',  '3', '+'},      
                                                { '4', '5',  '6', '-'},      
                                                { '7', '8',  '9', '*'},      
                                                { '.', '0',  '=', '/'}}; 

static xSemaphoreHandle xBinarySemaphoreKEYPAD;
static xSemaphoreHandle xMutexSetTemp;
static volatile int setTemp = 50;


void keypad_Init(void); /* Keypad initialization */