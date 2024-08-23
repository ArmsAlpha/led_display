#pragma once

#ifndef ERROR_STATES_H_
#define ERROR_STATES_H_

#include <Arduino.h>
#include <FastLED.h>

class ChErrors;
class LedGraphics;

class ErrorState {
  public:
    ErrorState(){}
    virtual ~ErrorState() {}
    virtual void enter(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
    virtual ErrorState* update(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
    virtual void exit(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY) = 0;
};

class SMPTEErrorState : public ErrorState{
  public:
    SMPTEErrorState();
    ~SMPTEErrorState(){}

    void enter(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);
    ErrorState* update(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);

  private:
    int entered_;

};

class StaticErrorState : public ErrorState{
  public:
    StaticErrorState();
    ~StaticErrorState(){}

    void enter(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);
    ErrorState* update(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);

  private:


};

class BSODErrorState : public ErrorState{
  public:
    BSODErrorState();
    ~BSODErrorState(){}

    void enter(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);
    ErrorState* update(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);
    void exit(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY);

  private:


};

#endif