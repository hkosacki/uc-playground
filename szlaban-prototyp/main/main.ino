/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 28 May 2015
  by Michael C. Miller
  modified 8 Nov 2013
  by Scott Fitzgerald

  http://arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

enum Servo_Direction {
  UP = 0,
  DOWN = 180
};

void setup() {
  myservo.attach(11);  // attaches the servo on GIO2 to the servo object
  myservo2.attach(0);  // attaches the servo on GIO2 to the servo object
}

void loop() {
  rotateWing(UP);
  delay(5000);
  rotateWing(DOWN);
  delay(5000);
}

void rotateWing(Servo_Direction dir){
  int initialPosition = myservo.read();
  int step = dir == UP ? -1 : 1;
  for(int pos = initialPosition; pos != dir +0; pos += step){
    myservo.write(pos);
    myservo2.write(pos);
    delay(150);
  }
}
