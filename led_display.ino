//big thanks to https://github.com/Roachbones/tv_head as a point of reference and inspiration
//as well as https://github.com/lyriarte/StripDisplay/ for key insight on using bitmaps
//and https://twitter.com/minbitt for inspiration and being super cool

//MODE IDEAS: terminal, emoticons, text, eyeball, audio visualizer, fishbowl, undertale, 8-ball
//MASKING: allow sprites to be used for masking effects such as fade/color change
//POSITIVE/NEGATIVE MASKING: Apply effects to the bits included in sprite mask, or all bits NOT covered by sprite mask
//Possibly use fastLED's build-in palette framework for colors?
//Alpha blending support
//Support for loading sprites from .bmp

#include <Adafruit_CircuitPlayground.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include "led_canvas.h"
//#include "led_drawables.h"
#include "led_graphics.h"


#define FRAME_TIME_MILLIS 100 //Duration of a single frame in millis
//LED-related defines
#define NUM_LEDS 300
#define NUM_LEDS_X 20
#define NUM_LEDS_Y 15
#define BRIGHTNESS 25
#define DEFAULT_COLOR CHSV(60, 255, 80)
//Defines for pinouts
#define LED_PIN 6
#define BUTTON_LEFT 4
#define BUTTON_RIGHT 5
#define BUTTON_POWER 4

CRGB leds[NUM_LEDS];
CRGB leds_buffer[NUM_LEDS];
Canvas ch(NUM_LEDS_X, NUM_LEDS_Y, leds, Canvas::ORIGIN_SW, Canvas::WRAP_H, 1);
ledGraphics ledcanvas(leds_buffer, NUM_LEDS_X, NUM_LEDS_Y);

uint8_t mode = 0; //Keeps track of current display mode
unsigned long frametimer = 0; //Keeps track of how long the current frame has been running for
int i = 0;


//-------------FUNCTIONS-------------

//listen(): Check for new inputs, called every frame. Returns a value based on input
uint8_t listen(){
  return 0;
}

// changeMode(): Change current screen mode
void changeMode(uint8_t t_mode){
  mode = t_mode;
}

// inRange(): returns whether or not x is between low and high
uint8_t inRange(float low, float high, float x)
{
    return ((x-high)*(x-low) <= 0);
}

//shiftup(): Shifts the contents of the canvas up by the number of lines specified
void shiftup(int num_lines){
  for(int i=0; i>ch.getHeight(); i++){
    for(int j=0; j>ch.getWidth(); j++){     
      if(i-num_lines>=0) ledcanvas.drawPoint(j,i-num_lines,ch.getPoint(j,i),0);
    }
  }
}


//------------ANIMATIONS------------
//scrolls a string from right to left
void marquee(char str[], int len, int y, CHSV color){
  
}


//-------------SETUP-------------
void setup() {
  delay(4000);
  // put your setup code here, to run once:
  CircuitPlayground.begin(50);
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
  Serial.begin(9600);
  //init leds
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  ledcanvas.erase();
  ch.update();
  FastLED.show();
  //init pins
  pinMode(LED_PIN, OUTPUT);
}

//-------------LOOP-------------
void loop() {
  // put your main code here, to run repeatedly:
  frametimer=millis();

  switch(mode){
    case 0: //Off - Don't do anything
      /*
      canvas.drawPoint(i%NUM_LEDS_X,i/NUM_LEDS_X,CRGB(255,255,255),0);
      canvas.update();
      FastLED.show();
      canvas.drawPoint(i%NUM_LEDS_X,i/NUM_LEDS_X,CRGB(0,0,0),0);
      i = (i+1)%NUM_LEDS;
      canvas.drawPoint(0,0,CRGB(0,255,0),0);
      canvas.drawPoint(19,14,CRGB(255,0,0),0);
      */
      break;

    case 1: //Power on/off - play a little animation when turning the monitor on/off
      break;

    case 2: //Face
      /*IDEAS:
       - Have eyes blink at semi-random intervals (chance to blink after x seconds, force blink after x+y seconds)
       - Have mouth move when speaker detects sound
       - Buttons to control expressions
       */
      break;
    case 3: //Eyeball
      /*IDEAS:
       - Have pupil move based on rotation (rot. f/b = move u/d,  rot. sideways = move l/r
       - Have eyeball blink every once in a while (obscures pupil
       - Button to change pupil type: normal, colored, cat eye, etc.
       - Pupil animations? like fire or something
       */
       break; 

       case 4: //Twitch Chat
      /*IDEAS:
       - Display lines that scroll up every so often to emulate a scrolling chat
       - Initial line is random length and color to represent username
       - Possibility of random colored bit + empty bit to represent sub badge
       - SUbsequent lines are grey and can be random length/span multiple lines
       - Duration before scrolling is random but is a multiple of the time it takes for twitch chat to update
       - Scroll is achieved by moving contents of buffer up x lines depending on how many new chats are added
       
       - Make function drawMessage() which takes in parameters for lengths (name, message, etc.)
       */

      //Draw name of random length and color
      //(Random) Overwrite first 2 bits of name with a color followed by black
      //Decide how long the message will be
      //Start drawing message 2 spaces after name ends
      //>If message would reach the edge of the screen, move down a line and continue until counter is done
      //>While message is being drawn, have chance to replace bit with blank bit if there have been consecutive bits drawn
      //

      //!!!Have chance to draw chat reminder instead of message
      break;
  }
  listen();
  while(frametimer < FRAME_TIME_MILLIS){
    //Kill time until the current frame is supposed to be over
  }
  

}
