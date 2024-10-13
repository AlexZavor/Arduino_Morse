/*
Alexander Carter - Morse code toy
  Just a simple toy for learning and playing with morse code
*/

#include "buzz.h"
#include "morse.h"
#include "menu.h"
#include "input.h"
#include "config.h"

// Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// buzzer
Buzzer buzz(OUTPUT_BUZZ_PIN);

/******************* Applications ******************/
// Options
void option(){
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print(F("What Options do you expect?\nThis is a tiny app"));
}

// Play
void play(){
  // Setup
  static char* buffer = (char*)malloc(WORD_BUFFER_SIZE);
  static int buffer_index = 0;
  static int instr = true;
  if(modeOS){
    memset(buffer, 0, WORD_BUFFER_SIZE);
    buffer_index = 0;
    display.setTextSize(1);
    buzz.follow_pin(INPUT_BUTTON_R);
    modeOS = 0;
    instr = true;
  }
  
  if(inputStateR || inputStateL){
    instr = false;
  }

  // Input - L
  if(inputOSL){ // Press L to bkspace
    if(buffer_index > 0){
      buffer_index--;
      buffer[buffer_index] = 0;
      buzz.sad_tone();
    }
  }

  char new_word = translateInput(true);
  if(new_word != 0){
    // new word
    buffer[buffer_index] = new_word;
    buffer_index++;
  }

  // Output
  display.setCursor(0, 24);
  if(instr){
    display.print(F("Backspace   |   Morse"));
  }else{
    display.print(getMorse());
  }
  display.setCursor(0, 0);
  display.print(buffer);
  buzz.tick();
  digitalWrite(OUTPUT_LED_PIN, inputStateR);
}

// Flashcards
void flashcards(){
  // Setup
  static int instr = true;
  static int instr_tmr = millis();
  static char leftans = 0;
  static char rightans = 0;
  static String solution = "";
  static unsigned int score = 0;
  if(modeOS){
    randomSeed(millis());
    instr_tmr = millis();
    modeOS = 0;
    instr = true;
    solution = "";
  }
  if(instr && (inputStateR || inputStateL || millis()>(instr_tmr+1500))){
    instr = false;
  }
  
  // Make new question
  if(solution.equals("")){
    leftans = (char)random(65,91);
    rightans = (char)random(65,91);
    while(rightans == leftans){
      rightans = (char)random(65,91);
    }

    if(random(0,2)){
      solution = getMorseCode(leftans);
    } else {
      solution = getMorseCode(rightans);
    }
  }


  // Input
  if(inputOSL||inputOSR){
    int check = 0;
    if(inputOSL){
      if (getMorseCode(leftans).equals(solution)){
        check = 1;
      }
    }else{
      if (getMorseCode(rightans).equals(solution)){
        check = 1;
      }
    }
    if(check){
      buzz.happy_tone();
      score++;
    }else{
      buzz.sad_tone();
      score--;
    }
    solution = "";
  }


  // Output
  display.drawRect(5, 10, 14, 20, SSD1306_WHITE);
  display.drawRect(display.width()-16, 10, 14, 20, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(7, 13);
  display.print(leftans);
  display.setCursor(display.width()-14, 13);
  display.print(rightans);
  display.setCursor(64-(solution.length()*6), 0);
  display.print(solution);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(score);
  if(instr){
    display.setTextSize(1);
    display.setCursor(0, 24);
    display.fillRect(0, 23, 128, 8, SSD1306_BLACK);
    display.print(F("Left            Right"));
  }
}

// Quiz
void quiz(){
  // Setup
  static int instr = true;
  static char question = 0;
  static unsigned int score = 0;
  if(modeOS){
    buzz.follow_pin(INPUT_BUTTON_R);
    randomSeed(millis());
    modeOS = 0;
    static char question = 0;
    instr = true;
  }
  if(inputStateR || inputStateL){
    instr = false;
  }

  // Input - L, Skip
  if(inputOSL){ // Press L to bkspace
    if(score){
      score--;
    }
    question = 0;
  }

  // Make new question
  if(question == 0){
    question = (char)random(65,91);
  }

  char new_word = translateInput(true);
  if(new_word != 0){
    if(question == new_word){
      buzz.happy_tone();
      score++;
      question = 0;
    }else{
      buzz.sad_tone();
    }
  }

  // Output
  display.setTextSize(1);
  display.setCursor(0, 24);
  if(instr){
    display.print(F("Skip            Morse"));
  }else{
    display.print(getMorse());
  }
  display.setTextSize(2);
  display.setCursor(58, 0);
  display.print(question);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(score);
  buzz.tick();
  digitalWrite(OUTPUT_LED_PIN, inputStateR);
}

/****************** Main Functions ****************/

void setup() {
  //System Init
  Serial.begin(9600);
  inputSetup();

  // Screen Init
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Screen Allocation Failure!"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
  display.setTextColor(SSD1306_WHITE);

  delay(100);
}

void loop() {
  //Input-Output
  input();
  
  // Draw
  display.clearDisplay();

  // Draw functions
  if(menu){
    drawMenu(&display, &buzz);
  }else{
    if(inputStateL && inputStateR){menuSwap(&buzz); return;}
    switch(menuSel){
      case 0:
        option();
        break;
      case 1:
        play();
        break;
      case 2:
        flashcards();
        break;
      case 3:
        quiz();
        break;
      default:
        menu = true;
        break;
    }
  }

  // Draw out
  display.display();

}
