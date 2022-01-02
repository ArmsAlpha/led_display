#pragma once
class Drawable;
//TODO: Figure out how to usr objects/shapes as masks for effects
class Canvas
{
  public:
  //Constructors:
    Canvas(uint8_t t_x, uint8_t t_y, CHSV *t_leds);
    Canvas(uint8_t t_x, uint8_t t_y, uint8_t t_s, uint8_t t_l, CHSV *t_leds);
    
    //Layout Definitions:
    static uint8_t NW;
    static uint8_t NE;
    static uint8_t SW;
    static uint8_t SE;
    
    //Accessors:
    uint8_t getSizeX();
    uint8_t getSizeY();
    int getSize();
    uint8_t inboundsX(uint8_t t_x);
    uint8_t inboundsY(uint8_t t_y);
    uint8_t inbounds(uint8_t t_x, uint8_t t_y);
    void printCanvas(); //Prints contents of canvas using Serial.println()

    //Helpers:
    int toIndex(int t_x, int t_y); //Converts X-Y coords to corresponding array index
    uint8_t toXY(int t_i); //Converts given index to X-Y coords.
    int remapXY(int t_x, int t_y); //Remaps coordinates to fit the assigned layout of LEDs and returns index i
    
    //Draw Functions:
    void drawPoint(uint8_t x, uint8_t y, CHSV t_color, uint8_t t_a);
    void drawRect(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, CHSV t_color);
    void drawLine(int8_t x, int8_t y, int8_t x2, int8_t y2, CHSV t_color);
    void drawSprite(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t *sprite, CHSV *palette);
    void drawSprite8(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint8_t *sprite, CHSV t_color);
    void drawSprite16(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint16_t *sprite, CHSV t_color);
    void drawSprite32(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, uint32_t *sprite, CHSV t_color);
    void drawChar(char character, int8_t x, int8_t y, CHSV t_color);
    void drawString(char str[], int8_t x, int8_t y, CHSV t_color);

    void drawObj(Drawable *t_d); //Calls draw() for the specified object

    //Effects:
    void linearFade(uint8_t amount); //Fades out every LED by a certain amount
    void linearFade(Drawable Mask); //TODO: maybe get id of this and use default arguments instead
    void erase(); //Clears entire canvas
    void eraseArea(int8_t x, int8_t y, uint8_t s_x, uint8_t s_y, CHSV t_color); //Clears canvas in rectangular area

  protected:
    uint8_t size_x;
    uint8_t size_y;
    uint8_t snake; //Denotes whether row directions alternate or stay the same. Default = 0
    uint8_t layout; //Denotes starting point of matrix, see definitions below. Default = 0
    static word font[];
    CHSV* leds;
    
};
