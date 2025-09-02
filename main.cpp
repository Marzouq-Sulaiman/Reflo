/**
 * ATTENTION: Do NOT add code to this file; add all "main" code that you wish to
 * be run in the cpp file found in reflo_esp_32_firmware/src/main.cpp This was
 * the old main file before PlatformIO was configured. It will likely be removed
 * in future
 */

#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Setup done");
}

void loop() {
  Serial.println("Looping");
  delay(1000);
}