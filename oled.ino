#include "headers.h"

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

void updateHour() {
  Time t = rtc.time();
  char firstByte;
  char secondByte;
  char aux[6];

  // day of week
  switch (t.day) {
    case Time::kSunday:
      currentDayOfWeek = STR_SUNDAY;
      break;
    case Time::kMonday:
      currentDayOfWeek = STR_MONDAY;
      break;
    case Time::kTuesday:
      currentDayOfWeek = STR_TUESDAY;
      break;
    case Time::kWednesday:
      currentDayOfWeek = STR_WEDNESDAY;
      break;
    case Time::kThursday:
      currentDayOfWeek = STR_THURSDAY;
      break;
    case Time::kFriday:
      currentDayOfWeek = STR_FRIDAY;
      break;
    case Time::kSaturday:
      currentDayOfWeek = STR_SATURDAY;
      break;
  }

  // hour
  formatNumber(t.hr, &firstByte, &secondByte);
  currentHour[0] = firstByte;
  currentHour[1] = secondByte;
  currentHour[2] = ':';
  formatNumber(t.min, &firstByte, &secondByte);
  currentHour[3] = firstByte;
  currentHour[4] = secondByte;
  currentHour[5] = '\0';  

  // day
  formatNumber(t.date, &firstByte, &secondByte);
  currentDate[0] = firstByte;
  currentDate[1] = secondByte;
  currentDate[2] = '/';
  formatNumber(t.mon, &firstByte, &secondByte);
  currentDate[3] = firstByte;
  currentDate[4] = secondByte;
  currentDate[5] = '\0';  

  // year
  sprintf(aux, "%u", t.yr);
  currentYear[0] = '>';
  currentYear[1] = aux[0];
  currentYear[2] = aux[1];
  currentYear[3] = aux[2];
  currentYear[4] = aux[3];
  currentYear[5] = '\0';  
}

void configureDisplay() {
  if (isBooting) return;
  uint8_t display = random(12);
  switch (display) {
    case 0:
      panelPos = 18;
      linePos = 0;
      ptrF = drawBootHour02;
      break;
    case 1:
      panelPos = 18;
      linePos = 0;
      ptrF = drawBootDate02;
      break;
    case 2:
      ptrF = drawBootDate01;
      break;
    case 3:
      ptrF = drawBootHour01;
      break;
    case 4:
      panelPos = 18;
      linePos = 0;
      ptrF = drawBootHour00;
      break;
    case 5:
      panelPos = 0;
      linePos = 49;
      ptrF = drawBootHour02;
      break;
    case 6:
      panelPos = 18;
      linePos = 0;
      ptrF = drawBootDate00;
      break;
    case 7:
      ptrF = drawBootHour03;
      break;
    case 8:
      panelPos = 0;
      linePos = 49;
      ptrF = drawBootDate02;
      break;
    case 9:
      panelPos = 0;
      linePos = 49;
      ptrF = drawBootHour00;
      break;
    case 10:
      ptrF = drawBootDate03;
      break;
    case 11:
      panelPos = 0;
      linePos = 49;
      ptrF = drawBootDate00;
      break;
  }
  textPos = panelPos + 38;
  textVPos = random(5, 16);
}

void writeToDisplay(uint8_t turnOffTheLights) {
  configureDisplay();
  updateHour();

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
        ptrF = drawBootHour00;
        currentDelay = 5000;
      }
    } else {
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

void drawBootHour00(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_fub30);
  drawLines(turnOffTheLights, linePos);
  u8g.drawRFrame(0, panelPos, 128, 46, 4);
  u8g.drawStr(textVPos, textPos, currentHour);
}

void drawBootHour01(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentDayOfWeek);
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentHour);
}

void drawBootHour02(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_fub30);
  drawLines(turnOffTheLights, linePos);
  u8g.drawStr(textVPos, textPos, currentHour);
}

void drawBootHour03(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentYear);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentHour);
}

void drawBootDate00(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_fub30);
  drawLines(turnOffTheLights, linePos);
  u8g.drawRFrame(0, panelPos, 128, 46, 4);
  u8g.drawStr(textVPos, textPos, currentDate);
}

void drawBootDate01(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentDayOfWeek);
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentDate);
}

void drawBootDate02(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_fub30);
  drawLines(turnOffTheLights, linePos);
  u8g.drawStr(textVPos, textPos, currentDate);
}

void drawBootDate03(uint8_t turnOffTheLights) {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentYear);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentDate);
}

