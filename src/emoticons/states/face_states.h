#pragma once

#ifndef FACE_STATES_H_
#define FACE_STATES_H_

#include <Arduino.h>
#include <FastLED.h>

//#include "../../../crt_channel.h"
//#include "../../../led_canvas.h"

class ChEmoticons;
class LedGraphics;

class FaceState {
  public:
    FaceState(){}
    virtual ~FaceState() {}
    virtual void enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
    virtual FaceState* update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
    virtual void exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
};


//Default: Blink every so often, change mouth by pressing button
class DefaultFaceState : public FaceState{
  public:
    DefaultFaceState();
    ~DefaultFaceState(){}

    void enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    FaceState* update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);

    const int blink_intervals_[8] = {40, 35, 50, 40, 45, 20, 40, 5};

  private:
    
    int blink_timer_; //Number of frames between blinks
    int blink_i_;

};

//Talking: Mouth alternates between open and closed while microphone picks up noise
class TalkingFaceState : public FaceState{
  public:
    TalkingFaceState();
    ~TalkingFaceState(){};

    void enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    FaceState* update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);

  private:

};

//Loading: Tilt head down to show a spinner
class LoadingFaceState : public FaceState{
  public:
    LoadingFaceState();
    ~LoadingFaceState(){};

    void enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    FaceState* update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);

  private:
    int timer_;
    int step_;

};

//Confused: Tilt head to make a question mark appear
class ConfusedFaceState : public FaceState{
  public:
    ConfusedFaceState();
    ~ConfusedFaceState(){};

    void enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    FaceState* update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);

  private:


};

class DotsFaceState : public FaceState{
  public:
    DotsFaceState();
    ~DotsFaceState(){};

    void enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    FaceState* update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY);

  private:
    int timer_;
};

#endif