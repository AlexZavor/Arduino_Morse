#ifndef BUZZ_H
#define BUZZ_H

#include <Arduino.h>

class Buzzer{
  private:
    int pin;
    int followed_pin;
    int followed_freq;
  public:
    // Create a new buzzer object
    Buzzer(int output_pin);
    // Play a happy tone on the buzzer
    void happy_tone();
    // Play a sad tone on the buzzer
    void sad_tone();
    // set pin for the buzzer to follow
    void follow_pin(int input_pin, int freq = 440);
    // tick the buzzer following an input button set by "follow_pin"
    void tick();
};

Buzzer::Buzzer(int output_pin){
  pin = output_pin;
}

void Buzzer::happy_tone(){
  tone(pin, 440);
  delay(150);
  tone(pin, 523, 150);
  delay(100);
}
void Buzzer::sad_tone(){
  tone(pin, 523);
  delay(150);
  tone(pin, 440, 150);
  delay(100);
}

void Buzzer::follow_pin(int input_pin, int freq = 440){
  followed_pin = input_pin;
  followed_freq = freq;
}
void Buzzer::tick(){
  if(!digitalRead(followed_pin)){
    tone(pin, followed_freq);
  } else {
    noTone(pin);
  }
}

#endif //BUZZ_H


