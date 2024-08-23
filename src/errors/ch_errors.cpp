#include "ch_errors.h"
#include "states/error_states.h"

//---CLASS ChErrors:

ChErrors::ChErrors(){
	error_state_ = new SMPTEErrorState();
	input_lockout_ = 5;
}

ChErrors::~ChErrors(){
	delete error_state_;
}

void ChErrors::enter(LedGraphics* g, int input, float mZ, float mY){

}

void ChErrors::update(LedGraphics* g, int input, float mZ, float mY){
	ErrorState* s = error_state_->update(*this, g, input, mZ, mY);
	if (s != NULL){
		error_state_->exit(*this, g, input, mZ, mY);
		delete error_state_;
		error_state_ = s;
		error_state_->enter(*this, g, input, mZ, mY);
  	}
}

void ChErrors::exit(LedGraphics* g, int input, float mZ, float mY){
	
}