#ifndef RATCHET_GAME_DEFINE_H
#define RATCHET_GAME_DEFINE_H


#include <stdexcept>
#include <memory>
#include <string>

#include <Mof.h>

#include "Base/Core/Math.h"
#include "MotionNames.h"
#include "ResourceManager.h"
#include "Base/Core/FunctionPointerContainer.h"
#include "Base/Resource/ResourceFont.h"
#include "Base/UI/UICanvas.h"
#include "Namespace.h"


#define DEBUG_PRINT(arg, ...)
#define TRACE
#if defined(_DEBUG)
#undef DEBUG_PRINT
#undef TRACE 
#define DEBUG_PRINT(arg, ...)\
{char str[256]; \
::sprintf_s(str, arg, __VA_ARGS__); \
::OutputDebugString(str);std::cout<<str;}
#define TRACE \
DEBUG_PRINT("%s %s %d \n", __FILE__, __func__, __LINE__);
#endif // defined (_DEBUG)


namespace ratchet {

constexpr int kTextWidth= 12;


struct Transform {
    Mof::CVector3 position = math::vec3::kZero;
    Mof::CVector3 rotate = math::vec3::kZero;
    Mof::CVector3 scale = math::vec3::kOne;
};
using ResourceMgr = ratchet::ResourceManager<
    std::shared_ptr<Mof::CTexture>,
    std::shared_ptr<Mof::CMeshContainer>,
    std::shared_ptr<ratchet::MotionNames>,
    std::shared_ptr<sip::CResourceFont>
>;

struct cbUVScrollParam {
    Mof::Vector4 value;
    cbUVScrollParam& operator+=(Mof::CVector2 scroll) {
        value.x += scroll.x;
        value.y += scroll.y;
        return *this;
    }
};
}
#endif // !RATCHET_GAME_DEFINE_H