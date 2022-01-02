#include "led_canvas.h"

//---CLASS CANVAS:

  //===Constructors===
  
  Canvas::Canvas(uint8_t t_x, uint8_t t_y, CHSV *t_leds){
    size_x = t_x;
    size_y = t_y;
    leds = t_leds;
    snake = 0;
    layout = 0;
  }
  
  //Constructor using defined layout and snake attribute
  Canvas::Canvas(uint8_t t_x, uint8_t t_y, uint8_t t_l, uint8_t t_s, CHSV *t_leds){
    size_x = t_x;
    size_y = t_y;
    leds = t_leds;
    snake = t_s;
    layout = t_l;
  }


  //===Accessors===
  
  uint8_t Canvas::getSizeX(){
    return size_x;
  }
  uint8_t Canvas::getSizeY(){
    return size_y;
  }
  int Canvas::getSize(){
    return getSizeX()*getSizeY();
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
    //TODO: Convert whatever LED layout is used to a linear layout before/while printing
    Serial.print("Canvas Size: ");
    Serial.println(getSize());
    Serial.print(getSizeX());
    Serial.print(" x ");
    Serial.println(getSizeY());
    for(int i=0; i<getSizeY(); i++){
      Serial.print("[");
      for(int j=0; j<getSizeX(); j++){
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
    int rev_x = getSizeX() - 1 - t_x;
    int rev_y = getSizeY() - 1 - t_y;
    switch(layout){
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
        if(snake == 0 || (snake == 1 && t_y % 2 != getSizeY()%2)){
          return (size_x * rev_y) + t_x;
        }
        else return (size_x * rev_y) + rev_x;
      case 3 : //SE
        if(snake == 0 || (snake == 1 && t_y % 2 != getSizeY()%2)){
          return (size_x * rev_y) + rev_x;
        }
        else return (size_x * rev_y) + t_x;
      default :
        return -1;
    }
  }
  
  //===Drawing Functions===
  
  void Canvas::drawPoint(uint8_t x, uint8_t y, CHSV t_color, uint8_t t_a){
    if(inbounds(x,y)) leds[remapXY(x,y)]=t_color;
  }
  void Canvas::drawRect(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, CHSV t_color){
    for(int i=y; i<y+s_y; i++){
      if(i >= getSizeY()) break;
      for(int j=x; j<x+s_x; j++){
        if(j >= getSizeX()) break;
        if(inbounds(j,i)) leds[remapXY(j,i)]=t_color;
      }
    }
  }
  void Canvas::drawLine(int8_t x, int8_t y, int8_t x2, int8_t y2, CHSV t_color){
    
  }
  
  void Canvas::drawSprite8(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t *sprite, CHSV t_color){
    uint8_t row;
    for(int i=0; i<s_y && i<8; i++){
      if((y+i) >= getSizeY()) break;
      row=sprite[i];
      for(int j=0; j<s_x && j<8; j++){
        if((x+j) >= getSizeX()) break;
        if((row & 0b10000000) && inbounds(x+j, y+i)){ //Write current bit if it's a 1 and within the screen
          leds[remapXY(x+j, y+i)] = t_color;
        }
        row = row << 1;
      }
    }
  }
  
  void Canvas::drawSprite16(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint16_t *sprite, CHSV t_color){
    uint16_t row;
    for(int i=0; i<s_y && i<16; i++){
      if((y+i) >= getSizeY()) break;
      row=sprite[i];
      for(int j=0; j<s_x && j<16; j++){
        if((x+j) >= getSizeX()) break;
        if((row & bit(15)) && inbounds(x+j, y+i)){ //Write current bit if it's a 1 and within the screen
          leds[remapXY(x+j, y+i)] = t_color;
        }
        row = row << 1;
      }
    }
  }
  
  void Canvas::drawSprite32(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint32_t *sprite, CHSV t_color){
    uint32_t row;
    for(int i=0; i<s_y && i<32; i++){
      if((y+i) >= getSizeY()) break;
      row=sprite[i];
      for(int j=0; j<s_x && j<32; j++){
        if((x+j) >= getSizeX()) break;
        if((row & bit(31-12)) && inbounds(x+j, y+i)){ //Write current bit if it's a 1 and within the screen
          leds[remapXY(x+j, y+i)] = t_color;
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
      if (sumX >= getSizeX()) {
        break;
      }
      if (sumX < 0) {
        continue;
      }
      for (int i = 0; i < 5; i++) {
        sumY = y + i;
        if (sumY >= getSizeY()) {
          break; 
        }
        if (sumY < 0) {
          continue;
        }
        if (bitRead(sprite, 15 - (j * 5 + i))) {
          leds[remapXY(sumX,sumY)] = t_color;
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
    while ((chr != 0) and (sumX < getSizeX()));
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
  uint8_t Canvas::NW = 0;
  uint8_t Canvas::NE = 1;
  uint8_t Canvas::SW = 2;
  uint8_t Canvas::SE = 3;
  word Canvas::font[64] = {0b0000000000000000, 0b0000011101000000, 0b1100000000110000, 0b1111101010111110, 0b1101011111101100, 0b1001100100110010, 0b1111111101001110, 0b0000011000000000, 0b0111010001000000, 0b0000010001011100, 0b1010101110101010, 0b0010001110001000, 0b0000100010000000, 0b0010000100001000, 0b0000000001000000, 0b0000101110100000, 0b1111110001111110, 0b1000111111000010, 0b1011110101111010, 0b1000110101111110, 0b1110000100111110, 0b1110110101101110, 0b1111110101101110, 0b1000010000111110, 0b1111110101111110, 0b1110010100111110, 0b0000001010000000, 0b0000101010000000, 0b0010001010100010, 0b0101001010010100, 0b1000101010001000, 0b1000010101111000, 0b0111010001011010, 0b1111110100111110, 0b1111110101110110, 0b0111010001100010, 0b1111110001011100, 0b1111110101100010, 0b1111110100100000, 0b0111110001100110, 0b1111100100111110, 0b1000111111100010, 0b1000111111100000, 0b1111100100110110, 0b1111100001000010, 0b1111111000111110, 0b1111110000011110, 0b0111110001111100, 0b1111110100111000, 0b0111010011011010, 0b1111110100010110, 0b0110110101101100, 0b1000011111100000, 0b1111000001111110, 0b1111000011111100, 0b1111100011111110, 0b1101100100110110, 0b1110100101111110, 0b1001110101110010, 0b1111110001000000, 0b1000001110000010, 0b0000010001111110, 0b0100010000010000, 0b0000100001000010};

  
