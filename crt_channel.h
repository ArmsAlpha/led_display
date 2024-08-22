#pragma once

#ifndef CRT_CHANNEL_H_
#define CRT_CHANNEL_H_

#include <Arduino.h>
#include <FastLED.h>

#include "led_canvas.h"
#include "led_graphics.h"

class CrtChannel{
  public:
    CrtChannel(){}
    virtual ~CrtChannel() {}
    virtual void enter(LedGraphics* g) = 0;
    virtual void update(LedGraphics* g) = 0;
    virtual void exit(LedGraphics* g) = 0;

  private:

};

#endif