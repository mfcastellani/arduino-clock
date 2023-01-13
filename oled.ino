#include "headers.h"

uint8_t display = 0;
uint8_t panelPos = 18;
uint8_t linePos = 0;
uint8_t textPos = 0;
uint8_t textVPos = 5;

void formatNumber(uint8_t number, char* firstByte, char* secondByte) {
  char zeros_pos[6] = "0o0*0o";
  char zeros_antes[6] = ". __. ";
  uint8_t pos = random(6);
  char aux[4];

  switch(number) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      *firstByte = zeros_antes[pos];
      sprintf(aux, "%u", number);
      *secondByte = aux[0];
      break;
    case 10:
    case 20:
    case 30:
    case 40:
    case 50:
      *secondByte = zeros_pos[pos];
      sprintf(aux, "%u", number);
      *firstByte = aux[0];
      break;
    default:
      sprintf(aux, "%u", number);
      *firstByte  = aux[0];
      *secondByte = aux[1];
      break;
  }
}

void writeToDisplay(uint8_t turnOffTheLights) {
  // random options for random display
  display = random(11);
  if(display >= 5) {
    panelPos = 0;
    linePos = 49;
  } else {
    panelPos = 18;
    linePos = 0;
  }
  textPos = panelPos + 38;
  textVPos = random(5, 16);

  // generate hour
  char firstByte;
  char secondByte;
  formatNumber(random(24), &firstByte, &secondByte);
  currentHour[0] = firstByte;
  currentHour[1] = secondByte;
  currentHour[2] = ':';
  formatNumber(random(60), &firstByte, &secondByte);
  currentHour[3] = firstByte;
  currentHour[4] = secondByte;
  currentHour[5] = '\0';

  u8g.firstPage();
  do {
    (*ptrF)(turnOffTheLights);
  } while( u8g.nextPage() );

  if (isBooting) {
    if (currentBootStage < 4) {
      currentBootStage += 1;
      if (currentBootStage == 1) ptrF = drawBoot01;
      if (currentBootStage == 2) ptrF = drawBoot02;
      if (currentBootStage == 3) {
        ptrF = drawBootHour;
        currentDelay = 5000;
      }
    } else {
      lcd.backlight();
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);

      currentDelay = 100;
      isBooting = false;
    }
  }
}

void drawLines(uint8_t turnOffTheLights, uint8_t pos) {
  uint8_t i;
  for(i = 0; i < (129 - turnOffTheLights); i = i + 3) {
    uint8_t linha = random(15);
    u8g.drawVLine(i,   pos, linha);
    u8g.drawVLine(i+1, pos, linha);
  }
}

void drawBoot00(uint8_t turnOffTheLights) {
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, STR_SICK);
}

void drawBoot01(uint8_t turnOffTheLights) {
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, STR_CLOCKS);
}

void drawBoot02(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(1, 15, STR_LOGO01);
  u8g.drawStr(1, 30, STR_LOGO02);
  u8g.drawStr(1, 45, STR_LOGO03);
}

void drawBootHour(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_fub30);
  drawLines(turnOffTheLights, linePos);
  u8g.drawRFrame(0, panelPos, 128, 46, 4);
  u8g.drawStr(textVPos, textPos, currentHour);
}


