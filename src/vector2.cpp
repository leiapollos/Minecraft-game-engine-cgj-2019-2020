#include <iostream>
#include <sstream>
#include <iomanip>
#include "vector2.h"


Vector2::Vector2(float x, float y) {
	set(x,y);
}

Vector2::Vector2() {
	set(0,0);
}
Vector2::~Vector2(void) {

}

inline void Vector2::set(float x, float y) { 
	this->x = x; this->y = y; 
}

float Vector2::dot(const Vector2 &vec) {
	return x*vec.x + y*vec.y;
}

float Vector2::angle(const Vector2 &vec) {
	float dota = dot(vec)/(vec.magnitude()*magnitude());
	return acosf((dota < -1.0f ? -1.0f : ( dota > 1.0f ? 1.0f : dota )));
}

Vector2 Vector2::rotate(float theta) {
	float cos_theta = cosf(theta * (float)M_PI / 180.0f);
	float sin_theta = sinf(theta * (float)M_PI / 180.0f);
	Vector2 v = Vector2(x*cos_theta - y*sin_theta, y*cos_theta + x*sin_theta);
	v.clean();
	return v;
}

Vector2 Vector2::normalize() {
	return x == 0 && y == 0 ? Vector2(0,0) : *this/this->magnitude();
}

void Vector2::clean(){
    float small = 1.0e-6f;
    if (x < small && -x < small) x = 0.0;
    if (y < small && -y < small) y = 0.0;
}

float Vector2::magnitude() const { 
	return sqrtf(x*x+y*y);
}