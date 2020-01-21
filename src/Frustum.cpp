#include "Frustum.h"

enum Planes {
    Near,
    Far,
    Left,
    Right,
    Top,
    Bottom,
};

float Plane::distanceToPoint(const Vector3& point) const {
    return point.dot(normal) + distanceToOrigin;
}

void ViewFrustum::update(const Matrix4& mat) noexcept {
    // left
    m_planes[Planes::Left].normal.x = mat.data[12] + mat.data[0];
    m_planes[Planes::Left].normal.y = mat.data[13] + mat.data[1];
    m_planes[Planes::Left].normal.z = mat.data[14] + mat.data[2];
    m_planes[Planes::Left].distanceToOrigin = mat.data[15] + mat.data[3];

    // right
    m_planes[Planes::Right].normal.x = mat.data[12] - mat.data[0];
    m_planes[Planes::Right].normal.y = mat.data[13] - mat.data[1];
    m_planes[Planes::Right].normal.z = mat.data[14] - mat.data[2];
    m_planes[Planes::Right].distanceToOrigin = mat.data[15] - mat.data[3];

    // bottom
    m_planes[Planes::Bottom].normal.x = mat.data[12] + mat.data[4];
    m_planes[Planes::Bottom].normal.y = mat.data[13] + mat.data[5];
    m_planes[Planes::Bottom].normal.z = mat.data[14] + mat.data[6];
    m_planes[Planes::Bottom].distanceToOrigin = mat.data[15] + mat.data[7];

    // top
    m_planes[Planes::Top].normal.x = mat.data[12] - mat.data[4];
    m_planes[Planes::Top].normal.y = mat.data[13] - mat.data[5];
    m_planes[Planes::Top].normal.z = mat.data[14] - mat.data[6];
    m_planes[Planes::Top].distanceToOrigin = mat.data[15] - mat.data[7];

    // near
    m_planes[Planes::Near].normal.x = mat.data[12] + mat.data[8];
    m_planes[Planes::Near].normal.y = mat.data[13] + mat.data[9];
    m_planes[Planes::Near].normal.z = mat.data[14] + mat.data[10];
    m_planes[Planes::Near].distanceToOrigin = mat.data[15] + mat.data[11];

    // far
    m_planes[Planes::Far].normal.x = mat.data[12] - mat.data[8];
    m_planes[Planes::Far].normal.y = mat.data[13] - mat.data[9];
    m_planes[Planes::Far].normal.z = mat.data[14] - mat.data[10];
    m_planes[Planes::Far].distanceToOrigin = mat.data[15] - mat.data[11];

    for (auto &plane : m_planes) {
        float length = plane.normal.magnitude();
        plane.normal /= length;
        plane.distanceToOrigin /= length;
    }
}

bool ViewFrustum::isBoxInFrustum(const AABB& box) const noexcept {
    bool result = true;
    for (auto &plane : m_planes) {
        //std::cout << plane.normal << "\n";
        if (plane.distanceToPoint(box.getVP(plane.normal)) < 0) {
            return false;
        }
        else if (plane.distanceToPoint(box.getVN(plane.normal)) < 0) {
            result = true;
        }
    }
    //std::cout << "---------------------\n";
    return result;
}