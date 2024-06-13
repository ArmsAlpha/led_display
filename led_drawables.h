#pragma once
#include <Arduino.h>
#include <FastLED.h>
class Canvas;

//TODO: Figure out how to delete class on command
class Drawable
{  
  public:
    //Accessors:
    //Position:
    int get_pos_x();
    int get_pos_y();
    int get_pos(); //Gets [pos_x,pos_y]
    //Size
    int get_width();
    int get_height();
    int get_size(); //Gets [width,height]
    //Misc:
    int get_alpha();
    unsigned long get_age();
    int inbounds(int x, int y);
  
    //Modifiers
    void set_pos_x(int x);
    void set_pos_y(int y);
    void set_visible(int);
    void moveTo(int x, int y);
    void draw(Canvas *t_canvas); //Draws the shape on the canvas - different behavior for different shapes
    void ageUp();  //Increments age by 1
    void ageReset(); //Sets age back to 0

    protected:
      int pos_x;
      int pos_y;
      int width;
      int height;
      unsigned long age = 0;
      int alpha;
      int visible = 1;
      int priority = 0;
};

class Point: public Drawable
{
  public:
    Point(int x, int y);
  
  private:
};


class Rect: public Drawable
{
  public:
    Rect(int x, int y, int s_x, int s_y);
    Rect(int x, int y, int s_x, int s_y, int t_alpha);
    void draw(Canvas *t_c);
  
  private:
};

class Line: public Drawable
{ 
  public:
    Line(int x, int y, int x2, int y2);
    Line(int x, int y, int x2, int y2, int t_alpha);

  private:
    int pos_x2;
    int pos_y2;
};

class DrawableChar: public Drawable
{
  public:
    char getChar();

  private:
    char c;
};

class DrawableString: public Drawable
{
  public:
    char getString();

  private:
    char* s;
};
class Sprite: public Drawable
{
  public:
    char changeSprite(int *n_Sprite);

  private:
    int* sprite;
    CHSV palette[];
};
