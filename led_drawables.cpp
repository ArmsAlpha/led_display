#include "led_drawables.h"

//TODO: figure out if I need to put all of this stuff in a namespace

//---CLASS DRAWABLE:
    //Accessors:
    int8_t Drawable::get_pos_x(){
      return pos_x;
    }
    int8_t Drawable::get_pos_y(){
      return pos_y;
    }
    int8_t Drawable::get_pos(){
      return pos_x;
      //TODO: return array of [x,y]
    }
    uint8_t Drawable::get_width(){
      return width;
    }
    uint8_t Drawable::get_height(){
      return height;
    }
    uint8_t Drawable::get_size(){
      //TODO: return array of [s_x, s_y]
    }
    int Drawable::get_alpha(){
      return alpha;
    }
    unsigned long Drawable::get_age(){
      return age;
    }
    uint8_t Drawable::inbounds(int t_x, int t_y){
      if(pos_x>=0 && pos_y>=0 && pos_x+width<t_x && pos_y+height<t_y) return 1;
      else return 0;
    }
  
    //Position modification:
    void Drawable::set_pos_x(int8_t x){
      pos_x = x;
    }
    void Drawable::set_pos_y(int8_t y){
      pos_y = y;
    }
    void Drawable::set_visible(uint8_t b){
      visible = b;
    }
    void Drawable::moveTo(int8_t x, int8_t y){
      set_pos_x(x);
      set_pos_y(y);
    }

    void Drawable::ageUp(){
      age++;
    }

    void Drawable::ageReset(){
      age = 0;
    }
    
//-------------------------------------------------------------------------------
//--CLASS POINT
    Point::Point(int8_t x, int8_t y){
      pos_x = x;
      pos_y = y;
      width = 1;
      height = 1;
      
    }
    
//-------------------------------------------------------------------------------
//--CLASS RECT
    Rect::Rect(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y){
      pos_x = x;
      pos_y = y;
      width = s_x;
      height = s_y;
      alpha = 0;
    }
    Rect::Rect(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t t_alpha){ //TODO: Merge both constructors using optional param for angle
      pos_x = x;
      pos_y = y;
      width = s_x;
      height = s_y;
      alpha = t_alpha;
    }
    /*
    void Rect::draw(Canvas* t_c){
      if(visible) t_c->drawRect(this->get_pos_x(), this->get_pos_y(), this->get_width(), this->get_height(), this->get_angle());
    }
    */
    
//-------------------------------------------------------------------------------
//--CLASS LINE
    Line::Line(int8_t x, int8_t y, int8_t x2, int8_t y2){
      pos_x = x;
      pos_y = y;
      pos_x2 = x2;
      pos_y2 = y2;
      width = x2-x;
      height = y2-y;
      alpha = 0;
  }

    Line::Line(int8_t x, int8_t y, int8_t x2, int8_t y2, uint8_t t_alpha){
      pos_x = x;
      pos_y = y;
      pos_x2 = x2;
      pos_y2 = y2;
      width = x2-x;
      height = y2-y;
      alpha = t_alpha;
  }

//-------------------------------------------------------------------------------
//--CLASS SPRITE
