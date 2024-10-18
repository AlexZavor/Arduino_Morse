#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Button Inputs
#define INPUT_BUTTON_L 3
#define INPUT_BUTTON_R 2
// Led/Speaker output
#define OUTPUT_BUZZ_PIN 4
#define OUTPUT_LED_PIN 5

// Morse Code settings
#define DASH_TIME_MS 140
#define WORD_TIME_MS 300
#define MORSE_BUFFER_SIZE 6
#define MORSE_DIT_CHAR ((char)0x07)
#define MORSE_DAH_CHAR '-'

// Define screen
#define SCREEN_WIDTH   128  // OLED display width, in pixels
#define SCREEN_HEIGHT  32   // OLED display height, in pixels
#define OLED_RESET     -1   // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// Play Buffer size
#define WORD_BUFFER_SIZE 64

#endif // CONFIG_H