#include "headers.h"

void writeToLCD(uint8_t turnOffTheLights) {
  char cstr[4];
    lcd.clear();
  itoa(turnOffTheLights, cstr, 10);
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(6, 0);
  lcd.print(cstr);
  lcd.setCursor(12, 0);
  lcd.setCursor(0, 1);
  lcd.print(STR_VERSION);
}
