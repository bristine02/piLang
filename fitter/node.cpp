#include "fitter.h"
#include <cstdlib>

Node::Node(){
	float x = std::rand() % FITTER_X_MAX;
	float y = std::rand() % FITTER_Y_MAX;

	this->location  = Vector2d(x, y);
	this->net_force = Vector2d(0, 0);

}

Node::~Node(){}
