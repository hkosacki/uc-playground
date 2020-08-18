#define BUZZER 11

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {  
    analogWrite(BUZZER, 255);
}
