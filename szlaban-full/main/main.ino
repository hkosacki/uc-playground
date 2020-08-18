#include<Wire.h>
#include<Servo.h>

#define LED_1 6
#define LED_2 7
#define BUZZER 8

#define SERVO_1 11
#define SERVO_2 12

#define INT_1 2
#define INT_2 3

const long BUZZING_TIME = 3000;
const long BLINK_DELAY = 500;

Servo lock1, lock2;

volatile bool shouldBlock = false;
volatile bool shouldBlinkLed = false;

enum ServoDirection {
  UP = 0,
  DOWN = 100
};

long startTime = 0;
long blinkTime = 0;
long rotateTime = 0;

void tearDownBlinking(){
  tearDownLed();
  shouldBlock = false;
  startTime = 0;
  blinkTime = 0;
}

void tearDownLed(){
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  shouldBlinkLed = false;
}

void tearDownBuzzer(){
  digitalWrite(BUZZER, LOW);
}



void enableLock(){
  Serial.println("Starting lock");
  shouldBlock = true;
  shouldBlinkLed = true;
  startTime = millis();
  blinkTime = startTime;
}

void disableLock(){
  Serial.println("Finishing lock");  
  shouldBlock = false;
}

long measuredTime = 0;
void block(){
  measuredTime = millis();
  
  blinkThings();
  measuredTime = millis();
  
  // buzz
  if(measuredTime - startTime > BUZZING_TIME && !rotateWing(DOWN)){
    tearDownBuzzer();
  } else {
    int buzzingTime = measuredTime - blinkTime;
    if(buzzingTime < BLINK_DELAY){
      digitalWrite(BUZZER, HIGH);
    }
    else if(buzzingTime < 2*BLINK_DELAY){
      digitalWrite(BUZZER, LOW);
    }
  }
  
}

bool rotateWing(ServoDirection dir){
  int currentPosition = lock1.read();
//  Serial.println("curr pos: " + String(currentPosition) + ", going " + String(dir));
  if(currentPosition == dir) return false;
//  Serial.println("diff " + String(measuredTime - rotateTime));
  if(measuredTime - rotateTime > 50){
//    Serial.println("Entered rotation: " + String(dir));
    rotateTime = measuredTime;
    int step = dir == UP ? -1 : 1;
    currentPosition += step;
    lock1.write(currentPosition);
    lock2.write(currentPosition);
//    delay(150);
  }
  return true;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(SERVO_1, OUTPUT);
  pinMode(SERVO_2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(INT_1, INPUT_PULLUP);
  pinMode(INT_2, INPUT_PULLUP);

  lock1.attach(SERVO_1);
  lock2.attach(SERVO_2);

  attachInterrupt(digitalPinToInterrupt(INT_1), enableLock, FALLING);
  attachInterrupt(digitalPinToInterrupt(INT_2), disableLock, FALLING);
  lock1.write(UP);
  lock2.write(UP);
}

void loop() {
  if(shouldBlock){
    block();
  } else {
    unblock();
  }
}

void unblock(){
    // should unblock or idle 
    tearDownBuzzer();
    blinkThings();
    measuredTime = millis();
    //first - locks should go up
    if(!rotateWing(UP)){
      // once up - disable led
      tearDownLed();
    }
}

void blinkThings(){
  if(!shouldBlinkLed) return;
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
}
