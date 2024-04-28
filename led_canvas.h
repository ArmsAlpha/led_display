#pragma once
#include "qdbmp.h"
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
    Canvas(uint8_t t_x, uint8_t t_y, CRGB *t_leds, Origin t_o=ORIGIN_NW, Wrap t_wr=WRAP_H, uint8_t t_s=0);

    //Accessors:
    uint8_t getWidth();
    uint8_t getHeight();
    int getSize();
    CRGB* getLEDs();
    CRGB* getBuffer();
    BMP* getBitmap();
    CRGB getPoint(int8_t t_x, uint8_t t_y);
    
    uint8_t inboundsX(uint8_t t_x);
    uint8_t inboundsY(uint8_t t_y);
    uint8_t inbounds(uint8_t t_x, uint8_t t_y);
    void printCanvas(); //Prints contents of canvas using Serial.println()

    //Helpers:
    int toIndex(int t_x, int t_y); //Converts X-Y coords to corresponding array index
    uint8_t toXY(int t_i); //Converts given index to X-Y coords.
    int remapIndex(int t_i); //Remaps index to fit the assigned layout of LEDS and returns index i
    int remapXY(int t_x, int t_y); //Remaps coordinates to fit the assigned layout of LEDs and returns index i
    
    //Draw Functions:
    void drawPoint(uint8_t x, uint8_t y, CRGB t_color, uint8_t t_a);
    void drawRect(int8_t x, int8_t y, uint8_t dx, uint8_t dy, CRGB t_color);
    void drawLine(int8_t x, int8_t y, int8_t x2, int8_t y2, CRGB t_color);
    
    //TODO: Replace drawSprite series with drawBMP, make size scalable
    void drawSprite(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t *sprite, CRGB *palette);
    void drawSprite8(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t *sprite, CRGB t_color);
    void drawSprite16(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint16_t *sprite, CRGB t_color);
    void drawSprite32(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint32_t *sprite, CRGB t_color);
    
    void drawChar(char character, int8_t x, int8_t y, CRGB t_color);
    void drawString(char str[], int8_t x, int8_t y, CRGB t_color);

    void drawObj(Drawable *t_d); //Calls draw() for the specified object

    //Effects:
    void linearFade(uint8_t amount); //Fades out every LED by a certain amount
    void linearFade(Drawable Mask); //TODO: maybe get id of this and use default arguments instead
    void erase(); //Clears entire canvas
    void eraseArea(int8_t x, int8_t y, uint8_t dx, uint8_t dy, CRGB t_color); //Clears canvas in rectangular area

    //Update
    void update(); //Copy (and translate) the buffer array to the main array used by FastLED

  protected:
    uint8_t width;
    uint8_t height;
    uint8_t origin; //Denotes starting point of matrix
    uint8_t wrap; //Denotes wrap direction (horizontal or vertical)
    uint8_t snake; //Denotes whether row directions alternate or stay the same
    static word font[];
    CRGB* leds; //TODO: Should the leds operate using RGB or HSV? Note: HSV can convert to RGB but not vice-versa, but HSV is better for color math (how expenive is constant conversion? and is there a loss in coplor quality?)
    CRGB* leds_buffer;
    BMP* bmp;
};
