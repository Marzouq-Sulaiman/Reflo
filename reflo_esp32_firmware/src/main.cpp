#include <Arduino.h>
#define BAUD 9600

// global variables used a lot
const double resolution = 4096.0;

// Voltage Sensor init
const int voltage_sensA = 32;
float v_voutA = 0.0;
float v_vinA = 0.0;
float v_R1A = 30000.0;
float v_R2A = 7500.0;
double v_valueA = 0;

// Current Sensor Init
const int current_sensA = 33;
double i_voutA = 0;
double currentA = 0;
const double i_scale_factorA = 0.066;
const double i_vRefA = 3.3;
double i_resADC_A = i_vRefA / resolution;
double zeroPoint = i_vRefA / 2;

void read_current() {
  // Vout is read 1000 Times for precision
  for (int i = 0; i < 1000; i++) {
    i_voutA = (i_voutA + (i_resADC_A * analogRead(current_sensA)));
    delay(1);
  }

  // Get Vout in mv
  i_voutA = i_voutA / 1000;

  // Convert Vout into Current using Scale Factor
  currentA = (i_voutA - zeroPoint) / i_scale_factorA;

  // Print Vout and Current to two Current = ");

  Serial.print("Vout = ");
  Serial.print(i_voutA, 2);
  Serial.print(" Volts");
  Serial.print("\t Current = ");
  Serial.print(currentA, 2);
  Serial.println(" Amps");

  delay(1000);
}

void read_voltage() {
  // read the value at analog input
  v_valueA = analogRead(voltage_sensA);
  v_voutA = (v_valueA * 3.3) / resolution;  // see text
  v_vinA = v_voutA / (v_R2A / (v_R1A + v_R2A));
  Serial.print("INPUT V= ");
  Serial.println(v_vinA, 2);
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
