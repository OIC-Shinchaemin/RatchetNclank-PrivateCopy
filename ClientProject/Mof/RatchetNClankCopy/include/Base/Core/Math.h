#ifndef BASE_CORE_MATH_H
#define BASE_CORE_MATH_H


#include <Mof.h>


namespace math {
constexpr float ƒÎ = 3.141529f;
constexpr float kPi = ƒÎ;
constexpr float kHalfPi = math::kPi / 2.0f;
constexpr float kTwoPi = math::kPi * 2.0f;
constexpr float kNearZero = 0.01f;


namespace vec3 {
static const Mof::CVector3 kZero = Mof::CVector3(0.0f, 0.0f, 0.0f);
static const Mof::CVector3 kUnitX = Mof::CVector3(1.0f, 0.0f, 0.0f);
static const Mof::CVector3 kUnitY = Mof::CVector3(0.0f, 1.0f, 0.0f);
static const Mof::CVector3 kUnitZ = Mof::CVector3(0.0f, 0.0f, 1.0f);
static const Mof::CVector3 kOne = Mof::CVector3(1.0f, 1.0f, 1.0f);
static const Mof::CVector3 kNegUnitX = Mof::CVector3(-1.0f, 0.0f, 0.0f);
static const Mof::CVector3 kNegUnitY = Mof::CVector3(0.0f, -1.0f, 0.0f);
static const Mof::CVector3 kNegUnitZ = Mof::CVector3(0.0f, 0.0f, -1.0f);
}
namespace vec4 {
static const Mof::CVector4 kZero = Mof::CVector4(0.0f, 0.0f, 0.0f, 0.0f);
static const Mof::CVector4 kOne = Mof::CVector4(1.0f, 1.0f, 1.0f, 1.0f);
}

constexpr float ToRadian(float degree) {
    return degree * (math::kPi / 180.0f);
}
constexpr float ToDegree(float radian) {
    return radian * (180.0f / math::kPi);
}
static Mof::CVector2 Rotate(float x, float y, float theta) {
    float temp_x = (x)*std::cosf(theta) - (y)*std::sinf(theta);
    float temp_y = (x)*std::sinf(theta) + (y)*std::cosf(theta);

    return Mof::CVector2(temp_x, temp_y);
};
static Mof::CVector3 SphericalToCartesian(float distance, float azimuth, float altitude) {
    float x = distance * std::cosf(azimuth) * std::sinf(altitude - math::kHalfPi);
    float y = distance * std::sinf(azimuth) * std::sinf(altitude - math::kHalfPi);
    float z = distance * std::cosf(altitude - math::kHalfPi);
    return Mof::CVector3(x, z, -y);
}

static Mof::CVector3 SphericalToCartesian(Mof::CVector3 spherical) {
    return math::SphericalToCartesian(spherical.x, spherical.y, spherical.z);
}
class Radian {
    float _degree;
public:
    Radian() :
        _degree(0.0f) {
    }
    math::Radian(float degree) :
        _degree(degree) {
    }
    float operator +(const float& radian) {
        return math::ToRadian(_degree) + radian;
    }
    float operator -(const float& radian) {
        return math::ToRadian(_degree) - radian;
    }
    float operator ()(void) const {
        return math::ToRadian(_degree);
    }
    bool operator <= (const float& degree) {
        return this->_degree <= degree;
    }
    bool operator >= (const float& degree) {
        return this->_degree >= degree;
    }
    math::Radian& operator+=(const math::Radian& obj) {
        this->_degree += obj._degree;
        return *this;
    }
};
}
#endif // !RATCHET_MATH_H