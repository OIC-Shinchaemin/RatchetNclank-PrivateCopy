#ifndef MY_MATH_H
#define MY_MATH_H


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
#endif // !MY_MATH_H