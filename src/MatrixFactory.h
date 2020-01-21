#ifndef MATRIXFACTORY_H
#define MATRIXFACTORY_H
#include "matrix4.h"
#include "matrix3.h"
#include "matrix2.h"
#include "mathf.h"
#include "Constants.h"

namespace MatrixFactory {
    const Vector3 x_axis = Vector3(1.0f,0.0f,0.0f);
    const Vector3 y_axis = Vector3(0.0f,1.0f,0.0f);
    const Vector3 z_axis = Vector3(0.0f,0.0f,1.0f);

    Matrix2 Create2DIdentity();
    Matrix3 Create3DIdentity();
    Matrix4 Create4DIdentity();

    Matrix2 Create2DRotation(float angle);
    Matrix3 Create3DZRotation(float angle);
    Matrix3 Create3DYRotation(float angle);
    Matrix3 Create3DXRotation(float angle);

    Matrix3 Create3DTranslation(float XTranslation, float YTranslation);
    Matrix4 Create4DTranslation(float XTranslation, float YTranslation, float ZTranslation);

    Matrix2 Create2DScalingMatrix(float XFactor, float YFactor);
    Matrix3 Create3DScalingMatrix(float XFactor, float YFactor, float ZFactor);

    Matrix3 CONVERT_2D_TO_3D_MATRIX(Matrix2 m);
    Matrix4 CONVERT_3D_TO_4D_MATRIX(Matrix3 m);

    Matrix3 Create3DDualMatrix(Vector3 a);
    Matrix3 CreateAxisRotation(float angle,Vector3 axis);
    //Matrix4 CreateTransformMatrix(float xTranslation,float yTranslation,float zTranslation,float angle, float scalingFactor);
    Matrix4 CreateTransformMatrix(float xTranslation,float yTranslation,float zTranslation,float angle, float scalingFactor, Vector3 axis = Vector3(0,0,1));
    Matrix4 Perspective(float fovy, float aspect, float zNear, float zFar);
    Matrix4 Ortho(float left, float right, float bottom, float top, float near, float far);
    Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up);

    Matrix4 translate(Vector3 v);
    Matrix3 translate(Vector2 v);

    Matrix4 rotate(float angle, Vector3 axis);
    Matrix3 rotate(float angle);

    Matrix4 scale(Vector3 v);
    Matrix3 scale(Vector2 v);
};


#endif