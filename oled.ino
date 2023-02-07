#include "headers.h"

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

  // sentence
  switch (t.day) {
    case Time::kSunday:
    case Time::kSaturday:
      currentSentence = STR_STCE_02;
      break;
    case Time::kMonday:
    case Time::kTuesday:
    case Time::kWednesday:
    case Time::kThursday:
    case Time::kFriday:
      if ((t.hr >= 8 && t.hr < 12) || (t.hr >= 14 && t.hr < 18)) {
        currentSentence = STR_STCE_03;
      } else {
        if (t.day == Time::kFriday) {
          currentSentence = STR_STCE_05;
        } else {
          currentSentence = STR_STCE_02;
        }
      }
      break;
  }  
  if (t.hr >= 7 && t.hr < 8) currentSentence = STR_STCE_04;
  if (t.hr >= 12 && t.hr < 14) currentSentence = STR_STCE_04;
  if (t.hr >= 18 && t.hr < 20) currentSentence = STR_STCE_04;
  if (t.min % 5 == 0) currentSentence = STR_STCE_01;

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
  uint8_t display = random(25);
  switch (display) {
    case 0:
    case 1:
      ptrF = drawBootHour00;
      break;
    case 2:
    case 3:
      ptrF = drawBootHour01;
      break;
    case 4:
    case 5:
      ptrF = drawBootHour02;
      break;
    case 6:
    case 7:
      ptrF = drawBootHour03;
      break;
    case 8:
      ptrF = drawBootDate00;
      break;
    case 9:
      ptrF = drawBootDate01;
      break;
    case 10:
      ptrF = drawBootDate02;
      break;
    case 11:
      ptrF = drawBootDate03;
      break;
    case 12:
    case 13:
      ptrF = drawBootHour04;
      break;
    case 14:
    case 15:
      ptrF = drawBootHour05;
      break;
    case 16:
    case 17:
      ptrF = drawBootHour06;
      break;
    case 18:
    case 19:
      ptrF = drawBootHour07;
      break;
    case 20:
      ptrF = drawBootDate04;
      break;
    case 21:
      ptrF = drawBootDate05;
      break;
    case 22:
      ptrF = drawBootDate06;
      break;
    case 23:
      ptrF = drawBootDate07;
      break;
    case 24:
      ptrF = drawBoot02;
      break;
  }
}

void writeToDisplay() {
  if (counterClock >= 3) {
    counterClock = 0;
  } else {
    return;
  }

  u8g.firstPage();
  do {
    (*ptrF)();
  } while( u8g.nextPage() );

  if (isBooting) {
    if (currentBootStage < 3) {
      currentBootStage += 1;
      if (currentBootStage == 1) ptrF = drawBoot01;
      if (currentBootStage == 2) ptrF = drawBoot02;
    } else {
      isBooting = false;
      configureDisplay();
      updateHour();
      ptrF = drawBootHour00;
    }
  } else {
    configureDisplay();
    updateHour();
  }
}

void drawBoot00() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, STR_VERSION);
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, STR_SICK);
}

void drawBoot01() {
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, STR_CLOCKS);
}

void drawBoot02() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(1, 15, STR_LOGO01);
  u8g.drawStr(1, 30, STR_LOGO02);
  u8g.drawStr(1, 45, STR_LOGO03);
}

void drawBootHour00() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentSentence);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentHour);
}

void drawBootHour01() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentDayOfWeek);
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentHour);
}

void drawBootHour02() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentSentence);
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentHour);
}

void drawBootHour03() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentYear);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentHour);
}

void drawBootHour04() {
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(5, 42, currentHour);
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 60, currentSentence);
}

void drawBootHour05() {
  u8g.drawRFrame(0,2, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(5, 42, currentHour);
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 60, currentDayOfWeek);
}

void drawBootHour06() {
  u8g.drawRFrame(0,2, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(5, 42, currentHour);
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 60, currentSentence);
}

void drawBootHour07() {
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(5, 42, currentHour);
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 60, currentYear);
}

void drawBootDate00() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentDayOfWeek);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentDate);
}

void drawBootDate01() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentSentence);
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentDate);
}

void drawBootDate02() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentYear);
  u8g.drawRFrame(0,18, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentDate);
}

void drawBootDate03() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 15, currentSentence);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(12, 57, currentDate);
}

void drawBootDate04() {
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(5, 42, currentDate);
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 60, currentSentence);
}

void drawBootDate05() {
  u8g.drawRFrame(0,2, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(5, 42, currentDate);
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 60, currentDayOfWeek);
}

void drawBootDate06() {
  u8g.drawRFrame(0,2, 128, 46, 4);
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(5, 42, currentDate);
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 60, currentSentence);
}

void drawBootDate07() {
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr(5, 42, currentDate);
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(5, 60, currentYear);
}
