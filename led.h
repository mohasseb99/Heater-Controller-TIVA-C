#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <stdint.h>
#include "basic_io.h"
#include "DIO.h"
#include "delay.h"
#include "string.h"
#include <stdlib.h>

static xSemaphoreHandle xBinarySemaphoreMeasuredTemp;
static xSemaphoreHandle xBinarySemaphoreBuzzer;
static xSemaphoreHandle xMutexSetTemp;

void PORTF_init(void);
