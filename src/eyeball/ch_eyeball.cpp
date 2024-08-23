#include "ch_eyeball.h"
#include "states/eyeball_states.h"

//---CLASS CHEYEBALL:

ChEyeball::ChEyeball(){
	eyeball_state_ = new DefaultEyeballState();
	eyelid_ = 0;
}

ChEyeball::~ChEyeball(){
	delete eyeball_state_;
}

void ChEyeball::enter(LedGraphics* g, int input, float mZ, float mY){
	Serial.println("Enter(ChEyeball)");
}

void ChEyeball::update(LedGraphics* g, int input, float mZ, float mY){
	EyeballState* s = eyeball_state_->update(*this, g, input, mZ, mY);
	if (s != NULL){
		eyeball_state_->exit(*this, g, input, mZ, mY);
		delete eyeball_state_;
		eyeball_state_ = s;
		eyeball_state_->enter(*this, g, input, mZ, mY);
  	}
}

void ChEyeball::exit(LedGraphics* g, int input, float mZ, float mY){
	
}