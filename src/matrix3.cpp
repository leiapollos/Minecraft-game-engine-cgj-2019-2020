#include "matrix3.h"
#include "matrix2.h"

Matrix3::Matrix3() {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, 0);
}

Matrix3::Matrix3(float a,float b,float c,float d,float e,float f,float g, float h, float i) {
    set(0,0,a);
    set(0,1,b);
    set(0,2,c);
    
    set(1,0,d);
    set(1,1,e);
    set(1,2,f);

    set(2,0,g);
    set(2,1,h);
    set(2,2,i);
}

Matrix3::Matrix3(const Matrix3& m) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(i,j, m.get(i,j));
}

/*Matrix3::Matrix3(const Matrix2& m) {
    //int i,j;
    //int height = 2;
    //int width  = 2;
    //Matrix3 converted = Matrix3();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << m.get(i,j) << "\n";
            set(i,j,m.get(i,j));
        }
    }
    set(2,2,1.0f);
}*/

Matrix3::Matrix3(float v[9]) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, v[getIndex(i,j)]);
}

Matrix3::Matrix3(std::vector<float> v) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, v[getIndex(i,j)]);
}

Matrix3::~Matrix3() {}

float Matrix3::get(int i, int j) const {
    return data[getIndex(i,j)];
}

void Matrix3::set(int i, int j, float v) {
    data[getIndex(i,j)] = v;
}

float Matrix3::determinant() {
    return get(0, 0) * (get(1, 1) * get(2, 2) - get(2, 1) * get(1, 2)) -
    get(0, 1) * (get(1, 0) * get(2, 2) - get(1, 2) * get(2, 0)) +
    get(0, 2) * (get(1, 0) * get(2, 1) - get(1, 1) * get(2, 0));
}

Matrix3 Matrix3::transpose() {
    Matrix3 m = Matrix3();
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            m.set(j,i, get(i,j));
    return m;
}


Matrix3 Matrix3::cofactors() {
    float a = get(0,0);
    float b = get(0,1);
    float c = get(0,2);
    float d = get(1,0);
    float e = get(1,1);
    float f = get(1,2);
    float g = get(2,0);
    float h = get(2,1);
    float i = get(2,2);
    Matrix2 m0 = Matrix2(e,f,h,i);
    Matrix2 m1 = Matrix2(d,f,g,i);
    Matrix2 m2 = Matrix2(d,e,g,h);
    Matrix2 m3 = Matrix2(b,c,h,i);
    Matrix2 m4 = Matrix2(a,c,g,i);
    Matrix2 m5 = Matrix2(a,b,g,h);
    Matrix2 m6 = Matrix2(b,c,e,f);
    Matrix2 m7 = Matrix2(a,c,d,f);
    Matrix2 m8 = Matrix2(a,b,d,e);
    
    return Matrix3(+m0.determinant(),-m1.determinant(),+m2.determinant(),
                   -m3.determinant(),+m4.determinant(),-m5.determinant(),
                   +m6.determinant(),-m7.determinant(),+m8.determinant());
}

Matrix3 Matrix3::adjugate() {
    float a = get(0,0);
    float b = get(0,1);
    float c = get(0,2);
    float d = get(1,0);
    float e = get(1,1);
    float f = get(1,2);
    float g = get(2,0);
    float h = get(2,1);
    float i = get(2,2);
    Matrix2 m0 = Matrix2(e,f,h,i);
    Matrix2 m1 = Matrix2(b,c,h,i);
    Matrix2 m2 = Matrix2(b,c,e,f);
    Matrix2 m3 = Matrix2(d,f,g,i);
    Matrix2 m4 = Matrix2(a,c,g,i);
    Matrix2 m5 = Matrix2(a,c,d,f);
    Matrix2 m6 = Matrix2(d,e,g,h);
    Matrix2 m7 = Matrix2(a,b,g,h);
    Matrix2 m8 = Matrix2(a,b,d,e);
    
    return Matrix3(+m0.determinant(),-m1.determinant(),+m2.determinant(),
                   -m3.determinant(),+m4.determinant(),-m5.determinant(),
                   +m6.determinant(),-m7.determinant(),+m8.determinant());
}

Matrix3 Matrix3::inverse() {
    float det = determinant();
    return adjugate()/det;
}

Matrix3 Matrix3::convert_opengl() {
    return transpose();
}

void Matrix3::clean() {
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