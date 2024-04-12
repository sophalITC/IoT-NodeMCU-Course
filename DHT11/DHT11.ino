#include <DHT.h>                // Include DHT sensor library
#define DHTTYPE DHT11        // Define type of sensor 
#define DHTPIN  D4              // Define connected pin

DHT dht(DHTPIN, DHTTYPE, 15);   // Initial DHT sensor

void setup()
{
  dht.begin();                  // Start DHT sensor operation
  Serial.begin(115200);         // Start Serial
}
void loop()
{
  if (dht.read()) {
    float humid = dht.readHumidity();     // Read humidity data
    float temp = dht.readTemperature();   // Read temperature data
    Serial.println(String("Humidity: ") + humid + String("%"));       // Show humidity value in %RH
    Serial.println(String("Temperature: ") + temp + String("C"));        // Show temperature value in Celcuis
    delay(2000);
  }
  else{
    Serial.println("Failed to read from sensor");
  }
  delay(2000);
}
