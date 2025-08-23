#include "Arduino.h"

#include "Thermistor.h"

Thermistor::Thermistor(int pin) {
  this->pin = pin;
  this->pinResolution = 12;     //ESP32 ADC is by default 12-bit
}

Thermistor::Thermistor(int pin, int pinResolution) {
  this->pin = pin;
  this->pinResolution = pinResolution;
}

/**
 * Returns the temperature of the 10K thermistor in celsius by reading the associated ADC pin and performing relevant calculations
 */
double Thermistor::getTemp() {

  int ADC = analogRead(this->pin);

  double resistance;
  double temp;

  //For 10k Thermistor, Resistance = (1024/ADC)
  if(this->pinResolution == 10){Resistance=((10240000/ADC) - 10000);} //10 bit
  else if(this->pinResolution == 11){Resistance=((20480000/ADC) - 10000);} //11 bit
  else if(this->pinResolution == 12){Resistance=((40960000/ADC) - 10000);} //12 bit
  else if(this->pinResolution == 13){Resistance=((81960000/ADC) - 10000);} //13 bit
  else if(this->pinResolution == 14){Resistance=((163840000/ADC) - 10000);} //14 bit
  else if(this->pinResolution == 15){Resistance=((327680000/ADC) - 10000);} //15 bit
  else if(this->pinResolution == 16){Resistance=((655360000/ADC) - 10000);} //16 bit

  // Steinhart-Hart Thermistor Equation:				
  //    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}		
  //    where A = 0.001129148, B = 0.000234125 and C = 8.76741E-08	
  temp = log(Resistance);
  temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));
  temp = temp - 273.15;     convert Kelvin to Celsius

//   remove lines with * to get serial print of data
//   Serial.print("ADC: "); Serial.print(RawADC); Serial.print("/1024");  // Print out RAW ADC Number
//   Serial.print(", Volts: "); printDouble(((RawADC*4.860)/1024.0),3);   // 4.860 volts is what my USB Port outputs.
//   Serial.print(", Resistance: "); Serial.print(Resistance); Serial.print("ohms");
  
  return temp;  // Return the Temperature
}
