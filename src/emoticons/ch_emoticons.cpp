#include "ch_emoticons.h"
#include "states/face_states.h"

//---CLASS CHEMOTICONS:

ChEmoticons::ChEmoticons(){
	face_state_ = new DefaultFaceState();
    eyes_i_ = 0;
    moutn_i_ = 0;
}

ChEmoticons::~ChEmoticons(){
	delete face_state_;
}

void ChEmoticons::enter(LedGraphics* g){

}

void ChEmoticons::update(LedGraphics* g){
	FaceState* s = face_state_->update(*this, g);
	if (s != NULL){
		face_state_->exit(*this, g);
		delete face_state_;
		face_state_ = s;
		face_state_->enter(*this, g);
  	}
}

void ChEmoticons::exit(LedGraphics* g){
	
}