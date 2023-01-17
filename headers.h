#ifndef HEADERFILE_H
#define HEADERFILE_H

// oled - 128x64
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK); 
typedef void TipoFuncao(uint8_t turnOffTheLights);
TipoFuncao *ptrF;

// strings
#include "strings.h"

// led pins
#define GREEN_LED   0 
#define RED_LED     1

// rtc
#include <DS1302.h>
DS1302 rtc(8, 9, 10);

// globals
bool isBooting = true;
bool isOledOFF = false;
uint8_t currentBootStage = 0;
int currentDelay = 1500;
char currentHour[6];
char currentDate[6];
char currentYear[6];
char * currentDayOfWeek;

// display functions
void writeToDisplay(uint8_t turnOffTheLights);

#endif