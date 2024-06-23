#include "fitter.h"
#include <cmath>


Vector2d::Vector2d(float x, float y){
	this->x = x;
	this->y = y;
}

Vector2d::Vector2d(){
	this->x = 0.f;
	this->y = 0.f;
}

Vector2d::~Vector2d(){

}

float Vector2d::get_x(){ return this->x; }

float Vector2d::get_y(){ return this->y; }

void Vector2d::set_x(float x){ this->x = x; }

void Vector2d::set_y(float y){ this->y = y; }


Vector2d Vector2d::copy(){
	return Vector2d(this->x, this->y);
}

float Vector2d::mag(){
	return sqrt(this->x * this->x + this->y * this->y);
}

Vector2d& Vector2d::mult(float n){
	this->x *= n;
	this->y *= n;
	return *this;
}

Vector2d& Vector2d::div(float n){
	this->x /= n;
	this->y /= n;
	return *this;
}

Vector2d& Vector2d::sub(Vector2d& other){
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2d& Vector2d::add(Vector2d& other){
	this->x += other.x;
	this->y += other.y;
	return *this;
}
