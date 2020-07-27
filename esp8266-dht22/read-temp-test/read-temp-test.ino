#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.println("Initializing...");
  Serial.begin(9600);
  Serial.setTimeout(3000);

  while(!Serial) { /* wait */ }

  dht.begin();
  Serial.println("Device started - running DHT");
}

int timeSinceLastRead = 0;

void loop() {
  if (timeSinceLastRead > 2000){
    float h = dht.readHumidity();
    float t = dht.readTemperature();

//    if(isnan(h) || isnan(t)) {
//      Serial.println("Error while reading the sensor data!");
//      timeSinceLastRead = 0;
//      return;
//    }

    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("Temperature *C: ");
    Serial.println(t);
    Serial.print("Heat index *C: ");
    Serial.println(hic);

    timeSinceLastRead = 0;
  }

  delay(100);
  timeSinceLastRead += 100;

}
