#ifndef MATRIX2_H
#define MATRIX2_H
#include <vector>
#include <ostream>
#include <iostream>
#include "vector2.h"
#include "Constants.h"

class Matrix2 {
    private:
        static const int width = 2;
        static const int height = 2;
        static const int size = width*height;
        int getIndex(int i,int j) const {return (i + j * width);}
        inline bool cmpf(float A, float B, float epsilon = 0.005f) const{ return (fabs(A - B) < epsilon); }

    public:
        float data[size];

        Matrix2();
        Matrix2(float a,float b,float c,float d);
        Matrix2(const Matrix2 &m);
        Matrix2(float v[4]);
        Matrix2(std::vector<float> v);
        ~Matrix2(void);

        float get(int i, int j) const;
        void set(int i, int j, float v);

        inline Matrix2 operator=(const Matrix2 &m) { 
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    set(i,j, m.get(i,j));
            return *this; 
        }
        
        // MULTIPLICATION OPERATORS
        inline friend Matrix2 operator*(const Matrix2 &m, float k) {
            Matrix2 n = Matrix2(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                        n.set(i,j, n.get(i,j)*k);
            return n;
        }

        inline friend Matrix2 operator*(float k, const Matrix2 &m) {
            return m*k;
        }

        inline Matrix2 operator*(const Matrix2 &m) { 
            float row_sum;
            Matrix2 n = Matrix2();
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

        inline friend Vector2 operator*(const Matrix2 &m, const Vector2 &v) {
            float x = m.get(0,0) * v.x + m.get(0,1) * v.y;
            float y = m.get(1,0) * v.x + m.get(1,1) * v.y;
            return Vector2(x,y);
        }

        inline friend Vector2 operator*(const Vector2 &v, const Matrix2 &m) {
            float x = m.get(0,0) * v.x + m.get(1,0) * v.y;
            float y = m.get(0,1) * v.x + m.get(1,1) * v.y;
            return Vector2(x,y);
        }

        // DIVISION OPERATORS
        inline friend Matrix2 operator/(const Matrix2 &m, float k) {
            Matrix2 n = Matrix2(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                        n.set(i,j, n.get(i,j)/k);
            return n;
        }

        // SUM OPERATORS
        inline friend Matrix2 operator+(const Matrix2 &m, float k) {
            Matrix2 n = Matrix2(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                        n.set(i,j, n.get(i,j)+k);
            return n;
        }

        inline Matrix2 operator+(const Matrix2 &m) { 
            Matrix2 n = Matrix2();
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    n.set(i, j, get(i,j) + m.get(i,j));
                }
            }       
            return n; 
        }

        // SUB OPERATORS
        inline friend Matrix2 operator-(const Matrix2 &m, float k) {
            Matrix2 n = Matrix2(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                        n.set(i,j, n.get(i,j)-k);
            return n;
        }

        inline Matrix2 operator-(const Matrix2 &m) { 
            Matrix2 n = Matrix2();
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    n.set(i, j, get(i,j) - m.get(i,j));
                }
            }       
            return n; 
        }

        inline bool operator==(const Matrix2 &m) const { 
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    if (!cmpf(get(i,j), m.get(i,j)))
                        return false;       
            return true;
        }

        inline bool operator!=(const Matrix2 &m) const { 
            return !(*this == m);
        }

        inline friend std::ostream& operator<<(std::ostream& os, const Matrix2 &m) {
            os << '|' << m.get(0,0) << " " << m.get(0,1) << "|\n" << '|' << m.get(1,0) << " " << m.get(1,1) << "|\n";
            return os;
        }

        inline friend std::istream& operator>>(std::istream& is, Matrix2 &m) {
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[0];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[2];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[1];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[3];
            while (is.peek() != '\n') { is.get();}
            is.get();
            return is;
        }
        
        float determinant();

        Matrix2 transpose();
        Matrix2 cofactors();
        Matrix2 adjugate();
        Matrix2 inverse();
        Matrix2 convert_opengl();
        void clean();

        
};
#endif