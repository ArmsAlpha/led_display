 #include "led_graphics.h"

//---CLASS LEDGRAPHICS:
 
  ledGraphics::ledGraphics(Canvas* t_canvas){
    canvas = t_canvas;
  }
  
 //=========Drawing Functions=========

  void ledGraphics::drawPixel(int x, int y, CRGB t_color, int t_a){
    canvas->drawPixel(x,y,t_color);
  }

  void ledGraphics::drawVLine(int x, int y, int h, CRGB t_color){
    if(canvas->inboundsX(x)){
      for(int i=y; i<x+h; i++){
        if(canvas->inboundsY(i)) drawPixel(x,i,t_color,0);
      }
    }
  }

  void ledGraphics::drawHLine(int x, int y, int w, CRGB t_color){
    if(canvas->inboundsY(y)){
      for(int i=x; i<x+w; i++){
        if(canvas->inboundsX(i)) drawPixel(i,y,t_color,0);
      }
    }
  }

   void ledGraphics::fillRect(int x, int y, int dx, int dy, CRGB t_color){
    for(int i=y; i<y+dy; i++){
      if(i >= canvas->getHeight()) break;
      for(int j=x; j<x+dx; j++){
        if(j >= canvas->getWidth()) break;
        drawPixel(j,i,t_color);
      }
    }
  }

  void ledGraphics::fillScreen(CRGB t_color){
    for(int i=0; i<canvas->getSize(); i++){
      drawPixel(i%canvas->getWidth(),i/canvas->getWidth(),t_color,0);
    }
  }

  void ledGraphics::drawRect(int x, int y, int dx, int dy, CRGB t_color){
    drawVLine(x, y, dy, t_color);
    drawVLine(x + dx, y, dy, t_color);
    drawHLine(x, y, dx, t_color);
    drawHLine(x, y + dy, dx, t_color);
  }
  
  void ledGraphics::drawLine(int x, int y, int x2, int y2, CRGB t_color){
    
  }
  
  void ledGraphics::drawChar(char character, int x, int y, CRGB t_color){
    if (character > 96) { // convert lowercase to uppercase
      character -= 32;
    }
    word sprite = font[character - 32];
    //int i = 0;
    int sumX; int sumY;
    for (int j = 0; j < 3; j++) {
      sumX = x + j;
      if (sumX >= canvas->getWidth()) {
        break;
      }
      if (sumX < 0) {
        continue;
      }
      for (int i = 0; i < 5; i++) {
        sumY = y + i;
        if (sumY >= canvas->getHeight()) {
          break; 
        }
        if (sumY < 0) {
          continue;
        }
        if (bitRead(sprite, 15 - (j * 5 + i))) {
          drawPixel(sumX,sumY,t_color);
        }
      }
    }
  }
  
  void ledGraphics::drawString(char str[], int x, int y, CRGB t_color){
    int i = 0;
    char chr = str[0];
    int sumX = x;
    do {
      drawChar(chr, sumX, y, t_color);
      i++;
      chr = str[i];
      sumX += 4;
    }
    while ((chr != 0) and (sumX < canvas->getWidth()));
    }

    void ledGraphics::drawSprite(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB t_color){
      int byteWidth = w/8;
	    for (int i=0; i<h; i++) {
		    int y=y0+i;
		    for (int j=0; j<byteWidth; j++) {
			    unsigned char bits = charBytes[i*byteWidth+j];
		      int byteX = x0+j*8;
		      for (int k=0; k<8; k++) {
			      if (bits & (1 << k))
              drawPixel(byteX+k, y, t_color, 0);
			      }
		      }
	    }
    }

  void ledGraphics::linearFade(int amount){
    for(int i=0; i<canvas->getSize(); i++){
      canvas->getLEDs()[i].subtractFromRGB(amount);
    }
  }
  
  void ledGraphics::erase(){
    fillScreen(CRGB(0,0,0));
  }

  word ledGraphics::font[64] = {0b0000000000000000, 0b0000011101000000, 0b1100000000110000, 0b1111101010111110, 0b1101011111101100, 0b1001100100110010, 0b1111111101001110, 0b0000011000000000, 0b0111010001000000, 0b0000010001011100, 0b1010101110101010, 0b0010001110001000, 0b0000100010000000, 0b0010000100001000, 0b0000000001000000, 0b0000101110100000, 0b1111110001111110, 0b1000111111000010, 0b1011110101111010, 0b1000110101111110, 0b1110000100111110, 0b1110110101101110, 0b1111110101101110, 0b1000010000111110, 0b1111110101111110, 0b1110010100111110, 0b0000001010000000, 0b0000101010000000, 0b0010001010100010, 0b0101001010010100, 0b1000101010001000, 0b1000010101111000, 0b0111010001011010, 0b1111110100111110, 0b1111110101110110, 0b0111010001100010, 0b1111110001011100, 0b1111110101100010, 0b1111110100100000, 0b0111110001100110, 0b1111100100111110, 0b1000111111100010, 0b1000111111100000, 0b1111100100110110, 0b1111100001000010, 0b1111111000111110, 0b1111110000011110, 0b0111110001111100, 0b1111110100111000, 0b0111010011011010, 0b1111110100010110, 0b0110110101101100, 0b1000011111100000, 0b1111000001111110, 0b1111000011111100, 0b1111100011111110, 0b1101100100110110, 0b1110100101111110, 0b1001110101110010, 0b1111110001000000, 0b1000001110000010, 0b0000010001111110, 0b0100010000010000, 0b0000100001000010};
