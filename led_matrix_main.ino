#include "led_matrix.h"

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  matrixStart(4);
}

void loop() {
  // put your main code here, to run repeatedly:
  matrixWrite("Te");
}