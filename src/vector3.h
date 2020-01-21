#ifndef VECTOR3_H
#define VECTOR3_H
#include <cmath>
#include "vector2.h"
#include <array>
#include "Constants.h"

class Vector3 {
    private:
        inline bool cmpf(float A, float B, float epsilon = 0.005f) const{ return (fabs(A - B) < epsilon); }
        inline bool cmp(const Vector3 &vec) const{ return cmpf(x, vec.x) && cmpf(y, vec.y) && cmpf(z, vec.z); }
    public:
        union {
            struct{
                float x, y, z;
            };
            std::array<float,3> data;
        };

        
        Vector3(float x, float y, float z);
        Vector3(const Vector2 &vec);
        Vector3();
        ~Vector3(void);
        
        inline void set(float x, float y, float z);


        inline Vector3 operator=(const Vector3 &vec) { 
            x = vec.x;
            y = vec.y;
            z = vec.z;
            return *this; 
        }

        



        inline Vector3 operator*(float num) const { return Vector3(x * num, y* num, z* num); }
        inline friend Vector3 operator*(float num, const Vector3 &vec) { return Vector3(vec.x * num, vec.y* num, vec.z* num); }
        inline Vector3 operator*(const Vector3 &vec) const { return Vector3(x * vec.x, y* vec.y, z* vec.z); }

        inline Vector3 operator/(float num) const { return Vector3(x / num, y/ num, z/ num); }
        inline friend Vector3 operator/(float num, const Vector3 &vec) { return Vector3(num/vec.x, num/vec.y, num/vec.z); }
        inline Vector3 operator/(const Vector3 &vec) const { return Vector3(x / vec.x, y/ vec.y, z/ vec.z); }
        
        inline Vector3 operator+(const Vector3 &vec) const{ return Vector3(x + vec.x, y + vec.y, z + vec.z); }
        inline friend Vector3 operator+(float num, const Vector3 &vec) { return Vector3(vec.x + num, vec.y+ num, vec.z+ num); }
        inline Vector3 operator+(float num) const { return Vector3(x + num, y+ num, z+ num); }
        
        inline Vector3 operator-(const Vector3 &vec) const{ return Vector3(x - vec.x, y - vec.y, z - vec.z); }
        inline friend Vector3 operator-(float num, const Vector3 &vec) { return Vector3(num -vec.x, num -vec.y, num-vec.z); }
        inline friend Vector3 operator-(const Vector3 &vec) { return Vector3(-vec.x, -vec.y, -vec.z);}
        inline Vector3 operator-(float num) const { return Vector3(x - num, y - num, z - num); }

        inline bool operator==(const Vector3 &vec) const{ return cmp(vec); }
        inline bool operator!=(const Vector3 &vec) const{ return !cmp(vec); }

        inline void operator += (Vector3 v){
            x += v.x;
            y += v.y;
            z += v.z;
        }

        inline void operator -= (Vector3 v){
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        inline void operator += (float k){
            x += k;
            y += k;
            z += k;
        }

        inline void operator -= (float k){
            x -= k;
            y -= k;
            z -= k;
        }

        inline void operator *= (float k){
            x *= k;
            y *= k;
            z *= k;
        }

        inline void operator /= (float k){
            x /= k;
            y /= k;
            z /= k;
        }

		inline bool operator() (const Vector3& lhs, const Vector3& rhs) const
		{
            return lhs.magnitude() < rhs.magnitude();
		}

        inline friend std::ostream& operator<<(std::ostream& os, const Vector3 &vec) {
            os << '{' << vec.x << ", " << vec.y << ", " << vec.z << "}\n";
            return os;
        }

        inline friend std::istream& operator>>(std::istream& is, Vector3 &vec) {
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> vec.x;
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> vec.y;
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> vec.z;
            while (is.peek() != '\n') { is.get();}
            is.get();
            return is;
        }
        friend Vector3 lerp(const Vector3& a,const Vector3& b, float n);
        friend float distance(const Vector3& a, const Vector3& b);
        float dot(const Vector3 &vec) const;
        Vector3 cross(const Vector3 &vec) const;
        float magnitude() const;
        float angle(const Vector3 &vec) const;
        Vector3 normalize() const;
        Vector3 rotate(float theta, const Vector3 &axis) const;
        void clean();

        
};

namespace std
{
    template<>
    struct hash<Vector3>
    {
        size_t operator()(const Vector3 vect) const
        {
            std::hash<decltype((size_t)vect.x)> hasher;

            auto hash1 = hasher((long)vect.x);
            auto hash2 = hasher((long)vect.y);
            auto hash3 = hasher((long)vect.z);

            return std::hash<decltype((size_t)vect.x)>{}((hash1 ^ (hash2 << hash3) ^ hash3));
        }
    };
}
#endif