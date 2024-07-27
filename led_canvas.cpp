#include "led_canvas.h"

//---CLASS CANVAS:

  //===Constructors===
  Canvas::Canvas(int t_x, int t_y, CRGB *t_leds, CRGB *t_buffer, Origin t_o, Wrap t_wr, int t_s){
    this->init(t_x, t_y, t_leds, t_buffer, t_o, t_wr, t_s);
  }

  void Canvas::init(int t_x, int t_y, CRGB *t_leds, CRGB *t_buffer, Origin t_o, Wrap t_wr, int t_s){
    width = t_x;
    height = t_y;
    origin = t_o;
    wrap = t_wr;
    snake = t_s;
    leds = t_leds;
    leds_buffer = t_buffer;
  }

  //===Accessors===
  int Canvas::getWidth(){
    return width;
  }

  int Canvas::getHeight(){
    return height;
  }

  int Canvas::getSize(){
    return getWidth() * getHeight();
  }

  CRGB* Canvas::getLEDs(){
    return leds;
  }

  CRGB* Canvas::getBuffer(){
    return leds_buffer;
  }

  CRGB Canvas::getPoint(int t_x, int t_y){
    return leds_buffer[toIndex(t_x, t_y)];
  }

  //===Helpers===
  int Canvas::inboundsX(int t_x){
    return (t_x >= 0 && t_x < width);
  }
  
  int Canvas::inboundsY(int t_y){
    return (t_y >= 0 && t_y < height);
  }

  int Canvas::inbounds(int t_x, int t_y){
    return (inboundsX(t_x) && inboundsX(t_y));
  }

  int Canvas::toIndex(int t_x, int t_y){
    //return remapIndex((t_x+(width*t_y))%getSize());
    return (t_x + (width * t_y));
  }
  int Canvas::toXY(int t_i){
    return 0; //TODO: Do the opposite of toIndex. Not sure if this is even needed.
  }

  int Canvas::remapIndex(int t_i){
    int t_x = t_i % getWidth();
    int t_y = t_i / getWidth();
    int rev_x = getWidth() - 1 - t_x;
    int rev_y = getHeight() - 1 - t_y;
    switch(origin){
      case ORIGIN_NW : //NW
        if(snake == 0 || (snake == 1 && t_y % 2 == 0)){
          return (width * t_y) + t_x;
        }
        else return (width * t_y) + rev_x;
      case ORIGIN_NE : //NE
        if(snake == 0 || (snake == 1 && t_y % 2 == 0)){
          return (width * t_y) +  rev_x;
        }
        else return (width * t_y) +  t_x;
      case ORIGIN_SW : //SW
        if(snake == 0 || (snake == 1 && t_y % 2 != getHeight() % 2)){
          return (width * rev_y) + t_x;
        }
        else return (width * rev_y) + rev_x;
      case ORIGIN_SE : //SE
        if(snake == 0 || (snake == 1 && t_y % 2 != getHeight() % 2)){
          return (width * rev_y) + rev_x;
        }
        else return (width * rev_y) + t_x;
      default :
        return -1;
    }
  }

  int Canvas::remapXY(int t_x, int t_y){
    return remapIndex(toIndex(t_x, t_y));
  }

  void Canvas::update(){
    for(int i = 0; i < getSize(); i++){
      leds[remapIndex(i)] = leds_buffer[i];
    }
  }

  void Canvas::drawPixel(int x, int y, CRGB t_color, int t_a){
    if(  (x >= 0 && x < width)
      && (y >= 0 && y < height)
      && (t_color != CRGB(255, 0, 255)) )
      leds_buffer[x + (width * y)] = t_color;

  }