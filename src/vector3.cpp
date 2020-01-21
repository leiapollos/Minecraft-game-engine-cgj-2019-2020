#include <iostream>
#include <sstream>
#include <iomanip>
#include "vector3.h"


Vector3::Vector3(float x, float y, float z) {
	set(x,y,z);
}

Vector3::Vector3() {
	set(0,0,0);
}

Vector3::Vector3(const Vector2 &vec){
	set(vec.x,vec.y,1.0f);
}

Vector3::~Vector3(void) {

}

inline void Vector3::set(float x, float y, float z) { 
	this->x = x; this->y = y; this->z = z; 
}

float Vector3::dot(const Vector3 &vec) const {
	return x*vec.x + y*vec.y + z*vec.z;
}

Vector3 Vector3::cross(const Vector3 &vec) const {
	return Vector3(y * vec.z - z * vec.y,z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

float Vector3::magnitude() const {
	return sqrtf(x*x+y*y+z*z);
}

Vector3 lerp(const Vector3& a, const Vector3& b, float n) {
	n = n > 1 ? 1 : n;
	return a + (b - a) * n;
}

float distance(const Vector3& a, const Vector3& b) {
	return (a-b).magnitude();
}

float Vector3::angle(const Vector3 &vec) const {
	float dota = dot(vec)/(vec.magnitude()*magnitude());
	return acosf((dota < -1.0f ? -1.0f : ( dota > 1.0f ? 1.0f : dota )));
}

Vector3 Vector3::normalize() const {
	return x == 0 && y == 0 && z == 0 ? Vector3(0,0,0) : *this/this->magnitude();
}

// Rodrigues rotation formula
Vector3 Vector3::rotate(float theta, const Vector3 &axis) const {
	float cos_theta = cosf(theta * (float)M_PI / 180.0f );
	float sin_theta = sinf(theta * (float)M_PI / 180.0f );
	Vector3 r = cos_theta*(*this) + sin_theta*axis.cross(*this) + axis*axis.dot(*this) * (1 - cos_theta);
	r.clean();
	return r;
}

void Vector3::clean(){
    float small = 1.0e-6f;
    if (x < small && -x < small) x = 0.0;
    if (y < small && -y < small) y = 0.0;
    if (z < small && -z < small) z = 0.0;
}

