#ifndef VECTOR4_H
#define VECTOR4_H
#include <cmath>
#include "vector3.h"
#include <array>
#include "Constants.h"

class Vector4 {
	private:
		inline bool cmpf(float A, float B, float epsilon = 0.005f) const{ return (fabs(A - B) < epsilon); }
		inline bool cmp(const Vector4 &vec) const{ return cmpf(x, vec.x) && cmpf(y, vec.y) && cmpf(z, vec.z) && cmpf(w, vec.w); }
	public:
		union {
            struct{
                float x, y, z, w;
            };
            std::array<float,4> data;
        };
		Vector4(float, float, float, float);
		
		Vector4();
		~Vector4(void);
		//Vector4(const Vector2 &vec);
		Vector4(const Vector3 &vec);
		Vector4(const Vector4 &vec);
		
		inline void set(float x, float y, float z, float w);


		inline Vector4 operator=(const Vector4 &vec) { 
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
			return *this; 
		}

		inline Vector4 operator*(float num) const { return Vector4(x * num, y* num, z* num, w* num); }
		inline friend Vector4 operator*(float num, const Vector4 &vec) { return Vector4(vec.x * num, vec.y* num, vec.z* num, vec.w* num); }
		inline Vector4 operator*(const Vector4 &vec) const { return Vector4(x * vec.x, y* vec.y, z* vec.z, w* vec.w); }

		inline Vector4 operator/(float num) const { return Vector4(x / num, y/ num, z/ num, w/ num); }
		inline friend Vector4 operator/(float num, const Vector4 &vec) { return Vector4(num/vec.x, num/vec.y, num/vec.z, num/vec.w); }
		inline Vector4 operator/(const Vector4 &vec) const { return Vector4(x / vec.x, y/ vec.y, z/ vec.z, w/ vec.w); }
		
		inline Vector4 operator+(const Vector4 &vec) const{ return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w); }
		inline friend Vector4 operator+(float num, const Vector4 &vec) { return Vector4(num+vec.x, num+vec.y, num+vec.z, num+vec.w); }
		inline Vector4 operator+(float num) const { return Vector4(x + num, y+ num, z+ num, w+ num); }
		
		inline Vector4 operator-(const Vector4 &vec) const{ return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w); }
		inline friend Vector4 operator-(float num, const Vector4 &vec) { return Vector4(num-vec.x, num-vec.y, num-vec.z, num-vec.w); }
		inline friend Vector4 operator-(const Vector4 &vec) { return Vector4(-vec.x, -vec.y, -vec.z, -vec.w); };
		inline Vector4 operator-(float num) const { return Vector4(x - num, y - num, z - num, w - num); }


		inline bool operator==(const Vector4 &vec) const{ return cmp(vec); }
		inline bool operator!=(const Vector4 &vec) const{ return !cmp(vec); }

		inline friend std::ostream& operator<<(std::ostream& os, const Vector4 &vec) { 
			os << '{' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "}\n";
			return os;
		}

		inline friend std::istream& operator>>(std::istream& is, Vector4 &vec) {
			while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
    		is >> vec.x;
    		while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
    		is >> vec.y;
    		while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
    		is >> vec.z;
    		while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
    		is >> vec.w;
    		while (is.peek() != '\n') { is.get();}
			is.get();
			return is;
		}

		float dot(const Vector4 &vec);
		Vector4 normalize();
		float magnitude() const;
		void clean();

};
#endif