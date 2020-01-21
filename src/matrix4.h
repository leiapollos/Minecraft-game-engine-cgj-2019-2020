#ifndef MATRIX4_H
#define MATRIX4_H
#include <vector>
#include <ostream>
#include <iostream>
#include "vector4.h"
#include "matrix3.h"
#include "Constants.h"

class Matrix4 {
    private:
        static const int width = 4;
        static const int height = 4;
        static const int size = width*height;
        int getIndex(int i,int j) const {return (i + j * width);}
        inline bool cmpf(float A, float B, float epsilon = 0.005f) const{ return (fabs(A - B) < epsilon); }

    public:
        float data[size];

        Matrix4();
        Matrix4(float a,float b,float c,float d, 
                float e,float f,float g, float h,  
                float i, float j, float k, float l,
                float m, float n, float o, float p);
        Matrix4(const Matrix4 &m);
        //Matrix4(const Matrix3 &m);
        Matrix4(float v[16]);
        Matrix4(std::vector<float> v);
        ~Matrix4(void);

        float get(int i, int j) const;
        void set(int i, int j, float v);

        inline Matrix4 operator=(const Matrix4 &m) { 
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j) {
                    set(i,j, m.get(i,j));
                }
            return *this;
         }
        
        // MULTIPLICATION OPERATORS
        inline friend Matrix4 operator*(const Matrix4 &m, float k) {
            Matrix4 n = Matrix4(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                        n.set(i,j, n.get(i,j)*k);
            return n;
        }

        inline friend Matrix4 operator*(float k, const Matrix4 &m) {
            return m*k;
        }

        inline Matrix4 operator*(const Matrix4 &m) { 
            float row_sum;
            Matrix4 n = Matrix4();
            for (int k = 0; k < height; ++k) {
                for (int i = 0; i < width; ++i) {
                    row_sum = 0;
                    for (int j = 0; j < height; ++j) {
                        row_sum +=get(k,j) * m.get(j,i);
                    }
                    n.set(k, i, row_sum);
                }
            }       
            return n; 
        }

        inline friend Vector4 operator*(const Matrix4 &m, const Vector4 &v) {
            float x = m.get(0,0) * v.x + m.get(0,1) * v.y + m.get(0,2) * v.z + m.get(0,3) * v.w;
            float y = m.get(1,0) * v.x + m.get(1,1) * v.y + m.get(1,2) * v.z + m.get(1,3) * v.w;
            float z = m.get(2,0) * v.x + m.get(2,1) * v.y + m.get(2,2) * v.z + m.get(2,3) * v.w;
            float w = m.get(3,0) * v.x + m.get(3,1) * v.y + m.get(3,2) * v.z + m.get(3,3) * v.w;
            
            return Vector4(x,y,z,w);
        }

        inline friend Vector4 operator*(const Vector4 &v, const Matrix4 &m){
            float x = m.get(0,0) * v.x + m.get(1,0) * v.y + m.get(2,0) * v.z + m.get(3,0) * v.w;
            float y = m.get(0,1) * v.x + m.get(1,1) * v.y + m.get(2,1) * v.z + m.get(3,1) * v.w;
            float z = m.get(0,2) * v.x + m.get(1,2) * v.y + m.get(2,2) * v.z + m.get(3,2) * v.w;
            float w = m.get(0,3) * v.x + m.get(1,3) * v.y + m.get(2,3) * v.z + m.get(3,3) * v.w;
            return Vector4(x,y,z,w);    
        }

        // DIVISION OPERATORS
        inline friend Matrix4 operator/(const Matrix4 &m, float k) {
            Matrix4 n = Matrix4(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                        n.set(i,j, n.get(i,j)/k);
            return n;
        }

        // SUM OPERATORS
        inline friend Matrix4 operator+(const Matrix4 &m, float k) {
            Matrix4 n = Matrix4(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                    n.set(i,j, n.get(i,j)+k);
            return n;
        }

        inline Matrix4 operator+(const Matrix4 &m) { 
            Matrix4 n = Matrix4();
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    n.set(i, j, get(i,j) + m.get(i,j));
                }
            }       
            return n; 
        }

        // SUB OPERATORS
        inline friend Matrix4 operator-(const Matrix4 &m, float k) {
            Matrix4 n = Matrix4(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                    n.set(i,j, n.get(i,j)-k);
            return n;
        }

        inline Matrix4 operator-(const Matrix4 &m) { 
            Matrix4 n = Matrix4();
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    n.set(i, j, get(i,j) - m.get(i,j));       
            return n;
        }

        inline bool operator==(const Matrix4 &m) const { 
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    if (!cmpf(get(i,j), m.get(i,j)))
                        return false;
            return true;
        }

        inline bool operator!=(const Matrix4 &m) const { 
            return !(*this == m);
        }

        inline friend std::ostream& operator<<(std::ostream& os, const Matrix4 &m) {
            os << '|' << m.get(0,0) << " " << m.get(0,1) << " " <<  m.get(0,2) << " " << m.get(0,3) << "|\n" << 
            '|' << m.get(1,0) << " " << m.get(1,1) << " " << m.get(1,2) << " " << m.get(1,3) << "|\n" << 
            '|' << m.get(2,0) << " " << m.get(2,1) << " " << m.get(2,2) << " " << m.get(2,3) << "|\n" <<
            '|' << m.get(3,0) << " " << m.get(3,1) << " " << m.get(3,2) << " " << m.get(3,3) << "|\n";
            return os;
        }

        inline friend std::istream& operator>>(std::istream& is, Matrix4 &m) {
            for (int i = 0; i < 16; i += 4) {
                while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
                is >> m.data[i];
            }

            for (int i = 0; i < 16; i += 4) {
                while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
                is >> m.data[1+i];
            }

            for (int i = 0; i < 16; i += 4) {
                while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
                is >> m.data[2+i];
            }

            for (int i = 0; i < 16; i += 4) {
                while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
                is >> m.data[3+i];
            }

            while (is.peek() != '\n') { is.get();}
            is.get();
            return is;
        }

        //float determinant();
        Matrix4 transpose();
        //Matrix4 cofactors();
        //Matrix4 adjugate();
        //Matrix4 inverse();
        Matrix4 convert_opengl();
        void clean();
};
#endif