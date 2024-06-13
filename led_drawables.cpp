#include "led_drawables.h"

//TODO: figure out if I need to put all of this stuff in a namespace

//---CLASS DRAWABLE:
    //Accessors:
    int Drawable::get_pos_x(){
      return pos_x;
    }
    int Drawable::get_pos_y(){
      return pos_y;
    }
    int Drawable::get_pos(){
      return pos_x;
      //TODO: return array of [x,y]
    }
    int Drawable::get_width(){
      return width;
    }
    int Drawable::get_height(){
      return height;
    }
    int Drawable::get_size(){
      //TODO: return array of [s_x, s_y]
    }
    int Drawable::get_alpha(){
      return alpha;
    }
    unsigned long Drawable::get_age(){
      return age;
    }
    int Drawable::inbounds(int t_x, int t_y){
      if(pos_x>=0 && pos_y>=0 && pos_x+width<t_x && pos_y+height<t_y) return 1;
      else return 0;
    }
  
    //Position modification:
    void Drawable::set_pos_x(int x){
      pos_x = x;
    }
    void Drawable::set_pos_y(int y){
      pos_y = y;
    }
    void Drawable::set_visible(int b){
      visible = b;
    }
    void Drawable::moveTo(int x, int y){
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
    Point::Point(int x, int y){
      pos_x = x;
      pos_y = y;
      width = 1;
      height = 1;
      
    }
    
//-------------------------------------------------------------------------------
//--CLASS RECT
    Rect::Rect(int x, int y, int s_x, int s_y){
      pos_x = x;
      pos_y = y;
      width = s_x;
      height = s_y;
      alpha = 0;
    }
    Rect::Rect(int x, int y, int s_x, int s_y, int t_alpha){ //TODO: Merge both constructors using optional param for angle
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
    Line::Line(int x, int y, int x2, int y2){
      pos_x = x;
      pos_y = y;
      pos_x2 = x2;
      pos_y2 = y2;
      width = x2-x;
      height = y2-y;
      alpha = 0;
  }

    Line::Line(int x, int y, int x2, int y2, int t_alpha){
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
