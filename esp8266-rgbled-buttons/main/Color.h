#include "Arduino.h"

class Color {
  public:
    Color(int buttonPin, int ledPin, bool initialLedState);
    void switchState();
    int buttonState, buttonPin;
    void setButtonState(int newButtonState);
    int getLedState();
  private:
    int _ledPin;
    int _ledState;
};
