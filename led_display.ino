//big thanks to https://github.com/Roachbones/tv_head as a point of reference and inspiration

//MODE IDEAS: terminal, expressions, text, eyeball, audio visualizer, fishbowl, undertale
//MASKING: allow sprites to be used for masking effects such as fade/color change
//POSITIVE/NEGATIVE MASKING: Apply effects to the bits included in sprite mask, or all bits NOT covered by sprite mask
//Possibly use fastLED's build-in palette framework for colors?
//Alpha blending support


//Adding a new comment here to test git stuff

#include <Adafruit_CircuitPlayground.h>
#include <FastLED.h>
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
CHSV hsv_leds[NUM_LEDS];
Canvas canvas(NUM_LEDS_X, NUM_LEDS_Y, Canvas::SW, 1, hsv_leds);

uint8_t mode = 3; //Keeps track of current display mode
unsigned long frametimer = 0; //Keeps track of how long the current frame has been running for

int mZ;
int mY;

CHSV pupil_colors[8] = {CHSV(255, 255, 255),
                        CHSV(100, 255, 20),
                        CHSV(250, 230, 20),
                        CHSV(220, 110, 20),
                        CHSV(255, 25, 120),
                        CHSV(210, 25, 255),
                        CHSV(40, 165, 240),
                        CHSV(40, 20, 230)};
CHSV white_c = CHSV(100,0,255);
int p_color_num = 0;

//-------------FUNCTIONS-------------

//Check for new inputs, called every frame. Returns a value based on input
uint8_t listen(){
  
}

void changeMode(uint8_t t_mode){
  
}

uint8_t inRange(float low, float high, float x)
{
    return ((x-high)*(x-low) <= 0);
}

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
  delay(25);
  canvas.drawSprite16(1,1,9,12,eyeballHalfL3_16,white_c);
  canvas.drawSprite16(10,1,9,12,eyeballHalfR3_16,white_c);
  FastLED.show();
  canvas.erase();
  delay(100);
  canvas.drawSprite16(1,1,9,12,eyeballHalfL2_16,white_c);
  canvas.drawSprite16(10,1,9,12,eyeballHalfR2_16,white_c);
  FastLED.show();
  canvas.erase();
  delay(50);
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
 
  //Test out the new canvas system
  canvas.drawSprite16(1,1,9,12,eyeballHalfL_16,white_c);
  canvas.drawSprite16(10,1,9,12,eyeballHalfR_16,white_c);
  canvas.drawSprite8(8,5,4,4,pupil_8,white_c);
  canvas.printCanvas();
  Serial.println("Done Drawing\n");
  FastLED.show();
  canvas.erase();
  /*
  canvas.drawRect(2,4,2,3,pupil_colors[0]);
  canvas.drawRect(4,7,2,3,pupil_colors[1]);
  canvas.drawRect(6,4,2,3,pupil_colors[2]);
  canvas.drawRect(8,7,2,3,pupil_colors[3]);
  canvas.drawRect(10,4,2,3,pupil_colors[4]);
  canvas.drawRect(12,7,2,3,pupil_colors[5]);
  canvas.drawRect(14,4,2,3,pupil_colors[6]);
  canvas.drawRect(16,7,2,3,pupil_colors[7]);
  canvas.drawRect(0,11,20,1,pupil_colors[0]);
  FastLED.show();
  */
  
  /*
  leds[1] = white_c;
  FastLED.show();
  */
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
       canvas.drawSprite8(mZ,mY,4,4,pupil_8,pupil_colors[p_color_num]); //TODO: Use accelerometer to have pupil follow rotation
       FastLED.show();
       canvas.erase();
       break; 
  }
  listen();
  while(frametimer < FRAME_TIME_MILLIS){
    //Kill time until the current frame is supposed to be over
  }
  

}
