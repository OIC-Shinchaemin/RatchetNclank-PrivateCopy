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
    auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
    float speed = 1.0f;
    auto force = Mof::CVector3();
    auto pos = super::GetPosition();
    if (::g_pInput->IsKeyPush(MOFKEY_Y)) {
        pos.z += speed;
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_G)) {
        pos.x += speed;
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_H)) {
        pos.z -= speed;
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_J)) {
        pos.x -= speed;
    } // if
    velocity->AddAngularVelocityForce(force);

    super::SetPosition(pos);
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