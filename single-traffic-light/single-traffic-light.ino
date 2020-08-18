#include "State.h"

#define RED 14
#define GREEN 12
#define YELLOW 13

State Red(HIGH, LOW, LOW, 10000);
const State RedYellow(HIGH, HIGH, LOW, 1500);
const State Green(LOW, LOW, HIGH, 10000);
const State Yellow(LOW, HIGH, LOW, 3000);

//enum LightState {
//  red, redyellow, green, yellow
//}

State states[4] = { Red, RedYellow, Green, Yellow };

//State lightStateToState(LightState state) {
//  State mapped;
//  switch(state){
//    case red: mapped = Red; break;
//    case redyellow: mapped = RedYellow; break;
//    case green: mapped = Green; break;
//    case yellow: mapped = Yellow; break;
//  }
//  return mapped;
//}

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
}

int i = 0;
void loop() {
  setStateAndWait(states[i]);
  i++;
  i %= 4;
}


void setStateAndWait(State state){
  digitalWrite(RED, state.getRedState());
  digitalWrite(GREEN, state.getGreenState());
  digitalWrite(YELLOW, state.getYellowState());
  
  delay(state.getDuration());
}
