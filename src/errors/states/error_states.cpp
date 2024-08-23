

#include "error_states.h"

#include "../ch_errors.h"
#include "../../../led_graphics.h"
#include "../sprites/error_sprites.h"

//---CLASS SMPTEERRORSTATE:

SMPTEErrorState::SMPTEErrorState(){
	entered_ = 0;
}

void SMPTEErrorState::enter(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){
	entered_ = 1;
	g->erase();
	//Draw the SMPTE screen
	//Top Bars
	g->fillRect(0, 0, 3, 10, CRGB(255, 255, 255));
	g->fillRect(3, 0, 3, 10, CRGB(255, 255, 0));
	g->fillRect(6, 0, 3, 10, CRGB(0, 255, 255));
	g->fillRect(9, 0, 3, 10, CRGB(0, 255, 0));
	g->fillRect(12, 0, 3, 10, CRGB(255, 0, 254));
	g->fillRect(15, 0, 3, 10, CRGB(255, 0, 0));
	g->fillRect(18, 0, 3, 10, CRGB(0, 0, 255));
	//Middle Bars
	g->fillRect(0, 10, 3, 2, CRGB(0, 0, 255));
	g->fillRect(6, 10, 3, 2, CRGB(255, 0, 254));
	g->fillRect(12, 10, 3, 2, CRGB(0, 255, 255));
	g->fillRect(18, 10, 3, 2, CRGB(255, 255, 255));
	//Bottom Bars
	g->fillRect(0, 12, 4, 3, CRGB(48, 96, 180));
	g->fillRect(4, 12, 4, 3, CRGB(255, 255, 255));
	g->fillRect(8, 12, 4, 3, CRGB(63, 30, 116));
	g->fillRect(16, 12, 4, 3, CRGB(100, 100, 100));
}

ErrorState* SMPTEErrorState::update(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){
	if(entered_ == 0) this->enter(ch, g, input, mZ, mY);

	//Handle inputs
	if(ch.input_lockout_ == 0 && input == 4){
		ch.input_lockout_ = 5;
		return new SMPTEErrorState();
	}

	if (ch.input_lockout_ > 0) ch.input_lockout_--;

	return NULL;
}

void SMPTEErrorState::exit(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){
	
}

//---CLASS StaticERRORSTATE:

StaticErrorState::StaticErrorState(){

}

void StaticErrorState::enter(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){

}

ErrorState* StaticErrorState::update(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){
	//Handle inputs
	if(ch.input_lockout_ == 0 && input == 4){
		ch.input_lockout_ = 5;
		return new SMPTEErrorState();
	}

	if (ch.input_lockout_ > 0) ch.input_lockout_--;

	return NULL;
}

void StaticErrorState::exit(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){
	
}

//---CLASS BSODERRORSTATE:

BSODErrorState::BSODErrorState(){

}

void BSODErrorState::enter(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){

}

ErrorState* BSODErrorState::update(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){
	//Handle inputs
	if(ch.input_lockout_ == 0 && input == 4){
		ch.input_lockout_ = 5;
		return new SMPTEErrorState();
	}

	if (ch.input_lockout_ > 0) ch.input_lockout_--;

	return NULL;
}

void BSODErrorState::exit(ChErrors& ch, LedGraphics* g, int input, float mZ, float mY){
	
}