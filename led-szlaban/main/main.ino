#include<Wire.h>

#define LED_1 4
#define LED_2 7

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
}

void loop() {
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, LOW);
  delay(500);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  delay(500);
}
