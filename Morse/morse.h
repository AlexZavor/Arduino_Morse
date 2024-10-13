#ifndef MORSE_H
#define MORSE_H

#include "config.h"
#include "input.h"

char morse_buffer[MORSE_BUFFER_SIZE];
int morse_buffer_index = 0;
bool morse_invalid_flag = 0;
enum morse_t{
  dit = 0,
  dah = 1,
};

void add_dit(){
  if(morse_buffer_index < MORSE_BUFFER_SIZE){
    morse_buffer[morse_buffer_index] = dit;
    morse_buffer_index++;
  }else{
    morse_invalid_flag = 1;
  }
  
}
void add_dah(){
  if(morse_buffer_index < MORSE_BUFFER_SIZE){
    morse_buffer[morse_buffer_index] = dah;
    morse_buffer_index++;
  }else{
    morse_invalid_flag = 1;
  }
}
char finish_word(){
  char word = '$';
  int solved;

  switch(morse_buffer_index){
    case 1:
      if(morse_buffer[0] == dit){
        word = 'E';
      } else {
        word = 'T';
      }
      break;
    case 2:
      solved = (morse_buffer[0]<<1)+(morse_buffer[1]);
      switch(solved){
        case 0:
          word = 'I';
          break;
        case 1:
          word = 'A';
          break;
        case 2:
          word = 'N';
          break;
        case 3:
          word = 'M';
          break;
      }
      break;
    case 3:
      solved = (morse_buffer[0]<<2)+(morse_buffer[1]<<1)+(morse_buffer[2]);
      switch(solved){
        case 0:
          word = 'S';
          break;
        case 1:
          word = 'U';
          break;
        case 2:
          word = 'R';
          break;
        case 3:
          word = 'W';
          break;
        case 4:
          word = 'D';
          break;
        case 5:
          word = 'K';
          break;
        case 6:
          word = 'G';
          break;
        case 7:
          word = 'O';
          break;
      }
      break;
    case 4:
      solved = (morse_buffer[0]<<3)+(morse_buffer[1]<<2)+(morse_buffer[2]<<1)+(morse_buffer[3]);
      switch(solved){
        case 0:
          word = 'H';
          break;
        case 1:
          word = 'V';
          break;
        case 2:
          word = 'F';
          break;
        case 4:
          word = 'L';
          break;
        case 6:
          word = 'P';
          break;
        case 7:
          word = 'J';
          break;
        case 8:
          word = 'B';
          break;
        case 9:
          word = 'X';
          break;
        case 10:
          word = 'C';
          break;
        case 11:
          word = 'Y';
          break;
        case 12:
          word = 'Z';
          break;
        case 13:
          word = 'Q';
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
  if(morse_invalid_flag){word = '#';}
  morse_buffer_index = 0;
  morse_invalid_flag = 0;
  return word;
}
String getMorse(){
  String temp = "";
  for(char i = 0; i < morse_buffer_index; i++){
    temp.concat(morse_buffer[i]?MORSE_DAH_CHAR:MORSE_DIT_CHAR);
  }
  return temp;
}
String getMorseCode(char chr){
  switch(chr){
    case 'A':{
      char out[] = {0x7,'-','\0'};
      return (String)out;
    }
    case 'B':{
      char out[] = {'-',0x7,0x7,0x7,'\0'};
      return (String)out;
    }
    case 'C':{
      char out[] = {'-',0x7,'-',0x7,'\0'};
      return (String)out;
    }
    case 'D':{
      char out[] = {'-',0x7,0x7,'\0'};
      return (String)out;
    }
    case 'E':{
      char out[] = {0x7,'\0'};
      return (String)out;
    }
    case 'F':{
      char out[] = {0x7,0x7,'-',0x7,'\0'};
      return (String)out;
    }
    case 'G':{
      char out[] = {'-','-',0x7,'\0'};
      return (String)out;
    }
    case 'H':{
      char out[] = {0x7,0x7,0x7,0x7,'\0'};
      return (String)out;
    }
    case 'I':{
      char out[] = {0x7,0x7,'\0'};
      return (String)out;
    }
    case 'J':{
      char out[] = {0x7,'-','-','-','\0'};
      return (String)out;
    }
    case 'K':{
      char out[] = {'-',0x7,'-','\0'};
      return (String)out;
    }
    case 'L':{
      char out[] = {0x7,'-',0x7,0x7,'\0'};
      return (String)out;
    }
    case 'M':{
      char out[] = {'-','-','\0'};
      return (String)out;
    }
    case 'N':{
      char out[] = {'-',0x7,'\0'};
      return (String)out;
    }
    case 'O':{
      char out[] = {'-','-','-','\0'};
      return (String)out;
    }
    case 'P':{
      char out[] = {0x7,'-','-',0x7,'\0'};
      return (String)out;
    }
    case 'Q':{
      char out[] = {'-','-',0x7,'-','\0'};
      return (String)out;
    }
    case 'R':{
      char out[] = {0x7,'-',0x7,'\0'};
      return (String)out;
    }
    case 'S':{
      char out[] = {0x7,0x7,0x7,'\0'};
      return (String)out;
    }
    case 'T':{
      char out[] = {'-','\0'};
      return (String)out;
    }
    case 'U':{
      char out[] = {0x7,0x7,'-','\0'};
      return (String)out;
    }
    case 'V':{
      char out[] = {0x7,0x7,0x7,'-','\0'};
      return (String)out;
    }
    case 'W':{
      char out[] = {0x7,'-','-','\0'};
      return (String)out;
    }
    case 'X':{
      char out[] = {'-',0x7,0x7,'-','\0'};
      return (String)out;
    }
    case 'Y':{
      char out[] = {'-',0x7,'-','-','\0'};
      return (String)out;
    }
    case 'Z':{
      char out[] = {'-','-',0x7,0x7,'\0'};
      return (String)out;
    }
    default:
      return "";
  }
}

char translateInput(bool is_right = true){
  static unsigned long start = millis();
  static bool charprint = 0;

  // Input - R
  if(is_right?inputOSR:inputOSL){ // Press
    start = millis();
    charprint = 0;
  }
  if(is_right?inputOSR_b:inputOSL_b){ // Release
    unsigned long end = millis();
    if(end-start > DASH_TIME_MS){
      // add dah
      add_dah();
    } else {
      // add dit
      add_dit();
    }
    start = millis();
    charprint = 1;
  }
  if(millis()-start > WORD_TIME_MS && charprint){
    // new word
    charprint = 0;
    return finish_word();
  }
  return 0;
}


#endif //MORSE_H


