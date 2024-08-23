#pragma once

#ifndef CH_EMOTICONS_H_
#define CH_EMOTICONS_H_

#include <Arduino.h>
#include <FastLED.h>

#include "../../crt_channel.h"
//#include "../../led_canvas.h"
//#include "states/face_states.h"
class FaceState;
class LedGraphics;

class ChEmoticons : public CrtChannel{
  public:
    ChEmoticons();
    ~ChEmoticons();

    void enter(LedGraphics* g, int input, float mZ, float mY);
    void update(LedGraphics* g, int input, float mZ, float mY);
    void exit(LedGraphics* g, int input, float mZ, float mY);
    int eyes_i_;
    int mouth_i_;
    int input_lockout_;
    int state_lockout_;

  private:
    FaceState* face_state_; //DEFINE CUSTOM DESTRUCTOR TO FREE THIS MEMORY
    
};

#endif


//if using an animation for blinking, have a variable to keep track of frame #. either store in separate animation class or
//have a set number of timers for the channel (maybe an array?)

//how to handle arduino stuff from within the channel? can global variables and arduino functions be accessed from within the class without problems?

//how to access canvas info and drawing functions from within the channel? store pointer to canvas and graphics or pass as arg

//