#include "Quaternion.h"
#include "mathf.h"


Quaternion::Quaternion(float _t, float _x, float _y, float _z) {
    t = _t;
    x = _x;
    y = _y;
    z = _z;
}

Quaternion::Quaternion(float theta, Vector4 _axis) {
    Vector4 axis = _axis.normalize();
    
    float a = math::toRadians(theta);
    t = cosf(a / 2.0f);
    float s = sinf(a / 2.0f);
    x = axis.x * s;
    y = axis.y * s;
    z = axis.z * s;
    clean();
    //normalize();
    //float s = 1 / norm();
    *this = normalize();
}

Quaternion::~Quaternion() {}

Quaternion& Quaternion::operator=(const Quaternion& q) {
    t = q.t;
    x = q.x;
    y = q.y;
    z = q.z;
    return *this;
}

// OPERATORS
Quaternion Quaternion::operator+ (const Quaternion& q)  {
    return Quaternion(t + q.t,
                      x + q.x,
                      y + q.y,
                      z + q.z);
}

Quaternion Quaternion::operator- (const Quaternion& q) {
    return Quaternion(t - q.t,
                      x - q.x,
                      y - q.y,
                      z - q.z);
}

Quaternion Quaternion::operator* (float k) const {
    return Quaternion(t * k,
                      x * k,
                      y * k,
                      z * k);
}

const Quaternion operator* (float k, const Quaternion &q) {
    return Quaternion(q.t * k,
                      q.x * k,
                      q.y * k,
                      q.z * k);
}

Quaternion Quaternion::operator* (const Quaternion& q) const {    
    return Quaternion(t * q.t - x * q.x - y * q.y - z * q.z,
                      t * q.x + x * q.t + y * q.z - z * q.y,
                      t * q.y + y * q.t + z * q.x - x * q.z,
                      t * q.z + z * q.t + x * q.y - y * q.x);
}

bool Quaternion::operator== (const Quaternion& q) const {
    return (fabs(t - q.t) < qThreshold &&
            fabs(x - q.x) < qThreshold &&
            fabs(y - q.y) < qThreshold &&
            fabs(z - q.z) < qThreshold);
}
//

void Quaternion::toAngleAxis(float& theta, Vector4& axis) {
    *this = normalize();
    Quaternion qn = *this;

    theta = math::toDegrees(2.0f * acosf(qn.t));//2.0f * acos(qn.t) * (float)RADIANS_TO_DEGREES;
    float s = sqrtf(1.0f - qn.t*qn.t);
    if (s < qThreshold) {
        axis.x = 1.0f;
        axis.y = 0.0f;
        axis.z = 0.0f;
        axis.w = 1.0f;
    }
    else {
        axis.x = qn.x / s;
        axis.y = qn.y / s;
        axis.z = qn.z / s;
        axis.w = 1.0f;
    }
}

Quaternion Quaternion::conjugate() {
    return Quaternion(t, -x, -y, -z);
}

Quaternion Quaternion::inverse() { return conjugate() * (1.0f / quadrance()); }

float Quaternion::quadrance() {
    return t*t + x*x + y*y + z*z;
}

float Quaternion::norm() {
    return sqrtf(quadrance());
}

Quaternion Quaternion::normalize() {
    float s = 1 / norm();
    return *this * s;
}

Matrix4 Quaternion::toMatrix() {
    Matrix4 m4 = Matrix4();
    Quaternion q = normalize();

    float xx = q.x * q.x;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float xt = q.x * q.t;
    float yy = q.y * q.y;
    float yz = q.y * q.z;
    float yt = q.y * q.t;
    float zz = q.z * q.z;
    float zt = q.z * q.t;

    m4.data[0] = 1.0f - 2.0f * ( yy + zz );
    m4.data[1] = 2.0f * ( xy + zt );
    m4.data[2] = 2.0f * ( xz - yt );
    m4.data[3] = 0.0f;

    m4.data[4] = 2.0f * ( xy - zt );
    m4.data[5] = 1.0f - 2.0f * ( xx + zz );
    m4.data[6] = 2.0f * ( yz + xt );
    m4.data[7] = 0.0f;

    m4.data[8] = 2.0f * ( xz + yt );
    m4.data[9] = 2.0f * ( yz - xt );
    m4.data[10] = 1.0f - 2.0f * ( xx + yy );
    m4.data[11] = 0.0f;

    m4.data[12] = 0.0f;
    m4.data[13] = 0.0f;
    m4.data[14] = 0.0f;
    m4.data[15] = 1.0f;

    m4.clean();
    return m4;
}

Quaternion lerp(const Quaternion& q0, const Quaternion& q1, float k) {
    float cos_angle = q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t;
    float k0 = 1.0f - k;
    float k1 = (cos_angle > 0) ? k : -k;
    Quaternion qi = (q0 * k0) + (q1 * k1);
    return qi.normalize();
}

Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float k){
    float angle = acosf(q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t);
    float k0 = sinf((1-k)*angle) / sinf(angle);
    float k1 = sinf(k*angle) / sinf(angle);
    Quaternion qi = (q0 * k0) + (q1 * k1);
    return qi.normalize();
}


std::ostream& operator << (std::ostream& os, const Quaternion& q) {
    os << "(" << q.t << ", " << q.x << ", " << q.y << ", " << q.z << ")";
    return os;
}

void Quaternion::clean() {
    if(fabs(t) < qThreshold)
        t = 0.0f;
    if(fabs(x) < qThreshold)
        x = 0.0f;
    if(fabs(y) < qThreshold)
        y = 0.0f;
    if(fabs(z) < qThreshold)
        z = 0.0f;
}