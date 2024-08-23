

#include "face_states.h"

#include "../ch_emoticons.h"
#include "../../../led_graphics.h"
#include "../sprites/emoticon_sprites.h"

//---CLASS DEFAULTFACESTATE:

DefaultFaceState::DefaultFaceState(){
	
	blink_timer_ = blink_intervals_[0];
}

void DefaultFaceState::enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	Serial.println("Enter(DefaultFaceState)");
}

FaceState* DefaultFaceState::update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	g->erase();

	//Handle Blinking
	if(blink_timer_ <= 0){
		ch.eyes_i_ = 0;
		blink_i_ = (blink_i_ + 1) % 7;
		blink_timer_ = blink_intervals_[blink_i_];
	}
	else if(blink_timer_ <= 1){
		ch.eyes_i_ = 1;
	}

	//Handle inputs
	if(ch.input_lockout_ == 0 && input == 4){
		ch.mouth_i_ = (ch.mouth_i_ + 1) % 6;
		ch.input_lockout_ = 5;
	}

	//Draw eyes and mouth
	g->drawSprite(2, 3, 8, 9, epd_bitmap_eyes_allArray[ch.eyes_i_], CRGB(255, 255, 255));
	g->drawSprite(9, 3, 8, 9, epd_bitmap_mouth_allArray[ch.mouth_i_], CRGB(255, 255, 255));


	//Decrement timers:
	blink_timer_ -= 1;
	if (ch.input_lockout_ > 0) ch.input_lockout_--;
	if (ch.state_lockout_ > 0) ch.state_lockout_--;

	//Handle state changes:
	
	if(ch.state_lockout_ == 0){
		if(mZ < -3) return new ConfusedFaceState(); //Tilting Left
		if(mZ > 3) return new DotsFaceState(); //Tilting Right
		//if(mY < -3) return new FaceState(); //Tilting Up
		if(mY > 3) return new LoadingFaceState(); //Tilting Down
	}
	

	return NULL;
}

void DefaultFaceState::exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
}

//--------------------------------------------------------


//---CLASS TALKINGFACESTATE:

TalkingFaceState::TalkingFaceState(){

}

void TalkingFaceState::enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){

}

FaceState* TalkingFaceState::update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
	return NULL;
}

void TalkingFaceState::exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
}

//--------------------------------------------------------


//---CLASS LOADINGFACESTATE:

LoadingFaceState::LoadingFaceState(){
	timer_ = 0;
	step_ = 0;
}

void LoadingFaceState::enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	g->erase();

}

FaceState* LoadingFaceState::update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
	if(timer_ == 2){
		g->linearFade(35);
		//g->erase();
		timer_ = 0;
		step_ = (step_ + 1) % 8;
	}

	switch(step_){
	case 0:
		g->fillRect(9, 1, 2, 2, CRGB(255, 255, 255));
		break;
	case 1:
		g->drawSprite(12, 2, 8, 3, epd_bitmap_misc_allArray[0], CRGB(255, 255, 255));
		//g->fillRect(12, 2, 3, 3, CRGB(255, 255, 255));
		break;
	case 2:
		g->fillRect(14, 6, 2, 2, CRGB(255, 255, 255));
		break;
	case 3:
		g->drawSprite(12, 9, 8, 3, epd_bitmap_misc_allArray[0], CRGB(255, 255, 255));
		//g->fillRect(12, 9, 3, 3, CRGB(255, 255, 255));
		break;
	case 4:
		g->fillRect(9, 11, 2, 2, CRGB(255, 255, 255));
		break;
	case 5:
		g->drawSprite(5, 9, 8, 3, epd_bitmap_misc_allArray[0], CRGB(255, 255, 255));
		//g->fillRect(5, 9, 3, 3, CRGB(255, 255, 255));
		break;
	case 6:
		g->fillRect(4, 6, 2, 2, CRGB(255, 255, 255));
		break;
	case 7:
		g->drawSprite(5, 2, 8, 3, epd_bitmap_misc_allArray[0], CRGB(255, 255, 255));
		//g->fillRect(5, 2, 3, 3, CRGB(255, 255, 255));
		break;
	}

	timer_++;

	if(mY < 1){
		return new DefaultFaceState();
	}

	return NULL;
}

void LoadingFaceState::exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
}

//--------------------------------------------------------


//---CLASS CONFUSEDFACESTATE:

ConfusedFaceState::ConfusedFaceState(){

}

void ConfusedFaceState::enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	Serial.println("Enter(ConfusedFaceState)");
	g->erase();
	g->drawSprite(7, 2, 8, 11, epd_bitmap_icons_allArray[2], CRGB(255, 255, 255));
}

FaceState* ConfusedFaceState::update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
	if(mZ > -1){
		return new DefaultFaceState();
	}
	return NULL;
}

void ConfusedFaceState::exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
}

//--------------------------------------------------------


//---CLASS DOTSFACESTATE:

DotsFaceState::DotsFaceState(){
	timer_ = 15;
}

void DotsFaceState::enter(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	g->erase();
}

FaceState* DotsFaceState::update(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
	if(timer_ == 15) g->fillRect(5, 11, 2, 2, CRGB(255, 255, 255));
	if(timer_ == 10) g->fillRect(9, 11, 2, 2, CRGB(255, 255, 255));
	if(timer_ == 5) g->fillRect(13, 11, 2, 2, CRGB(255, 255, 255));
	
	timer_--;
	if(timer_ == 0){
		g->erase();
		timer_ = 20;
	}

	if(mZ < 1){
		return new DefaultFaceState();
	}

	return NULL;
}

void DotsFaceState::exit(ChEmoticons& ch, LedGraphics* g, int input, float mZ, float mY){
	
}