#include "SphericalCamera.h"


SphericalCamera::SphericalCamera(GLuint _UBO_BP) : ICamera(_UBO_BP) {
    gimbleLock = true;
    translationMatrix = MatrixFactory::Create4DTranslation(0.0f,0.0f,-zoom);
    rotationQ = Quaternion(1.0f,0.0f,0.0f,0.0f);
    //vMatrix = lookAt(Vector3(0,0,5), Vector3(0,0,0), Vector3(0,1,0));
    mRotX = MatrixFactory::CONVERT_3D_TO_4D_MATRIX(MatrixFactory::Create3DXRotation(0));
    mRotY = MatrixFactory::CONVERT_3D_TO_4D_MATRIX(MatrixFactory::Create3DYRotation(0));
    
    rotation(0,0);
}

SphericalCamera::~SphericalCamera() {

}

Matrix4& SphericalCamera::lookAt(Vector3 eye, Vector3 center, Vector3 up) {
    Vector3 view = center - eye;
    Vector3 v = view.normalize();
    Vector3 side = v.cross(up);
    Vector3 s = side.normalize();
    Vector3 u = s.cross(v);

    vMatrix = Matrix4(s.x, s.y, s.z, -s.dot(eye),
                                 u.x, u.y, u.z, -u.dot(eye),
                                -v.x,-v.y, -v.z, v.dot(eye),
                                 0, 0, 0 ,1);

    return vMatrix;
}

void SphericalCamera::setViewMatrix(const Matrix4& viewMatrix) {
    glBindBuffer(GL_UNIFORM_BUFFER, matricesVbo);
    glFinish();
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(viewMatrix.data), viewMatrix.data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SphericalCamera::setProjectionMatrix(const Matrix4& projectionMatrix) {
    glBindBuffer(GL_UNIFORM_BUFFER, matricesVbo);   
    glFinish();
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(projectionMatrix.data), sizeof(projectionMatrix.data), projectionMatrix.data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Matrix4& SphericalCamera::getViewMatrix() {
    //vMatrix = translationMatrix;

    return vMatrix; 
}

void SphericalCamera::computeKeyboardInputs(Movement direction, GLfloat deltaTime) {
    /*GLfloat velocity = this->movementSpeed * deltaTime;

    if (direction == FORWARD)
        this->position += front * velocity;
    if (direction == BACKWARD)
        this->position -= front * velocity;
    if (direction == LEFT)
        this->position -= right * velocity;
    if (direction == RIGHT)
        this->position += right * velocity;*/


}
void SphericalCamera::updateView() {
    translationMatrix = MatrixFactory::Create4DTranslation(0.0f,0.0f,-zoom);
    if (gimbleLock) {
        std::cout << "EULER\n";
        vMatrix = translationMatrix * rotationMatrix;
    }
    else {
        std::cout << "QUATERNION\n";
        vMatrix = translationMatrix * rotationQ.toMatrix();
    }
}

void SphericalCamera::setGimbleLock(bool _gimbleLock) {
    gimbleLock = _gimbleLock;
}

bool SphericalCamera::getGimbleLock() {
    return gimbleLock;
}


void SphericalCamera::rotation(float rotX, float rotY) {
    mRotX = MatrixFactory::CONVERT_3D_TO_4D_MATRIX(MatrixFactory::Create3DXRotation(rotX)) * mRotX;
    mRotY = MatrixFactory::CONVERT_3D_TO_4D_MATRIX(MatrixFactory::Create3DYRotation(rotY)) * mRotY;
    rotationMatrix = mRotX * mRotY;
    
    Quaternion rotationQtrnX = Quaternion(rotX,Vector4(1.0f,0.0f,0.0f,1.0f));
    Quaternion rotationQtrnY = Quaternion(rotY,Vector4(0.0f,1.0f,0.0f,1.0f));
    //Quaternion rotationQtrnZ = Quaternion(0,Vector4(0.0f,0.0f,1.0f,1.0f));
    rotationQ = (rotationQtrnX * rotationQtrnY).normalize() * rotationQ;
    

    updateView();
    lastX = mousePosition.x;
    lastY = mousePosition.y;
}
void SphericalCamera::update() {

}
void SphericalCamera::computeMouseMovement(GLfloat xoffset, GLfloat yoffset) {
    if (mousePosition.x != lastX || mousePosition.y != lastY) {
        float rotX = std::fmod(mousePosition.x - lastX * mouseSensitivity, (GLfloat) 360.0f);
        float rotY = std::fmod(mousePosition.y - lastY * mouseSensitivity, (GLfloat) 360.0f);
        rotation(rotY, rotX);
    }
}

void SphericalCamera::setMousePosition(const Vector2& _mousePosition) {
    lastX = _mousePosition.x;
    lastY = _mousePosition.y;
    mousePosition = _mousePosition;
}

void SphericalCamera::computeMouseScroll(GLfloat yoffset) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
    updateView();
}