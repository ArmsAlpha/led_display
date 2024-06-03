#include "led_canvas.h"

//---CLASS CANVAS:

  //===Constructors===
  Canvas::Canvas(uint8_t t_x, uint8_t t_y, CRGB *t_leds, Origin t_o, Wrap t_wr, uint8_t t_s){
    width = t_x;
    height = t_y;
    origin = t_o;
    wrap = t_wr;
    snake = t_s;
    leds = t_leds;
    leds_buffer = new CRGB[t_x*t_y];
    bmp = NULL;
  }

  //===Accessors===
  uint8_t Canvas::getWidth(){
    return width;
  }
  uint8_t Canvas::getHeight(){
    return height;
  }
  int Canvas::getSize(){
    return getWidth()*getHeight();
  }

  CRGB* Canvas::getLEDs(){
    return leds;
  }

  CRGB* Canvas::getBuffer(){
    return leds_buffer;
  }

  BMP* Canvas::getBitmap(){
    return bmp;
  }

  CRGB Canvas::getPoint(int8_t t_x, uint8_t t_y){
    return leds[toIndex(t_x, t_y)];
  }

  uint8_t Canvas::inboundsX(uint8_t t_x){
    return (t_x>=0 && t_x<width);
  }
  uint8_t Canvas::inboundsY(uint8_t t_y){
    return (t_y>=0 && t_y<height);
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
        if(leds[remapXY(j,i)]){
          Serial.print(" X ");
        }
        else{
          Serial.print(" . ");
        }
      }
      Serial.print("]\n");
    }
  }

  //===Helpers===
  int Canvas::toIndex(int t_x, int t_y){
    //return remapIndex((t_x+(width*t_y))%getSize());
    return (t_x+(width*t_y));
  }
  uint8_t Canvas::toXY(int t_i){
    return 0; //TODO: Do the opposite of toIndex. Not sure if this is even needed.
  }

  int Canvas::remapIndex(int t_i){
    int t_x = t_i % getWidth();
    int t_y = t_i/getWidth();
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
        if(snake == 0 || (snake == 1 && t_y % 2 != getHeight()%2)){
          return (width * rev_y) + t_x;
        }
        else return (width * rev_y) + rev_x;
      case ORIGIN_SE : //SE
        if(snake == 0 || (snake == 1 && t_y % 2 != getHeight()%2)){
          return (width * rev_y) + rev_x;
        }
        else return (width * rev_y) + t_x;
      default :
        return -1;
    }
  }

  int Canvas::remapXY(int t_x, int t_y){
    return remapIndex(toIndex(t_x,t_y));
  }
  
  //=========Drawing Functions=========


  //TODO: Have drawPoint and other drawing functions effect the buffer, and don't remap indeces at draw time (remap when copying buffer)
  void Canvas::drawPoint(uint8_t x, uint8_t y, CRGB t_color, uint8_t t_a){
    //TODO: implement alpha blending
    //if(inbounds(x,y)) leds[remapXY(x,y)]=t_color;
    if(inbounds(x,y)) leds_buffer[toIndex(x,y)]=t_color;
  }

  void Canvas::drawRect(int8_t x, int8_t y, uint8_t dx, uint8_t dy, CRGB t_color){
    for(int i=y; i<y+dy; i++){
      if(i >= getHeight()) break;
      for(int j=x; j<x+dx; j++){
        if(j >= getWidth()) break;
        if(inbounds(j,i)) drawPoint(j,i,t_color, 0);
      }
    }
  }
  
  void Canvas::drawLine(int8_t x, int8_t y, int8_t x2, int8_t y2, CRGB t_color){
    
  }
  
  void Canvas::drawSprite8(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t *sprite, CRGB t_color){
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
  
  void Canvas::drawSprite16(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint16_t *sprite, CRGB t_color){
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
  
  void Canvas::drawSprite32(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint32_t *sprite, CRGB t_color){
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
  
  void Canvas::drawChar(char character, int8_t x, int8_t y, CRGB t_color){
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
  
  void Canvas::drawString(char str[], int8_t x, int8_t y, CRGB t_color){
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

  void Canvas::linearFade(uint8_t amount){
    for(int i=0; i<getSize(); i++){
      leds[i].subtractFromRGB(amount);
    }
  }
  
void Canvas::newBitmap() {
	if (bmp != NULL)
		BMP_Free(bmp);
	bmp = BMP_Create(width, height, 24);
	if (bmp == NULL)
		Serial.println("Display bitmap allocation failed");
}

void Canvas::fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb) {
	for (unsigned int x=x0; x<x0+dx; x++)
		for (unsigned int y=y0; y<y0+dy; y++)
			BMP_SetPixelRGB(bmp, x, y, crgb.r, crgb.g, crgb.b);
}

void Canvas::blitBitmap(int i0, int x0, int y0, int dx, int dy) {
  //TODO
}

void Canvas::renderXpm(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB crgb) {
	int byteWidth = w/8;
	for (int i=0; i<h; i++) {
		int y=y0+i;
		for (int j=0; j<byteWidth; j++) {
			unsigned char bits = charBytes[i*byteWidth+j];
			int byteX = x0+j*8;
			for (int k=0; k<8; k++) {
				if (bits & (1 << k))
					BMP_SetPixelRGB(bmp, byteX+k, y, crgb.r, crgb.g, crgb.b);
			}
		}
	}
}


  void Canvas::erase(){
    for(int i=0; i<getSize(); i++){
      leds[i]=CRGB(0,0,0);
    }
  }


  void Canvas::update(){
    /*
    for(int i=0; i+=getHeight(); i++){
      for(int j=0; j+=getWidth(); j++){
        leds[remapXY(j,i)] = leds_buffer[toIndex(j,i)];
      }
    }
    */
    for(int i=0; i+=getSize(); i++){
      leds[remapIndex(i)] = leds_buffer[i];
    }
  }

  //==Constants==
  /*uint8_t Canvas::NW = 0;
  uint8_t Canvas::NE = 1;
  uint8_t Canvas::SW = 2;
  uint8_t Canvas::SE = 3;*/
  word Canvas::font[64] = {0b0000000000000000, 0b0000011101000000, 0b1100000000110000, 0b1111101010111110, 0b1101011111101100, 0b1001100100110010, 0b1111111101001110, 0b0000011000000000, 0b0111010001000000, 0b0000010001011100, 0b1010101110101010, 0b0010001110001000, 0b0000100010000000, 0b0010000100001000, 0b0000000001000000, 0b0000101110100000, 0b1111110001111110, 0b1000111111000010, 0b1011110101111010, 0b1000110101111110, 0b1110000100111110, 0b1110110101101110, 0b1111110101101110, 0b1000010000111110, 0b1111110101111110, 0b1110010100111110, 0b0000001010000000, 0b0000101010000000, 0b0010001010100010, 0b0101001010010100, 0b1000101010001000, 0b1000010101111000, 0b0111010001011010, 0b1111110100111110, 0b1111110101110110, 0b0111010001100010, 0b1111110001011100, 0b1111110101100010, 0b1111110100100000, 0b0111110001100110, 0b1111100100111110, 0b1000111111100010, 0b1000111111100000, 0b1111100100110110, 0b1111100001000010, 0b1111111000111110, 0b1111110000011110, 0b0111110001111100, 0b1111110100111000, 0b0111010011011010, 0b1111110100010110, 0b0110110101101100, 0b1000011111100000, 0b1111000001111110, 0b1111000011111100, 0b1111100011111110, 0b1101100100110110, 0b1110100101111110, 0b1001110101110010, 0b1111110001000000, 0b1000001110000010, 0b0000010001111110, 0b0100010000010000, 0b0000100001000010};

  
