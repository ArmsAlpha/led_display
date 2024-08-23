//big thanks to https://github.com/Roachbones/tv_head as a point of reference and inspiration
//as well as https://github.com/lyriarte/StripDisplay/ for key insight on using bitmaps
//and https://twitter.com/minbitt for inspiration and being super cool

#include <Adafruit_CircuitPlayground.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>

#include "led_canvas.h"
#include "led_graphics.h"
#include "led_animation.h"
#include "crt_channel.h"
#include "src/emoticons/ch_emoticons.h"
#include "src/eyeball/ch_eyeball.h"
#include "src/errors/ch_errors.h"

//#include "src/emoticons/sprites/emoticon_sprites.h"
//#include "led_drawables.h"

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
#define BUTTON_CH_UP 4
#define BUTTON_CH_DOWN
#define BUTTON_A 5
#define BUTTON_B
#define BUTTON_POWER

CRGB leds[NUM_LEDS];
CRGB leds_buffer[NUM_LEDS];
Canvas canvas(NUM_LEDS_X, NUM_LEDS_Y, leds, leds_buffer, Canvas::ORIGIN_SW, Canvas::WRAP_H, 1);
LedGraphics graphics(&canvas);

CrtChannel* channel;

uint8_t mode = 0; //Current display mode/channel
uint8_t power = 1; //Keeps track of whether monitor display is 'on' or 'off'
int input = 0;
uint8_t input_lockout = 1000/FRAME_TIME_MILLIS;
unsigned long frametimer = 0; //How long the current frame has been running for
int i = 0;


//-------------FUNCTIONS-------------

void update(){

}

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
    return ((x - high) * (x - low) <= 0);
}

//-------------SETUP-------------
void setup() {
  delay(4000);
  // put your setup code here, to run once:

  //init board parameters
  CircuitPlayground.begin(50);
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
  Serial.begin(9600);

  //init leds
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  //init pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_LEFT, INPUT_PULLDOWN);
  pinMode(BUTTON_RIGHT, INPUT_PULLDOWN);

  //init channel
  channel = new ChEmoticons();
  channel->enter(&graphics, input, CircuitPlayground.motionZ(), CircuitPlayground.motionY());

  //Test graphics
  //graphics.drawSprite(2, 3, 8, 9, epd_bitmap_eyes_allArray[1], CRGB(255, 255, 255));
  //graphics.drawSprite(9, 3, 8, 9, epd_bitmap_mouth_allArray[1], CRGB(255, 255, 255));

  canvas.update();
  FastLED.show();

  delay(1);
}

//-------------LOOP-------------
void loop() {
  // put your main code here, to run repeatedly:
  frametimer = millis();

   //Change Channel
  if(input_lockout == 0 && input == BUTTON_CH_UP){
    
    input_lockout = 1000/FRAME_TIME_MILLIS; //Reset lockout timer
    channel->exit(&graphics, input, CircuitPlayground.motionZ(), CircuitPlayground.motionY());
    delete channel;
    Serial.print("Changing mode from ");
    Serial.println(mode);
    if(mode == 0) channel = new ChEyeball();
    else if (mode == 1) channel = new ChErrors();
    else if (mode == 2) channel = new ChEmoticons();
    channel->enter(&graphics, input, CircuitPlayground.motionZ(), CircuitPlayground.motionY());
    mode = (mode + 1) % 3;
  }
  

  channel->update(&graphics, input, CircuitPlayground.motionZ(), CircuitPlayground.motionY());


  canvas.update();
  FastLED.show();
  delay(1);

  //Serial.println(input);

  if (input_lockout > 0) input_lockout--;
  
  while(millis() - frametimer < FRAME_TIME_MILLIS){
    //Listen for input and kill time until the current frame is supposed to be over
    listen();
    if (digitalRead(BUTTON_LEFT)) {
      input = BUTTON_LEFT;
    }
    else if (digitalRead(BUTTON_RIGHT)){
      input = BUTTON_RIGHT;
    }
    else input = 0;

    FastLED.show();
    delay(1);
  }
  
}
