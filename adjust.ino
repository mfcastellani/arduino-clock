#include "headers.h"
#include <avr/wdt.h>

void resetAdjustAuxVars() {
  adjTens = 0;
  adjUnits = 0;
}

void nextAdjustStep() {
  if(shouldChange) {
    adjustStep += 1;
    shouldChange = false;
  }

  switch(adjustStep) {
    case ADJUST_HOUR_SAVE:
      newHour = (adjTens * 10) + adjUnits;
      adjustStep += 1;
      resetAdjustAuxVars();
      adjustLines();
      break;
    case ADJUST_MINS_SAVE:
      newMin = (adjTens * 10) + adjUnits;
      adjustStep += 1;
      resetAdjustAuxVars();
      adjustLines();
      break;
    case ADJUST_DAY_SAVE:
      newDay = (adjTens * 10) + adjUnits;
      adjustStep += 1;
      resetAdjustAuxVars();
      adjustLines();
      break;
    case ADJUST_MONT_SAVE:
      newMonth = (adjTens * 10) + adjUnits;
      adjustStep += 1;
      resetAdjustAuxVars();
      adjustLines();
      break;
    case ADJUST_YEAR_SAVE:
      newYear = 2000 + (adjTens * 10) + adjUnits;
      adjustStep += 1;
      resetAdjustAuxVars();
      adjustLines();
      break;
    case ADJUST_WDAY_SAVE:
      rtc.writeProtect(false);
      rtc.halt(false);
      Time t(newYear, newMonth, newDay, newHour, newMin, 0, (adjTens + 1));
      rtc.time(t);
      wdt_enable(WDTO_1S); 
      for(;;) {}
      break;
  }
}

void incrementCurrentPosition() {
  switch(adjustStep) {
    case ADJUST_HOUR_TENS:
    case ADJUST_MINS_TENS:
    case ADJUST_DAY_TENS:
    case ADJUST_MONT_TENS:
    case ADJUST_YEAR_TENS:
    case ADJUST_WDAY_TENS:
      adjTens = adjTens + 1;
      break;
    case ADJUST_HOUR_UNTS:
    case ADJUST_MINS_UNTS:
    case ADJUST_DAY_UNTS:
    case ADJUST_MONT_UNTS:
    case ADJUST_YEAR_UNTS:
      adjUnits = adjUnits + 1;
      break;
  }

  if((adjustStep == ADJUST_HOUR_TENS) && (adjTens > 2)) adjTens = 0;
  if((adjustStep == ADJUST_MONT_TENS) && (adjTens > 1)) adjTens = 0;
  if((adjustStep == ADJUST_MINS_TENS) && (adjTens > 5)) adjTens = 0;
  if((adjustStep == ADJUST_DAY_TENS) && (adjTens > 3)) adjTens = 0;
  if((adjustStep == ADJUST_WDAY_TENS) && (adjTens > 6)) adjTens = 0;
  if((adjustStep == ADJUST_HOUR_UNTS) && (adjTens == 2) && (adjUnits > 3)) adjUnits = 0;
  if((adjustStep == ADJUST_DAY_UNTS) && (adjTens == 3) && (adjUnits > 1)) adjUnits = 0;
  if((adjustStep == ADJUST_MONT_UNTS) && (adjTens == 1) && (adjUnits > 2)) adjUnits = 0;
  if(adjUnits > 9) adjUnits = 0;
  adjustLines();
}

void adjustLines() {
  char aux[4];
  
  // linha 1 - prompt
  adjustLine1[0] = '>';
  adjustLine1[1] = ' ';
  sprintf(aux, "%u", adjTens);
  adjustLine1[2] = aux[0];
  sprintf(aux, "%u", adjUnits);
  adjustLine1[3] = aux[0];
  adjustLine1[4] = ' ';
  adjustLine1[5] = '-';
  adjustLine1[6] = ' ';
  switch(adjustStep) {
    case ADJUST_HOUR_TENS:
    case ADJUST_HOUR_UNTS:
      adjustLine1[7] = 'H';
      adjustLine1[8] = 'o';
      adjustLine1[9] = 'R';
      break;
    case ADJUST_MINS_TENS:
    case ADJUST_MINS_UNTS:
      adjustLine1[7] = 'M';
      adjustLine1[8] = 'i';
      adjustLine1[9] = 'N';
      break;
    case ADJUST_DAY_TENS:
    case ADJUST_DAY_UNTS:
      adjustLine1[7] = 'D';
      adjustLine1[8] = 'i';
      adjustLine1[9] = 'a';
      break;      
    case ADJUST_MONT_TENS:
    case ADJUST_MONT_UNTS:
      adjustLine1[7] = 'M';
      adjustLine1[8] = 'e';
      adjustLine1[9] = 'S';
      break;      
    case ADJUST_YEAR_TENS:
    case ADJUST_YEAR_UNTS:
      adjustLine1[7] = 'a';
      adjustLine1[8] = 'N';
      adjustLine1[9] = 'o';
      break;   
    case ADJUST_WDAY_TENS:   
      adjustLine1[7] = 'S';
      adjustLine1[8] = 'e';
      adjustLine1[9] = 'M';
      break;   
  }
  adjustLine1[10] = ' ';
  adjustLine1[11] = '[';
  sprintf(aux, "%u", adjustStep);
  if(adjustStep > 9) {
    adjustLine1[12] = aux[0];
    adjustLine1[13] = aux[1];
  } else {
    adjustLine1[12] = '0';
    adjustLine1[13] = aux[0];
  }
  adjustLine1[14] = ']';
  adjustLine1[15] = '\0';

  // linha 2
  adjustLine2[0] = ' ';
  adjustLine2[1] = ' ';
  if(adjustStep > ADJUST_HOUR_SAVE) {
    sprintf(aux, "%u", newHour);
    if(newHour > 9) {
      adjustLine2[2] = aux[0];
      adjustLine2[3] = aux[1];
    } else {
      adjustLine2[2] = '0';
      adjustLine2[3] = aux[0];
    }
  }
  adjustLine2[4] = ':';
  if(adjustStep > ADJUST_MINS_SAVE) {
    sprintf(aux, "%u", newMin);
    if(newMin > 9) {
      adjustLine2[5] = aux[0];
      adjustLine2[6] = aux[1];
    } else {
      adjustLine2[5] = '0';
      adjustLine2[6] = aux[0];
    }
  }  
  adjustLine2[7] = ' ';
  if(adjustStep > ADJUST_DAY_SAVE) {
    sprintf(aux, "%u", newDay);
    if(newDay > 9) {
      adjustLine2[8] = aux[0];
      adjustLine2[9] = aux[1];
    } else {
      adjustLine2[8] = '0';
      adjustLine2[9] = aux[0];
    }
  }
  adjustLine2[10] = '/';
  if(adjustStep > ADJUST_MONT_SAVE) {
    sprintf(aux, "%u", newMonth);
    if(newMonth > 9) {
      adjustLine2[11] = aux[0];
      adjustLine2[12] = aux[1];
    } else {
      adjustLine2[11] = '0';
      adjustLine2[12] = aux[0];
    }
  }
  adjustLine2[13] = '\0';

  // linha 3
  adjustLine3[0] = ' ';
  adjustLine3[1] = ' ';
  if(adjustStep > ADJUST_YEAR_SAVE) {
    sprintf(aux, "%u", newYear);
    adjustLine3[2] = aux[0];
    adjustLine3[3] = aux[1];
    adjustLine3[4] = aux[2];
    adjustLine3[5] = aux[3];
  }
  adjustLine3[6] = ' ';
  adjustLine3[7] = ' ';
  if(adjustStep >= ADJUST_WDAY_TENS) {
    switch(adjTens){
      case 0:
        adjustLine3[8] = 'D';
        adjustLine3[9] = 'O';
        adjustLine3[10] = 'M';
        break;
      case 1:
        adjustLine3[8] = 'S';
        adjustLine3[9] = 'E';
        adjustLine3[10] = 'G';
        break;
      case 2:
        adjustLine3[8] = 'T';
        adjustLine3[9] = 'E';
        adjustLine3[10] = 'R';
        break;
      case 3:
        adjustLine3[8] = 'Q';
        adjustLine3[9] = 'U';
        adjustLine3[10] = 'A';
        break;
      case 4:
        adjustLine3[8] = 'Q';
        adjustLine3[9] = 'U';
        adjustLine3[10] = 'I';
        break;
      case 5:
        adjustLine3[8] = 'S';
        adjustLine3[9] = 'E';
        adjustLine3[10] = 'X';
        break;
      case 6:
        adjustLine3[8] = 'S';
        adjustLine3[9] = 'A';
        adjustLine3[10] = 'B';
        break;
    }
  }
  adjustLine3[11] = '\0';  
}