

#include "eyeball_states.h"

#include "../ch_eyeball.h"
#include "../../../led_graphics.h"
#include "../sprites/eyeball_sprites.h"

//---CLASS DEFAULTEyeballState:

DefaultEyeballState::DefaultEyeballState(){
	
	blink_timer_ = blink_intervals_[0];
}

int DefaultEyeballState::remapZ(float t_z){
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

int DefaultEyeballState::remapY(float t_y){
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

void DefaultEyeballState::enter(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY){
	Serial.println("Enter(DefaultEyeballState)");
}

EyeballState* DefaultEyeballState::update(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY){
	
	g->erase();

	//Handle Blinking
	if(blink_timer_ <= 0){
		ch.eyelid_ = 0;
		blink_i_ = (blink_i_ + 1) % 7;
		blink_timer_ = blink_intervals_[blink_i_];
	}
	else if(blink_timer_ == 1 || blink_timer_ == 3){
		ch.eyelid_ = 1;
	}
	else if (blink_timer_ == 2){
		ch.eyelid_ = 2;
	}

	//Draw Eye
	g->drawSprite(1, 1, 24, 12, epd_bitmap_eyeball_allArray[ch.eyelid_], CRGB(255, 255, 255));

	if(ch.eyelid_ != 2) g->drawSprite(8 + remapZ(mZ), 5 + remapY(mY), 8, 4, epd_bitmap_eyeball_pupil, CRGB(255, 255, 255));

	//Decrement timers:
	blink_timer_ -= 1;

	return NULL;
}

void DefaultEyeballState::exit(ChEyeball& ch, LedGraphics* g, int input, float mZ, float mY){
	
}