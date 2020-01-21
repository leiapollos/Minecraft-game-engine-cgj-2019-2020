#ifndef MATHF_H
#define MATHF_H

#include <cmath>

#include "vector3.h"

namespace math {
    #define MAX(x,y) (x > y ? x : y)

    #define MIN(x,y) (x < y ? x : y)

    

    inline float toRadians(float degrees){
        return (degrees * (float)M_PI) / 180.0f;
    }

    inline float toDegrees(float radians){
        return (radians * 180.0f) / (float)M_PI;
    }

    inline float cotangent(float value){
        float angle = toRadians(value);
        return (1.0f / ((float)tan(angle)));
    }

    inline float compareEqual(float x, float y) {
        float floatThreshold = 1.0e-6f;
        float difference = x - y;
        return difference < floatThreshold && -difference < floatThreshold;
    }

    inline float clamp(float n, float minn, float maxn) {
        return MIN(MAX(n, minn), maxn);
    }

    inline void clampVector(Vector3 v, float minn, float maxn) {
        v.x = clamp(v.x, minn, maxn);
        v.y = clamp(v.y, minn, maxn);
        v.z = clamp(v.z, minn, maxn);
    }

    inline float inverseLerp(float a, float b, float x) {
        if(a != b)
            return clamp((x-a)/(b-a),0,1);
        else
            return 0.0f;
        //return (x - a) / (b - a);
    }

    inline float lerp2(float a, float b, float x) {
        float mu2 = (1 - cosf(x * 3.14f)) / 2;
        return (a * (1 - mu2) + b * mu2);
    }
    inline float lerp(float a, float b, float x) {
        return a + (b - a) * clamp(x,0,1);
    }

};

#endif