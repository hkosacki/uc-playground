#include<Wire.h>

#define IR_GATE_PIN 2

void setup() {
  pinMode(IR_GATE_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(IR_GATE_PIN), handleInt, FALLING);
}

int readVal = 0;
void loop() {
  readVal = digitalRead(IR_GATE_PIN);
  Serial.println("readVal: " + String(readVal));
  delay(500);
}

void handleInt(){
  Serial.println("Something entered the sensor!");
}
