#pragma once

#ifndef CH_ERRORS_H_
#define CH_ERRORS_H_

#include <Arduino.h>
#include <FastLED.h>

#include "../../crt_channel.h"

class ErrorState;
class LedGraphics;

class ChErrors : public CrtChannel{
  public:
    ChErrors();
    ~ChErrors();

    void enter(LedGraphics* g, int input, float mZ, float mY);
    void update(LedGraphics* g, int input, float mZ, float mY);
    void exit(LedGraphics* g, int input, float mZ, float mY);

    int input_lockout_;

  private:
    ErrorState* error_state_; //DEFINE CUSTOM DESTRUCTOR TO FREE THIS MEMORY
    
};

#endif