#pragma once
#include "qdbmp.h"
#include <Arduino.h>
#include <FastLED.h>
class Drawable;
//TODO: Figure out how to usr objects/shapes as masks for effects
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
    Canvas( t_x,  t_y, CRGB *t_leds, Origin t_o=ORIGIN_NW, Wrap t_wr=WRAP_H,  t_s=0);

    //Accessors:
     getWidth();
     getHeight();
    int getSize();
    CRGB* getLEDs();
    CRGB* getBuffer();
    BMP* getBitmap();
    CRGB getPoint( t_x,  t_y);
    
    //Utilities
     inboundsX( t_x);
     inboundsY( t_y);
     inbounds( t_x,  t_y);
    void printCanvas(); //Prints contents of canvas using Serial.println()

    //Helpers:
    int toIndex(int t_x, int t_y); //Converts X-Y coords to corresponding array index
     toXY(int t_i); //Converts given index to X-Y coords.
    int remapIndex(int t_i); //Remaps index to fit the assigned layout of LEDS and returns index i
    int remapXY(int t_x, int t_y); //Remaps coordinates to fit the assigned layout of LEDs and returns index i
    
    //Draw Functions:
    void drawPoint( x,  y, CRGB t_color,  t_a);
    void drawRect( x,  y,  dx,  dy, CRGB t_color);
    void drawLine( x,  y,  x2,  y2, CRGB t_color);
    
    //TODO: Replace drawSprite series with drawBMP, make size scalable
    void drawSprite( x,  y,  s_x,  s_y,  *sprite, CRGB *palette);
    void drawSprite8( x,  y,  s_x,  s_y,  *sprite, CRGB t_color);
    void drawSprite16( x,  y,  s_x,  s_y, uint16_t *sprite, CRGB t_color);
    void drawSprite32( x,  y,  s_x,  s_y, uint32_t *sprite, CRGB t_color);
    
    void drawChar(char character,  x,  y, CRGB t_color);
    void drawString(char str[],  x,  y, CRGB t_color);

    //BMP Functions
    void newBitmap();
    void fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb);
    void blitBitmap(int i0, int x0, int y0, int dx, int dy);
    void renderXpm(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB crgb); //Render bmp at coordinates

    void drawObj(Drawable *t_d); //Calls draw() for the specified object

    //Effects:
    void linearFade( amount); //Fades out every LED by a certain amount
    void linearFade(Drawable Mask); //TODO: maybe get id of this and use default arguments instead
    void erase(); //Clears entire canvas
    void eraseArea( x,  y,  dx,  dy, CRGB t_color); //Clears canvas in rectangular area

    //Update
    void update(); //Copy (and translate) the buffer array to the main array used by FastLED

  protected:
     width;
     height;
     origin; //Denotes starting point of matrix
     wrap; //Denotes wrap direction (horizontal or vertical)
     snake; //Denotes whether row directions alternate or stay the same
    static word font[];
    CRGB* leds; //TODO: Should the leds operate using RGB or HSV? Note: HSV can convert to RGB but not vice-versa, but HSV is better for color math (how expenive is constant conversion? and is there a loss in coplor quality?)
    CRGB* leds_buffer;
    BMP* bmp;
};
