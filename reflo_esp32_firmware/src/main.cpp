#include <Arduino.h>
#define BAUD 9600
#define VREF 3.3

// global variables used a lot
const double resolution = 4096.0;

// Voltage Sensor init
const int voltage_sensA = 32;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
double value = 0;

// Current Sensor Init
const int current_sensA = 33;
double Vout = 0;
double Current = 0;
const double scale_factor = 0.066;
const double vRef = 3.3;
const double resConvert = 4096.0;
double resADC = vRef / resConvert;
double zeroPoint = vRef / 2;

void read_current() {
  // Vout is read 1000 Times for precision
  for (int i = 0; i < 1000; i++) {
    Vout = (Vout + (resADC * analogRead(current_sensA)));
    delay(1);
  }

  // Get Vout in mv
  Vout = Vout / 1000;

  // Convert Vout into Current using Scale Factor
  Current = (Vout - zeroPoint) / scale_factor;

  // Print Vout and Current to two Current = ");

  Serial.print("Vout = ");
  Serial.print(Vout, 2);
  Serial.print(" Volts");
  Serial.print("\t Current = ");
  Serial.print(Current, 2);
  Serial.println(" Amps");

  delay(1000);
}

void read_voltage() {
  // read the value at analog input
  value = analogRead(voltage_sensA);
  vout = (value * 3.3) / resolution;  // see text
  vin = vout / (R2 / (R1 + R2));
  Serial.print("INPUT V= ");
  Serial.println(vin, 2);
  delay(500);
}

void setup() {
  // set up the baud rate, ensuring that it matches the one you put in the ini
  // file
  Serial.begin(BAUD);
  // Voltage Sensor
  pinMode(voltage_sensA, INPUT);
  // Serial.print("DC VOLTMETER");
  //  Current Sensor
  pinMode(current_sensA, INPUT);
}

void loop() {
  // read_voltage();
  read_current();
}
