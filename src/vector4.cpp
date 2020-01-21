#include <iostream>
#include <sstream>
#include <iomanip>
#include "vector4.h"



Vector4::Vector4(float x=0, float y=0, float z=0, float w=0) {
	set(x,y,z,w);
}

Vector4::Vector4() {
	set(0,0,0,0);
}

/*Vector4::Vector4(const Vector2 &vec){
	set(vec.x,vec.y,1.0f,1.0f);
}*/

Vector4::Vector4(const Vector4 &vec){
	set(vec.x,vec.y,vec.z,vec.w);
}

Vector4::Vector4(const Vector3 &vec){
	set(vec.x,vec.y,vec.z,1.0f);
}
Vector4::~Vector4(void) {

}

inline void Vector4::set(float x, float y, float z, float w) { 
	this->x = x; this->y = y; this->z = z; this->w = w; 
}

float Vector4::dot(const Vector4 &vec) {
	return x*vec.x + y*vec.y + z*vec.z + w*vec.w;
}

Vector4 Vector4::normalize() {
	Vector4 v = Vector4(0,0,0,0);
	float s = 1 / (w * sqrtf(x*x + y*y + z*z));
	v.x = x * s;
	v.y = y * s;
	v.z = z * s;
	v.w = 1.0f;
	return v;

	//return (x == 0 && y == 0 && z == 0 && w == 0) ? Vector4(0,0,0,0) : *this/this->magnitude();
}

float Vector4::magnitude() const {
	return sqrtf(x*x+y*y+z*z+w*w);
}

void Vector4::clean(){
    float small = 1.0e-6f;
    if (x < small && -x < small) x = 0.0;
    if (y < small && -y < small) y = 0.0;
    if (z < small && -z < small) z = 0.0;
    if (w < small && -w < small) w = 0.0;
}