#include "fitter.h"


FitterLocation::FitterLocation(float x, float y){
	this->x = x;
	this->y = y;
}

FitterLocation::~FitterLocation(){

}

float FitterLocation::get_x(){ return this->x; }

float FitterLocation::get_y(){ return this->y; }

void FitterLocation::set_x(float x){ this->x = x; }

void FitterLocation::set_y(float y){ this->y = y; }



Node::Node(){}
Node::~Node(){}
//virtual FitterLocation get_location();
//virtual void  set_location(FitterLocation location);
//virtual float get_mass();


Fitter::Fitter(){}
Fitter::~Fitter(){}

void Fitter::layout(std::vector<Node> nodes){

}
