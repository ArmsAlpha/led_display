#pragma once
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
    Canvas(int t_x, int t_y, CRGB *t_leds, Origin t_o=ORIGIN_NW, Wrap t_wr=WRAP_H, int t_s=0);

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
    void printCanvas(); //Prints contents of canvas using Serial.println()

    //Helpers:
    int toIndex(int t_x, int t_y); //Converts X-Y coords to corresponding array index
    int toXY(int t_i); //Converts given index to X-Y coords.
    int remapIndex(int t_i); //Remaps index to fit the assigned layout of LEDS and returns index i
    int remapXY(int t_x, int t_y); //Remaps coordinates to fit the assigned layout of LEDs and returns index i
    
    //Draw Functions:
    void drawPoint(int x, int y, CRGB t_color, int t_a);
    void drawRect(int x, int y, int dx, int dy, CRGB t_color);
    void drawLine(int x, int y, int x2, int y2, CRGB t_color);
    
    void drawChar(char character, int x, int y, CRGB t_color);
    void drawString(char str[], int x, int y, CRGB t_color);

    void drawSprite(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB t_color);

    //BMP Functions
    void renderXpm(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB crgb); //Render Xpm onto bmp array

    void drawObj(Drawable *t_d); //Calls draw() for the specified object

    //Effects:
    void linearFade(int amount); //Fades out every LED by a certain amount
    void linearFade(Drawable Mask); //TODO: maybe get id of this and use default arguments instead
    void erase(); //Clears entire canvas
    void eraseArea(int x, int y, int dx, int dy, CRGB t_color); //Clears canvas in rectangular area

    //Update
    void update(); //Copy (and translate) the buffer array to the main array used by FastLED

  private:

    void init(int t_x, int t_y, CRGB *t_leds, Origin t_o, Wrap t_wr, int t_s);

    int width;
    int height;
    int origin; //Denotes starting corner of matrix
    int wrap; //Denotes wrap direction (horizontal or vertical)
    int snake; //Denotes whether row directions alternate or remain the same

    static word font[];
    CRGB* leds; //TODO: Should the leds operate using RGB or HSV? Note: HSV can convert to RGB but not vice-versa, but HSV is better for color math (how expenive is constant conversion? and is there a loss in coplor quality?)
    CRGB* leds_buffer;
};
