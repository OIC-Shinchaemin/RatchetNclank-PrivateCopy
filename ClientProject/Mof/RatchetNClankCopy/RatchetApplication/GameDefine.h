#ifndef RATCHET_GAME_DEFINE_H
#define RATCHET_GAME_DEFINE_H


#include <stdexcept>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include <Mof.h>

#include "Base/Core/Math.h"
#include "MotionNames.h"
#include "ResourceManager.h"
//#include "MessageObservationManager.h"
#include "Base/Accessor/Setter.h"
#include "Base/Accessor/Getter.h"
#include "Base/Accessor/Accessor.h"
#include "Base/Core/FunctionPointerContainer.h"
#include "Base/Resource/ResourceFont.h"
#include "Base/UI/UICanvas.h"
#include "DebugManager.h"
#include "Game/Audio/SoundPlayer.h"
#include "Game/Audio/BGMPlayer.h"
#include "Game/Audio/SEPlayer.h"


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
constexpr int kTextWidth = 12;
constexpr int kWindowWidth = 1920;
//constexpr int kWindowWidth = 1024;
constexpr int kWindowHiehgt = 1080;
//constexpr int kWindowHiehgt = 768;
///static debug::DebugManager g_DebugManager;

struct Transform {
    Mof::CVector3 position = math::vec3::kZero;
    Mof::CVector3 rotate = math::vec3::kZero;
    Mof::CVector3 scale = math::vec3::kOne;
};
/*
struct Tag {
    std::string tag;
};
*/
using Tag = std::string;
struct TagHolder {
    std::vector<Tag> tags;
    /*
    bool Contain(Tag& tag) const {
        auto it = std::find_if(tags.begin(), tags.end(), [&](Tag& elem) {
            return elem.tag == tag.tag;
        });
        if (it != tags.end()) {
            return true;
        } // if
        return false;
    }
    */
};

using ResourceMgr = ratchet::ResourceManager<
    std::shared_ptr<Mof::CTexture>,
    std::shared_ptr<Mof::CMeshContainer>,
    std::shared_ptr<ratchet::MotionNames>,
    std::shared_ptr<sip::CResourceFont>,
    std::shared_ptr<Mof::CStreamingSoundBuffer>,
    std::shared_ptr<Mof::CSoundBuffer>
>;
//using ObservationMgr = ratchet::ObservationManager<
//    ratchet::game::gamesystem::text::TextSystemOpenObservation,
//    ratchet::game::gamesystem::text::TextSystemClosedObservation
//>;


using GameBGMPlayer = ratchet::game::audio::BGMPlayer;
using GameSEPlayer = ratchet::game::audio::SEPlayer;
//using GameBGMPlayer = ratchet::game::audio::SoundPlayer<ratchet::game::audio::BGMEvent, Mof::CStreamingSoundBuffer>;
//using GameSEPlayer = ratchet::game::audio::SoundPlayer<ratchet::game::audio::SEEvent, Mof::CSoundBuffer>;


struct cbUVScrollParam {
    Mof::Vector4 value;
    cbUVScrollParam& operator+=(Mof::CVector2 scroll) {
        value.x += scroll.x;
        value.y += scroll.y;
        return *this;
    }
};
struct cbSceneEffectParam {
    Mof::Vector4 value;
    cbSceneEffectParam& operator+=(float time) {
        value.x += time;
        return *this;
    }
};
}
#endif // !RATCHET_GAME_DEFINE_H