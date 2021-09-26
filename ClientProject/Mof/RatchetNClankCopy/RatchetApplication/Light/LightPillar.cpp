#include "LightPillar.h"


ratchet::light::LightPillar::LightPillar() :
    _enable(true),
    _position(),
    _pillar_slice(256),
    _pillar_radius(1.5f),
    _pillar_height(200.0f),
    _geometry(::CGraphicsUtilities::CreateCapsuleGeometry(_pillar_radius, _pillar_height, _pillar_slice,
                                                        _pillar_slice, Mof::CVector3())) {
}

ratchet::light::LightPillar::~LightPillar() {
    delete _geometry;
    _geometry = nullptr;
}

void ratchet::light::LightPillar::SetPosition(const Mof::CVector3& value) {
    this->_position = value;
}

void ratchet::light::LightPillar::SetShader(const std::shared_ptr<ratchet::light::Shader3DPrimitive>& ptr) {
    this->_primitive_shader = ptr;
}

bool ratchet::light::LightPillar::Disable(void) {
    _enable = false;
    return true;
}

bool ratchet::light::LightPillar::Render(void) {
    if (!_enable) {
        return false;
    } // if

    if (auto s = _primitive_shader.lock()) {
        auto shader = s->GetShader();
        auto bind = s->GetBind();

        bind->SetCamera(::CGraphicsUtilities::GetCamera());
        auto shader_buffer = cbLightPillarParam();
        shader_buffer.cblgPosition = Mof::CVector3(0.0f, 5.0f, 1.0f);
        shader_buffer.cblgDiffuse = Mof::CVector4(1.0f, 1.0f, 1.0f, 1.0f);
        shader_buffer.cblgAttenuation = Mof::CVector4(0.0f, 0.1f, 0.05f, 0.0f);

        bind->GetShaderBuffer(0)->SetBuffer(&shader_buffer);

        // •`‰æ
        CMatrix44 matWorld;
        matWorld.Translation(_position);
        _geometry->Render(matWorld, shader.get(), bind.get());
    } // if
    return true;
}

bool ratchet::light::LightPillar::Release(void) {
    return true;
}