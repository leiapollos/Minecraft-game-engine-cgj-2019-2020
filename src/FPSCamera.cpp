#include "FPSCamera.h"
#include "mathf.h"
#include "Quaternion.h"
FPSCamera::FPSCamera(GLuint _UBO_BP, 
                Vector3 _position,
                Vector3 _up, 
                float _yaw, 
                float _pitch) : ICamera(_UBO_BP) {
    
    movementSpeed = 9.00f;
    mouseSensitivity = 0.05f; 
    zoom = 3.0f;

    //position = _position;
    position = Vector3(-57.2633f, 10.0225f, 75.76f);
    //position = Vector3(1.0f, 1.0f, 1.0f);
    worldUp = _up;
    yaw = _yaw;
    pitch = _pitch;
    roll = 0.0f;
    //matrixRotation();
    
    //updateView();
}
FPSCamera::~FPSCamera(){}

void FPSCamera::updateView() {
    matrixRotation();
    //std::cout << position << "\n";
    /*std::cout << "------------------------------------" << "\n";
    std::cout << position << "\n";
    std::cout << yaw << "\n";
    std::cout << pitch << "\n";
    std::cout << "------------------------------------" << "\n";*/
    
    //eulerRotation();
}

void FPSCamera::setGimbleLock(bool _gimbleLock) {
    gimbleLock = _gimbleLock;
}

bool FPSCamera::getGimbleLock() {
    return gimbleLock;
}

void FPSCamera::matrixRotation() {
    Matrix4 matPitch = MatrixFactory::rotate(pitch, Vector3(1,0,0));
    Matrix4 matYaw = MatrixFactory::rotate(yaw, Vector3(0,1,0));
    //Matrix4 matRoll = MatrixFactory::rotate(roll, Vector3(0,0,1));
    Matrix4 rotate = /*matRoll * */matPitch * matYaw;
    Matrix4 translate = MatrixFactory::translate(position);
    vMatrix = rotate * translate; //* MatrixFactory::scale(Vector3(1.0f,1.0f,1.0f));
    front = -Vector3(vMatrix.get(2,0),vMatrix.get(2,1),vMatrix.get(2,2)).normalize();
    right = Vector3(vMatrix.get(0,0),vMatrix.get(0,1),vMatrix.get(0,2)).normalize();
    up = right.cross(front);
}

void FPSCamera::eulerRotation() {
    Vector3 _front = Vector3();
    _front.x=cosf(math::toRadians(pitch))*cosf(math::toRadians(yaw));
    _front.y=sinf(math::toRadians(pitch));
    _front.z=cosf(math::toRadians(pitch))*sinf  (math::toRadians(yaw));
    front = _front.normalize();
    right = front.cross(worldUp);
    up = right.cross(front);
}


void FPSCamera::setViewMatrix(const Matrix4& viewMatrix) {
	glBindBuffer(GL_UNIFORM_BUFFER, matricesVbo);
    #ifdef _WIN32
    #else
        glFinish();
    #endif 
 	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(viewMatrix.data), viewMatrix.data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void FPSCamera::update() {
    updateView();
    m_frustum.update(pMatrix*getViewMatrix());
    /*const float *pSource = (pMatrix*getViewMatrix()).data;
    std::cout << "--------------\n";
    for (int i = 0; i < 16; ++i){
        if ((i+1)%4 == 0)
            std::cout << pSource[i] << "\n";
        else
            std::cout << pSource[i] << " ";
    }
    std::cout << "\n--------------\n";*/
    //std::cout << position << "\n";
}

void FPSCamera::setProjectionMatrix(const Matrix4& projectionMatrix) {
    pMatrix = projectionMatrix;
	glBindBuffer(GL_UNIFORM_BUFFER, matricesVbo);	
    #ifdef _WIN32
    #else
    	glFinish();
    #endif 
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(projectionMatrix.data), sizeof(projectionMatrix.data), projectionMatrix.data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Matrix4& FPSCamera::getViewMatrix() {
    //return vMatrix;
    return lookAt(position, position+front, up);
}

Matrix4& FPSCamera::lookAt(Vector3 eye, Vector3 center, Vector3 up) {
    Vector3 view = center - eye;
    Vector3 v = view.normalize();
    Vector3 side = v.cross(up);
    Vector3 s = side.normalize();
    Vector3 u = s.cross(v);

    vMatrix = Matrix4(s.x, s.y, s.z, -s.dot(eye),
                      u.x, u.y, u.z, -u.dot(eye),
                     -v.x,-v.y, -v.z, v.dot(eye),
                      0, 0, 0 ,1);
    return vMatrix;//MatrixFactory::;//vMatrix;
}

void FPSCamera::setMousePosition(const Vector2& _mousePosition) {
    mousePosition = _mousePosition;
}

void FPSCamera::computeKeyboardInputs(Movement direction, GLfloat deltaTime) {
    GLfloat velocity = this->movementSpeed * deltaTime;

    if (direction == FORWARD)
        this->position += front * velocity;
    if (direction == BACKWARD)
        this->position -= front * velocity;
    if (direction == LEFT)
        this->position -= right * velocity;
    if (direction == RIGHT)
        this->position += right * velocity;
    //updateView();
    /*vMatrix = getViewMatrix();
    front = -Vector3(vMatrix.get(2,0),vMatrix.get(2,1),vMatrix.get(2,2)).normalize();
    right = Vector3(vMatrix.get(0,0),vMatrix.get(0,1),vMatrix.get(0,2)).normalize();
    up = right.cross(front);*/


}

void FPSCamera::computeMouseMovement(GLfloat xoffset, GLfloat yoffset){
    Vector2 mouse_delta = Vector2(xoffset,yoffset) - mousePosition;

    pitch = std::fmod(pitch + mouseSensitivity * mouse_delta.y, (GLfloat)360.0f);
    yaw = std::fmod(yaw + mouseSensitivity * mouse_delta.x, (GLfloat)360.0f);
    //roll = std::fmod(roll + mouseSensitivity * mouse_delta.x, (GLfloat)360.0f);
    //yaw += mouseSensitivity * mouse_delta.x;
    //pitch += mouseSensitivity * mouse_delta.y;
    mousePosition = Vector2(xoffset, yoffset);
    
    /* Gimbal lock (only on euler rotation) */
    /*if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;*/
    


    //updateView();
}
const Vector3& FPSCamera::getPosition() const {
    return position;
}

void FPSCamera::computeMouseScroll(GLfloat yoffset) {
    if (this->zoom >= 1.0f && this->zoom <= 45.0f)
        this->zoom -= yoffset;
    if (this->zoom <= 1.0f)
        this->zoom = 1.0f;
    if (this->zoom >= 45.0f)
        this->zoom = 45.0f;
    //updateCameraVectors()
}