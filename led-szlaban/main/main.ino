#include<Wire.h>

#define LED_1 4
#define LED_2 7

#define BUZZER 3

#define BUTTON 2

bool shouldBlinkLed = false;

const long BLINKING_TIME = 10000;
const long BUZZING_TIME = 4000;
const long BLINK_DELAY = 500;

long startTime = 0;
long blinkTime = 0;
//ICACHE_RAM_ATTR
void handleLedTrigger(){
  Serial.println("Button pressed");
  shouldBlinkLed = true;
  startTime = millis();
  blinkTime = startTime;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

long measuredTime = 0;
void blinkLed(){
  measuredTime = millis();
  
  if(measuredTime - blinkTime < BLINK_DELAY){
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
  }
  else if(measuredTime - blinkTime < 2*BLINK_DELAY){
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
  } else {
    blinkTime = millis();
  }
  measuredTime = millis();
  if(measuredTime - startTime < BUZZING_TIME){
   // buzz
    if(measuredTime - blinkTime < BLINK_DELAY){
      digitalWrite(BUZZER, HIGH);
    }
    else if(measuredTime - blinkTime < 2*BLINK_DELAY){
      digitalWrite(BUZZER, LOW);
    }
  }
  else {
    tearDownBuzzer();
  }
  if(measuredTime - startTime >= BLINKING_TIME){
    tearDownBlinking();
  }
}

void tearDownBlinking(){
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  shouldBlinkLed = false;
  startTime = 0;
  blinkTime = 0;
}

void tearDownBuzzer(){
  digitalWrite(BUZZER, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON), handleLedTrigger, RISING);
}

void loop() {
  if(shouldBlinkLed){ 
    blinkLed();
  }
}
