#include "headers.h"

uint8_t turnOffTheLights = 0;

void setup() {
  // Leds
  pinMode(RED_LED, OUTPUT); // vermelho
  pinMode(GREEN_LED, OUTPUT); // verde
  pinMode(LED_BUILTIN, OUTPUT); // internal
  digitalWrite(RED_LED, HIGH);

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

  // NAO APAGAR CODIGO PRA DEFINIR A HORA
  // rtc
  // rtc.writeProtect(false);
  // rtc.halt(false);
  // Time t(2023, 1, 16, 18, 25, 0, Time::kMonday);
  // rtc.time(t);
}

void loop() {
  if (isBooting) {
    writeToDisplay(turnOffTheLights);
    delay(currentDelay);
  } else {
    turnOffTheLights += 1;
    if (turnOffTheLights % 5 == 0) writeToDisplay(turnOffTheLights);

    if (turnOffTheLights % 2 == 0) {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
    switch (turnOffTheLights) {
      case 1:
        writeToDisplay(turnOffTheLights);
        break;
      // case 130:
      //   u8g.sleepOn();
      //   turnOffTheLights = 0;
      //   isOledOFF = true;
      //   break;
    }

    uint8_t i;
    for(i = 0; i < 10; i += 1) {
      // if (digitalRead(PUSH_BUTTON) == LOW) {
      //   if(isOledOFF) {
      //     digitalWrite(RED_LED, HIGH);
      //     u8g.sleepOff();
      //     turnOffTheLights = 0;
      //   } else {
      //     u8g.sleepOn();
      //   }
      //   turnOffTheLights = 0;
      //   isOledOFF = !isOledOFF;
      // }

      delay(currentDelay);
    }
  }
}
