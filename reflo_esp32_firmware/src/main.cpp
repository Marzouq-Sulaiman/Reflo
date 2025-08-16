#include <Arduino.h>

float read_current();
float read_voltage();

void setup() {
  // set up the baud rate, ensuring that it matches the one you put in the ini file
  Serial.begin(115200);  
}

void loop() {
  
}

