#include "Fence.h"

#include "../../Component/TransformComponent.h"
#include "../../Component/VelocityComponent.h"


ratchet::actor::gimmick::Fence::Fence() :
    super(),
    _mesh(){
    _mesh.Load("../Resource/mesh/fence/fence.mom");
}

ratchet::actor::gimmick::Fence::~Fence() {
    _mesh.Release();
}

bool ratchet::actor::gimmick::Fence::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);

    auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
    velocity->SetUseGravity(false);
    return true;
}

bool ratchet::actor::gimmick::Fence::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::actor::gimmick::Fence::Render(void) {
    super::Render();
    
    Mof::CMatrix44 scale, rotate, translate;
    Mof::CQuaternion quat; quat.Rotation(super::GetRotate());

    scale.Scaling(super::GetScale(), scale);
    quat.ConvertMatrixTranspose(rotate);
    translate.Translation(super::GetPosition(), translate);

    Mof::CMatrix44 world = scale * rotate * translate;
    _mesh.Render(world);
    return true;
}