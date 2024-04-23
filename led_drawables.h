#pragma once
class Canvas;

//TODO: Figure out how to delete class on command
class Drawable
{  
  public:
    //Accessors:
    //Position:
    int8_t get_pos_x();
    int8_t get_pos_y();
    int8_t get_pos(); //Gets [pos_x,pos_y]
    //Size
    uint8_t get_width();
    uint8_t get_height();
    uint8_t get_size(); //Gets [width,height]
    //Misc:
    int get_alpha();
    unsigned long get_age();
    uint8_t inbounds(int x, int y);
  
    //Modifiers
    void set_pos_x(int8_t x);
    void set_pos_y(int8_t y);
    void set_visible(uint8_t);
    void moveTo(int8_t x, int8_t y);
    void draw(Canvas *t_canvas); //Draws the shape on the canvas - different behavior for different shapes
    void ageUp();  //Increments age by 1
    void ageReset(); //Sets age back to 0

    protected:
      int8_t pos_x;
      int8_t pos_y;
      uint8_t width;
      uint8_t height;
      unsigned long age = 0;
      uint8_t alpha;
      uint8_t visible = 1;
      uint8_t priority = 0;
};

class Point: public Drawable
{
  public:
    Point(int8_t x, int8_t y);
  
  private:
};


class Rect: public Drawable
{
  public:
    Rect(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y);
    Rect(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t t_alpha);
    void draw(Canvas *t_c);
  
  private:
};

class Line: public Drawable
{ 
  public:
    Line(int8_t x, int8_t y, int8_t x2, int8_t y2);
    Line(int8_t x, int8_t y, int8_t x2, int8_t y2, uint8_t t_alpha);

  private:
    int8_t pos_x2;
    int8_t pos_y2;
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
    char changeSprite(uint8_t *n_Sprite);

  private:
    uint8_t* sprite;
    CHSV palette[];
};
