#include "LightManager.h"

#include "Base/Core/Math.h"
#include "Base/Core/Define.h"


ratchet::light::LightManager::LightManager() :
    _simple_light() {
}

ratchet::light::LightManager::~LightManager() {
}

bool ratchet::light::LightManager::Initialize(void) {
    auto dir = Mof::CVector3(1.0f, -1.0f, -1.0f);
    _simple_light.SetDirection(dir);
    _simple_light.SetDiffuse(def::color_rgba::kWhite);
    _simple_light.SetAmbient(def::color_rgba::kWhite * 0.8f);
    ::CGraphicsUtilities::SetDirectionalLight(&_simple_light);
    return true;
}