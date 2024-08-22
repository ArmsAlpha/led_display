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

//#include "src/emoticons/sprites/emoticon_sprites.h"
//#include "led_drawables.h"

#define FRAME_TIME_MILLIS 250 //Duration of a single frame in millis
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
uint8_t power = 0; //Keeps track of whether monitor display is 'on' or 'off'
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

  //init channel
  channel = new ChEmoticons();
  channel->enter(&graphics);

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

  channel->update(&graphics);
  canvas.update();
  FastLED.show();
  
  while(millis() - frametimer < FRAME_TIME_MILLIS){
    //Listen for input and kill time until the current frame is supposed to be over
    listen();
    FastLED.show();
    delay(1);
  }
  
}
