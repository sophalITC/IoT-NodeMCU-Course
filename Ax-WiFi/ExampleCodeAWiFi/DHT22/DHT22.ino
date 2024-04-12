#include "DHT.h"
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht (DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  } else {
    Serial.println("H: " + String(h, 0) + " % - " + "T: " + String(t, 1) + " ");
    delay(2000);
  }
}
