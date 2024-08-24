#pragma once

#ifndef EYEBALL_STATES_H_
#define EYEBALL_STATES_H_

#include <Arduino.h>
#include <FastLED.h>

class ChEyeball;
class LedGraphics;

class EyeballState {
  public:
    EyeballState(){}
    virtual ~EyeballState() {}
    virtual void enter(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
    virtual EyeballState* update(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
    virtual void exit(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
};


//Default: Blink every so often, change mouth by pressing button
class DefaultEyeballState : public EyeballState{
  public:
    DefaultEyeballState();
    ~DefaultEyeballState(){}

    int remapZ(float t_z);
    int remapY(float t_y);

    void enter(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY);
    EyeballState* update(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY);

    const int blink_intervals_[8] = {40, 35, 50, 40, 45, 20, 40, 5};

  private:
    
    int blink_timer_; //Number of frames between blinks
    int blink_i_;

};

#endif