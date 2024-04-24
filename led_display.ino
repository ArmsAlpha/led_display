//big thanks to https://github.com/Roachbones/tv_head as a point of reference and inspiration

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
#include "led_drawables.h"
#include "sprites.h"

#define FRAME_TIME_MILLIS 100
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
Canvas canvas(NUM_LEDS_X, NUM_LEDS_Y, leds, Canvas::ORIGIN_SW, WRAP_H, 1);

uint8_t mode = 4; //Keeps track of current display mode
unsigned long frametimer = 0; //Keeps track of how long the current frame has been running for
unsigned int chat_delay = 1000; //Min. length of time before twitch chat updates

int mZ;
int mY;

CHSV pupil_colors[8] = {CHSV(255, 255, 255),
                        CHSV(100, 255, 20),
                        CHSV(250, 230, 20),
                        CHSV(220, 110, 20),
                        CHSV(255, 25,  120),
                        CHSV(210, 25,  255),
                        CHSV(40,  165, 240),
                        CHSV(40,  20,  230)};
CHSV white_c = CHSV(100,0,255);
int p_color_num = 0;

CHSV chat_colors[15] = {CHSV(0,   240, 120),
                        CHSV(160, 240, 120),
                        CHSV(80,  240, 60),
                        CHSV(0,   163, 100),
                        CHSV(11,  240, 158),
                        CHSV(53,  146, 120),
                        CHSV(11,  240, 120),
                        CHSV(98,  121, 87),
                        CHSV(29,  179, 118),
                        CHSV(17,  180, 113),
                        CHSV(121, 61,  120),
                        CHSV(140, 240, 134),
                        CHSV(220, 240, 169),
                        CHSV(181, 182, 127),
                        CHSV(0,   255, 127),};

//-------------FUNCTIONS-------------

//Check for new inputs, called every frame. Returns a value based on input
uint8_t listen(){
  
}

//
void changeMode(uint8_t t_mode){
  
}

//
uint8_t inRange(float low, float high, float x)
{
    return ((x-high)*(x-low) <= 0);
}

//
int remapZ(float t_z){
  if(t_z>3){
    return -4;
  }
  else if(t_z<-3){
    return 3;
}
  else if(t_z>2){
    return -2;
  }
  else if (t_z<-2){
    return 2;
  }
  else if(t_z>1){
    return -1;
  }
  else if (t_z<-1){
    return 1;
  }
  else return 0;
}

int remapY(float t_y){
  if(t_y>4){
    return 2;
  }
  else if(t_y<-4){
    return -2;
}
  else if(t_y>2){
    return 1;
  }
  else if (t_y<-2){
    return -1;
  }
  else return 0;
}


//Shifts the contents of the canvas up by the number of lines specified
void shiftup(int num_lines){
  for(int i=0; i>canvas.getHeight(); i++){
    for(int j=0; j>canvas.getWidth(); j++){     
      if(i-num_lines>=0) canvas.drawPoint(j,i-num_lines,canvas.getPoint(j,i),0);
    }
  }
}

//------------ANIMATIONS------------
//scrolls a string from right to left
void marquee(char str[], int len, int y, CHSV color){
  
}

void eyeBlink(){
  canvas.erase();
  canvas.drawSprite16(1,1,9,12,eyeballHalfL2_16,white_c);
  canvas.drawSprite16(10,1,9,12,eyeballHalfR2_16,white_c);
  FastLED.show();
  canvas.erase();
  FastLED.delay(25);
  canvas.drawSprite16(1,1,9,12,eyeballHalfL3_16,white_c);
  canvas.drawSprite16(10,1,9,12,eyeballHalfR3_16,white_c);
  FastLED.show();
  canvas.erase();
  FastLED.delay(100);
  canvas.drawSprite16(1,1,9,12,eyeballHalfL2_16,white_c);
  canvas.drawSprite16(10,1,9,12,eyeballHalfR2_16,white_c);
  FastLED.show();
  canvas.erase();
  FastLED.delay(50);
  p_color_num +=1;
  p_color_num = p_color_num%8;
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
  //init pins
  pinMode(LED_PIN, OUTPUT);

}

//-------------LOOP-------------
void loop() {
  // put your main code here, to run repeatedly:
  frametimer=millis();

  switch(mode){
    case 0: //Off - Don't do anything
    
      break;
    case 1: //Power on/off - play a little animation when turning the monitor on/off
      EVERY_N_MILLIS(200){
  Serial.print("\nX: ");
  Serial.println(CircuitPlayground.motionX());
  Serial.print("Y: ");
  Serial.println(CircuitPlayground.motionY());
  Serial.print("Z: ");
  Serial.println(CircuitPlayground.motionZ());
  Serial.print("H Rot: ");
  Serial.println(remapZ(CircuitPlayground.motionZ()));
  Serial.print("V Rot: ");
  Serial.println(remapY(CircuitPlayground.motionY()));
  }
    
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
       EVERY_N_MILLIS(5000){
          eyeBlink();
       }
       canvas.drawSprite16(1,1,9,12,eyeballHalfL_16,white_c);
       canvas.drawSprite16(10,1,9,12,eyeballHalfR_16,white_c);

       mZ = 8+remapZ(CircuitPlayground.motionZ()); //map();
       mY = 5+remapY(CircuitPlayground.motionY());
       canvas.drawSprite8(mZ,mY,4,4,pupil_8,pupil_colors[p_color_num]);
       FastLED.show();
       canvas.erase();
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
