#pragma once
#include <Arduino.h>
#include <FastLED.h>
//class Drawable;
class Canvas
{
  public:
    //Point where the board connects to the LED display
    enum Origin{
      ORIGIN_NW,
      ORIGIN_NE,
      ORIGIN_SW,
      ORIGIN_SE
    };

    //Vertical or Horizontal Weapping
    enum Wrap{
      WRAP_H,
      WRAP_V
    };

    //Constructors:
    Canvas(int t_x, int t_y, CRGB *t_leds, CRGB* t_buffer, Origin t_o=ORIGIN_NW, Wrap t_wr=WRAP_H, int t_s=0);

    //Accessors:
    int getWidth();
    int getHeight();
    int getSize();
    CRGB* getLEDs();
    CRGB* getBuffer();
    CRGB getPoint(int t_x, int t_y);
    
    //Utilities
    int inboundsX(int t_x);
    int inboundsY(int t_y);
    int inbounds(int t_x, int t_y);

    //Helpers:
    int toIndex(int t_x, int t_y); //Converts X-Y coords to corresponding array index
    int toXY(int t_i); //Converts given index to X-Y coords.
    int remapIndex(int t_i); //Remaps index to fit the assigned layout of LEDS and returns index i
    int remapXY(int t_x, int t_y); //Remaps coordinates to fit the assigned layout of LEDs and returns index i

    //Update
    void update(); //Copy (and translate) the buffer array to the main array used by FastLED

  private:

    void init(int t_x, int t_y, CRGB *t_leds, CRGB *t_buffer, Origin t_o, Wrap t_wr, int t_s);

    int width;
    int height;
    int origin; //Denotes starting corner of matrix
    int wrap; //Denotes wrap direction (horizontal or vertical)
    int snake; //Denotes whether row directions alternate or remain the same

    static word font[];
    CRGB* leds;
    CRGB* leds_buffer;
};
