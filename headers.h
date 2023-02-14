#ifndef HEADERFILE_H
#define HEADERFILE_H

// oled - 128x64
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK); 

typedef void TipoFuncao(void);
TipoFuncao *ptrF;

// strings
#include "strings.h"

// led pins
// #define PUSH_BUTTON 7
#define RTC_01      8
#define RTC_02      9
#define RTC_03      10
#define DELAY       10
#define PINO_PIR    11

// rtc
#include <DS1302.h>
DS1302 rtc(RTC_01, RTC_02, RTC_03);

// globals
bool isBooting = true;
bool turnOffTheLights = false;
bool isBacklightOn = false;
uint8_t currentBootStage = 0;
uint8_t counterClock = 0;
uint8_t counterPIR = 0;
char currentHour[6];
char currentDate[6];
char currentYear[6];
char * currentDayOfWeek;
char * currentSentence;

// display functions
void writeToDisplay();

#endif