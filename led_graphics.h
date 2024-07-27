#pragma once

#ifndef LED_GRAPHICS_H_
#define LED_GRAPHICS_H_

#include <Arduino.h>
#include <FastLED.h>

#include "led_canvas.h"

//class Drawable;
class ledGraphics
{
  public:
    //Constructor:
    ledGraphics(Canvas* t_canvas);

    //Draw Functions:
    void drawPixel(int x, int y, CRGB t_color, int t_a = 0);
    void drawVLine(int x, int y, int h, CRGB t_color);
    void drawHLine(int x, int y, int w, CRGB t_color);
    void fillRect(int x, int y, int dx, int dy, CRGB t_color);
    void fillScreen(CRGB t_color);
    void drawLine(int x, int y, int x2, int y2, CRGB t_color);
    void drawRect(int x, int y, int dx, int dy, CRGB t_color);
  
    void drawChar(char character, int x, int y, CRGB t_color);
    void drawString(char str[], int x, int y, CRGB t_color);
    void drawSprite(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB t_color);

    /*
    //Adafruit_GFX drawBitmap - still trying to wrap head around implementation
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
    */

    //void drawObj(Drawable *t_d); //Calls draw() for the specified object

    //Effects:
    void linearFade(int amount); //Fades out every LED by a certain amount
    //void linearFade(Drawable Mask); //TODO: maybe get id of this and use default arguments instead
    void erase(); //Clears entire canvas
    void eraseArea(int x, int y, int dx, int dy, CRGB t_color); //Clears canvas in rectangular area

  private:
    Canvas* canvas;
    static word font[];
};

#endif