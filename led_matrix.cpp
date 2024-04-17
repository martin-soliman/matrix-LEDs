#include "led_matrix.h"
#include <MD_MAX72xx.h>

//librar for string to char array conversion
#include <string.h> 

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    4  // or SS

//definition of alphabetical bitmaps
const uint8_t ALPHABET[][8] = {
{
  0b00000000,
  0b00111110,
  0b01111110,
  0b11001000,
  0b11001000,
  0b01111110,
  0b00111110,
  0b00000000
},{
  0b00000000,
  0b01101100,
  0b11111110,
  0b10010010,
  0b10010010,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b01000100,
  0b11000110,
  0b10000010,
  0b10000010,
  0b11000110,
  0b01111100,
  0b00111000
},{
  0b00000000,
  0b00111000,
  0b01111100,
  0b11000110,
  0b10000010,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b11000110,
  0b10000010,
  0b10111010,
  0b10010010,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b11000000,
  0b10000000,
  0b10111000,
  0b10010010,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b01001110,
  0b11001110,
  0b10001010,
  0b10000010,
  0b11000110,
  0b01111100,
  0b00111000
},{
  0b00000000,
  0b11111110,
  0b11111110,
  0b00010000,
  0b00010000,
  0b11111110,
  0b11111110,
  0b00000000
},{
  0b00000000,
  0b00000000,
  0b10000010,
  0b11111110,
  0b11111110,
  0b10000010,
  0b00000000,
  0b00000000
},{
  0b00000000,
  0b10000000,
  0b11111100,
  0b11111110,
  0b10000010,
  0b00000010,
  0b00001110,
  0b00001100
},{
  0b00000000,
  0b11000110,
  0b11101110,
  0b00111000,
  0b00010000,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b00001110,
  0b00000110,
  0b00000010,
  0b10000010,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b11111110,
  0b11111110,
  0b01110000,
  0b00111000,
  0b01110000,
  0b11111110,
  0b11111110
},{
  0b00000000,
  0b11111110,
  0b11111110,
  0b00011000,
  0b00110000,
  0b01100000,
  0b11111110,
  0b11111110
},{
  0b00000000,
  0b00111000,
  0b01111100,
  0b11000110,
  0b10000010,
  0b11000110,
  0b01111100,
  0b00111000
},{
  0b00000000,
  0b01100000,
  0b11110000,
  0b10010000,
  0b10010010,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b01111010,
  0b11111110,
  0b10001110,
  0b10000100,
  0b11111100,
  0b01111000,
  0b00000000
},{
  0b00000000,
  0b01100110,
  0b11111110,
  0b10011000,
  0b10010000,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b01001100,
  0b11001110,
  0b10011010,
  0b10110010,
  0b11110110,
  0b01100100,
  0b00000000
},{
  0b00000000,
  0b11000000,
  0b10000010,
  0b11111110,
  0b11111110,
  0b10000010,
  0b11000000,
  0b00000000
},{
  0b00000000,
  0b11111110,
  0b11111110,
  0b00000010,
  0b00000010,
  0b11111110,
  0b11111110,
  0b00000000
},{
  0b00000000,
  0b11111000,
  0b11111100,
  0b00000110,
  0b00000110,
  0b11111100,
  0b11111000,
  0b00000000
},{
  0b00000000,
  0b11111110,
  0b11111110,
  0b00001100,
  0b00011000,
  0b00001100,
  0b11111110,
  0b11111110
},{
  0b00000000,
  0b11000010,
  0b11100110,
  0b00111100,
  0b00011000,
  0b00111100,
  0b11100110,
  0b11000010
},{
  0b00000000,
  0b11100000,
  0b11110010,
  0b00011110,
  0b00011110,
  0b11110010,
  0b11100000,
  0b00000000
},{
  0b00000000,
  0b11001110,
  0b11100110,
  0b10110010,
  0b10011010,
  0b10001110,
  0b11000110,
  0b11100010
},{
  0b00000000,
  0b00000010,
  0b00011110,
  0b00111100,
  0b00101010,
  0b00101010,
  0b00101110,
  0b00000100
},{
  0b00000000,
  0b00001100,
  0b00011110,
  0b00010010,
  0b00010010,
  0b11111100,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b00010100,
  0b00110110,
  0b00100010,
  0b00100010,
  0b00111110,
  0b00011100,
  0b00000000
},{
  0b00000000,
  0b00000010,
  0b11111110,
  0b11111100,
  0b10010010,
  0b00010010,
  0b00011110,
  0b00001100
},{
  0b00000000,
  0b00011000,
  0b00111010,
  0b00101010,
  0b00101010,
  0b00111110,
  0b00011100,
  0b00000000
},{
  0b00000000,
  0b01000000,
  0b11000000,
  0b10010010,
  0b11111110,
  0b01111110,
  0b00010010,
  0b00000000
},{
  0b00000000,
  0b00100000,
  0b00111110,
  0b00011111,
  0b00100101,
  0b00100101,
  0b00111101,
  0b00011001
},{
  0b00000000,
  0b00011110,
  0b00111110,
  0b00100000,
  0b00010000,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b00000000,
  0b00000010,
  0b10111110,
  0b10111110,
  0b00100010,
  0b00000000,
  0b00000000
},{
  0b00000000,
  0b10111110,
  0b10111111,
  0b00000001,
  0b00000001,
  0b00000111,
  0b00000110,
  0b00000000
},{
  0b00000000,
  0b00100010,
  0b00110110,
  0b00011100,
  0b00001000,
  0b11111110,
  0b11111110,
  0b10000010
},{
  0b00000000,
  0b00000000,
  0b00000010,
  0b11111110,
  0b11111110,
  0b10000010,
  0b00000000,
  0b00000000
},{
  0b00000000,
  0b00011110,
  0b00111110,
  0b00111000,
  0b00011100,
  0b00011000,
  0b00111110,
  0b00111110
},{
  0b00000000,
  0b00011110,
  0b00111110,
  0b00100000,
  0b00100000,
  0b00111110,
  0b00111110,
  0b00000000
},{
  0b00000000,
  0b00011100,
  0b00111110,
  0b00100010,
  0b00100010,
  0b00111110,
  0b00011100,
  0b00000000
},{
  0b00000000,
  0b00011000,
  0b00111100,
  0b00100100,
  0b00100101,
  0b00011111,
  0b00111111,
  0b00100001
},{
  0b00000000,
  0b00100001,
  0b00111111,
  0b00011111,
  0b00100101,
  0b00100100,
  0b00111100,
  0b00011000
},{
  0b00000000,
  0b00011000,
  0b00111000,
  0b00100000,
  0b00110010,
  0b00011110,
  0b00111110,
  0b00100010
},{
  0b00000000,
  0b00100100,
  0b00101110,
  0b00101010,
  0b00101010,
  0b00111010,
  0b00010010,
  0b00000000
},{
  0b00000000,
  0b00000000,
  0b00100100,
  0b00100010,
  0b11111110,
  0b01111100,
  0b00100000,
  0b00000000
},{
  0b00000000,
  0b00000010,
  0b00111110,
  0b00111100,
  0b00000010,
  0b00000010,
  0b00111110,
  0b00111100
},{
  0b00000000,
  0b00111000,
  0b00111100,
  0b00000110,
  0b00000110,
  0b00111100,
  0b00111000,
  0b00000000
},{
  0b00000000,
  0b00111100,
  0b00111110,
  0b00001110,
  0b00011100,
  0b00001110,
  0b00111110,
  0b00111100
},{
  0b00000000,
  0b00100010,
  0b00110110,
  0b00011100,
  0b00001000,
  0b00011100,
  0b00110110,
  0b00100010
},{
  0b00000000,
  0b00111110,
  0b00111111,
  0b00000101,
  0b00000101,
  0b00111101,
  0b00111001,
  0b00000000
},{
  0b00000000,
  0b00100110,
  0b00110010,
  0b00111010,
  0b00101110,
  0b00100110,
  0b00110010,
  0b00000000
}};
const int ALPHABET_LEN = sizeof(ALPHABET)/8;

//definition of numerical bitmaps
const uint8_t NUMBERS[][8] = {
{
  0b00110000,
  0b01110000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b11111100,
  0b00000000
},{
  0b01111000,
  0b11001100,
  0b00001100,
  0b00111000,
  0b01100000,
  0b11001100,
  0b11111100,
  0b00000000
},{
  0b01111000,
  0b11001100,
  0b00001100,
  0b00111000,
  0b00001100,
  0b11001100,
  0b01111000,
  0b00000000
},{
  0b00011100,
  0b00111100,
  0b01101100,
  0b11001100,
  0b11111110,
  0b00001100,
  0b00011110,
  0b00000000
},{
  0b11111100,
  0b11000000,
  0b11111000,
  0b00001100,
  0b00001100,
  0b11001100,
  0b01111000,
  0b00000000
},{
  0b00111000,
  0b01100000,
  0b11000000,
  0b11111000,
  0b11001100,
  0b11001100,
  0b01111000,
  0b00000000
},{
  0b11111100,
  0b11001100,
  0b00001100,
  0b00011000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b00000000
},{
  0b01111000,
  0b11001100,
  0b11001100,
  0b01111000,
  0b11001100,
  0b11001100,
  0b01111000,
  0b00000000
},{
  0b01111000,
  0b11001100,
  0b11001100,
  0b01111100,
  0b00001100,
  0b00011000,
  0b01110000,
  0b00000000
},{
  0b01111100,
  0b11000110,
  0b11001110,
  0b11011110,
  0b11110110,
  0b11100110,
  0b01111100,
  0b00000000
}};
const int NUMBERS_LEN = sizeof(NUMBERS)/8;

const uint8_t ERROR[8] = {
  0b00000000,
  0b01100000,
  0b11110000,
  0b10011010,
  0b10001010,
  0b11000000,
  0b01000000,
  0b00000000
};

//workaround for scope issues
const int NUM_DISPLAYS = 8;
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, NUM_DISPLAYS);

void matrixStart(int numDisplays) {
  Serial.print("\n");
  Serial.print("-------------------------------------");
  Serial.print("\n");
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
  if(led_output.length() > NUM_DISPLAYS)
  {
    Serial.print("String is too long");
    Serial.print("\n");
    return;
  }

  //if text to out output has not changed, quickly set prev_buffer to avoid flickering
  if(led_output == prev_string) {
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
  for(int i = length - 1; i >= 0; i--)
  {
    setBuffer(char_arr[i], counter);
    counter++;
  }
  
  //deallocating dynamic memory used for char arr
  delete[] char_arr;
}

//definition of ASCII ranges
const int NUM_MIN = 48;
const int NUM_MAX = 57;
const int UPPER_MIN = 65;
const int UPPER_MAX = 90;
const int LOWER_MIN = 97;
const int LOWER_MAX = 122;

void setBuffer(char input, int displayNum) {
  //declaring variable to store bitmap
  uint8_t bitmap[8]; 

  //identify char and find to corresponding bitmap
  if(int(input) >= NUM_MIN && int(input) <= NUM_MAX) {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = NUMBERS[int(input) - NUM_MIN][i];
    }
    Serial.print("num");
    Serial.print("\n");
  }

  else if(int(input) >= UPPER_MIN && int(input) <= UPPER_MAX) {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = ALPHABET[int(input) - UPPER_MIN][i];
    }
    Serial.print("upper");
    Serial.print("\n");
  }

  else if(int(input) >= LOWER_MIN && int(input) <= LOWER_MAX) {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = ALPHABET[int(input) - LOWER_MIN + 26][i];
    }
    Serial.print("lower");
    Serial.print("\n");
  }

  else {
    for(int i = 0; i < 8; i++)
    {
      bitmap[i] = ERROR[i];
    }
    Serial.print(displayNum);
    Serial.print("\n");
  }
  
  //set bitmap buffer
  mx.setBuffer(displayNum*SIZE - 1, SIZE, bitmap);
}