#include "led_canvas.h"

//---CLASS CANVAS:

  //===Constructors===
  
  Canvas::Canvas(uint8_t t_x, uint8_t t_y, CHSV *t_leds){
    /*size_x = t_x;
    size_y = t_y;
    leds = t_leds;
    snake = 0;
    layout = 0;
    */
    this -> Canvas(uint8_t t_x, uint8_t t_y, ORIGIN_NW, 0, t_leds)
  }
  
  //Constructor using defined origin and snake attribute
  Canvas::Canvas(uint8_t t_x, uint8_t t_y, uint8_t t_o, uint8_t t_s, CHSV *t_leds){
    size_x = t_x;
    size_y = t_y;
    leds = t_leds;
    snake = t_s;
    origin = t_o;
  }

//TODO: Can have one constructor call the other, but in what order?
//i.e. First one calling second one with t_l and t_s as 0, or second one calling first one after populating snake and layout
//Also look into whether using default function values for undefined arguments is better or worse practice


  //===Accessors===
  
  uint8_t Canvas::getWidth(){
    return size_x;
  }
  uint8_t Canvas::getHeight(){
    return size_y;
  }
  int Canvas::getSize(){
    return getWidth()*getHeight();
  }

  CHSV* Canvas::getLEDs(){
    return leds;
  }

  CHSV Canvas::getPoint(int8_t t_x, uint8_t t_y){
    return leds[toIndex(t_x, t_y)];
  }

  uint8_t Canvas::inboundsX(uint8_t t_x){
    return (t_x>=0 && t_x<size_x);
  }
  uint8_t Canvas::inboundsY(uint8_t t_y){
    return (t_y>=0 && t_y<size_y);
  }
  uint8_t Canvas::inbounds(uint8_t t_x, uint8_t t_y){
    return (inboundsX(t_x) && inboundsX(t_y));
  }
  void Canvas::printCanvas(){
    Serial.print("Canvas Size: ");
    Serial.println(getSize());
    Serial.print(getWidth());
    Serial.print(" x ");
    Serial.println(getHeight());
    for(int i=0; i<getHeight(); i++){
      Serial.print("[");
      for(int j=0; j<getWidth(); j++){
        if(leds[remapXY(j,i)].v==0){
          Serial.print(" . ");
        }
        else{
          Serial.print(" X ");
        }
      }
      Serial.print("]\n");
    }
  }

  int Canvas::toIndex(int t_x, int t_y){
    //return remapIndex((t_x+(size_x*t_y))%getSize());
    return (t_x+(size_x*t_y));
  }
  uint8_t Canvas::toXY(int t_i){
    return 0; //TODO: Do the opposite of toIndex. Not sure if this is even needed.
  }

  int Canvas::remapXY(int t_x, int t_y){
    int rev_x = getWidth() - 1 - t_x;
    int rev_y = getHeight() - 1 - t_y;
    switch(origin){
      case 0 : //NW
        if(snake == 0 || (snake == 1 && t_y % 2 == 0)){
          return (size_x * t_y) + t_x;
        }
        else return (size_x * t_y) + rev_x;
      case 1 : //NE
        if(snake == 0 || (snake == 1 && t_y % 2 == 0)){
          return (size_x * t_y) +  rev_x;
        }
        else return (size_x * t_y) +  t_x;
      case 2 : //SW
        if(snake == 0 || (snake == 1 && t_y % 2 != getHeight()%2)){
          return (size_x * rev_y) + t_x;
        }
        else return (size_x * rev_y) + rev_x;
      case 3 : //SE
        if(snake == 0 || (snake == 1 && t_y % 2 != getHeight()%2)){
          return (size_x * rev_y) + rev_x;
        }
        else return (size_x * rev_y) + t_x;
      default :
        return -1;
    }
  }
  
  //=========Drawing Functions=========

  void Canvas::drawPoint(uint8_t x, uint8_t y, CHSV t_color, uint8_t t_a){
    //TODO: implement alpha blending
    if(inbounds(x,y)) leds[remapXY(x,y)]=t_color;
  }

  void Canvas::drawRect(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, CHSV t_color){
    for(int i=y; i<y+s_y; i++){
      if(i >= getHeight()) break;
      for(int j=x; j<x+s_x; j++){
        if(j >= getWidth()) break;
        if(inbounds(j,i)) drawPoint(j,i,t_color, 0);
      }
    }
  }
  
  void Canvas::drawLine(int8_t x, int8_t y, int8_t x2, int8_t y2, CHSV t_color){
    
  }
  
  void Canvas::drawSprite8(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t *sprite, CHSV t_color){
    uint8_t row;
    for(int i=0; i<s_y && i<8; i++){
      if((y+i) >= getHeight()) break;
      row=sprite[i];
      for(int j=0; j<s_x && j<8; j++){
        if((x+j) >= getWidth()) break;
        if((row & 0b10000000) && inbounds(x+j, y+i)){ //Write current bit if it's a 1 and within the screen
          drawPoint(x+j,y+i,t_color, 0);
        }
        row = row << 1;
      }
    }
  }
  
  void Canvas::drawSprite16(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint16_t *sprite, CHSV t_color){
    uint16_t row;
    for(int i=0; i<s_y && i<16; i++){
      if((y+i) >= getHeight()) break;
      row=sprite[i];
      for(int j=0; j<s_x && j<16; j++){
        if((x+j) >= getWidth()) break;
        if((row & bit(15)) && inbounds(x+j, y+i)){ //Write current bit if it's a 1 and within the screen
          drawPoint(x+j,y+i,t_color, 0);
        }
        row = row << 1;
      }
    }
  }
  
  void Canvas::drawSprite32(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint32_t *sprite, CHSV t_color){
    uint32_t row;
    for(int i=0; i<s_y && i<32; i++){
      if((y+i) >= getHeight()) break;
      row=sprite[i];
      for(int j=0; j<s_x && j<32; j++){
        if((x+j) >= getWidth()) break;
        if((row & bit(31-12)) && inbounds(x+j, y+i)){ //Write current bit if it's a 1 and within the screen
          drawPoint(x+j,y+i,t_color, 0);
        }
        row = row << 1;
      }
    }
  }
  
  void Canvas::drawChar(char character, int8_t x, int8_t y, CHSV t_color){
    if (character > 96) { // convert lowercase to uppercase
      character -= 32;
    }
    word sprite = font[character - 32];
    //uint8_t i = 0;
    int sumX; int sumY;
    for (int j = 0; j < 3; j++) {
      sumX = x + j;
      if (sumX >= getWidth()) {
        break;
      }
      if (sumX < 0) {
        continue;
      }
      for (int i = 0; i < 5; i++) {
        sumY = y + i;
        if (sumY >= getHeight()) {
          break; 
        }
        if (sumY < 0) {
          continue;
        }
        if (bitRead(sprite, 15 - (j * 5 + i))) {
          drawPoint(sumX,sumY,t_color, 0);
        }
      }
    }
  }
  
  void Canvas::drawString(char str[], int8_t x, int8_t y, CHSV t_color){
    int i = 0;
    char chr = str[0];
    int sumX = x;
    do {
      drawChar(chr, sumX, y, t_color);
      i++;
      chr = str[i];
      sumX += 4;
    }
    while ((chr != 0) and (sumX < getWidth()));
    }

  void Canvas::erase(){
    for(int i=0; i<getSize(); i++){
      leds[i]=CHSV(0,0,0);
    }
  }

  void Canvas::linearFade(uint8_t amount){
    for(int i=0; i<getSize(); i++){
      leds[i].v-=amount;
    }
  }

  //==Constants==
  /*uint8_t Canvas::NW = 0;
  uint8_t Canvas::NE = 1;
  uint8_t Canvas::SW = 2;
  uint8_t Canvas::SE = 3;*/
  word Canvas::font[64] = {0b0000000000000000, 0b0000011101000000, 0b1100000000110000, 0b1111101010111110, 0b1101011111101100, 0b1001100100110010, 0b1111111101001110, 0b0000011000000000, 0b0111010001000000, 0b0000010001011100, 0b1010101110101010, 0b0010001110001000, 0b0000100010000000, 0b0010000100001000, 0b0000000001000000, 0b0000101110100000, 0b1111110001111110, 0b1000111111000010, 0b1011110101111010, 0b1000110101111110, 0b1110000100111110, 0b1110110101101110, 0b1111110101101110, 0b1000010000111110, 0b1111110101111110, 0b1110010100111110, 0b0000001010000000, 0b0000101010000000, 0b0010001010100010, 0b0101001010010100, 0b1000101010001000, 0b1000010101111000, 0b0111010001011010, 0b1111110100111110, 0b1111110101110110, 0b0111010001100010, 0b1111110001011100, 0b1111110101100010, 0b1111110100100000, 0b0111110001100110, 0b1111100100111110, 0b1000111111100010, 0b1000111111100000, 0b1111100100110110, 0b1111100001000010, 0b1111111000111110, 0b1111110000011110, 0b0111110001111100, 0b1111110100111000, 0b0111010011011010, 0b1111110100010110, 0b0110110101101100, 0b1000011111100000, 0b1111000001111110, 0b1111000011111100, 0b1111100011111110, 0b1101100100110110, 0b1110100101111110, 0b1001110101110010, 0b1111110001000000, 0b1000001110000010, 0b0000010001111110, 0b0100010000010000, 0b0000100001000010};

  
