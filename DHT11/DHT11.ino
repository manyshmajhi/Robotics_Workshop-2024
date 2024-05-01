#include "DHT.h"
#define DHTpin 8
DHT dht(DHTpin, DHT11);

void setup() {
  pinMode(DHTpin, INPUT);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  float tempInC = dht.readTemperature();
  Serial.print("Temperature = " + String(tempInC) + "°C");
  float humidity = dht.readHumidity();
  Serial.println("\tHumidity = " + String(humidity) + "%");
}
