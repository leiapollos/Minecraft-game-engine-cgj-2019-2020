#ifndef ISPHERICALCAMERA_H
#define ISPHERICALCAMERA_H
#include "ICamera.h"
#include "MatrixFactory.h"
#include "Quaternion.h"

class SphericalCamera : public ICamera {
	Matrix4 translationMatrix;
    Matrix4 rotationMatrix;
    Matrix4 mRotX;
    Matrix4 mRotY;

    Quaternion rotationQ;

    float lastX = 0.0f;
    float lastY = 0.0f;
    float zoom = 5.0f;
    float mouseSensitivity = 1.00f;

	public:
		SphericalCamera(GLuint _UBO_BP);
		virtual ~SphericalCamera();
		virtual Matrix4& getViewMatrix();

		virtual void rotation(float rotX, float rotY);
		virtual void updateView();

		virtual void setViewMatrix(const Matrix4& viewMatrix);
		virtual void setProjectionMatrix(const Matrix4& projectionMatrix);
		virtual void setGimbleLock(bool _gimbleLock);
		virtual bool getGimbleLock();
		virtual void setMousePosition(const Vector2& mousePosition);
		void update();
		Matrix4& lookAt(Vector3 eye, Vector3 center, Vector3 up);
		virtual void computeMouseMovement(GLfloat xoffset, GLfloat yoffset);
        virtual void computeMouseScroll(GLfloat yoffset);
        virtual void computeKeyboardInputs(Movement direction, GLfloat deltaTime);
};
#endif