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

DeviceAddress sensorAddress;
bool sensorFound = false;

String addressToString(const DeviceAddress address) {
  String result = "";
  for (int i = 0; i < 8; i++) {
    if (address[i] < 0x10) {
      result += "0";
    }
    result += String(address[i], HEX);
  }
  result.toUpperCase();
  return result;
}

String judgeTemperature(float temp) {
  if (temp < 10) return "Cold!";
  if (temp < 15) return "Cool";
  if (temp < 25) return "Perfect";
  if (temp < 30) return "Warm";
  if (temp < 35) return "Hot";
  return "Too Hot!";
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("Temperature Application");

  DS18B20.begin();

  // we only have one sensor, so look for the one at index 0
  if (!DS18B20.getAddress(sensorAddress, 0)) {
    Serial.println("No DS18B20 temperature sensors are installed!");
    return;
  }

  sensorFound = true;
  Serial.println("Found DS18B20 sensor with address: " + addressToString(sensorAddress));
}

void loop() {
  // nothing to do without a sensor
  if (!sensorFound) {
    delay(1000);
    return;
  }

  DS18B20.requestTemperatures();
  float fTemp = DS18B20.getTempC(sensorAddress);

  if (fTemp == DEVICE_DISCONNECTED_C) {
    Serial.println("Lost contact with the DS18B20 sensor!");
  } else {
    Serial.println("Current temperature is: " + String(fTemp) + "° C or " + judgeTemperature(fTemp));
  }

  delay(5000);
}
