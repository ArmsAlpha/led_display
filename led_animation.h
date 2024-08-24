#pragma once

#ifndef LED_ANIMATION_H_
#define LED_ANIMATION_H_

#include <Arduino.h>
#include <FastLED.h>

//#include "led_canvas.h"
//#include "led_animation.h"

class LedAnimation {
  public:
    LedAnimation(){}
    virtual ~LedAnimation() {}
    virtual void update() = 0;
};

#endif