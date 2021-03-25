#ifndef MY_TEST_DEFINE_H
#define MY_TEST_DEFINE_H

#include <stdexcept>
#include <string>
#include <Mof.h>

#include "My/Core/Math.h"


namespace my {
struct Transform {
    Mof::CVector3 position = math::vec3::kZero;
    Mof::CVector3 rotate = math::vec3::kZero;
    Mof::CVector3 scale = math::vec3::kOne;
};
}
#endif // !MY_TEST_DEFINE_H