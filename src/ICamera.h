#ifndef ICAMERA_H
#define ICAMERA_H
#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "matrix4.h"
#include "Frustum.h"


class ICamera {
    public:
        enum Movement {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

        enum WheelMovement {
            MOUSE_SCROLL_UP = 3,
            MOUSE_SCROLL_DOWN = 4
        };
        GLuint UBO_BP;
        GLuint matricesVbo;
        Matrix4 vMatrix;
        Matrix4 pMatrix;
        Vector2 mousePosition;
        ViewFrustum m_frustum;
        bool gimbleLock;
        bool initiation = false;
        ICamera(GLuint _UBO_BP);
        virtual ~ICamera();

        virtual Matrix4& getViewMatrix() = 0;
        virtual void setViewMatrix(const Matrix4& viewMatrix) = 0;
        virtual void setProjectionMatrix(const Matrix4& projectionMatrix) = 0;
        virtual void setGimbleLock(bool gimbleLock) = 0;
        virtual void setMousePosition(const Vector2& mousePosition) = 0;
        virtual bool getGimbleLock() = 0;
        virtual void computeKeyboardInputs(Movement direction, GLfloat deltaTime) = 0;
        virtual void computeMouseMovement(GLfloat xoffset, GLfloat yoffset) = 0;
        virtual void computeMouseScroll(GLfloat yoffset) = 0;
        virtual void update() = 0;
        virtual const Vector3& getPosition() const = 0;
        const ViewFrustum& getFrustum() const;
};
#endif