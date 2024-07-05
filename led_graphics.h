#pragma once
#include <Arduino.h>
#include <FastLED.h>
//class Drawable;
class ledGraphics
{
  public:
    //Constructor:
    ledGraphics(CRGB* t_canvas, int t_w, int t_h);

    //Draw Functions:
    void drawPoint(int x, int y, CRGB t_color, int t_a=0);
    void drawRect(int x, int y, int dx, int dy, CRGB t_color);
    void drawLine(int x, int y, int x2, int y2, CRGB t_color);
  
    void drawChar(char character, int x, int y, CRGB t_color);
    void drawString(char str[], int x, int y, CRGB t_color);
    void drawSprite(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB t_color);

    //BMP Functions
    void renderXpm(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB crgb); //Render Xpm onto bmp array

   // void drawObj(Drawable *t_d); //Calls draw() for the specified object

    //Effects:
    void linearFade(int amount); //Fades out every LED by a certain amount
    //void linearFade(Drawable Mask); //TODO: maybe get id of this and use default arguments instead
    void erase(); //Clears entire canvas
    void eraseArea(int x, int y, int dx, int dy, CRGB t_color); //Clears canvas in rectangular area

  private:
    CRGB* canvas;
    int width;
    int height;
    static word font[];
};