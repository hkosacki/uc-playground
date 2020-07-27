#include<Wire.h>
#include "Color.h"

#define LED_R 13
#define LED_G 12
#define LED_B 14

#define BUTTON_R 4
#define BUTTON_G 5
#define BUTTON_B 16

int STATE_R = 0;
int STATE_G = 0;
int STATE_B = 0;

Color R(BUTTON_R, LED_R, STATE_R);
Color G(BUTTON_G, LED_G, STATE_G);
Color B(BUTTON_B, LED_B, STATE_B);

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON_R, INPUT);
  pinMode(BUTTON_G, INPUT);
  pinMode(BUTTON_B, INPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  Serial.println("Started!");
}

void loop() {
  handleColor(R);
  handleColor(G);
  handleColor(B);
}

int newButtonState = 0;
void handleColor(Color &color) {
  int newButtonState = digitalRead(color.buttonPin);
  if(newButtonState != color.buttonState){
    color.setButtonState(newButtonState);
    if(color.buttonState == 1) {
      color.switchState();
    }
  }
  delay(10);
}
