#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <array>

#include "Physics/AABB.h"

struct Plane {
    float distanceToPoint(const Vector3& point) const;

    float distanceToOrigin;
    Vector3 normal;
};

class ViewFrustum {
  public:
    void update(const Matrix4& projViewMatrix) noexcept;

    bool isBoxInFrustum(const AABB& box) const noexcept;

  private:
    std::array<Plane, 6> m_planes;
};

#endif // FRUSTUM_H_INCLUDED