#ifndef MENU_H
#define MENU_H

#include "config.h"
#include "buzz.h"

// Menu controls
#define MENU_ITEMS 4
bool menu = true;
uint8_t menuSel = 0;
bool modeOS = 0;


void menuSwap(Buzzer* buzz = NULL){
  menu = !menu; 
  if(buzz != NULL){
    if(menu){
      buzz->sad_tone();
    } else {
      buzz->happy_tone();
    }
    delay(100);
  }else{
    delay(200);
  }
  inputStateL = 0;
  inputStateR = 0;
  digitalWrite(OUTPUT_LED_PIN, LOW);
  modeOS = 1;
}

__FlashStringHelper* getMenuItem(int item){
  if (item < 0) {item = MENU_ITEMS-item;}
  if (item >= MENU_ITEMS) {item = item-MENU_ITEMS;}
  switch(item){
    case 0:
      return F("Option");
    case 1:
      return F("Play");
    case 2:
      return F("F-Card");
    case 3:
      return F("Quiz");
    default:
      return F("Error");
  }
}

void drawMenu(Adafruit_SSD1306 *display, Buzzer* buzz){
  if(inputStateL && inputStateR){menuSwap(buzz); return;}
  else if (inputOSL_b){ if(!menuSel){menuSel = MENU_ITEMS;} menuSel--; }
  else if (inputOSR_b){ menuSel++; menuSel%=MENU_ITEMS; }
  int strLen = strlen_P((const char*)getMenuItem(menuSel));
  display->drawRect(((display->width() - (strLen*12))/2)-2, 4, (strLen*12)+4, 20, SSD1306_WHITE);
  display->setCursor((display->width() - (strLen*12))/2, 6);
  display->setTextSize(2);
  display->print(getMenuItem(menuSel));
  display->setCursor(16, 25);
  display->setTextSize(1);
  display->print(F("Press L+R to Sel"));
  display->setCursor(0, 0);
  display->print(menuSel+1);
}

#endif // MENU_H