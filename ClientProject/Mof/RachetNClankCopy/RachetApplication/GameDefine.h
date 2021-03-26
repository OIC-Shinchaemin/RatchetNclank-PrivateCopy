#ifndef MY_GAME_DEFINE_H
#define MY_GAME_DEFINE_H

#include <stdexcept>
#include <string>
#include <Mof.h>

#include "My/Core/Math.h"
#include "ResourceManager.h"


namespace my {
struct Transform {
    Mof::CVector3 position = math::vec3::kZero;
    Mof::CVector3 rotate = math::vec3::kZero;
    Mof::CVector3 scale = math::vec3::kOne;
};
using ResourceMgr = my::ResourceManager<
    std::shared_ptr<Mof::CTexture>,
    std::shared_ptr<Mof::CMeshContainer>
>;
}
#endif // !MY_GAME_DEFINE_H