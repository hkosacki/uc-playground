#include "State.h"

State::State(int redState, int yellowState, int greenState, int durationTime){
  this->_redState = redState;
  this->_yellowState = yellowState;
  this->_greenState = greenState;
  this->_duration = durationTime;
};

int State::getRedState(){
  return _redState;
}

int State::getYellowState(){
  return _yellowState;
}

int State::getGreenState(){
  return _greenState;
}

int State::getDuration(){
  return _duration;
}
