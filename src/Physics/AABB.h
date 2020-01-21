#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED
#include "../vector3.h"
#include "../matrix4.h"

struct AABB {
    AABB(const Vector3& dim)
        : m_dimensions(dim) {
    }

    void update(const Vector3& position) {
        m_min = position;
        m_max = m_min + m_dimensions;
    }

    bool isCollidingWith(const AABB& other) noexcept {
        return  (m_min.x <= other.m_max.x && m_max.x >= m_min.x) &&
            (m_min.y <= other.m_max.y && m_max.y >= m_min.y) &&
            (m_min.z <= other.m_max.z && m_max.z >= m_min.z);
    }

    Vector3 getVN(const Vector3& normal) const {
        Vector3 res = m_min;

        if (normal.x < 0) {
            res.x += m_dimensions.x;
        }
        if (normal.y < 0) {
            res.y += m_dimensions.y;
        }
        if (normal.z < 0) {
            res.z += m_dimensions.z;
        }

        return res;
    }

    Vector3 getVP(const Vector3& normal) const {
        Vector3 res = m_min;

        if (normal.x > 0) {
            res.x += m_dimensions.x;
        }
        if (normal.y > 0) {
            res.y += m_dimensions.y;
        }
        if (normal.z > 0) {
            res.z += m_dimensions.z;
        }

        return res;
    }
    const Vector3& getDimensions() const noexcept { return m_dimensions; }

    private:
        Vector3 m_min;
        Vector3 m_max;
        Vector3 m_dimensions;
};

#endif // AABB_H_INCLUDED