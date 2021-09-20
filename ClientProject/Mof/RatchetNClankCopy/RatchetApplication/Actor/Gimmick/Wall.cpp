#include "Wall.h"

#include "../../Event/EventReferenceTable.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/VelocityComponent.h"


ratchet::actor::gimmick::Wall::Wall() :
    super() {
}

ratchet::actor::gimmick::Wall::~Wall() {
}

void ratchet::actor::gimmick::Wall::End(void) {
    super::End();
    ratchet::event::EventReferenceTable::Singleton().Dispose(super::GetName());

}

bool ratchet::actor::gimmick::Wall::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);

    debug::DebugManager::GetInstance().ChangeDebugMode();
    auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
    velocity->SetUseGravity(false);
    return true;
}

bool ratchet::actor::gimmick::Wall::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::actor::gimmick::Wall::Release(void) {
    super::Release();
    return true;
}