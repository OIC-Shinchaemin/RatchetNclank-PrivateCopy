#include "LightManager.h"

#include "Base/Core/Math.h"
#include "Base/Core/Define.h"


ratchet::light::LightManager::LightManager() :
    _simple_light(),
    _light_pillars(),
    _pillar_shader(std::make_shared<Mof::CShader>()),
    _pillar_bind(std::make_shared<Mof::CShaderBind_3DPrimitiveBase>()) {
}

ratchet::light::LightManager::~LightManager() {
}

std::weak_ptr<ratchet::light::LightPillar> ratchet::light::LightManager::CreateLightPillar(const ratchet::light::LightPillarCreateInfo& info) {
    auto ptr = std::make_shared<ratchet::light::LightPillar>();
    
    ptr->SetShader(_pillar_primitive_shader);
    ptr->SetPosition(info.position);
    
    _light_pillars.push_back(ptr);
    return ptr;
}

bool ratchet::light::LightManager::Initialize(void) {

    _pillar_primitive_shader = std::make_shared<light::Shader3DPrimitive>();
    _pillar_shader->Load("../Resource/shader/light_pillar.hlsl");
    _pillar_bind->Create(_pillar_shader.get());
    _pillar_bind->CreateShaderBuffer("cbLightPillarParam", sizeof(light::cbLightPillarParam));
    _pillar_primitive_shader->shader = _pillar_shader;
    _pillar_primitive_shader->bind = _pillar_bind;

    auto dir = Mof::CVector3(1.0f, -1.0f, -1.0f);
    _simple_light.SetDirection(dir);
    _simple_light.SetDiffuse(def::color_rgba::kWhite);
    _simple_light.SetAmbient(def::color_rgba::kWhite * 0.8f);
    ::CGraphicsUtilities::SetDirectionalLight(&_simple_light);
    
    return true;
}

bool ratchet::light::LightManager::Render(void) {
    for (auto ptr : _light_pillars) {
        if (!ptr->Render()) {
            _light_pillars_delete_list.push_back(ptr);
        } // if
    } // for
    for (auto ptr : _light_pillars_delete_list) {
        ut::EraseRemove(_light_pillars, ptr);
    } // for
    _light_pillars_delete_list.clear();
    return true;
}

bool ratchet::light::LightManager::Release(void) {
    _light_pillars.clear();
    if (_pillar_bind) {
        _pillar_bind->Release();
    } // if
    if (_pillar_shader) {
        _pillar_shader->Release();
    } // if
    return true;
}