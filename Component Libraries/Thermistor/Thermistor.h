#include "Arduino.h"

#ifndef Thermistor.h
#define Thermistor.h


class Thermistor{
    public:
        Thermistor(int pin);
        Thermistor(int pin, int pinResolution);       //12 bit by default for ESP32
        double getTemp();
    
    private:
        int pin;
        int pinResolution;
};

#endif
