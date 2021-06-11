#include "LightManager.h"

#include "Base/Core/Math.h"
#include "Base/Core/Define.h"


rachet::LightManager::LightManager() :
    _simple_light() {
}

rachet::LightManager::~LightManager() {
}

bool rachet::LightManager::Initialize(void) {
    _simple_light.SetDirection(-math::vec3::kOne);
    _simple_light.SetDiffuse(def::color_rgba::kWhite);
    _simple_light.SetAmbient(def::color_rgba::kWhite * 0.8f);
    ::CGraphicsUtilities::SetDirectionalLight(&_simple_light);
    return true;
}