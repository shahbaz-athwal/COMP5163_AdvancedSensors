// Acadia University - COMP 5163
//
// Lab Application - Advanced Sensors
//
// I, Shahbaz Singh, certify that this program is my
// own work and has not been copied from any other source.
//
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// DS18B20 data line on D3 (4.7k pull-up to 3V3)
const int oneWireBus = D3;

OneWire oneWire(oneWireBus);
DallasTemperature DS18B20(&oneWire);

void setup() {
  Serial.begin(115200);
  DS18B20.begin();
}

void loop() {
  DS18B20.requestTemperatures();
  float fTemp = DS18B20.getTempCByIndex(0);
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius");
  delay(2000);
}
