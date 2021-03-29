#include "Arduino.h"
#include "Color.h"

Color::Color(int buttonPin, int ledPin, bool initialLedState){
  this->buttonPin = buttonPin;
  _ledPin = ledPin;
  _ledState = initialLedState;
  pinMode(buttonPin, INPUT);
  pinMode(_ledPin, OUTPUT);
  buttonState = 0;
};

void Color::switchState(){
  _ledState = !_ledState;
  digitalWrite(_ledPin, _ledState ? HIGH : LOW);
}

void Color::setButtonState(int newButtonState){
  this->buttonState = newButtonState;
}

int Color::getLedState(){
  return _ledState;
}
