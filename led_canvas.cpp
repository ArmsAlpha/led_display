#include "led_canvas.h"

//---CLASS CANVAS:

  //===Constructors===
  Canvas::Canvas(int t_x, int t_y, CRGB *t_leds, Origin t_o, Wrap t_wr, int t_s){
    this->init(t_x, t_y, t_leds, t_o, t_wr, t_s);
  }

  void Canvas::init(int t_x, int t_y, CRGB *t_leds, Origin t_o, Wrap t_wr, int t_s){
    width = t_x;
    height = t_y;
    origin = t_o;
    wrap = t_wr;
    snake = t_s;
    leds = t_leds;
    leds_buffer = new CRGB[t_x*t_y];
    bmp = NULL;
    newBitmap();
  }

  //===Accessors===
  int Canvas::getWidth(){
    return width;
  }
  int Canvas::getHeight(){
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

  CRGB Canvas::getPoint(int t_x, int t_y){
    return leds_buffer[toIndex(t_x, t_y)];
  }

  int Canvas::inboundsX(int t_x){
    return (t_x>=0 && t_x<width);
  }
  int Canvas::inboundsY(int t_y){
    return (t_y>=0 && t_y<height);
  }
  int Canvas::inbounds(int t_x, int t_y){
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
  int Canvas::toXY(int t_i){
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

  void Canvas::drawPoint(int x, int y, CRGB t_color, int t_a){
    //TODO: implement alpha blending
    //if(inbounds(x,y)) leds[remapXY(x,y)]=t_color;
    if(inbounds(x,y)&&t_color!=CRGB(255,0,255)) leds_buffer[toIndex(x,y)]=t_color;
  }

  void Canvas::drawRect(int x, int y, int dx, int dy, CRGB t_color){
    for(int i=y; i<y+dy; i++){
      if(i >= getHeight()) break;
      for(int j=x; j<x+dx; j++){
        if(j >= getWidth()) break;
        if(inbounds(j,i)) drawPoint(j,i,t_color, 0);
      }
    }
  }
  
  void Canvas::drawLine(int x, int y, int x2, int y2, CRGB t_color){
    
  }
  
  void Canvas::drawChar(char character, int x, int y, CRGB t_color){
    if (character > 96) { // convert lowercase to uppercase
      character -= 32;
    }
    word sprite = font[character - 32];
    //int i = 0;
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
  
  void Canvas::drawString(char str[], int x, int y, CRGB t_color){
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

  void Canvas::linearFade(int amount){
    for(int i=0; i<getSize(); i++){
      leds_buffer[i].subtractFromRGB(amount);
    }
  }
  
  //=========Bitmap Functions=========

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
  byte r,g,b;
  for (int i=0; i<dy; i++){
    for (int j=0; j<dx; j++){
      if(inbounds(j,i)){
        BMP_GetPixelRGB(bmp,j,i,&r,&g,&b);
        drawPoint(j,i,CRGB(r,g,b),0);
      }
    }
  }
}

void Canvas::renderBmp(const char* filename){
  bmp = BMP_ReadFile(filename);
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
      leds_buffer[i]=CRGB(0,0,0);
    }
  }


  void Canvas::update(){
    for(int i=0; i<getSize(); i++){
      leds[remapIndex(i)] = leds_buffer[i];
    }
  }

  //==Constants==
  /*int Canvas::NW = 0;
  int Canvas::NE = 1;
  int Canvas::SW = 2;
  int Canvas::SE = 3;*/
  word Canvas::font[64] = {0b0000000000000000, 0b0000011101000000, 0b1100000000110000, 0b1111101010111110, 0b1101011111101100, 0b1001100100110010, 0b1111111101001110, 0b0000011000000000, 0b0111010001000000, 0b0000010001011100, 0b1010101110101010, 0b0010001110001000, 0b0000100010000000, 0b0010000100001000, 0b0000000001000000, 0b0000101110100000, 0b1111110001111110, 0b1000111111000010, 0b1011110101111010, 0b1000110101111110, 0b1110000100111110, 0b1110110101101110, 0b1111110101101110, 0b1000010000111110, 0b1111110101111110, 0b1110010100111110, 0b0000001010000000, 0b0000101010000000, 0b0010001010100010, 0b0101001010010100, 0b1000101010001000, 0b1000010101111000, 0b0111010001011010, 0b1111110100111110, 0b1111110101110110, 0b0111010001100010, 0b1111110001011100, 0b1111110101100010, 0b1111110100100000, 0b0111110001100110, 0b1111100100111110, 0b1000111111100010, 0b1000111111100000, 0b1111100100110110, 0b1111100001000010, 0b1111111000111110, 0b1111110000011110, 0b0111110001111100, 0b1111110100111000, 0b0111010011011010, 0b1111110100010110, 0b0110110101101100, 0b1000011111100000, 0b1111000001111110, 0b1111000011111100, 0b1111100011111110, 0b1101100100110110, 0b1110100101111110, 0b1001110101110010, 0b1111110001000000, 0b1000001110000010, 0b0000010001111110, 0b0100010000010000, 0b0000100001000010};

  
