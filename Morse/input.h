#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "config.h"

bool inputStateL = 0;
bool inputOSL = 0;
bool inputOSL_b = 0;
bool inputStateR = 0;
bool inputOSR = 0;
bool inputOSR_b = 0;

void inputSetup(){
  pinMode(INPUT_BUTTON_L, INPUT_PULLUP);
  pinMode(INPUT_BUTTON_R, INPUT_PULLUP);
  pinMode(OUTPUT_BUZZ_PIN, OUTPUT);
  pinMode(OUTPUT_LED_PIN, OUTPUT);
}

void input(){
  bool buttonl = (!digitalRead(INPUT_BUTTON_L));
  if(buttonl && !inputStateL){inputOSL = 1;}
  else{inputOSL = 0;}
  if(!buttonl && inputStateL){inputOSL_b = 1;}
  else{inputOSL_b = 0;}
  if(inputStateL != buttonl){
    inputStateL = buttonl;
  }
  bool buttonr = (!digitalRead(INPUT_BUTTON_R));
  if(buttonr && !inputStateR){inputOSR = 1;}
  else{inputOSR = 0;}
  if(!buttonr && inputStateR){inputOSR_b = 1;}
  else{inputOSR_b = 0;}
  if(inputStateR != buttonr){
    inputStateR = buttonr;
  }
}


#endif // INPUT_H
