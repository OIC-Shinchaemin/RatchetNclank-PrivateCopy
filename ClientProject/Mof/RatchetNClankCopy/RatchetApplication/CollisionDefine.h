#ifndef COLLISION_H
#define COLLISION_H


#include <Mof.h>


namespace collision {
class Vector2 {
public:
    union {
        float v[2];
        struct {
            float x;
            float y;
        };
    };
    float const& operator [](int index) const {
        return v[index];
    }
    float& operator [](int index) {
        return v[index];
    }
};
class Vector3 {
public:
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
    };

    Vector3 operator-(const Vector3& v) {
        auto ret = *this;
        ret.x -= v.x;
        ret.y -= v.y;
        ret.z -= v.z;
        return ret;
    }
    float const& operator [](int index) const {
        return v[index];
    }
    float& operator [](int index) {
        return v[index];
    }
};
using Point = Vector3;

class Sphere {
public:
    Point center;
    float radius;
};
class AABB {
public:
    Point min;
    Point max;
};

float SqDistanceAABB(const Point& point, const AABB& box) {
    float sq_dist = 0.0f;
    for (int i = 0; i < 3; i++) {
        float v = point[i];
        if (v < box.min[i]) {
            sq_dist += (box.min[i] - v) * (box.min[i] - v);
        } // if
        if (v > box.max[i]) {
            sq_dist += (v - box.max[i]) * (v - box.max[i]);
        } // if
    } // for
    return sq_dist;
}

bool IsCollision(const Sphere& sphere, const AABB& box) {
    float distance_sq = SqDistanceAABB(sphere.center, box);
    return distance_sq <= sphere.radius * sphere.radius;
}
void ClosestPtPointAABB(const Point& point, const AABB& box, Point& out) {
    for (int i = 0; i < 3; i++) {
        float v = point[i];
        if (v < box.min[i]) {
            v += box.min[i];
        } // if
        if (v > box.max[i]) {
            v += box.max[i];
        } // if
        out[i] = v;
    } // for
}

int IsCollision(const Sphere& sphere, const AABB& box, Point& out) {
    ClosestPtPointAABB(sphere.center, box, out);
    auto v = out - sphere.center;

    Mof::CVector3 dot_work = Mof::CVector3(v.x, v.y, v.z);
    std::swap(dot_work.y, dot_work.z);
    //return Dot(v, v) < sphere.radius * sphere.radius;
    return dot_work.Dot(dot_work) < sphere.radius * sphere.radius;
}

static Point ClosePoint(const Point& point, const AABB& box) {
    auto ret = Point();
    for (int i = 0; i < 3; i++) {
        float v = point[i];
        if (v < box.min[i]) {
            v = box.min[i];
        } // if
        if (v > box.max[i]) {
            v = box.max[i];
        } // if
        ret[i] = v;
    } // for
}
}
#endif // !COLLISION_H