#include "matrix2.h"


Matrix2::Matrix2() {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, 0);
}

Matrix2::Matrix2(float a,float b,float c,float d) {
    set(0,0,a);
    set(0,1,b);
    set(1,0,c);
    set(1,1,d);
}

Matrix2::Matrix2(const Matrix2& m) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(i,j, m.get(i,j));
}

Matrix2::Matrix2(float v[4]) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, v[getIndex(i,j)]);
}

Matrix2::Matrix2(std::vector<float> v) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, v[getIndex(i,j)]);
}

Matrix2::~Matrix2() {}

float Matrix2::get(int i, int j) const {
    return data[getIndex(i,j)];
}

void Matrix2::set(int i, int j, float v) {
    data[getIndex(i,j)] = v;
}

float Matrix2::determinant() {
    float a = get(0,0);
    float b = get(0,1);
    float c = get(1,0);
    float d = get(1,1);
    return a*d-c*b;
}

Matrix2 Matrix2::transpose() {
    Matrix2 m = Matrix2();
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            m.set(j,i, get(i,j));
    return m;
}


Matrix2 Matrix2::cofactors() {
    return Matrix2(get(1,1), -get(1,0), -get(0,1), get(0,0));
}

Matrix2 Matrix2::adjugate() {
    return Matrix2(get(1,1),-get(0,1),-get(1,0),get(0,0));
}

Matrix2 Matrix2::inverse() {
    float det = determinant();
    return adjugate()/det;
}

Matrix2 Matrix2::convert_opengl() {
    return transpose();
}

void Matrix2::clean() {
    float eps = 1.0e-6f;
    int index;
    float diff;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            index = getIndex(i,j);
            diff = data[index];
            if(diff < eps && -diff < eps)
                data[index] = 0.0f;
        }
    }
}
