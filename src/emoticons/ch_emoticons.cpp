#include "ch_emoticons.h"
#include "states/face_states.h"

//---CLASS CHEMOTICONS:

ChEmoticons::ChEmoticons(){
	face_state_ = new DefaultFaceState();
    eyes_i_ = 0;
    mouth_i_ = 0;
    input_lockout_ = 5;
    state_lockout_ = 10;
}

ChEmoticons::~ChEmoticons(){
	delete face_state_;
}

void ChEmoticons::enter(LedGraphics* g, int input, float mZ, float mY){

}

void ChEmoticons::update(LedGraphics* g, int input, float mZ, float mY){
	FaceState* s = face_state_->update(*this, g, input, mZ, mY);
	if (s != NULL){
		face_state_->exit(*this, g, input, mZ, mY);
		delete face_state_;
		face_state_ = s;
		face_state_->enter(*this, g, input, mZ, mY);
  	}
}

void ChEmoticons::exit(LedGraphics* g, int input, float mZ, float mY){
	
}