#include "MatrixFactory.h"

namespace MatrixFactory {
    Matrix2 Create2DIdentity(){
        Matrix2 identity = Matrix2(1.0f,0.0f,
                                   0.0f,1.0f);
        return identity;
    }

    Matrix3 Create3DIdentity(){
        Matrix3 identity = Matrix3(1.0f,0.0f,0.0f,
                                   0.0f,1.0f,0.0f,
                                   0.0f,0.0f,1.0f);
        return identity;
    }

    Matrix4 Create4DIdentity(){
        Matrix4 identity = Matrix4(1.0f,0.0f,0.0f,0.0f,
                                   0.0f,1.0f,0.0f,0.0f,
                                   0.0f,0.0f,1.0f,0.0f,
                                   0.0f,0.0f,0.0f,1.0f);
        return identity;
    }

    Matrix2 Create2DRotation(float angle){
        float radToDegree = ((float)M_PI * angle) / 180.0f;
        float sin0 = sinf(radToDegree);
        float cos0 = cosf(radToDegree);
        Matrix2 rot = Matrix2(cos0,-sin0, 
                              sin0, cos0);
        return rot;
    }

    Matrix3 Create3DZRotation(float angle){
        float radToDegree = ((float)M_PI * angle) / 180.0f;
        float sin0 = sinf(radToDegree);
        float cos0 = cosf(radToDegree);
        Matrix3 rot = Matrix3(cos0,-sin0,0.0f,
                              sin0,cos0,0.0f,
                              0.0f,0.0f,1.0f);
        return rot;
    }

    Matrix3 Create3DYRotation(float angle){
        float radToDegree = ((float)M_PI * angle) / 180.0f;
        float sin0 = sinf(radToDegree);
        float cos0 = cosf(radToDegree);
        Matrix3 rot = Matrix3(cos0,0.0f,sin0,
                              0.0f,1.0f,0.0f,
                              sin0 * -1,0.0f,cos0);
        return rot;
    }

    Matrix3 Create3DXRotation(float angle){
        float radToDegree = ((float)M_PI * angle) / 180.0f;
        float sin0 = sinf(radToDegree);
        float cos0 = cosf(radToDegree);
        Matrix3 rot = Matrix3(1.0f,0.0f,0.0f,
                              0.0f,cos0,-sin0,
                              0.0f,sin0,cos0);
        return rot;
    }

    /*
    Matrix2 Create2DXShearing(float k){
        Matrix2 shear = Matrix2(1, k, 
                                0, 0);
        return shear;
    }

    Matrix2 Create2DYShearing(float k){
        Matrix2 shear = Matrix2(1, 0, 
                                k, 0);
        return shear;
    }

    Matrix3 Create3DShearing(Vector2 v){
        Matrix3 shear = Matrix3(1,   0,   0, 
                                0,   1,   0,
                                v.x, v.y, 1);
        return shear;
    }*/



    Matrix3 Create3DTranslation(float XTranslation, float YTranslation){
        Matrix3 trans = Matrix3(1.0f,0.0f,XTranslation,
                                0.0f,1.0f,YTranslation,
                                0.0f,0.0f,1.0f);
        return trans;
    }

    Matrix4 Create4DTranslation(float XTranslation, float YTranslation, float ZTranslation){
        Matrix4 trans = Matrix4(1.0f,0.0f,0.0f,XTranslation,
                                0.0f,1.0f,0.0f,YTranslation,
                                0.0f,0.0f,1.0f,ZTranslation,
                                0.0f,0.0f,0.0f,1.0f);
        return trans;
    }

    Matrix2 Create2DScalingMatrix(float XFactor, float YFactor){
        Matrix2 scale = Matrix2(XFactor,0.0f,
                                0.0f,YFactor);
        return scale;
    }

    Matrix3 Create3DScalingMatrix(float XFactor, float YFactor, float ZFactor){
        Matrix3 scale = Matrix3(XFactor,0.0f,0.0f,
                                0.0f,YFactor,0.0f,
                                0.0f,0.0f,ZFactor);
        return scale;
    }

    Matrix3 CONVERT_2D_TO_3D_MATRIX(Matrix2 m){
        int i,j;
        int height = 2;
        int width  = 2;
        Matrix3 converted = Matrix3();
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                converted.set(i,j,m.get(i,j));
            }
        }
        converted.set(2,2,1.0f);
        return converted;
    }

    Matrix4 CONVERT_3D_TO_4D_MATRIX(Matrix3 m){
        int i,j;
        int height = 3;
        int width  = 3;
        Matrix4 converted = Matrix4();
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                converted.set(i,j,m.get(i,j));
            }
        }
        converted.set(3,3,1.0f);
        return converted;
    }

    Matrix3 Create3DDualMatrix(Vector3 a){
        Matrix3 dual = Matrix3(0.0f,-a.z,a.y,
                               a.z,0.0f,-a.x,
                               -a.y,a.x,0.0f);
        return dual;
    }

    Matrix3 CreateAxisRotation(float angle,Vector3 axis){
        float degAngle = (angle * (float)M_PI) / 180.0f;
        float sin0 = sinf(degAngle);
        float cos0 = cosf(degAngle);
        Matrix3 Id = Create3DIdentity();
        Matrix3 dualv0 = Create3DDualMatrix(axis.normalize());
        Matrix3 Rv0 = Id + (sin0 * dualv0) + ((1 - cos0) * dualv0 * dualv0);
        return Rv0;
    }

    /*Matrix4 CreateTransformMatrix(float xTranslation,float yTranslation,float zTranslation,float angle, float scalingFactor) {
        Matrix4 translation = Create4DTranslation(xTranslation,yTranslation,zTranslation);
        Matrix3 _rotation = Create3DZRotation(angle);
        Matrix4 rotation = CONVERT_3D_TO_4D_MATRIX(_rotation);
        Matrix3 _scaling = Create3DScalingMatrix(scalingFactor,scalingFactor,scalingFactor);
        Matrix4 scaling = CONVERT_3D_TO_4D_MATRIX(_scaling);
        Matrix4 transform = translation * rotation * scaling;
        //Matrix4 transform = translation;
        return transform;
    }*/

    Matrix4 CreateTransformMatrix(float xTranslation,float yTranslation,float zTranslation,float angle, float scalingFactor, Vector3 axis) {
        Matrix4 translation = Create4DTranslation(xTranslation,yTranslation,zTranslation);
        Matrix4 rotation = rotate(angle, axis);
        //Matrix4 rotation = CONVERT_3D_TO_4D_MATRIX(_rotation);
        Matrix3 _scaling = Create3DScalingMatrix(scalingFactor,scalingFactor,scalingFactor);
        Matrix4 scaling = CONVERT_3D_TO_4D_MATRIX(_scaling);
        Matrix4 transform = translation * rotation * scaling;
        //Matrix4 transform = translation;
        return transform;
    }

    Matrix4 Perspective(float fovy, float aspect, float zNear, float zFar) {
        const float rad = fovy;
        const float tanHalfFovy = tanf(rad / 2.0f);

        Matrix4 m;
        m.set(0,0, 1.0f / (aspect * tanHalfFovy));
        m.set(1,1, 1.0f / (tanHalfFovy));
        m.set(2,2,- (zFar + zNear) / (zFar - zNear));
        m.set(3,2,- 1.0f);
        m.set(2,3,- (2.0f * zFar * zNear) / (zFar - zNear));
        return m;
    }

    Matrix4 Ortho(float left, float right, float bottom, float top, float near, float far) {
        Matrix4 m = Matrix4(2.0f / (right - left),        0             ,         0          , (left + right) / (left - right),
                                0           , 2.0f / (top - bottom),         0          , (bottom + top) / (bottom - top),
                                0           ,        0             , -2.0f / (far - near),   (near + far) / (near - far)  ,
                                0           ,        0             ,         0          ,                1               );
        return m;
    }

	Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up)
	{
			Vector3 view = center - eye;
			Vector3 v = view.normalize();
			Vector3 side = v.cross(up);
			Vector3 s = side.normalize();
			Vector3 u = s.cross(v);

			Matrix4 vMatrix = Matrix4(s.x, s.y, s.z, -s.dot(eye),
				u.x, u.y, u.z, -u.dot(eye),
				-v.x, -v.y, -v.z, v.dot(eye),
				0, 0, 0, 1);
			return vMatrix;//MatrixFactory::;//vMatrix;
	}

    Matrix4 translate(Vector3 v) {
        Matrix4 translationMatrix = Create4DTranslation(v.x,v.y,v.z);
        return translationMatrix;
    }

    Matrix3 translate(Vector2 v) {
        Matrix3 translationMatrix = Create3DTranslation(v.x,v.y);
        return translationMatrix;
    }

    Matrix4 rotate(float angle, Vector3 axis) {
        Matrix4 rotationMatrix = CONVERT_3D_TO_4D_MATRIX(CreateAxisRotation(angle,axis));
        return rotationMatrix;
    }

    Matrix3 rotate(float angle) {
        Matrix3 translationMatrix = CONVERT_2D_TO_3D_MATRIX(Create2DRotation(angle));
        return translationMatrix;
    }

    Matrix4 scale(Vector3 v) {
        Matrix4 scaleMatrix = CONVERT_3D_TO_4D_MATRIX(Create3DScalingMatrix(v.x,v.y,v.z));
        return scaleMatrix;
    }

    Matrix3 scale(Vector2 v) {
        Matrix3 scaleMatrix = CONVERT_2D_TO_3D_MATRIX(Create2DScalingMatrix(v.x,v.y));
        return scaleMatrix;
    }
}