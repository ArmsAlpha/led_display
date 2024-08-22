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
    virtual void enter(ChEmoticons& ch, LedGraphics* g) = 0;
    virtual FaceState* update(ChEmoticons& ch, LedGraphics* g) = 0;
    virtual void exit(ChEmoticons& ch, LedGraphics* g) = 0;
};


class DefaultFaceState : public FaceState{
  public:
    DefaultFaceState();
    ~DefaultFaceState(){}

    void enter(ChEmoticons& ch, LedGraphics* g);
    FaceState* update(ChEmoticons& ch, LedGraphics* g);
    void exit(ChEmoticons& ch, LedGraphics* g);

  private:
    int blink_timer_ = 0;

};


class TalkingFaceState : public FaceState{
  public:
    TalkingFaceState();
    ~TalkingFaceState();

    void enter(ChEmoticons& ch, LedGraphics* g);
    FaceState* update(ChEmoticons& ch, LedGraphics* g);
    void exit(ChEmoticons& ch, LedGraphics* g);

  private:

};


class DazedFaceState : public FaceState{
  public:
    DazedFaceState();
    ~DazedFaceState();

    void enter(ChEmoticons& ch, LedGraphics* g);
    FaceState* update(ChEmoticons& ch, LedGraphics* g);
    void exit(ChEmoticons& ch, LedGraphics* g);

  private:

};


class ConfusedFaceState : public FaceState{
  public:
    ConfusedFaceState();
    ~ConfusedFaceState();

    void enter(ChEmoticons& ch, LedGraphics* g);
    FaceState* update(ChEmoticons& ch, LedGraphics* g);
    void exit(ChEmoticons& ch, LedGraphics* g);

  private:

};

#endif