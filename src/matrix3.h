#ifndef MATRIX3_H
#define MATRIX3_H
#include <vector>
#include <ostream>
#include <iostream>
#include "vector3.h"
#include "matrix2.h"
#include "Constants.h"

class Matrix3 {
    private:
        static const int width = 3;
        static const int height = 3;
        static const int size = width*height;
        int getIndex(int i,int j) const {return (i + j * width);}
        inline bool cmpf(float A, float B, float epsilon = 0.005f) const{ return (fabs(A - B) < epsilon); }

    public:
        float data[size];

        Matrix3();
        Matrix3(float a,float b,float c,float d,float e,float f,float g, float h, float i);
        Matrix3(const Matrix3& m);
        Matrix3(float v[9]);
        Matrix3(std::vector<float> v);
        ~Matrix3(void);

        float get(int i, int j) const;
        void set(int i, int j, float v);

        inline Matrix3 operator=(const Matrix3 &m) { 
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    set(i,j, m.get(i,j));
            return *this;
        }
        
        // MULTIPLICATION OPERATORS
        inline friend Matrix3 operator*(const Matrix3 &m, float k) {
            Matrix3 n = Matrix3(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                        n.set(i,j, n.get(i,j)*k);
            return n;
        }

        inline friend Matrix3 operator*(float k, const Matrix3 &m) {
            return m*k;
        }

        inline Matrix3 operator*(const Matrix3 &m) { 
            float row_sum;
            Matrix3 n = Matrix3();

            for (int k = 0; k < width; ++k) {
                for (int i = 0; i < height; ++i) {
                    row_sum = 0;
                    for (int j = 0; j < height; ++j) {
                        row_sum += get(k,j) * m.get(j,i);
                    }
                    n.set(k, i, row_sum);
                }
            }
            return n; 
        }



        inline friend Vector3 operator*(const Matrix3 &m, const Vector3 &v) {
            float x = m.get(0,0) * v.x + m.get(0,1) * v.y + m.get(0,2) * v.z;
            float y = m.get(1,0) * v.x + m.get(1,1) * v.y + m.get(1,2) * v.z;
            float z = m.get(2,0) * v.x + m.get(2,1) * v.y + m.get(2,2) * v.z;
            return Vector3(x,y,z);
        }


        inline friend Vector3 operator*(const Vector3 &v, const Matrix3 &m) {
            float x = m.get(0,0) * v.x + m.get(1,0) * v.y + m.get(2,0) * v.z;
            float y = m.get(0,1) * v.x + m.get(1,1) * v.y + m.get(2,1) * v.z;
            float z = m.get(0,2) * v.x + m.get(1,2) * v.y + m.get(2,2) * v.z;
            return Vector3(x,y,z);    
        }

        // DIVISION OPERATORS
        inline friend Matrix3 operator/(const Matrix3 &m, float k) {
            Matrix3 n = Matrix3(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                        n.set(i,j, n.get(i,j)/k);
            return n;
        }

        // SUM OPERATORS
        inline friend Matrix3 operator+(const Matrix3 &m, float k) {
            Matrix3 n = Matrix3(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                    n.set(i,j, n.get(i,j)+k);
            return n;
        }

        inline Matrix3 operator+(const Matrix3 &m) { 
            Matrix3 n = Matrix3();
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    n.set(i, j, get(i,j) + m.get(i,j));
                }
            }       
            return n; 
        }

        // SUB OPERATORS
        inline friend Matrix3 operator-(const Matrix3 &m, float k) {
            Matrix3 n = Matrix3(m);
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                    n.set(i,j, n.get(i,j)-k);
            return n;
        }

        inline Matrix3 operator-(const Matrix3 &m) { 
            Matrix3 n = Matrix3();
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    n.set(i, j, get(i,j) - m.get(i,j));       
            return n;
        }

        inline bool operator==(const Matrix3 &m) const { 
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    if (!cmpf(get(i,j), m.get(i,j)))
                        return false;
            return true;
        }

        inline bool operator!=(const Matrix3 &m) const { 
            return !(*this == m);
        }

        inline friend std::ostream& operator<<(std::ostream& os, const Matrix3 &m) {
            os << '|' << m.get(0,0) << " " << m.get(0,1) << " " <<  m.get(0,2) << "|\n" << 
            '|' << m.get(1,0) << " " << m.get(1,1) << " " << m.get(1,2) << "|\n" << 
            '|' << m.get(2,0) << " " << m.get(2,1) << " " << m.get(2,2) << "|\n";
            return os;
        }

        inline friend std::istream& operator>>(std::istream& is, Matrix3 &m) {
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[0];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[3];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[6];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[1];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[4];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[7];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[2];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[5];
            while (is.peek() < 0x30 || is.peek() > 0x39) { is.get();}
            is >> m.data[8];
            while (is.peek() != '\n') { is.get();}
            is.get();
            return is;
        }

        float determinant();
        Matrix3 transpose();
        Matrix3 cofactors();
        Matrix3 adjugate();
        Matrix3 inverse();
        Matrix3 convert_opengl();
        void clean();
};
#endif