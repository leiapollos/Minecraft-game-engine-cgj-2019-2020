#include "matrix4.h"

Matrix4::Matrix4() {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, 0);
}

Matrix4::Matrix4(float a,float b,float c,float d, 
				float e,float f,float g, float h,  
				float i, float j, float k, float l,
				float m, float n, float o, float p) {
    set(0,0,a);
    set(0,1,b);
    set(0,2,c);
    set(0,3,d);
    
    set(1,0,e);
    set(1,1,f);
    set(1,2,g);
    set(1,3,h);

    set(2,0,i);
    set(2,1,j);
    set(2,2,k);
    set(2,3,l);

    set(3,0,m);
    set(3,1,n);
    set(3,2,o);
    set(3,3,p);
}

Matrix4::Matrix4(const Matrix4& m) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(i,j, m.get(i,j));
}

/*Matrix4::Matrix4(const Matrix3& m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            set(i,j,m.get(i,j));
        }
    }
    set(3,3,1.0f);
}*/

Matrix4::Matrix4(float v[9]) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, v[getIndex(i,j)]);
}

Matrix4::Matrix4(std::vector<float> v) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            set(j,i, v[getIndex(i,j)]);
}

Matrix4::~Matrix4() {}

float Matrix4::get(int i, int j) const {
    return data[getIndex(i,j)];
}

void Matrix4::set(int i, int j, float v) {
    data[getIndex(i,j)] = v;
}

Matrix4 Matrix4::transpose() {
    Matrix4 m = Matrix4();
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            m.set(j,i, get(i,j));
    return m;
}

Matrix4 Matrix4::convert_opengl() {
    return transpose();
}

void Matrix4::clean() {
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
