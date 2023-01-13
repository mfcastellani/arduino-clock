#include "headers.h"

uint8_t turnOffTheLights = 0;

void setup() {
  // Leds
  pinMode(YELLOW_LED, OUTPUT); // amarelo
  pinMode(RED_LED, OUTPUT); // vermelho
  pinMode(GREEN_LED, OUTPUT); // verde
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

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

  // LCD
  lcd.begin(16, 2, LCD_5x8DOTS);

  // push button
  pinMode(PUSH_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  writeToDisplay(turnOffTheLights);

  if (isBooting) {
    delay(currentDelay);
  } else {
    turnOffTheLights += 1;

    writeToLCD(turnOffTheLights);

    switch (turnOffTheLights) {
      case 10:
        digitalWrite(RED_LED, LOW);
        lcd.noBacklight();
        break;
      case 12:
      case 34:
      case 61:
      case 83:
      case 115:
        digitalWrite(YELLOW_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        break;
      case 23:
      case 47:
      case 68:
      case 99:
      case 128:
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        break;
      case 130:
        u8g.sleepOn();
        lcd.noDisplay();
        turnOffTheLights = 0;
        break;
    }

    uint8_t i;
    for(i = 0; i < 10; i += 1) {
      if (digitalRead(PUSH_BUTTON) == LOW) {
        digitalWrite(RED_LED, HIGH);
        u8g.sleepOff();
        lcd.backlight();
        lcd.display();
        turnOffTheLights = 0;
      }

      delay(currentDelay);
    }
  }
}
