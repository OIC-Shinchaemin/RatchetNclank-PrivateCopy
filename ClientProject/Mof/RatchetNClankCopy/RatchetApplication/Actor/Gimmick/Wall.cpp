#include "Wall.h"

#include "../../Component/TransformComponent.h"
#include "../../Component/VelocityComponent.h"


ratchet::actor::gimmick::Wall::Wall() :
    super() {
}

ratchet::actor::gimmick::Wall::~Wall() {
}

#include "../../DebugManager.h"
bool ratchet::actor::gimmick::Wall::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);

    debug::DebugManager::GetInstance().ChangeDebugMode();
    auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
    velocity->SetUseGravity(false);
    return true;
}

bool ratchet::actor::gimmick::Wall::Update(float delta_time) {
    super::Update(delta_time);

    if (super::GetName() == "wall_1") {
        return true;
    } // if
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

bool ratchet::actor::gimmick::Wall::Release(void) {
    super::Release();
    return true;
}