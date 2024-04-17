#include <MD_MAX72xx.h>

//declaration of alphabetical bitmaps
extern const uint8_t ALPHABET[][8];
extern const int ALPHABET_LEN;

//declaration of numerical bitmaps
extern const uint8_t NUMBERS[][8];
extern const int NUMBERS_LEN;

//declaration of error bitmap
extern const uint8_t ERROR[8];


//declaration of matrix display object
extern MD_MAX72XX mx;

//start function must be called in setup() with numDisplays by user!
void matrixStart(int numDisplays);

//declaration of useful constants
extern const int NUM_DISPLAYS;
extern const int NUM_ROWS;
extern const int SIZE;
extern const int NUM_COLS;

//declaration of prev string global
extern String prev_string;

//declaration of prev bitmap global
extern uint8_t prev_bitmap[];

void matrixWrite(String output);

void stringParse(String input);

//declaration of constants used for ASCII ranges
extern const int NUM_MIN;
extern const int NUM_MAX;
extern const int UPPER_MIN;
extern const int UPPER_MAX;
extern const int LOWER_MIN;
extern const int LOWER_MAX;

void setBuffer(char input, int displayNum);

