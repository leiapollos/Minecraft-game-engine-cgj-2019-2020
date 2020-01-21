#ifndef VECTOR2_H
#define VECTOR2_H
#include <cmath>
#include <ostream>
#include <istream>
#include <array>
#include "Constants.h"

class Vector2 {
	private:
		inline bool cmpf(float A, float B, float epsilon = 0.005f) const{ return (fabs(A - B) < epsilon); }
		inline bool cmp(const Vector2 &vec) const{ return cmpf(x, vec.x) && cmpf(y, vec.y); }
	public:
		union {
            struct{
                float x, y;
            };
            std::array<float,2> data;
        };
		Vector2(float x, float y);
		Vector2();
		~Vector2(void);
		
		inline void set(float x, float y);


		inline Vector2 operator=(const Vector2 &vec) { x = vec.x; y = vec.y; return *this;}

		inline Vector2 operator*(float num) const { return Vector2(x * num, y* num); }
		inline friend Vector2 operator*(float num, const Vector2 &vec) { return Vector2(vec.x * num, vec.y* num); }
		inline Vector2 operator*(const Vector2 &vec) const { return Vector2(x * vec.x, y* vec.y); }

		inline Vector2 operator/(float num) const { return Vector2(x / num, y/ num); }
		inline friend Vector2 operator/(float num, const Vector2 &vec) { return Vector2(num/vec.x, num/vec.y); }
		inline Vector2 operator/(const Vector2 &vec) const { return Vector2(x / vec.x, y/ vec.y); }
		
		inline Vector2 operator+(const Vector2 &vec) const{ return Vector2(x + vec.x, y + vec.y); }
		inline friend Vector2 operator+(float num, const Vector2 &vec) { return Vector2(vec.x + num, vec.y+ num); }
		inline Vector2 operator+(float num) const { return Vector2(x + num, y+ num); }
		
		inline Vector2 operator-(const Vector2 &vec) const{ return Vector2(x - vec.x, y - vec.y); }
		inline friend Vector2 operator-(float num, const Vector2 &vec) { return Vector2(num-vec.x, num-vec.y); }
		inline friend Vector2 operator-(const Vector2 &vec) { return Vector2(-vec.x, -vec.y); }
		inline Vector2 operator-(float num) const { return Vector2(x - num, y - num); }

		inline bool operator==(const Vector2 &vec) const{ return cmp(vec); }
		inline bool operator!=(const Vector2 &vec) const{ return !cmp(vec); }

		inline friend std::ostream& operator<<(std::ostream& os, const Vector2 &vec) { 
			os << '{' << vec.x << ", " << vec.y << "}\n";
			return os;
		}

		inline friend std::istream& operator>>(std::istream& is, Vector2 &vec) {
			while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
    		is >> vec.x;
    		while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
    		is >> vec.y;
    		while (is.peek() != '\n') { is.get();}
			is.get();
			return is;
		}

		float angle(const Vector2 &vec);
		float dot(const Vector2 &vec);
		Vector2 rotate(float theta);
		Vector2 normalize();
		float magnitude() const;
		void clean();
};
#endif