class State {
  public: 
    State(int redState, int yellowState, int greenState, int durationTime);
    int getRedState();
    int getYellowState();
    int getGreenState();
    int getDuration();
  private:
    int _redState, _yellowState, _greenState, _duration;
};
