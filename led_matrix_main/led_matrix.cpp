#include "led_matrix.h"
#include "bitmaps.h"
#include <MD_MAX72xx.h>

//library for string to char array conversion
#include <string.h> 

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    4  // or SS

//workaround for scope issues, must be set manually
const int NUM_DISPLAYS = 8;
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, NUM_DISPLAYS);

void matrixStart(int numDisplays) {
  mx.begin();
}

//definition of useful constants
const int NUM_ROWS = 8;
const int SIZE = 8;
const int NUM_COLS = 8*NUM_DISPLAYS;

//definition of prev string global
String prev_string;

//definition of prev bitmap global
uint8_t prev_bitmap[NUM_COLS];

void matrixWrite(String led_output) {
  //clearing matrix display and turning off until bitmap buffers are ALL set
  mx.clear();
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  //check that string to be outputted is within 16 character limit
  if (led_output.length() > NUM_DISPLAYS)
  {
    matrixWrite("TOO LONG");
    return;
  }

  //if text to out output has not changed, quickly set prev_buffer to avoid flickering
  if (led_output == prev_string) {
    mx.setBuffer(NUM_COLS - 1, NUM_COLS, prev_bitmap);
  }

  else {
  //parse string and send bitmap of each char to led matrix
  stringParse(led_output);

  //transforming buffer
  mx.transform(MD_MAX72XX::TFLR);
  
  prev_string = led_output;
  }

  //turn on display now that all buffers have been set
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  delay(600);
  mx.getBuffer(NUM_COLS - 1, NUM_COLS, prev_bitmap);
}

void stringParse(String input) {
  //converting string to char array for iteration
  const int length = input.length();
  char* char_arr = new char[length + 1];
  strcpy(char_arr, input.c_str()); 

  //for loop which iterates through each char and calls charToBitmap
  int counter = (NUM_DISPLAYS - length)/2 + 1;
  for (int i = length - 1; i >= 0; i--)
  {
    setBuffer(char_arr[i], counter);
    counter++;
  }
  
  //deallocating dynamic memory used for char arr
  delete[] char_arr;
}

//definition of ASCII ranges for characters
const int WHITESPACE = 32;
const int NUM_MIN = 48;
const int NUM_MAX = 57;
const int UPPER_MIN = 65;
const int UPPER_MAX = 90;
const int LOWER_MIN = 97;
const int LOWER_MAX = 122;

void setBuffer(char input, int displayNum) {
  //declaring variable to store bitmap for single char
  uint8_t bitmap[8]; 

  //identify char and find  corresponding bitmap
  //whitespace
  if (int(input) == WHITESPACE) {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = 0;
    }
  }

  //number
  else if (int(input) >= NUM_MIN && int(input) <= NUM_MAX) {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = NUMBERS[int(input) - NUM_MIN][i];
    }
  }

  //uppercase
  else if (int(input) >= UPPER_MIN && int(input) <= UPPER_MAX) {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = ALPHABET[int(input) - UPPER_MIN][i];
    }
  }

  //lowercase
  else if (int(input) >= LOWER_MIN && int(input) <= LOWER_MAX) {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = ALPHABET[int(input) - LOWER_MIN + 26][i];
    }
  }

  //unknown char
  else {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = ERROR[i];
    }
  }
  
  //set bitmap buffer
  mx.setBuffer(displayNum*SIZE - 1, SIZE, bitmap);
}