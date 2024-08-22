#include "face_states.h"
#include "../ch_emoticons.h"
#include "../../../led_graphics.h"
#include "../sprites/emoticon_sprites.h"

//---CLASS DEFAULTFACESTATE:

DefaultFaceState::DefaultFaceState(){
	blink_timer_ = 30;
}

void DefaultFaceState::enter(ChEmoticons& ch, LedGraphics* g){

}

FaceState* DefaultFaceState::update(ChEmoticons& ch, LedGraphics* g){
	if(blink_timer_ = 0){
		ch.eyes_i_ = 0;
		blink_timer_ = 30;
	}
	else if(blink_timer_ = 2){
		ch.eyes_i_ = 1;
	}

	g->drawSprite(2, 3, 8, 9, epd_bitmap_eyes_allArray[1], CRGB(255, 255, 255));
	g->drawSprite(9, 3, 8, 9, epd_bitmap_mouth_allArray[1], CRGB(255, 255, 255));

	return NULL;
}

void DefaultFaceState::exit(ChEmoticons& ch, LedGraphics* g){
	
}

//--------------------------------------------------------


//---CLASS TALKINGFACESTATE:

TalkingFaceState::TalkingFaceState(){

}

void TalkingFaceState::enter(ChEmoticons& ch, LedGraphics* g){

}

FaceState* TalkingFaceState::update(ChEmoticons& ch, LedGraphics* g){
	
	return NULL;
}

void TalkingFaceState::exit(ChEmoticons& ch, LedGraphics* g){
	
}

//--------------------------------------------------------


//---CLASS DAZEDFACESTATE:

DazedFaceState::DazedFaceState(){

}

void DazedFaceState::enter(ChEmoticons& ch, LedGraphics* g){

}

FaceState* DazedFaceState::update(ChEmoticons& ch, LedGraphics* g){
	
	return NULL;
}

void DazedFaceState::exit(ChEmoticons& ch, LedGraphics* g){
	
}

//--------------------------------------------------------


//---CLASS CONFUSEDFACESTATE:

ConfusedFaceState::ConfusedFaceState(){

}

void ConfusedFaceState::enter(ChEmoticons& ch, LedGraphics* g){

}

FaceState* ConfusedFaceState::update(ChEmoticons& ch, LedGraphics* g){
	
	return NULL;
}

void ConfusedFaceState::exit(ChEmoticons& ch, LedGraphics* g){
	
}