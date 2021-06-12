#include "UpdateComponent.h"


ratchet::component::UpdateComponent::UpdateComponent(int priority) :
    super(priority) {
}

ratchet::component::UpdateComponent::UpdateComponent(const UpdateComponent& obj) :
    super(obj) {
}

ratchet::component::UpdateComponent::~UpdateComponent() {
}

void ratchet::component::UpdateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

bool ratchet::component::UpdateComponent::IsUpdate(void) const {
    return true;
}

bool ratchet::component::UpdateComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::component::UpdateComponent::Update(float delta_time) {
    return true;
}

bool ratchet::component::UpdateComponent::Release(void) {
    super::Release();
    return true;
}