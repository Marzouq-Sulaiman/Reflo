#include <Arduino.h>

const double resolution = 4096.0;

// Voltage Sensor init
const int voltage_sensA = 32;
float v_voutA = 0.0;
float v_vinA = 0.0;
float v_R1A = 30000.0;
float v_R2A = 7500.0;
double v_valueA = 0;
double Vref = 1.1;  // reference voltage of ADC with attenuation = 0db

double read_voltage() {
  // read the value at analog input
  v_valueA = analogRead(voltage_sensA);
  v_voutA = (v_valueA * Vref) / resolution;  // see text
  v_vinA = v_voutA / (v_R2A / (v_R1A + v_R2A));
  // Serial.print("INPUT V= ");
  // Serial.println(v_vinA, 2);
  // delay(500);
  return v_vinA;
}

struct CalV {
  float v_meas;
  float v_true;
};

// Replace with your measured pairs; SORT by v_meas ascending
static const CalV CAL[] = {{0.70f, 0.69f}, {0.72f, 0.71f},  {0.74f, 0.73f},
                           {0.77f, 0.75f},  // example “bad” region
                           {0.79f, 0.77f}, {0.81f, 0.79f},  {0.82f, 0.80f},
                           {0.85f, 0.82f}, {0.855f, 0.83f}, {0.86f, 0.84f},
                           {0.88f, 0.85f}, {0.89f, 0.86f}};
static const size_t N = sizeof(CAL) / sizeof(CAL[0]);

// Linear interpolation on v_meas
float correct_voltage(float v_meas) {
  if (v_meas <= CAL[0].v_meas) return CAL[0].v_true;
  if (v_meas >= CAL[N - 1].v_meas) return CAL[N - 1].v_true;

  size_t lo = 0, hi = N - 1;
  while (hi - lo > 1) {
    size_t mid = (lo + hi) >> 1;
    if (CAL[mid].v_meas <= v_meas)
      lo = mid;
    else
      hi = mid;
  }
  float x0 = CAL[lo].v_meas, y0 = CAL[lo].v_true;
  float x1 = CAL[hi].v_meas, y1 = CAL[hi].v_true;
  return y0 + (y1 - y0) * ((v_meas - x0) / (x1 - x0));
}

// Example: produce the same "uncalibrated" V_meas you used during calibration
float read_uncalibrated_voltage() {
  const int PIN = 32;
  const int N = 10;           // you used 10 samples
  const float RES = 4096.0f;  // 12-bit → 0..4095
  const float VREF =
      1.1;  // <-- set to EXACTLY what you used before (e.g. 3.3 or 3.9)

  double acc = 0.0;
  for (int i = 0; i < N; ++i) {
    acc += analogRead(PIN);
    delay(10);
  }
  double value = acc / double(N);
  float voltage = float(value / RES) * VREF;  // our original formula
  return voltage;                             // this is V_meas for the LUT
}

void setup() {
  // put your setup code here, to run once:
  pinMode(32, INPUT);
  Serial.begin(9600);
  analogReadResolution(12);
  analogSetPinAttenuation(32, ADC_0db);  // allow ~0–3.3V on GPIO32
}

void loop() {
  float v_meas =
      read_uncalibrated_voltage();  // same method as during calibration
  float v_corr;
  float Vfinal;

  //if (v_meas > 0.69) {
  Serial.printf("SECTION 1");  
    v_corr = correct_voltage(v_meas);  // calibrated estimate
    Serial.printf("corr=%.2f V\n", v_corr);
    Serial.println();
    Serial.println();
    Serial.printf("Actual Voltage: %.2f", v_corr * 5.0);
    Serial.println();

  //}

  //else {
  Serial.printf("      ");
  Serial.printf("SECTION 2");
    Serial.printf("meas=%.2f V\n", v_meas);  // below LUT range, no correction
    Serial.println();
    Serial.println();
    Serial.printf("Actual Voltage: %.2f", v_meas * 5.0);
    Serial.println();
    
  //}

  // Serial.printf("meas=%.2f V  corr=%.2f V\n", v_meas, v_corr);
  delay(50);

  // //HERE HERE
  //   //put your main code here, to run repeatedly:
  //   double value = 0;
  //   for (int i = 0; i < 10; i++) {
  //     //value += read_voltage();
  //     value += analogRead(32);
  //     delay(10);
  //   }

  //   value = value / 10.0;
  //   // double value = analogRead(32);

  //    double voltage = (value / resolution) * Vref;   //Voltage at ADC pin

  //   //Serial.println(value);
  //   Serial.println(voltage, 2);
  //   delay(100);

  // //HERE HERE
}