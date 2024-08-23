#pragma once

#ifndef CH_EYEBALL_H_
#define CH_EYEBALL_H_

#include <Arduino.h>
#include <FastLED.h>

#include "../../crt_channel.h"

class EyeballState;
class LedGraphics;

class ChEyeball : public CrtChannel{
  public:
    ChEyeball();
    ~ChEyeball();

    void enter(LedGraphics* g, int input, float mZ, float mY);
    void update(LedGraphics* g, int input, float mZ, float mY);
    void exit(LedGraphics* g, int input, float mZ, float mY);

    int eyelid_;

  private:
    EyeballState* eyeball_state_; //DEFINE CUSTOM DESTRUCTOR TO FREE THIS MEMORY
    
};

#endif