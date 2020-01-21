#ifndef IFPSCAMERA_H
#define IFPSCAMERA_H
#include "vector3.h"
#include "matrix4.h"
#include "ICamera.h"
#include "mathf.h"
#include "MatrixFactory.h"


class FPSCamera : public  ICamera {
public:
	Vector3 position;
    Vector3 front;
    Vector3 up;
    Vector3 right;
    Vector3 worldUp;

    float yaw, roll, pitch;
    float zoom;

    float movementSpeed;
    float mouseSensitivity;
    private:
        void updateView();
    public:
        
        FPSCamera(GLuint _UBO_BP, 
                    Vector3 _position = Vector3(0.0f, 0.0f, 0.0f),
                    Vector3 _up = Vector3(0.0f,1.0f,0.0f), 
                    float _yaw = 0.0f,//-90.0f, 
                    float _pitch = 0.0f);//5.0f);
        virtual ~FPSCamera();
        Matrix4& getViewMatrix();
        void update();
        Matrix4& lookAt(Vector3 eye, Vector3 center, Vector3 up);
        virtual void setViewMatrix(const Matrix4& viewMatrix);
        virtual void setProjectionMatrix(const Matrix4& projectionMatrix);
        virtual void setGimbleLock(bool _gimbleLock);
        virtual bool getGimbleLock();
        virtual void setMousePosition(const Vector2& _mousePosition);
        const Vector3& getPosition() const;
        void eulerRotation();
        void matrixRotation();
        void computeMouseMovement(GLfloat xoffset, GLfloat yoffset);
        void computeMouseScroll(GLfloat yoffset);
        void computeKeyboardInputs(Movement direction, GLfloat deltaTime);

};
#endif