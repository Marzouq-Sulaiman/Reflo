#include <Thermistor.h>


Thermistor therm1(0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int temperature = int(thermo1.getTemp());
  
  Serial.println(temperature);
  delay(1000);

/**
 * TODO: Will be adding improved sensitivity before Myhal testing. See https://lastminuteengineers.com/esp32-basics-adc/ or Reflo Spreadsheet row 6
 */

}