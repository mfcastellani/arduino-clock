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
#define PUSH_BUTTON 7
#define RTC_01      8
#define RTC_02      9
#define RTC_03      10
#define DELAY       10
#define CONF_BUTTON 11

// rtc
#include <DS1302.h>
DS1302 rtc(RTC_01, RTC_02, RTC_03);

// globals
bool isBooting = true;
bool turnOffTheLights = false;
bool isBacklightOn = false;
bool shouldChange = true;
uint8_t currentBootStage = 0;
uint8_t counterClock = 0;
char currentHour[6];
char currentDate[6];
char currentYear[6];
char * currentDayOfWeek;
char * currentSentence;

// adjust 
uint8_t adjustStep  = 0;
uint8_t newHour     = 0;
uint8_t newMin      = 0;
uint8_t newDay      = 0;
uint8_t newMonth    = 0;
int     newYear     = 0;
uint8_t newWeekDay  = 0;

// vars aux do adjust
uint8_t adjThousand = 0;
uint8_t adjHundred  = 0;
uint8_t adjTens     = 0;
uint8_t adjUnits    = 0;

// strings aux do adjust
char adjustLine1[16];
char adjustLine2[16];
char adjustLine3[16];

#define NO_ADJUST        0
#define ADJUST_INIT      1
#define ADJUST_HOUR_TENS 2
#define ADJUST_HOUR_UNTS 3
#define ADJUST_HOUR_SAVE 4
#define ADJUST_MINS_TENS 5
#define ADJUST_MINS_UNTS 6
#define ADJUST_MINS_SAVE 7
#define ADJUST_DAY_TENS  8
#define ADJUST_DAY_UNTS  9
#define ADJUST_DAY_SAVE  10
#define ADJUST_MONT_TENS 11
#define ADJUST_MONT_UNTS 12
#define ADJUST_MONT_SAVE 13
#define ADJUST_YEAR_TENS 14
#define ADJUST_YEAR_UNTS 15
#define ADJUST_YEAR_SAVE 16
#define ADJUST_WDAY_TENS 17
#define ADJUST_WDAY_SAVE 18

// display functions
void writeToDisplay();

#endif