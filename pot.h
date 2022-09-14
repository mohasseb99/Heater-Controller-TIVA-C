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


static const unsigned int alarmTemp = 70;


void ADC0SS3_init(void);
