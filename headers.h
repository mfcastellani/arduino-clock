#ifndef HEADERFILE_H
#define HEADERFILE_H

// oled - 128x64
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK); 
typedef void TipoFuncao(uint8_t turnOffTheLights);
TipoFuncao *ptrF;

// Wire
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

// strings
#include "strings.h"

// led pins
#define GREEN_LED   2 
#define YELLOW_LED  3
#define RED_LED     4
#define PUSH_BUTTON 5

// globals
bool isBooting = true;
uint8_t currentBootStage = 0;
int currentDelay = 1500;
char currentHour[6];

// display functions
void writeToDisplay(uint8_t turnOffTheLights);

// LCD
void writeToLCD(uint8_t turnOffTheLights);

#endif