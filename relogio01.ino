#include "headers.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // internal
  pinMode(PUSH_BUTTON, INPUT_PULLUP);

  // oled
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  ptrF = drawBoot00;

  // CODIGO PRA INICIAR A DATA/HORA NO RTC
  // rtc
  // rtc.writeProtect(false);
  // rtc.halt(false);
  // Time t(2023, 2, 5, 19, 18, 0, Time::kSunday);
  // rtc.time(t);
}

void loop() {
  counterClock += 1;

  uint8_t i = 0;
  for (i = 0; i < 101; i++) {
    if (digitalRead(PUSH_BUTTON) == LOW) {
      if (isBacklightOn) {
        u8g.sleepOn();
      } else {
        u8g.sleepOff();
      }
      isBacklightOn = !isBacklightOn;
      while (digitalRead(PUSH_BUTTON) == LOW);
    }  
    delay(DELAY);
  }

  if (isBooting) {
    writeToDisplay();
  } else {
    turnOffTheLights = !turnOffTheLights;
    if (turnOffTheLights) {
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    writeToDisplay();
  }
}
